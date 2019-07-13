cmake_minimum_required(VERSION 3.14)
project(FileINIProject)

set(CMAKE_CXX_STANDARD 14)

#Path di inclusione del package BOOST per Windows
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files (x86)/boost_1_70_0")
SET (BOOST_INCLUDEDIR "C:/Program Files (x86)/boost_1_70_0/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files (x86)/boost_1_70_0/libs")

#Path di inclusione del package BOOST per Linux
#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/opt/boost_1_70_0")
#SET (BOOST_INCLUDEDIR "/opt/boost_1_70_0/include")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/opt/boost_1_70_0/libs")

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

add_executable(FileINIProject main.cpp CIniFile.h Key.h CIniFile.cpp)
