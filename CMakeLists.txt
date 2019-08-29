cmake_minimum_required(VERSION 3.14)
project(FileINIProject)

set(CMAKE_CXX_STANDARD 17)

#Comando che serve per creare un eseguibile del programma
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

#Path di inclusione del package BOOST per Windows
#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files (x86)/boost")
#SET(BOOST_INCLUDEDIR "C:/Program Files (x86)/boost/include")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files (x86)/boost/libs")

#Path di inclusione del package BOOST per Linux
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/opt/boost_1_70_0")
SET(BOOST_INCLUDE_DIR "/opt/boost_1_70_0/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/opt/boost_1_70_0/libs")

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

set(TEST_FILES Key.h CIniFile.h CIniFile.cpp TestCIniFile.cpp)
add_executable(CatchUnitTesting ${TEST_FILES})
add_executable(FileINIProject CIniFile.h Key.h CIniFile.cpp main.cpp)