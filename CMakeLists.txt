cmake_minimum_required(VERSION 3.5)

project(FirstProject VERSION 0.1 LANGUAGES CXX )

file(GLOB ALL_SOURCE
	"${PROJECT_SOURCE_DIR}/Include/*.h"
	"${PROJECT_SOURCE_DIR}/Include/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.c"
)

configure_file(
	${CMAKE_SOURCE_DIR}/ProjectConfig.h.in
	${CMAKE_SOURCE_DIR}/ProjectConfig.h)

add_executable(${PROJECT_NAME} ${ALL_SOURCE})