cmake_minimum_required(VERSION 3.10)

project(PokerEngine) 

# Set the directory where the source files are
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

# Add executable to project using source files from the specified directory
add_executable(PokerEngineExe ${SOURCE_DIR}/main.cpp)  # Add other source files as needed

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
