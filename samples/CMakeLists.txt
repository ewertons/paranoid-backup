cmake_minimum_required(VERSION 2.8.11)

project(paranoid_backup_sample)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(source_files
)

set(source_files
    ./main.c
)

add_executable(paranoid_backup_sample ${source_files} ${header_files})

target_link_libraries(paranoid_backup_sample 
    paranoid_backup
    paranoid_backup_utils
)
