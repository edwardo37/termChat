cmake_minimum_required(VERSION 3.21.0)
project(termChat VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CURSES_USE_NCURSESW TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

add_executable(termChat main.cpp
    App.cpp
    Controller.cpp
    Model.cpp
    ViewNcursesImpl.cpp
)
target_include_directories(termChat PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(termChat PRIVATE ${CURSES_LIBRARIES})
