cmake_minimum_required(VERSION 3.10)

project(PokerBot)

set(CMAKE_CXX_STANDARD 17)

# add_executable(PokerBot
#     src/generate_table.cpp
#     src/pokerlib.cpp
#     src/mtrand.cpp
# )

# # GenerateTable executable
# add_executable(GenerateTable src/stdafx.cpp src/generate_table.cpp src/pokerlib.cpp src/mtrand.cpp)

# Test executable
add_executable(PokerBot src/evaluator_test.cpp)

# Include directories for headers
# target_include_directories(GenerateTable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(PokerBot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})