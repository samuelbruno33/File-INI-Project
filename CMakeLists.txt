cmake_minimum_required(VERSION 3.14)
project(FileINIProject)

set(CMAKE_CXX_STANDARD 17)

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

set(TEST_FILES Key.h CIniFile.h CIniFile.cpp TestCIniFile.cpp)
add_executable(CatchUnitTesting ${TEST_FILES})
add_executable(FileINIProject CIniFile.h Key.h CIniFile.cpp main.cpp)