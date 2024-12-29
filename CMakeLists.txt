cmake_minimum_required(VERSION 3.16)

project(newtree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# добавляем поддержку ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(newtree main.cpp)

# линкуем ncurses
target_link_libraries(newtree ${CURSES_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS newtree
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
