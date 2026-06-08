cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME asides)

project(${PROJECT_NAME} VERSION 0.1.0)

find_package(libCellML REQUIRED)

set(_PART_SRC understanding_collections.cpp)

add_executable(understanding_collections ${_PART_SRC})
target_link_libraries(understanding_collections PUBLIC cellml)

set(_PART_SRC understanding_units.cpp)

add_executable(understanding_units ${_PART_SRC})
target_link_libraries(understanding_units PUBLIC cellml)
