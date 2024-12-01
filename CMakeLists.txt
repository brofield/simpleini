cmake_minimum_required(VERSION 3.14)

project(
	SimpleIni
	VERSION 4.22
	DESCRIPTION "Cross-platform C++ library providing a simple API to read and write INI-style configuration files"
	LANGUAGES CXX
)

option(SIMPLEINI_USE_SYSTEM_GTEST "Use system GoogleTest dependency" OFF)

# disable in-source builds
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not allowed, use cmake -S . -B build.")
endif()


# Define library paths and include directories
set(EXPORT_NAMESPACE "${PROJECT_NAME}::")
set(HEADERS SimpleIni.h)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${EXPORT_NAMESPACE}${PROJECT_NAME} ALIAS ${PROJECT_NAME})

include(GNUInstallDirs)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)
configure_package_config_file(${PROJECT_NAME}Config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}
)

install(FILES SimpleIni.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Targets
)

install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
	DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}
)
install(EXPORT ${PROJECT_NAME}Targets
	DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}
	NAMESPACE ${EXPORT_NAMESPACE}
)

target_include_directories(${PROJECT_NAME} INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# only build tests when top level and testing enabled
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
	if(BUILD_TESTING)
		add_subdirectory(tests)
	endif()
endif()
