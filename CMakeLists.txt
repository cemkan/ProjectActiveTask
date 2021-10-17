# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("ProjectActiveTask" CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
target_compile_features(project_options INTERFACE cxx_std_11)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

add_library(project_warnings INTERFACE)

# enable cache system
#include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)

#conan config
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")
include(cmake/Conan.cmake)
run_conan()


# Include sub-projects.
add_subdirectory ("include/ActiveTask")
#
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests. ")
  add_subdirectory ("test")
endif()

if(ENABLE_FUZZING)
  message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  add_subdirectory(fuzz_test)
endif()

