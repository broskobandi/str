#include "test_utils.h"
#include "str.h"

void test_str_new() {
	{ // Normal case
		str_t *str = str_new(NULL);
		ASSERT(str);
	} 
	{ // Normal case: from string
		str_t *str = str_new("some text");
		ASSERT(str);
	}
}
