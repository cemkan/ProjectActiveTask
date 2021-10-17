# ProjectActiveTask

[![pipeline status](https://gitlab.com/cemkan/ProjectActiveTask/badges/master/pipeline.svg)](https://gitlab.com/cemkan/ProjectActiveTask/-/commits/master)

Active Task is a header only library which provides exclusive thread to any class who inherit from it.

ActiveTask is a helper tool that abstracts thread implementation.

#Usage:
1. Inherit from ActiveTask
2. Call ExecuteOnMyThread!

Samples can be found on ActiveTaskTester.

Any function given as parameter to ExecuteOnMyThread will be executed on a task exclusive to the child task. This provides simple thread management:

#Use Cases:
- Create Worker Threads
- Release crucial tasks (like tasks that have strict timing needs) while accessing IO or doing excessive time consuming jobs.

#Running tests:
- Install Conan Packet Manager
- Install CMake
- fetch
- mkdir build
- cd build
- cmake ..
