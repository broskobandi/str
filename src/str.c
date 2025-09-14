/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/** \file src/str.c
 * \brief Implementation for the str library.
 * \details This file contains the declarations of the public functions 
 * for the str library. */

#include "str.h"
#include <string.h>
#include <vec.h>
#include <stdint.h>

/** Creates a new str object.
 * \param src A string to initialize the object with (can be NULL).
 * \return A pointer to the str object. */
str_t *str_new(const char *src) {
	vec_generic_t *vec = vec_generic_new(sizeof(char));
	if (!vec) return NULL;
	if (src) {
		if (vec_generic_append(vec, src, strlen(src), sizeof(char)))
			return NULL;
	}
	char nullterm = '\0';
	if (vec_generic_push_back(vec, &nullterm, sizeof(char)))
		return NULL;
	return (str_t*)vec;
}

/** Deletes a str object.
 * \param str A pointer to the str object. 
 * \return 0 on success or 1 on failure. */
int str_del(str_t *str) {
	if (!str) return 1;
	vec_generic_t *vec = (vec_generic_t*)str;
	return vec_generic_del(vec);
}

/** Returns a const pointer to the raw c string.
 * \param str A pointer to the str object to be accessed. 
 * \return A const pointer to the raw c string. */
const char *str_view(const str_t *str) {
	if (!str) return NULL;
	vec_generic_t *vec = (vec_generic_t*)str;
	return (const char*)vec_generic_view(vec, 0);
}

/** Returns the length of the str object (excluding the zero terminator).
 * \param str A pointer to the str object.
 * \return The length of the str object or (size_t)-1 on failure. */
size_t str_len(const str_t *str) {
	if (!str) return (size_t)-1;
	vec_generic_t *vec = (vec_generic_t*)str;
	return vec_generic_len(vec) - 1;
}

/** Appends a string at the end of the str object.
 * \param str A pointer to the str object to be modified. 
 * \param src The raw c string to be appended.
 * \return 0 on success or 1 on failure. */
int str_append(str_t *str, const char *src) {
	if (!str || !src) return 1;
	vec_generic_t *vec = (vec_generic_t*)str;
	if (
		vec_generic_replace_range(
			vec, src, strlen(src),
			vec_generic_len(vec) - 1, 0, sizeof(char)
		)
	) {
		return 1;
	}
	return 0;
}

/** Prepends a string at the beginning of the str object.
 * \param str A pointer to the str object to be modified. 
 * \param src The raw c string to be prepended.
 * \return 0 on success or 1 on failure. */
int str_prepend(str_t *str, const char *src) {
	if (!str || !src) return 1;
	vec_generic_t *vec = (vec_generic_t*)str;
	if (vec_generic_prepend(vec, src, strlen(src), sizeof(char)))
		return 1;
	return 0;
}

/** Find a substring in the str object (case sensitive).
 * \param str A pointer to the str object to be accessed. 
 * \param keyword The substring to be found. 
 * \return A const pointer to the index where 'keyword' is found or NULL 
 * if the keyword is not found and on failure.*/
const char *str_find(const str_t *str, const char *keyword) {
	if (!str || !keyword) return NULL;
	const char *c_str = str_view(str);
	return strstr(c_str, keyword);
}

/** Replace all occurrances of a substring in the str object
 * (case sensitive).
 * \param str A pointer to the str object to be modified. 
 * \param toreplace The substring to be replaced. 
 * \param src The string to replace the substring with.
 * \return 0 on success or 1 on failure.*/
int str_replace(str_t *str, const char *toreplace, const char *src) {
	if (!str || !toreplace || !src) return 1;
	while (str_find(str, toreplace)) {
		vec_generic_t *vec = (vec_generic_t*)str;
		size_t index = (size_t)((intptr_t)str_find(str, toreplace) - 
			(intptr_t)str_view(str));
		if (
			vec_generic_replace_range(
				vec, src, strlen(src), index,
				strlen(toreplace), sizeof(char)
			)
		) {
			return 1;
		}
	}
	
	return 0;
}

/** Compares a str object and a raw c string.
 * \param str A pointer to the string to be compared.
 * \param src The raw c string to compare with. 
 * \return 0 if the strings are not the same, 1 if the strings are the same,
 * -1 on failure. */
int str_same(const str_t *str, const char *src) {
	if (!str || !src) return -1;
	if (!strcmp(str_view(str), src)) {
		return 1;
	} else {
		return 0;
	}
}

/** Removes the last character (excluding the zero terminator)
 * and copies it into 'c'.
 * \param str A pointer to the str object to be modified.
 * \param c A pointer to the variable to copy the data into.
 * \return 0 on success or 1 on failure. */
int str_pop_back(str_t *str, char *c) {
	if (!str) return 1;
	vec_generic_t *vec = (vec_generic_t*)str;
	if (c)
		if (vec_generic_at(vec, c, vec_generic_len(vec) - 2, sizeof(char)))
			return 1;
	if (vec_generic_remove(vec, vec_generic_len(vec) - 2))
		return 1;
	return 0;
}

/** Removes the first character (excluding the zero terminator)
 * and copies it into 'c'.
 * \param str A pointer to the str object to be modified.
 * \param c A pointer to the variable to copy the data into.
 * \return 0 on success or 1 on failure. */
int str_pop_front(str_t *str, char *c) {
	if (!str) return 1;
	vec_generic_t *vec = (vec_generic_t*)str;
	if (c)
		if (vec_generic_at(vec, c, 0, sizeof(char)))
			return 1;
	if (vec_generic_remove(vec, 0))
		return 1;
	return 0;
}

/** Appends a character at the end of a str object.
 * \param str A pointer to the str object to be modified.
 * \param c The character to be appended. 
 * \return 0 on success or 1 on failure. */
int str_push_back(str_t *str, char c) {
	if (!str) return 1;
	vec_generic_t *vec = (vec_generic_t*)str;
	if (vec_generic_insert(vec, &c, vec_generic_len(vec) - 1, sizeof(char)))
		return 1;
	return 0;
}

/** Prepends a character at the beginning of a str object.
 * \param str A pointer to the str object to be modified.
 * \param c The character to be prepended. 
 * \return 0 on success or 1 on failure. */
int str_push_front(str_t *str, char c) {
	if (!str) return 1;
	vec_generic_t *vec = (vec_generic_t*)str;
	if (vec_generic_push_front(vec, &c, sizeof(char)))
		return 1;
	return 0;
}
