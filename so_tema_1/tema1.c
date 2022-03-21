#include "util.h"
#include "structures.h"

#define NAME_LEN 256
#define LINE_LEN 256
#define BUFF_LEN 1000

static list d_list;
static hash_table *ht;

/*
 * Adds element to the hash table
 * For NULL in mapping it adds an empty string
 * Returns 1 on succes or 12 if malloc fails
 */
static int add_symbol(char *symbol, char *mapping)
{
	int ret;

	if (!mapping) {
		ret = add_entry(ht, symbol, "");
		if (ret != 1)
			return ret;
	} else {
		ret = add_entry(ht, symbol, mapping);
		if (ret != 1)
			return ret;
	}

	return 1;
}

/*
 * Parses arguments in command line
 * Checks arguments and based on that it either
 * adds an element to the hash table or a directory
 * to the list
 * It also sets input and output files
 */
static int parse_arguments(char **arguments, int argc, char *input_file,
	char *output_file)
{
	int ret;
	char *aux, *symbol, *mapping;
	int first_input = 0;
	int i;

	for (i = 1; i < argc; i++) {
		if (arguments[i][1] == 'D' && arguments[i][0] == '-'
			&& strlen(arguments[i]) > 2) {

			aux = my_strdup(&arguments[i][2]);
			if (!aux)
				return 12;

			symbol = strtok(aux, "=");
			mapping = strtok(NULL, "=");

			add_symbol(symbol, mapping);

			free(aux);
		} else if (strcmp(arguments[i], "-D") == 0) {

			aux = my_strdup(arguments[i + 1]);
			if (!aux)
				return 12;

			symbol = strtok(aux, "=");
			mapping = strtok(NULL, "=");

			add_symbol(symbol, mapping);

			free(aux);

			i++;
		} else if (strcmp(arguments[i], "-I") == 0) {

			ret = add_item(&d_list, arguments[i + 1]);
			if (ret == 12)
				return 12;

			i++;
		} else if (arguments[i][1] == 'I' && arguments[i][0] == '-'
			     && strlen(arguments[i]) > 2) {

			ret = add_item(&d_list, &arguments[i][2]);
			if (ret == 12)
				return 12;
		} else if (arguments[i][1] == 'o' && arguments[i][0] == '-'
			     && strlen(arguments[i]) > 2) {

			strcpy(output_file, &arguments[i][2]);
		} else if (strcmp(arguments[i], "-o") == 0) {
			strcpy(output_file, arguments[i + 1]);

			i++;
		} else {
			if (first_input == 0) {
				strcpy(input_file, arguments[i]);
				first_input++;
			} else if (first_input == 1) {
				strcpy(output_file, arguments[i]);
				first_input++;
			} else
				return -1;
		}
	}

	return 1;
}

/*Function taken from geeksforgeeks and modified */
static char *replaceWord(const char *s, const char *oldW, const char *newW)
{
	char *result;
	int i, cnt = 0;
	int newWlen = strlen(newW);
	int oldWlen = strlen(oldW);
	/* Variable to keep track of quotes in order to avoid bad replaces */
	int quoutes = 0;

	/* Counting the number of times old word occur in the string */
	for (i = 0; s[i] != '\0'; i++) {

		if ((s[i] == '\"' || s[i] == '\'') && quoutes == 0)
			quoutes = 1;
		else if ((s[i] == '\"' || s[i] == '\'') && quoutes == 1)
			quoutes = 0;

		if (strstr(&s[i], oldW) == &s[i] && quoutes == 0) {
			cnt++;

			/* Jumping to index after the old word. */
			i += oldWlen - 1;
		}
	}

	result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

	i = 0;
	quoutes = 0;
	while (*s) {
		if ((*s == '\"' || *s == '\'') && quoutes == 0)
			quoutes = 1;
		else if ((*s == '\"' || *s == '\'') && quoutes == 1)
			quoutes = 0;

		/* compare the substring with the result */
		if (strstr(s, oldW) == s && quoutes == 0) {
			strcpy(&result[i], newW);
			i += newWlen;
			s += oldWlen;
		} else
			result[i++] = *s++;
	}

	result[i] = '\0';
	return result;
}

/*
 *Searches for nested defines
 * Returns the final result or unchanged string
 */
static void define_define(char *s)
{
	char *res;
	char aux[LINE_LEN];

	strcpy(aux, s);

	res = get_value(ht, s);

	while (res != NULL) {
		strcpy(aux, res);
		res = get_value(ht, res);
	}

	strcpy(s, aux);
}

static void nested_define(char *s)
{
	char *new;
	char aux[LINE_LEN];
	int i;

	strcpy(aux, s);
	for (i = 0; i < ht->index; i++) {
		new = replaceWord(aux, ht->items[i].key, ht->items[i].value);

		strcpy(aux, new);
		free(new);
	}

	strcpy(s, aux);
}

