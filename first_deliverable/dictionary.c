#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dictionary int
int dict_int_find_index(dict_int_t dict, int key) {
    for (int i = 0; i < dict->len; i++) {
        if (dict->entry[i].key == key) {
            return i;
        }
    }
    return -1;
}

void dict_int_add(dict_int_t dict, int key, int value) {
   int idx = dict_int_find_index(dict, key);
   if (idx != -1) {
       dict->entry[idx].value += value;
       return;
   }
   if (dict->len == dict->cap) {
       dict->cap *= 2;
       dict->entry = realloc(dict->entry, dict->cap * sizeof(dict_int_entry_s));
   }
   dict->entry[dict->len].key = key;
   dict->entry[dict->len].value = value;
   dict->len++;
}

dict_int_t dict_int_new(void) {
    dict_int_s proto = {0, 10, malloc(10 * sizeof(dict_int_entry_s))};
    dict_int_t d = malloc(sizeof(dict_int_s));
    *d = proto;
    return d;
}

void dict_int_free(dict_int_t dict) {
    free(dict->entry);
    free(dict);
}

// Dictionary string
int dict_string_find_index(dict_string_t dict, const char *key) {
    for (int i = 0; i < dict->len; i++) {
        if (!strcmp(dict->entry[i].key, key)) {
            return i;
        }
    }
    return -1;
}

void dict_string_add(dict_string_t dict, const char *key, const char *value) {
   int idx = dict_string_find_index(dict, key);
   if (idx != -1) {
       dict->entry[idx].value = strdup(value);
       return;
   }
   if (dict->len == dict->cap) {
       dict->cap *= 2;
       dict->entry = realloc(dict->entry, dict->cap * sizeof(dict_string_entry_s));
   }
   dict->entry[dict->len].key = strdup(key);
   dict->entry[dict->len].value = strdup(value);
   dict->len++;
}

dict_string_t dict_string_new(void) {
    dict_string_s proto = {0, 10, malloc(10 * sizeof(dict_string_entry_s))};
    dict_string_t d = malloc(sizeof(dict_string_s));
    *d = proto;
    return d;
}

// List
void list_add(list_t list, int Re, int Im) {
   if (list->len == list->cap) {
       list->cap *= 2;
       list->entry = realloc(list->entry, list->cap * sizeof(list_entry_s));
   }
   list->entry[list->len].Re = Re;
   list->entry[list->len].Im = Im;
   list->len++;
}

list_t list_new(void) {
    list_s proto = {0, 10, malloc(10 * sizeof(list_entry_s))};
    list_t d = malloc(sizeof(list_s));
    *d = proto;
    return d;
}

void list_free(list_t list) {
    free(list->entry);
    free(list);
}
