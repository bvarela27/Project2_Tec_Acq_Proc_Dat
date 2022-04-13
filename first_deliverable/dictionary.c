#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dictionary
int dict_find_index(dict_t dict, int key) {
    for (int i = 0; i < dict->len; i++) {
        if (dict->entry[i].key == key) {
            return i;
        }
    }
    return -1;
}

void dict_add(dict_t dict, int key, int value) {
   int idx = dict_find_index(dict, key);
   if (idx != -1) {
       dict->entry[idx].value += value;
       return;
   }
   if (dict->len == dict->cap) {
       dict->cap *= 2;
       dict->entry = realloc(dict->entry, dict->cap * sizeof(dict_entry_s));
   }
   dict->entry[dict->len].key = key;
   dict->entry[dict->len].value = value;
   dict->len++;
}

dict_t dict_new(void) {
    dict_s proto = {0, 10, malloc(10 * sizeof(dict_entry_s))};
    dict_t d = malloc(sizeof(dict_s));
    *d = proto;
    return d;
}

void dict_free(dict_t dict) {
    free(dict->entry);
    free(dict);
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
