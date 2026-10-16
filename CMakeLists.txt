cmake_minimum_required(VERSION 3.14)
project(example1 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LOG_VERBOSITY SPDLOG_LEVEL_DEBUG CACHE STRING "Log level verbosity")

set(CMAKE_CXX_STANDARD 17)

set(ENABLE_TEST ON CACHE BOOL "Enable project testing")
set(LOG_VERBOSITY SPDLOG_LEVEL_DEBUG CACHE STRING "Log level verbosity")
set(ENABLE_LINKER_LTO ON CACHE BOOL "Enable the Link time optimizer")


set(COMPILATION_FLAGS -ggdb -Wall -Wextra -Wconversion -Wno-sign-conversion -Wpedantic -Wnon-virtual-dtor -Woverloaded-virtual -Wreorder -Wuninitialized -fsanitize=undefined -DSPDLOG_ACTIVE_LEVEL=${LOG_VERBOSITY}  CACHE STRING "Compilation flags")
set(LINK_SANITIZER ubsan CACHE STRING "Link to sanitizer")
set(LINK_FLAGS -fsanitize=undefined CACHE STRING "Linker flags for sanitizer")
set(LIBRARY_BUILD "SHARED" CACHE STRING "SHARED or STATIC library build")

separate_arguments(COMPILATION_FLAGS UNIX_COMMAND "${COMPILATION_FLAGS}")



add_executable( testphy  
    src/main.cpp 
    src/car.cpp 
    src/car.hpp 
    src/world.cpp 
    src/world.hpp 
    src/utils.hpp
)

