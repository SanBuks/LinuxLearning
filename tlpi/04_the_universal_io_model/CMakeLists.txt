project(04)

add_executable(io_test        code/io_test.cc)
target_link_libraries(io_test PUBLIC tlpi_header)

add_executable(seek_io        code/seek_io.cc)
target_link_libraries(seek_io PUBLIC tlpi_header)

add_executable(copy           code/copy.cc)
target_link_libraries(copy    PUBLIC tlpi_header)

add_executable(copy_file_hole        code/copy_file_hole.cc)
target_link_libraries(copy_file_hole PUBLIC tlpi_header)

