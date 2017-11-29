cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

# Local source files here
SET(TARGET_SRC
    ${CMAKE_SOURCE_DIR}/pid/pid.cpp
)
add_library(pid ${TARGET_SRC})

add_executable(pidSim main.cpp)
target_link_libraries(pidSim pid)
