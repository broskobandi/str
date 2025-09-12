#include "str.h"
#include <test.h>
#include <string.h>

TEST_INIT;

void test_str_new_view_del_len() {
	{ // empty string
		str_t *str = str_new(NULL);
		ASSERT(str);
		ASSERT(!str_len(str));
		ASSERT(!str_del(str));
	}
	{ // initialized string
		str_t *str = str_new("Some text");
		ASSERT(str);
		ASSERT(str_len(str) == strlen("Some text"));
		ASSERT(!strcmp(str_view(str), "Some text"));
		ASSERT(!str_del(str));
	}
}

void test_append() {
	str_t *str = str_new("Hello, ");
	ASSERT(!str_append(str, "World!"));
	ASSERT(!strcmp(str_view(str), "Hello, World!"));
	str_del(str);
}

void test_prepend() {
	str_t *str = str_new("World!");
	ASSERT(!str_prepend(str, "Hello, "));
	ASSERT(!strcmp(str_view(str), "Hello, World!"));
	str_del(str);
}

void test_find() {
	str_t *str = str_new("Hello, World!");
	ASSERT(str_find(str, "Hell"));
	ASSERT(str_find(str, "Wor"));
	ASSERT(str_find(str, "lo") == str_view(str) + 3);
	ASSERT(str_find(str, "Wo") == str_view(str) + 7);
	str_del(str);
}

void test_replace() {
	{ // same
		str_t *str = str_new("Hello, World!");
		ASSERT(!str_replace(str, "Hello", "Jello"));
		ASSERT(!strcmp(str_view(str), "Jello, World!"));
		str_del(str);
	}
	{ // longer
		str_t *str = str_new("Hello, World!");
		const char *src = "Super duper very very long greetings to you";
		ASSERT(!str_replace(str, "Hello", src));
		ASSERT(
			!strcmp(str_view(str),
			"Super duper very very long greetings to you, World!")
		);
		str_del(str);
	}
	{ // shorter
		str_t *str = str_new(
			"Super duper very very long greetings to you, World!"
		);
		ASSERT(
			!str_replace(str,
			"Super duper very very long greetings to you", "Hello")
		);
		ASSERT(!strcmp(str_view(str), "Hello, World!"));
		str_del(str);
	}
}

void test_same() {
	str_t *str = str_new("Hello");
	ASSERT(str_same(str, "Hello") == 1);
	ASSERT(str_same(str, "Jello") == 0);
	ASSERT(str_same(str, NULL) == -1);
	str_del(str);
}

void test_pop_back() {
	str_t *str = str_new("Hello!");
	char c;
	ASSERT(!str_pop_back(str, &c));
	ASSERT(c == '!');
	ASSERT(str_same(str, "Hello"));
	str_del(str);
}

void test_pop_front() {
	str_t *str = str_new("Hello!");
	char c;
	ASSERT(!str_pop_front(str, &c));
	ASSERT(c == 'H');
	ASSERT(str_same(str, "ello!"));
	str_del(str);
}

void test_push_back() {
	str_t *str = str_new("Hello");
	ASSERT(!str_push_back(str, '!'));
	ASSERT(str_same(str, "Hello!"));
	str_del(str);
}

void test_push_front() {
	str_t *str = str_new("ello!");
	ASSERT(!str_push_front(str, 'H'));
	ASSERT(str_same(str, "Hello!"));
	str_del(str);
}

int main(void) {
	test_str_new_view_del_len();
	test_append();
	test_prepend();
	test_find();
	test_replace();
	test_same();
	test_pop_back();
	test_pop_front();
	test_push_back();
	test_push_front();

	test_print_results();
	return 0;
}
