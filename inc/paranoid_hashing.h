// Copyright (c) 2018 Scaboro da Silva, Ewerton. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PARANOID_HASHING_H
#define PARANOID_HASHING_H

#include <stdlib.h>
#include <stddef.h>

int pb_get_hash(const char* data, size_t length, char** hash);

#endif // PARANOID_HASHING_H