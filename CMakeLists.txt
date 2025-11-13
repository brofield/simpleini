cmake_minimum_required(VERSION 3.16)

project(
	SimpleIni
	VERSION 4.24
	DESCRIPTION "Cross-platform C++ library providing a simple API to read and write INI-style configuration files"
	LANGUAGES CXX C
)

option(SIMPLEINI_USE_SYSTEM_GTEST "Use system GoogleTest dependency" OFF)
option(SIMPLEINI_BUILD_TESTS "Build tests" ON)
option(SIMPLEINI_BUILD_EXAMPLES "Build examples" ON)

# disable in-source builds
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not allowed, use cmake -S . -B build.")
endif()

set(EXPORT_NAMESPACE "${PROJECT_NAME}::")
set(SIMPLEINI_HEADERS SimpleIni.h)

# ConvertUTF files are only needed on Windows for SI_CONVERT_WIN32
if(WIN32)
    list(APPEND SIMPLEINI_HEADERS ConvertUTF.h)
    set(SIMPLEINI_SOURCES ConvertUTF.c)
endif()

add_library(${PROJECT_NAME} INTERFACE)
add_library(${EXPORT_NAMESPACE}${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# On Windows, add ConvertUTF.c as a source file
if(WIN32)
    target_sources(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ConvertUTF.c>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ConvertUTF.c>
    )
endif()

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

install(FILES ${SIMPLEINI_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install ConvertUTF.c on Windows (needed for SI_CONVERT_WIN32)
if(WIN32)
    install(FILES ConvertUTF.c
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()

install(TARGETS ${PROJECT_NAME}
    EXPORT SimpleIniTargets
)

install(EXPORT SimpleIniTargets
    FILE SimpleIniTargets.cmake
    NAMESPACE SimpleIni::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimpleIni
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# only build tests when top level and testing enabled
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
	if(BUILD_TESTING)
		add_subdirectory(tests)
	endif()
endif()
