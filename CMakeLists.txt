
cmake_minimum_required(VERSION 3.20)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra)

set(FLTK_ROOT "C:/FLTK/bin")
find_package(FLTK REQUIRED)

set(TARGET "chess")

add_executable(
    ${TARGET}

    gui/main.cpp

    logic/Board.cpp
    logic/Game.cpp
    logic/History.cpp
    logic/Analyzer.cpp

    gui/fltk_wrapper/Graph.cpp
    gui/fltk_wrapper/GUI.cpp
    gui/fltk_wrapper/Window.cpp
    gui/fltk_wrapper/Resizable_window.cpp

    gui/BoardView.cpp
    gui/GameWindow.cpp
    gui/PromotionDialog.cpp
    gui/StatusPanel.cpp
)

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/logic
    ${CMAKE_SOURCE_DIR}/gui
    ${CMAKE_SOURCE_DIR}/gui/fltk_wrapper
    ${FLTK_INCLUDE_DIR}
)

target_link_directories(${TARGET} PRIVATE
    ${FLTK_INCLUDE_DIR}/../lib
)

target_link_libraries(${TARGET} PRIVATE
    ${FLTK_LIBRARIES}
    fltk_jpeg
    fltk_png
    fltk_z
    gdiplus
)
