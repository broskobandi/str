#ifndef STR_H
#define STR_H

#include <stddef.h> /* For size_t */

typedef struct str str_t;

str_t *str_new(const char *src);
int str_del(str_t *str);
const char *str_view(const str_t *str);
size_t str_len(const str_t *str);
int str_append(str_t *str, const char *src);
int str_prepend(str_t *str, const char *src);
/** this is case sensitive! */
const char *str_find(const str_t *str, const char *keyword);
/** this is case sensitive! */
int str_replace(str_t *str, const char *toreplace, const char *src);
int str_cmp(const str_t *str, const char *src);
int str_pop_back(str_t *str, char *c);
int str_pop_front(str_t *str, char *c);
int str_push_back(str_t *str, char c);
int str_push_front(str_t *str, char c);

#endif
