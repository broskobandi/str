#include "str_utils.h"

str_t *str_new(const char *str) {
	VEC(char) *vec = VEC_NEW(char);
	if (!vec) RET_ERR("Failed to create char vec.", NULL);
	if (str)
		if (VEC_APPEND(char, &vec, str, strlen(str)))
			RET_ERR("Failed to append string.", NULL);
	RET_OK((str_t*)vec);
}