/* Parses file to get the symbol and mapping */
static void get_symbol_and_mapping(char *s, char *symbol, char *mapping)
{
	int c = 0;
	int i;

	for (i = 8; s[i] != '\0'; i++) {
		if (s[i] == ' ') {
			s[i] = '\0';
			strcpy(symbol, s + 8);
			break;

		}
		c++;
	}

	strcpy(mapping, s + 9 + c);

}

/* Appends line to buffer and resizes it if there is not enough space */
static int append(char *buffer, char *to_append, int *size)
{
	if (strlen(buffer) + strlen(to_append) >= *size) {
		buffer = realloc(buffer, *size * 2);
		if (!buffer)
			return 12;
		*size = *size * 2;
	}

	strcat(buffer, to_append);
	return 1;
}

/* Appends file which should be included to the path of directory */
static void get_directory(char *path, char *aux)
{
	int len = strlen(path) - 1;
	int i;

	for (i = len; i > 0; i--) {
		if (path[i] == '/' || path[i] == '\\') {
			path[i + 1] = '\0';
			strcpy(aux, path);
			break;
		}
	}
}

static void delete_new_line(char *s)
{
	int last_char = strlen(s) - 1;

	if (s[last_char] == '\n')
		s[last_char] = '\0';
}

/* Deletes quotes from the  "file.h" */
static int strip_quotes(char *s)
{
	int last_char;
	char *aux = malloc(sizeof(int) * strlen(s));

	if (!aux)
		return 12;

	strcpy(aux, s + 1);

	last_char = strlen(aux) - 1;
	aux[last_char] = '\0';

	strcpy(s, aux);

	free(aux);

	return 1;
}

/*
 * Searches for the file that must be included
 * Depending on the source of the input(stdin/file) it checks
 * in the current directory or the file directory
 * If the files is not found it is looked for in the directory list
 */
static char *search_file(char *file, int console, char *input_file)
{
	FILE *found;
	char *aux;
	int len;
	int i;
	int last_char;
	int ret;

	last_char = strlen(file) - 1;

	delete_new_line(file);

	ret = strip_quotes(file);
	if (ret != 1)
		return NULL;

	if (console == 1) {
		found = fopen(file, "r");
		if (found) {
			fclose(found);
			return file;
		}
	} else {
		len = strlen(input_file) + last_char + 3;
		aux = malloc(sizeof(char) * len);

		strcpy(aux, "");

		get_directory(input_file, aux);
		strcat(aux, file);

		found = fopen(aux, "r");
		if (found) {
			fclose(found);
			return aux;
		}

		free(aux);
	}

	for (i = 0; i < d_list.index; i++) {
		len = strlen(d_list.directories[i]) + last_char + 3;
		aux = malloc(sizeof(char) * len);
		strcpy(aux, "");

		strcat(aux, d_list.directories[i]);
		strcat(aux, "/");
		strcat(aux, file);

		found = fopen(aux, "r");
		if (found) {
			fclose(found);
			return aux;
		}

		free(aux);
	}

	return NULL;
}

/*
 * Adds each line in a multi line define to a buffer
 * If \ is not found then it adds an entry in the hash table
 */
static int multi_line(char *aux, char *symbol, char *multi_mapping,
	int *backslash)
{
	char copy[LINE_LEN];
	int i;
	int last_char;
	int ret;

	for (i = 0; aux[i] != '\0'; i++) {
		if (aux[i] != ' ') {
			strcpy(copy, aux + i);
			break;
		}
	}

	strcpy(aux, copy);

	last_char = strlen(aux) - 1;

	if (aux[last_char - 1] == '\\') {
		aux[last_char - 1] = ' ';
		aux[last_char] = '\0';

		strcat(multi_mapping, aux);
	} else {
		if (aux[last_char] == '\n')
			aux[last_char] = '\0';

		*backslash = 0;

		strcat(multi_mapping, aux);

		ret = add_entry(ht, symbol, multi_mapping);
		if (ret != 1)
			return ret;
	}

	return 1;
}

static void delete_backslash(char *mapping, int *backslash)
{
	int last_char;

	last_char = strlen(mapping) - 1;

	if (strchr(mapping, '\\')) {
		mapping[last_char - 1] = '\0';
		*backslash = 1;
	}
}

/* Replaces word with its mapping if it exists */
static int check_hash_map(int *directive, char *line, char *word)
{
	char *value;
	char *modified_line;
	int len;

	*directive = 0;
	value = get_value(ht, word);

	if (value) {
		modified_line = replaceWord(line, word, value);

		len = strlen(modified_line);
		if (len > LINE_LEN) {
			line = realloc(line, len + 1);

			if (!line)
				return 12;
		}

		strcpy(line, modified_line);

		free(modified_line);
	}

	return 1;
}

/* Checks if the line contains a directive and updates variables */
static void check_if_block(char *line, int *directive, int *ifdef)
{
	if (*ifdef == 1) {
		if (strstr(line, "#endif")) {
			*directive = 1;
			*ifdef = 1;
		}

		if (strstr(line, "#else")) {
			*directive = 1;
			*ifdef = 0;
		}
	} else {
		if (strstr(line, "#else") || strstr(line, "#endif")) {
			*directive = 1;
			*ifdef = 1;
		}
	}
}

