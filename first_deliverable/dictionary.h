#ifndef DICTIONARY_H
#define DICTIONARY_H

///////////////////////////////////////////////////////////
// Structs
typedef struct dict_int_entry_s {
    int key;
    int value;
} dict_int_entry_s;

typedef struct dict_int_s {
    int len;
    int cap;
    dict_int_entry_s *entry;
} dict_int_s, *dict_int_t;

typedef struct dict_string_entry_s {
    const char *key;
    const char *value;
} dict_string_entry_s;

typedef struct dict_string_s {
    int len;
    int cap;
    dict_string_entry_s *entry;
} dict_string_s, *dict_string_t;

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
int dict_int_find_index(dict_int_t dict, int key);
void dict_int_add(dict_int_t dict, int key, int value);
dict_int_t dict_int_new(void);
void dict_int_free(dict_int_t dict);

int dict_string_find_index(dict_string_t dict, const char *key);
void dict_string_add(dict_string_t dict, const char *key, const char *value);
dict_string_t dict_string_new(void);
void dict_string_free(dict_string_t dict);

void list_add(list_t list, int Re, int Im);
list_t list_new(void);
void list_free(list_t list);

#endif