/* Include the library. */
#include <str.h>
#include <assert.h>

int main(void) {
	/* Create a str object.
	 * The argument can be NULL in which case 
	 * the string will be initialized with just a '\0' */
	str_t *str = str_new("Hello, World!");

	/* Get the length of the str
	 * (excluding the \0 terminator). */
	assert(str_len(str) == 13);

	/* Append a new string at the end. */
	str_append(str, " How are you?");

	/* Prepend a new string at the beginning. */
	str_prepend(str, "Good Morning! ");

	/* Get a const pointer to a substring, if exists. */
	assert(str_find(str, "Good"));

	/* Replace all occurrances of a substring. */
	str_replace(str, "Hello", "Jello");

	/* Compare to strings. */
	assert(str_same(str, "Good Morning! Jello, World! How are you?"));

	/* Remove the last character and return it via an out param. */
	char c;
	str_pop_back(str, &c);
	assert(c == '?');

	/* Remove the first character and return it via an out param. */
	str_pop_front(str, &c);
	assert(c == 'G');

	/* Append a character at the end. */
	str_push_back(str, '?');
	assert(str_same(str, "ood Morning! Jello, World! How are you?"));

	/* Prepend a character at the beginning. */
	str_push_front(str, 'G');
	assert(str_same(str, "Good Morning! Jello, World! How are you?"));

	/* Delete the str object. */
	str_del(str);

	return 0;
}
