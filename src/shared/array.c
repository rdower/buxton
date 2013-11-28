/*
 * This file is part of buxton.
 *
 * Copyright (C) 2013 Intel Corporation
 *
 * buxton is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#include <stdlib.h>
#include <string.h>

#include "buxton-array.h"

BuxtonArray *buxton_array_new(void)
{
	BuxtonArray *ret = NULL;
	/* If this fails, we simply return NULL and allow the user
	 * to deal with the error */
	ret = calloc(1, sizeof(BuxtonArray));
	return ret;
}

bool buxton_array_add(BuxtonArray *array,
		      void *data)
{
	uint new_len;

	if (!array || !data)
		return false;
	if (!array->data) {
		array->data = calloc(1, sizeof(void*));
		if (!array->data)
			return false;
	}

	new_len = array->len += 1;
	if (new_len >= array->len) {
		/* Resize the array to hold one more pointer */
		array->data = realloc(array->data, (new_len+1)*sizeof(void*));
		if (!array->data)
			return false;
	}
	/* Store the pointer at the end of the array */
	array->len = new_len;
	array->data[array->len-1] = data;
	return true;
}

bool buxton_array_has(BuxtonArray *array,
		      void *data)
{
	bool ret = false;
	int i;

	if (!array || !data)
		return false;
	for (i = 0; i < array->len; i++) {
		/* This will work for either pointers or simple stack
		 * members like char* */
		if (data == array->data[i]) {
			ret = true;
			break;
		}
	}
	return ret;
}

bool buxton_array_remove(BuxtonArray *array,
			 void *data,
			 buxton_free_func free_method)
{
	uint i;
	uint index;
	bool found = false;
	uint new_size;

	if (!array || !data)
		return false;

	for (i=0; i < array->len; i++) {
		if (data == array->data[i]) {
			index = i;
			found = true;
			break;
		}
	}
	if (!found)
		return false;

	/* Optionally call the free function, to free this member */
	if (free_method)
		free_method(array->data[index]);

	new_size = array->len - 1;
	memmove(array->data+index, array->data+index+1, sizeof(void*) *
		(array->len-index-1));
	array->data[array->len] = NULL;
	array->data = realloc(array->data, new_size*(sizeof(void*)));

	array->len -= 1;
	return true;
}

void buxton_array_free(BuxtonArray **array,
		       buxton_free_func free_method)
{
	int i;
	if (!array)
		return;

	if (free_method) {
		/* Call the free_method on all members */
		for (i = 0; i < (*array)->len; i++)
			free_method((*array)->data[i]);
	}
	/* Ensure this array is indeed gone. */
	free((*array)->data);
	free(*array);
	*array = NULL;
}

/*
 * Editor modelines  -  http://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: t
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 noexpandtab:
 * :indentSize=8:tabSize=8:noTabs=false:
 */