cmake_minimum_required (VERSION 3.5.0)

project (raytracer LANGUAGES CXX)

#find_package(MPI REQUIRED)  # MPI exclusive

# Set to C++17
#set(CMAKE_CXX_COMPILER mpicxx)  # MPI exclusive
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source
set(EXTERNAL src/external/stb_image.h)

set(SRC 
    src/main.cpp
    src/vec.hpp
    src/vec.cpp
    src/point.hpp
    src/color.hpp
    src/color.cpp
    src/ray.hpp
    src/ray.cpp
    src/hittable.hpp
    src/hittable.cpp
    src/hittable_list.hpp
    src/hittable_list.cpp
    src/sphere.hpp
    src/sphere.cpp
    src/utils.hpp
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
#target_link_libraries(raytracer MPI::MPI_CXX)  # MPI exclusive