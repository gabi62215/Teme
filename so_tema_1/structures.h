#define CAPACITY 50

/* List of directories to look for include file */
typedef struct list {
	char *directories[CAPACITY];
	int index;
} list;

/* Element in the hash table,the key is the symbol and value the mapping */
typedef struct hash_entry {
	char *key;
	char *value;
} hash_entry;

/*
 * Just a vector with the hash
 * entries and a counter to the
 * last avaiable slot
 */
typedef struct hash_table {
	hash_entry *items;
	int index;
} hash_table;

/*
 * Takes keyu and value and adds it to the hash table
 * Return 1 on succes or 12 if malloc fails
 */
int add_entry(hash_table *ht, char *key, char *value);

/* Frees the memory allocated for the hash table */
void delete_table(hash_table **ht);

/* Retrives pointer to value of key or NULL if it is not present */
char *get_value(hash_table *ht, char *key);

/* Deletes entry from hash table */
void delete_key(hash_table *ht, char *key);

/*
 * Allocates memory for the table
 * Returns NULL on failure or pointer to allocated memory on succes
 */
hash_table *create_ht(void);

/* Adds directory to the list */
int add_item(list *x, char *s);

/* Frees memory allocated for list */
void delete_list(list *x);

/* Implementation of strdup */
char *my_strdup(char *s);
