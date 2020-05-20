cmake_minimum_required(VERSION 3.9)

project(Gravity)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(EXECUTABLE_NAME "Gravity")
add_executable(${EXECUTABLE_NAME} main.cpp Planet.cpp Planet.h Entry.cpp Entry.h functions.cpp functions.h Vector2D.cpp Vector2D.h)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")

find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

