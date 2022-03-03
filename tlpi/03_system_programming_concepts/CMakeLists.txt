project(03)

add_executable(get_libc_version code/get_libc_version.cc)
add_executable(confstr          code/confstr.cc)
add_executable(print_error      code/print_error.cc)
add_executable(stdarg_test      code/stdarg_test.cc)
add_executable(atexit           code/atexit_test.cc)
add_executable(my_strtol        code/my_strtol.cc)

add_executable(error_functions_test        code/error_functions_test.cc)
target_link_libraries(error_functions_test PUBLIC tlpi_header)
add_executable(get_num_test                code/get_num_test.cc)
target_link_libraries(get_num_test         PUBLIC tlpi_header)
add_executable(reboot_test                 code/reboot_test.cc)
target_link_libraries(reboot_test          PUBLIC tlpi_header)

