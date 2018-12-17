// Copyright (c) 2018 Scaboro da Silva, Ewerton. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef STORAGE_ENDPOINT_H
#define STORAGE_ENDPOINT_H

#include <stdlib.h>
#include <stddef.h>

typedef struct STORAGE_ENDPOINT_HOST_STRUCT
{
    char* address;
    size_t port;
} STORAGE_ENDPOINT_HOST;

typedef struct STORAGE_ENDPOINT_STRUCT 
{
    char* id;
    STORAGE_ENDPOINT_HOST host;
    char* path;
    size_t max_size_in_mbytes;
    STORAGE_ENDPOINT* next;  
} STORAGE_ENDPOINT;

STORAGE_ENDPOINT* storage_endpoint_get_list();
int storage_endpoint_add(STORAGE_ENDPOINT* description);
int storage_endpoint_remove(STORAGE_ENDPOINT* description);
int storage_endpoint_update(STORAGE_ENDPOINT* description);

#endif // STORAGE_ENDPOINT_H