#include "test_utils.h"
#include "str_utils.h"
#include <error.h>

void test_str_new_and_del() {
	{ // Normal case
		str_t *str = str_new(NULL);
		ASSERT(str);
		vec_char_t *vec = (vec_char_t*)str;
		ASSERT(vec);
		ASSERT(VEC_LEN(char, vec) == 1);
		char termination = 'a';
		ASSERT(!VEC_AT(char, vec, 0, &termination));
		ASSERT(termination == '\0');
		str_del(&str);
		ASSERT(!str);
	} 
	{ // Normal case: from string
		str_t *str = str_new("some text");
		ASSERT(str);
		VEC(char) *vec = (VEC(char)*)str;
		char termination = 'a';
		ASSERT(!VEC_AT(char, vec, VEC_LEN(char, vec) - 1, &termination));
		ASSERT(VEC_LEN(char, vec) == strlen("some text") + 1);
		ASSERT(termination == '\0');
		str_del(&str);
		ASSERT(!str);
	} 
}

void test_str_append_and_ptr_and_len() {
	{ // Normal case
		str_t *str = str_new("Hello");
		ASSERT(!str_append(&str, ", World!"));
		VEC(char) *vec = (VEC(char)*)str;
		ASSERT(VEC_LEN(char, vec) == strlen("Hello, World!") + 1);
		ASSERT(!strcmp(str_ptr(str), "Hello, World!"));
		ASSERT(str_len(str) == strlen("Hello, World!"));
		str_del(&str);
	}
	{ // Invalid input
		ASSERT(!str_ptr(NULL));
	}
}
