#include "str_utils.h"

str_t *str_new(const char *str) {
	VEC(char) *vec = VEC_NEW(char);
	if (!vec) RET_ERR("Failed to create char vec.", NULL);
	if (str)
		if (VEC_APPEND(char, &vec, str, strlen(str)))
			RET_ERR("Failed to append string.", NULL);
	if (VEC_PUSH(char, &vec, '\0'))
		RET_ERR("Failed to zero terminate string.", NULL);
	RET_OK((str_t*)vec);
}

void str_del(str_t **str) {
	if (!str || !*str) RET_ERR("Invalid argument.");
	VEC(char) **vec = (VEC(char)**)str;
	if (VEC_DEL(char, vec)) RET_ERR("Failed to delete vec.");
	*str = NULL;
}

#include <stdio.h>
int str_append(str_t **str, const char *src) {
	if (!str || !*str || !src) RET_ERR("Invalid argument.", 1);
	VEC(char) **vec = (VEC(char)**)str;
	if (VEC_POP(char, vec, NULL))
		RET_ERR("Failed to remove zero termination.", 1);
	if (VEC_APPEND(char, vec, src, strlen(src)))
		RET_ERR("Failed to delete vec.", 1);
	if (VEC_PUSH(char, vec, '\0'))
		RET_ERR("Failed to zero terminate string.", 1);
	RET_OK(0);
}

const char *str_ptr(const str_t *str) {
	if (!str) RET_ERR("Invalid input.", NULL);
	VEC(char) *vec = (VEC(char)*)str;
	RET_OK(VEC_PTR(char, vec, 0));
}

size_t str_len(const str_t *str) {
	if (!str) RET_ERR("Invalid input.", (size_t)-1);
	VEC(char) *vec = (VEC(char)*)str;
	RET_OK(VEC_LEN(char, vec) - 1);
}

size_t str_size(const str_t *str) {
	if (!str) RET_ERR("Invalid input.", (size_t)-1);
	VEC(char) *vec = (VEC(char)*)str;
	RET_OK(VEC_LEN(char, vec));
}

char str_at(const str_t *str, size_t index) {
	if (!str) RET_ERR("Invalid input.", (char){0});
	VEC(char) *vec = (VEC(char)*)str;
	char elem = {0};
	if (VEC_AT(char, vec, index, &elem))
		RET_ERR("Failed to access element.", (char){0});
	RET_OK(elem);
}

int str_cpy(str_t **dst, const str_t *src) {
	if (!dst || !src) RET_ERR("Invalid argument.", 1);
	VEC(char) **dstvec = (VEC(char)**)dst;
	VEC(char) *srcvec = (VEC(char)*)src;
	if (VEC_CPY(char, dstvec, srcvec)) RET_ERR("VEC_CPY() failed.", 1);
	RET_OK(0);
}

size_t str_capacity(const str_t *str) {
	if (!str) RET_ERR("Invalid argument.", 1);
	VEC(char) *vec = (VEC(char)*)str;
	RET_OK(VEC_CAPACITY(char, vec));
}

int str_has(const str_t *str, const char *keyword) {
	if (!str || !keyword) RET_ERR("Invalid argument.", -1);
	if (strstr(str_ptr(str), keyword)) RET_OK(1);
	RET_OK(0);
}
