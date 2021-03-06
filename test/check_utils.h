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

/**
 * \file check_utils.h Internal header
 * This file is used internally by buxton to provide functionality
 * used for testing
 */

#pragma once

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

/**
 * Set up a socket pair
 * @param client Client socket file descriptor
 * @param server Server socket file descriptor
 */
void setup_socket_pair(int *client, int *server);

/*
 * Editor modelines  -	http://www.wireshark.org/tools/modelines.html
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
