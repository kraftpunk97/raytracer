cmake_minimum_required ( VERSION 3.1.0)

project (raytracer LANGUAGES CXX)

# Set to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source

set(EXTERNAL src/external/stb_image.h)

set(SRC 
    src/main.cpp
)

include_directories(src)

message(STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message(STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message(STATUS "Debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})


# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
add_compile_options(-Wreorder) # Data member will be init after [other] data member
add_compile_options(-Wmaybe-uninitialized) # Variables improperly initialized
add_compile_options(-Wunused-variable) # Variable is defined but not used.
# endif()

add_executable(raytracer ${EXTERNAL} ${SRC})