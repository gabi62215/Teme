#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

char *my_strdup(char *s)
{
	int len = strlen(s);
	char *new = malloc(len + 1);

	if (!new)
		return NULL;

	strcpy(new, s);

	return new;
}

int add_item(list *x, char *s)
{
	x->directories[x->index] = my_strdup(s);
	if (!x->directories[x->index])
		return 12;

	x->index++;

	return 1;
}

void delete_list(list *x)
{
	int i;

	for (i = 0; i < x->index; i++) {
		free(x->directories[i]);
		x->directories[i] = NULL;
	}
}

int add_entry(hash_table *ht, char *key, char *value)
{
	if (ht->index == CAPACITY) {
		ht->items = realloc(ht->items, ht->index * 2);
		if (!ht->items)
			return 12;
	}

	if (key)
		ht->items[ht->index].key = my_strdup(key);
	if (value)
		ht->items[ht->index].value = my_strdup(value);

	if (!ht->items[ht->index].key || !ht->items[ht->index].value)
		return 12;

	ht->index++;

	return 1;
}

void delete_table(hash_table **ht)
{
	int i;

	for (i = 0; i < (*ht)->index; i++) {
		free((*ht)->items[i].value);
		free((*ht)->items[i].key);

		(*ht)->items[i].value = NULL;
		(*ht)->items[i].key = NULL;
	}

	free((*ht)->items);
	(*ht)->items = NULL;

	free(*ht);
	*ht = NULL;
}

char *get_value(hash_table *ht, char *key)
{
	int i;

	for (i = 0; i < ht->index; i++) {
		if (strcmp(key, ht->items[i].key) == 0)
			return ht->items[i].value;
	}

	return NULL;
}

void delete_key(hash_table *ht, char *key)
{
	int i;

	for (i = 0; i < ht->index; i++) {
		if (strcmp(key, ht->items[i].key) == 0) {
			strcpy(ht->items[i].key, "");
			strcpy(ht->items[i].value, "");
		}
	}
}

hash_table *create_ht(void)
{
	hash_table *ht = (hash_table *)malloc(sizeof(hash_table));

	if (!ht)
		return NULL;

	ht->items = calloc(CAPACITY, sizeof(hash_entry));

	if (!ht->items)
		return NULL;

	ht->index = 0;

	return ht;
}


