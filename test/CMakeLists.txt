# CMakeList.txt : CMake project for ProjectActiveTask, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.




# TODO: Add tests and install targets if needed.

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("Building with GNU, including coverage")
    add_compile_options("--coverage")
    add_executable (gtester "test.cpp")
    target_link_libraries(gtester PRIVATE ActiveTask CONAN_PKG::gtest gcov)
else()
    message("Skipping coverage")
    add_executable (gtester "test.cpp")
    target_link_libraries(gtester PRIVATE project_options project_warnings ActiveTask CONAN_PKG::gtest)
endif()



#target_link_libraries(gtester PRIVATE ActiveTask)

#target_link_libraries(gtester PRIVATE CONAN_PKG::gtest)
