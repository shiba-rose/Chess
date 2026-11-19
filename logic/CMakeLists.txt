cmake_minimum_required(VERSION 3.16)
project(ChessLogic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Таргет 1: библиотека с логикой
add_library(chess_logic STATIC
    Board.cpp
    Analyzer.cpp 
    Game.cpp 
    History.cpp
)
target_include_directories(chess_logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Таргет 2: тестовый запуск (в init_for_tests.cpp должен быть main)
add_executable(logic_test init_for_tests.cpp)
target_link_libraries(logic_test PRIVATE chess_logic)

# Предупреждения
if(MSVC)
    target_compile_options(chess_logic PRIVATE /W4)
    target_compile_options(logic_test PRIVATE /W4)
else()
    target_compile_options(chess_logic PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(logic_test PRIVATE -Wall -Wextra -Wpedantic)
endif()