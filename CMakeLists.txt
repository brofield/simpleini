cmake_minimum_required(VERSION 3.14)

project(
	SimpleIni
	VERSION 4.20
	DESCRIPTION "Cross-platform C++ library providing a simple API to read and write INI-style configuration files"
	LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(IS_TOPLEVEL_PROJECT TRUE)
else()
	set(IS_TOPLEVEL_PROJECT FALSE)
endif()

# Disable in-source builds:
get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

if("${srcdir}" STREQUAL "${bindir}")
	message("")
	message("ERROR:: in-source builds are disabled!")
	message("Run cmake in a separate build directory:")
	message("$ cmake -S . -B build")
	message("")
	message(FATAL_ERROR "Aborting...")
endif()

# Define library paths and include directories
set(EXPORT_NAMESPACE "${PROJECT_NAME}::")
set(HEADERS SimpleIni.h)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${EXPORT_NAMESPACE}${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE .)

