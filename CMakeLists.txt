cmake_minimum_required(VERSION 3.1)

project(FirstProject VERSION 0.1 LANGUAGES CXX )

set(SOURCES
	Include/Read_BMP.hpp
	Src/main.cpp
	Src/Read_BMP.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})