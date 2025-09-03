#ifndef STR_H
#define STR_H

typedef struct str str_t;

str_t *str_new(const char *str);
void str_del(str_t **str);
void str_append();
void str_at();
void str_len();
void str_data();
void str_capacity();
void str_has();
void str_cmp();
void str_prepend();
void str_replace();
void str_slice();

#endif
