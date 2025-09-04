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
