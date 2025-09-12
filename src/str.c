#include "str.h"
#include <string.h>
#include <vec.h>
#include <stdint.h>

str_t *str_new(const char *src) {
	vec_t *vec = vec_new(sizeof(char));
	if (!vec) return NULL;
	if (src) {
		if (vec_append(vec, src, strlen(src), sizeof(char)))
			return NULL;
	}
	char nullterm = '\0';
	if (vec_push_back(vec, &nullterm, sizeof(char)))
		return NULL;
	return (str_t*)vec;
}

int str_del(str_t *str) {
	if (!str) return 1;
	vec_t *vec = (vec_t*)str;
	return vec_del(vec);
}

const char *str_view(const str_t *str) {
	if (!str) return NULL;
	vec_t *vec = (vec_t*)str;
	return (const char*)vec_view(vec, 0);
}

size_t str_len(const str_t *str) {
	if (!str) return (size_t)-1;
	vec_t *vec = (vec_t*)str;
	return vec_len(vec) - 1;
}

int str_append(str_t *str, const char *src) {
	if (!str || !src) return 1;
	vec_t *vec = (vec_t*)str;
	if (
		vec_replace_range(
			vec, src, strlen(src),
			vec_len(vec) - 1, 0, sizeof(char)
		)
	) {
		return 1;
	}
	return 0;
}

int str_prepend(str_t *str, const char *src) {
	if (!str || !src) return 1;
	vec_t *vec = (vec_t*)str;
	if (vec_prepend(vec, src, strlen(src), sizeof(char)))
		return 1;
	return 0;
}

const char *str_find(const str_t *str, const char *keyword) {
	if (!str || !keyword) return NULL;
	const char *c_str = str_view(str);
	return strstr(c_str, keyword);
}

int str_replace(str_t *str, const char *toreplace, const char *src) {
	if (!str || !toreplace || !src) return 1;
	while (str_find(str, toreplace)) {
		vec_t *vec = (vec_t*)str;
		size_t index = (size_t)((intptr_t)str_find(str, toreplace) - 
			(intptr_t)str_view(str));
		if (
			vec_replace_range(
				vec, src, strlen(src), index,
				strlen(toreplace), sizeof(char)
			)
		) {
			return 1;
		}
	}
	
	return 0;
}

int str_cmp(const str_t *str, const char *src) {
	if (!str || !src) return -1;
	return strcmp(str_view(str), src);
}

int str_pop_back(str_t *str, char *c) {
	if (!str) return 1;
	vec_t *vec = (vec_t*)str;
	if (c)
		if (vec_at(vec, c, vec_len(vec) - 2, sizeof(char)))
			return 1;
	if (vec_remove(vec, vec_len(vec) - 2))
		return 1;
	return 0;
}

int str_pop_front(str_t *str, char *c) {
	if (!str) return 1;
	vec_t *vec = (vec_t*)str;
	if (c)
		if (vec_at(vec, c, 0, sizeof(char)))
			return 1;
	if (vec_remove(vec, 0))
		return 1;
	return 0;
}

int str_push_back(str_t *str, char c) {
	if (!str) return 1;
	vec_t *vec = (vec_t*)str;
	if (vec_insert(vec, &c, vec_len(vec) - 1, sizeof(char)))
		return 1;
	return 0;
}

int str_push_front(str_t *str, char c) {
	if (!str) return 1;
	vec_t *vec = (vec_t*)str;
	if (vec_push_front(vec, &c, sizeof(char)))
		return 1;
	return 0;
}
