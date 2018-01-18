cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

# SETUP DIRECTIORIES #
# Main output dir
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output DLLs into main folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

# ADD EXTERNAL DEPENDANCIES #
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

## PRACTICAL 1 ##
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

## SPACE INVADERS ##
file(GLOB_RECURSE SOURCES practical_2/*.cpp practical_2/*.h)
add_executable(PRACTICAL_2_INVADERS ${SOURCES})
target_include_directories(PRACTICAL_2_INVADERS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_2_INVADERS sfml-graphics)

## COPY RESOURCES ##
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" 											${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)
add_dependencies(PRACTICAL_2_INVADERS copy_resources)
