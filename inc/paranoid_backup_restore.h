// Copyright (c) 2018 Scaboro da Silva, Ewerton. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PARANOID_BACKUP_RESTORE_H
#define PARANOID_BACKUP_RESTORE_H

typedef void (*RESTORE_PROGRESS_REPORT_CALLBACK)();

typedef struct PB_RESTORE_REQUEST_STRUCT 
{
    const char* source_path;
    int version_id;
    const char* destination_path;
    RESTORE_PROGRESS_REPORT_CALLBACK on_progress_report_callback;
    void* on_progress_report_context;
} PB_RESTORE_REQUEST;

int pb_restore_async(PB_RESTORE_REQUEST* request);

#endif // PARANOID_BACKUP_RESTORE_H