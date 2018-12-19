cmake_minimum_required(VERSION 2.8.11)

project(paranoid_backup)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_subdirectory(deps)

include_directories(${PB_UTILS_INC_FOLDER} ./inc)

set(source_files
    ./inc/paranoid_backup.h
    ./inc/paranoid_backup_restore.h
    ./inc/storage_endpoint.h
    ./inc/paranoid_backup_restore.h
)

set(source_files
    ./src/paranoid_backup.c
    ./src/storage_endpoint.c
)

add_library(paranoid_backup ${source_files} ${header_files})

add_subdirectory(samples)
