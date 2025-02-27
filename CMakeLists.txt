cmake_minimum_required(VERSION 3.5)

project(FirstProject VERSION 0.1 LANGUAGES CXX )

file(GLOB ALL_SOURCE
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(${PROJECT_NAME} ${ALL_SOURCE})

target_compile_definitions(FirstProject PUBLIC PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
