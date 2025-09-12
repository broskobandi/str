# str
## Dynamic string written in C.
The goal of the project is to provide a fast, reliable, and safe abstractions
for common string operations.
## Features
### Type safety
The provided str_t type ensures that only the appropriate pointers are passed 
to the provided functions. This feature can be further improved by using 
the -Wconversion copmiler flag in your application.
### Memory safety
The encapsulated raw string data can only be operated over using the provided
functions. None of these functions take a pointer to the actual encapsulated 
data, only the provided str_t opaque handle. Only const pointers are returned 
by functions that expose the internal data (such as str_find or str_view).
### Automatic zero terminator
Each newly created string objects, whether they are initialized or left empty,
are terminated with '\0'. The zero termination is preserved whenever modifying
the string using any of the provided function ensuring that the encapsulated 
raw string is always compatible with the standard C string.h library.
### High performance
The library uses the highly performant [vec](https://github.com/broskobandi/vec.git)
for operating over the encapsulated data ensuring fast and reliable usage.
### Consistent return types
All the getter and setter functions return an integer value indicating success
or failure (except the str_len function which returns the expected value on
success or (size_t)-1 on failure). 
## Installation
```bash
git clone https://github.com/broskobandi/vec.git &&
cd vec &&
make &&
sudo make install
```
## Uninstallation
```bash
cd vec &&
sudo make uninstall
```
## Usage
```c
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
```
Use the -L/usr/local/lib -lstr linker flags when compiling your application.
## Testing
```bash
cd vec &&
make clean &&
make test &&
make clean
```
## Documentation
```bash
cd vec &&
make doc
```
