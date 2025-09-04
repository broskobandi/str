#include "../test_utils.h"

TEST_INIT;

int main(void) {
	test_str_new_and_del();
	test_str_append_and_ptr_and_len();

	test_print_results();
	return 0;
}
