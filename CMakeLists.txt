project(raytracing-demo)
cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src CPP_SRC)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(rt_demo ${CPP_SRC})

