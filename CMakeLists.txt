cmake_minimum_required(VERSION 3.26)

include_directories(CMAKE_CURRENT_SOURCE_DIR)

project(nanoxml_example)
set(CMAKE_CXX_STANDARD 23)

include_directories(src)

#########################
# Regarding the Library #
#########################
add_library(nanoxml STATIC                                                                                                            
        src/nanoxml.c
        src/nanoxml.h
        src/error.h
        src/error.c
)

################################
# Regarding the Client Program #
################################
add_executable(nanoxml_example
        example/nanoxml_example.c
)

target_link_libraries(nanoxml_example nanoxml)
