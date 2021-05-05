# CMakeList.txt : CMake project for ProjectActiveTask, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.

add_executable (gtester "test.cpp")



# TODO: Add tests and install targets if needed.

target_link_libraries(gtester PRIVATE ActiveTask)
target_link_libraries(gtester PRIVATE CONAN_PKG::gtest)

#target_link_libraries(ProjectActiveTask PRIVATE active-task-header)