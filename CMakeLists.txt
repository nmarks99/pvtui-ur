cmake_minimum_required(VERSION 3.22)
project(pvtui-ur LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find pvtui
# Unless pvtui is installed in a standard location (e.g. /usr/lib)
# you'll need to set -Dpvtui_DIR=/path/to/lib/cmake/pvtui
find_package(pvtui REQUIRED)

# Add exectuble and link libraries
add_executable(pvtui_ur
    src/main.cpp
    src/dashboard.cpp
    src/status.cpp
    src/control.cpp
)
target_link_libraries(pvtui_ur PRIVATE pvtui::pvtui)
