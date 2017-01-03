project(pbkp)

include_directories(./inc)

SET (h_files
	./inc/file-attributes.h
	./inc/file_info.h
	./inc/filesystem.h
	./inc/filesystem_tree.h
	./inc/double_linked_list.h
	./inc/merge_sort.h
)

SET (c_files
    ./src/double_linked_list.c
    ./src/merge_sort.c
	./src/file_info.c
	./src/filesystem_tree.c
)

IF (WIN32)
	set (c_files
	    ${c_files}
		./src/file-attributes-win32.c
		./src/filesystem_win32.c
	)
ELSE()
	set (c_files
	    ${c_files}
		./src/file-attributes-linux.c
		./src/filesystem_linux.c
	)
ENDIF()

add_executable(pbkp ./src/main.c ${c_files} ${h_files})