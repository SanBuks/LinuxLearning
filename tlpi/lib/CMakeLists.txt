project (lib)
add_library (tlpi_header SHARED get_num.cc error_functions.cc)
target_include_directories(tlpi_header PUBLIC include)