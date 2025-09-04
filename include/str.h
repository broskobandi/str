#ifndef STR_H
#define STR_H

#include <stddef.h>

typedef struct str str_t;

str_t *str_new(const char *str);
void str_del(str_t **str);
int str_append(str_t **str, const char *src);
const char *str_ptr(const str_t *str);
size_t str_len(const str_t *str); // this has to exclude \0!
void str_at();
void str_cpy(); // do we need this?
void str_capacity();
void str_has();
void str_cmp();
void str_prepend();
void str_replace();
void str_slice();

#endif
