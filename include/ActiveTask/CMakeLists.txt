# CMakeList.txt : CMake project for ProjectActiveTask, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_library(ActiveTask INTERFACE)

message(STATUS "Adding ActiveTask HOL")
target_include_directories(ActiveTask INTERFACE .)

#target_include_directories(aaa INTERFACE
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#    $<INSTALL_INTERFACE:ActiveTask>
#)

# Add source to this project's executable.


# TODO: Add tests and install targets if needed.
