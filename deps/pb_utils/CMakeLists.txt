cmake_minimum_required(VERSION 2.8.11)

project(paranoid_backup_utils)

include_directories(./inc)

get_filename_component(PB_UTILS_FOLDER ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)
set(PB_UTILS_FOLDER "${PB_UTILS_FOLDER}" CACHE INTERNAL "" FORCE)
set(PB_UTILS_INC_FOLDER ${PB_UTILS_FOLDER}/inc CACHE INTERNAL "")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(source_files
    ./inc/logging.h
)

set(source_files
    ./src/logging.c
)

add_library(paranoid_backup_utils ${source_files} ${header_files})
