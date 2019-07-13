cmake_minimum_required(VERSION 3.14)
project(FileINIProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(FileINIProject main.cpp CIniFile.h Key.h CIniFile.cpp)