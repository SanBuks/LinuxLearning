project(05)

add_executable(bad_exclusive_open        code/bad_exclusive_open.cc)
target_link_libraries(bad_exclusive_open PUBLIC tlpi_header)

add_executable(t_fcntl                   code/t_fcntl.cc)
target_link_libraries(t_fcntl            PUBLIC tlpi_header)

add_executable(t_dup                     code/t_dup.cc)
target_link_libraries(t_dup              PUBLIC tlpi_header)

add_executable(t_readv                   code/t_readv.cc)
target_link_libraries(t_readv            PUBLIC tlpi_header)

add_executable(t_truncate                code/t_truncate.cc)
target_link_libraries(t_truncate         PUBLIC tlpi_header)

add_executable(large_file                code/large_file.cc)
target_link_libraries(large_file         PUBLIC tlpi_header)
