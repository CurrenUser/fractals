cmake_minimum_required(VERSION 3.17.3 FATAL_ERROR)

set(PROJECT_NAME fractals)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
src/main.cpp
src/fractals.cpp
src/fractals.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

