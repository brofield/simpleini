if(SIMPLEINI_USE_SYSTEM_GTEST)
	find_package(GTest REQUIRED)
else()
	include(FetchContent)
	# Force GoogleTest to use the same runtime library as our tests (MSVC)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_Declare(
		googletest
		DOWNLOAD_EXTRACT_TIMESTAMP ON
		URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
		URL_HASH SHA1=0ac421f2ec11af38b0fff0f1992184032731a8bc
		)
	FetchContent_MakeAvailable(googletest)
endif()

set(TEST_SOURCES
	ts-bugfix.cpp
	ts-noconvert.cpp
	ts-quotes.cpp
	ts-roundtrip.cpp
	ts-snippets.cpp
	ts-utf8.cpp
	ts-numeric.cpp
	ts-boolean.cpp
	ts-sections.cpp
	ts-deletion.cpp
	ts-edgecases.cpp
	ts-multiline.cpp
	ts-casesensitivity.cpp
)

# ts-wchar.cpp uses wchar_t which is primarily for Windows
if(WIN32)
	list(APPEND TEST_SOURCES ts-wchar.cpp)
endif()

add_executable(tests ${TEST_SOURCES})

# Enable precompiled headers for faster builds
target_precompile_headers(tests PRIVATE
	<string>
	<map>
	<list>
	<algorithm>
	"../SimpleIni.h"
)

add_test(NAME tests COMMAND tests)
target_link_libraries(tests PRIVATE ${PROJECT_NAME} GTest::gtest_main)

add_custom_command(
	TARGET tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_CURRENT_SOURCE_DIR}/example.ini
		${CMAKE_CURRENT_SOURCE_DIR}/tests.ini
		${CMAKE_CURRENT_BINARY_DIR})
