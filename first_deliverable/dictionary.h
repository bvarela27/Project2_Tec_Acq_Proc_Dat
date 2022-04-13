#ifndef DICTIONARY_H
#define DICTIONARY_H

///////////////////////////////////////////////////////////
// Structs
typedef struct dict_entry_s {
    int key;
    int value;
} dict_entry_s;

typedef struct dict_s {
    int len;
    int cap;
    dict_entry_s *entry;
} dict_s, *dict_t;

typedef struct list_entry_s {
    int Re;
    int Im;
} list_entry_s;

typedef struct list_s {
    int len;
    int cap;
    list_entry_s *entry;
} list_s, *list_t;

///////////////////////////////////////////////////////////
// Functions
int dict_find_index(dict_t dict, int key);
void dict_add(dict_t dict, int key, int value);
dict_t dict_new(void);
void dict_free(dict_t dict);

void list_add(list_t list, int Re, int Im);
list_t list_new(void);
void list_free(list_t list);

#endif