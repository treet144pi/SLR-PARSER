cmake_minimum_required(VERSION 3.16)

project(SLRParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(FLEX REQUIRED)

FLEX_TARGET(
    Lexer
    lexer/lexer.l
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

add_library(slr_core
    src/parser.cpp
    src/outputstates.cpp
    src/slrbuild.cpp)

target_include_directories(slr_core PUBLIC include)

add_executable(slr_parser src/main.cpp ${FLEX_Lexer_OUTPUTS})
target_link_libraries(slr_parser slr_core)

add_executable(slr_tests tests/tests.cpp)
target_link_libraries(slr_tests slr_core)
