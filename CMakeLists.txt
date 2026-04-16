cmake_minimum_required(VERSION 3.22)
project(pvtui-ur LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(FETCH_PVTUI "Fetch and build pvtui (and FTXUI) via FetchContent" ON)

if(FETCH_PVTUI)
    include(FetchContent)
    set(BUILD_APPS OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(BUILD_DOCS OFF CACHE BOOL "" FORCE)
    message(STATUS "Fetching pvtui using FetchContent")
    FetchContent_Declare(pvtui
        GIT_REPOSITORY https://github.com/BCDA-APS/pvtui.git
        GIT_TAG        master
        GIT_SHALLOW    TRUE
    )
    FetchContent_MakeAvailable(pvtui)
else()
    find_package(pvtui REQUIRED)
endif()

# Add executable and link libraries
add_executable(pvtui_ur
    src/main.cpp
    src/dashboard.cpp
    src/status.cpp
    src/control.cpp
    src/io.cpp
    src/gripper.cpp
)
target_link_libraries(pvtui_ur PRIVATE pvtui::pvtui)
