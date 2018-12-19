// Copyright (c) 2018 Scaboro da Silva, Ewerton. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "logging.h"
#include <stdarg.h>
#include <time.h>
#include <stdio.h>

void log_entry(LOGGING_LEVEL level, const char* format, ...)
{
    time_t now;
    va_list args;
    va_start(args, format);

    now = time(NULL);

    switch (level)
    {
        case LOGGING_LEVEL_INFO:
            (void)printf("[INFO]: ");
            break;
        case LOGGING_LEVEL_ERROR:
            (void)printf("[ERROR]: ");
            break;
        case LOGGING_LEVEL_WARNING:
            (void)printf("[WARN]: ");
            break;
        case LOGGING_LEVEL_TRACE:
            (void)printf("[TRACE]: ");
            break;
        default:
            break;
    }

    // (void)printf("Time:%.24s File:%s Func:%s Line:%d ", ctime(&t), file, func, line);
    (void)printf("Time:%.24s ", ctime(&now));

    va_end(args);

    (void)vprintf(format, args);
    (void)printf("\r\n");
}