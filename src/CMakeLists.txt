# src/CMakeLists.txt
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

# Project name and current version
project(rascam VERSION 0.1 LANGUAGES CXX)

# Enable general warnings
# See http://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Use 2017 C++ standard.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Creates the compile_commands.json used by editors for code completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Must use GNUInstallDirs to install libraries into correct locations on all platforms:
include(GNUInstallDirs)

# To allow 'make test' command.
enable_testing()

# Include all subdirectories that contain targets:
add_subdirectory(app)
add_subdirectory(lib)
