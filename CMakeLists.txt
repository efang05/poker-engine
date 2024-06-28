cmake_minimum_required(VERSION 3.10)

project(PokerBot)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(TestEvaluator
    src/evaluator_test.cpp
)

add_executable(PokerEngine
    src/main.cpp
    src/Game.cpp
    src/Evaluator.cpp
    src/MCCFR.cpp
    src/Strategy.cpp
)


target_include_directories(PokerEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)