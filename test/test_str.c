#include "test_utils.h"
#include "str.h"

void test_str_new_and_del() {
	{ // Normal case
		str_t *str = str_new(NULL);
		ASSERT(str);
		str_del(&str);
		ASSERT(!str);
	} 
	{ // Normal case: from string
		str_t *str = str_new("some text");
		ASSERT(str);
		str_del(&str);
		ASSERT(!str);
	}
}
