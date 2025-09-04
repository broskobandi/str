#include "test_utils.h"
#include "str_utils.h"
#include <error.h>

void test_str() {
	str_t *str = str_new("Hello");
	ASSERT(!str_append(&str, ", World!"));
	VEC(char) *vec = (VEC(char)*)str;
	ASSERT(VEC_LEN(char, vec) == strlen("Hello, World!") + 1);
	ASSERT(!strcmp(str_ptr(str), "Hello, World!"));
	ASSERT(str_len(str) == strlen("Hello, World!"));
	ASSERT(str_at(str, 1) == 'e');
	ASSERT(str_at(str, 13) == '\0');
	ASSERT(str_at(str, str_len(str)) == '\0');
	ASSERT(str_size(str) == str_len(str) + 1);
	str_t *new_str = str_new("some text");
	ASSERT(!str_cpy(&new_str, str));
	ASSERT(!strcmp(str_ptr(new_str), "Hello, World!"));
	ASSERT(str_len(new_str) == str_len(str));
	ASSERT(str_capacity(new_str) == str_capacity(str));
	str_del(&str);
}
