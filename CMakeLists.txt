cmake_minimum_required(VERSION 3.27)
project(sw_battle_test)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/ftxui)
include_directories(external/ftxui/include)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
add_executable(sw_battle_test ${SOURCES})

target_include_directories(sw_battle_test PUBLIC src/)

target_link_libraries(sw_battle_test PRIVATE
    ftxui::component
    ftxui::dom
    ftxui::screen
)
