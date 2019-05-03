cmake_minimum_required(VERSION 3.8)
project(Semaphore)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES calc/main.c)
set(SOURCE_FILES tool/main.c)
add_executable(SemaphoreCalc calc/main.c params.h)
add_executable(SemaphoreTool tool/main.c params.h)