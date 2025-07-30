#Minium cmake version.
cmake_minimum_required(VERSION 3.8)

# set project output directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#Project name. 
project(basic_OPEN_GL_PROJECT)

#set c++ standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#platform specific settings.
if(MSVC)
    add_compile_options(/W4 /WX)  # Enable warnings as errors
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)  # Enable warnings as errors
endif()

# Add subdirectories
add_subdirectory(src)       # Main executable