/*
 * Read line by line from the input and checks for directives
 * If the line does not contain a directive and it is not stopped
 * by a previous if or ifdef directive its defines are replaced
 * and it is added to a buffer
 * If the line contains a directive a specific action based on
 * the directive type is taken
 */
static char *parse_file(char *input_file)
{
	char line[LINE_LEN], symbol[LINE_LEN], mapping[LINE_LEN];
	char multi_mapping[LINE_LEN * 2];
	char *p, *key;
	int ret;
	int backslash = 0;
	char *aux = malloc(sizeof(char) * LINE_LEN);
	int console = 1;
	FILE *in;
	char *include_file, *condition, *value;
	int ifdef = 1;
	int directive = 0;
	char *include_buffer;
	int size = BUFF_LEN;
	char *buffer = malloc(BUFF_LEN);

	if (!buffer)
		return NULL;
	if (strcmp(input_file, "stdin") != 0) {
		in = fopen(input_file, "r");
		console = 0;
		if (!in)
			return NULL;
	} else
		in = stdin;

	strcpy(aux, "");
	strcpy(buffer, "");
	strcpy(line, "");
	while (fgets(line, LINE_LEN, in)) {
		strcpy(aux, line);

		if (backslash == 1) {
			ret = multi_line(aux, symbol, multi_mapping, &backslash);
			if (ret != 1)
				return NULL;
			continue;
		}
		p = strtok(line, "\t []{}<>=+-*/%!&|^.,:;()\\");

		while (p != NULL) {
			if (strcmp(p, "#define") == 0) {
				directive = 1;

				get_symbol_and_mapping(line, symbol, mapping);
				delete_backslash(mapping, &backslash);

				if (backslash == 0) {
					delete_new_line(mapping);
					nested_define(mapping);

					ret = add_entry(ht, symbol, mapping);
					if (ret != 1)
						return NULL;
				} else {
					strcpy(multi_mapping, "");
					strcat(multi_mapping, mapping);
				}

				break;
			} else if (strcmp(p, "#undef") == 0) {
				directive = 1;
				key = strtok(NULL, " ");

				delete_new_line(key);
				delete_key(ht, key);

				break;
			} else if (strcmp(p, "#include") == 0) {
				directive = 1;
				include_file = strtok(NULL, " ");
				include_file = search_file(include_file, console,
					input_file);
				if (!include_file)
					return NULL;

				include_buffer = parse_file(include_file);
				if (!include_buffer)
					return NULL;

				ret = append(buffer, include_buffer, &size);
				if (ret != 1)
					return  NULL;

				free(include_buffer);
				free(include_file);
				break;
			} else if (strcmp(p, "#ifdef") == 0) {
				directive = 1;
				condition = strtok(NULL, " ");

				delete_new_line(condition);
				value = get_value(ht, condition);
				if (value)
					ifdef = 1;
				else
					ifdef = 0;

				break;
			} else if (strcmp(p, "#ifndef") == 0) {
				directive = 1;
				condition = strtok(NULL, " ");

				delete_new_line(condition);
				value = get_value(ht, condition);
				if (!value)
					ifdef = 1;
				else
					ifdef = 0;

				break;
			} else if ((strcmp(p, "#if") == 0) || (strcmp(p, "#elif") == 0)) {
				directive = 1;
				condition = strtok(NULL, " ");

				delete_new_line(condition);
				define_define(condition);

				if (strcmp(condition, "0") != 0)
					ifdef = 1;
				else
					ifdef = 0;
			} else {
				if (ifdef == 1) {
					ret = check_hash_map(&directive, aux, p);

					if (ret != 1)
						return NULL;

					check_if_block(aux, &directive, &ifdef);
				} else if (ifdef == 0) {
					directive = 0;
					check_if_block(aux, &directive, &ifdef);
					break;
				}
			}
			p = strtok(NULL, "\t []{}<>=+-*/%!&|^.,:;()\\");
		}

		if (ifdef == 1 && directive == 0) {
			ret = append(buffer, aux, &size);
			if (ret != 1)
				return NULL;
		}
	}
	if (console == 0)
		fclose(in);

	free(aux);
	return buffer;
}

int main(int argc, char *argv[])
{
	int ret;
	char output_file[NAME_LEN];
	char input_file[NAME_LEN];
	char *s;

	strcpy(input_file, "stdin");
	strcpy(output_file, "stdout");

	ht = create_ht();
	if (!ht)
		return 12;

	ret = parse_arguments(argv, argc, input_file, output_file);
	if (ret != 1)
		return ret;

	s = parse_file(input_file);
	if (!s)
		return 12;

	if (strcmp(output_file, "stdout") != 0) {
		FILE *out = fopen(output_file, "w");

		fprintf(out, "%s", s);
		fclose(out);
	} else
		printf("%s", s);

	free(s);
	delete_list(&d_list);
	delete_table(&ht);
}

