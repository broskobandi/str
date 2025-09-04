#ifndef STR_H
#define STR_H

#include <stddef.h>

typedef struct str str_t;

str_t *str_new(const char *str);
void str_del(str_t **str);
int str_append(str_t **str, const char *src);
const char *str_ptr(const str_t *str);
/** Excludes \0 */
size_t str_len(const str_t *str);
size_t str_size(const str_t *str);
char str_at(const str_t *str, size_t index);
int str_cpy(str_t **dst, const str_t *src);
size_t str_capacity(const str_t *str);
int str_has(const str_t *str, const char *keyword);
void str_cmp();
void str_prepend();
void str_replace();
void str_slice();

#endif
