#
# CMakeLists.txt -- zip module
#
# Copyright (c) 2013-2018 David Demelier <markand@malikania.fr>
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#

cmake_minimum_required(VERSION 3.5)
project(zip)

set(ZIP_VERSION_MAJOR "2")
set(ZIP_VERSION_MINOR "0")
set(ZIP_VERSION_PATCH "0")
set(ZIP_VERSION "${ZIP_VERSION_MAJOR}.${ZIP_VERSION_MINOR}.${ZIP_VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${zip_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED unit_test_framework)
find_package(Doxygen QUIET)
find_package(ZIP REQUIRED)

enable_testing()
add_executable(
	zip
	${zip_SOURCE_DIR}/zip.hpp
	${zip_SOURCE_DIR}/test/main.cpp
	${zip_SOURCE_DIR}/INSTALL.md
	${zip_SOURCE_DIR}/LICENSE.md
	${zip_SOURCE_DIR}/README.md
)
target_link_libraries(zip ${ZIP_LIBRARIES} Boost::unit_test_framework)
target_include_directories(zip PRIVATE ${zip_SOURCE_DIR} ${ZIP_INCLUDE_DIRS})
target_compile_definitions(
	zip
	PRIVATE
		BOOST_TEST_DYN_LINK
		DIRECTORY=\"${zip_SOURCE_DIR}/test/data/\"
)
add_test(NAME zip COMMAND zip)

if (DOXYGEN_FOUND)
	set(DOXYGEN_PROJECT_NAME zip)
	set(DOXYGEN_PROJECT_NUMBER ${ZIP_VERSION})
	set(DOXYGEN_STRIP_FROM_PATH ${zip_SOURCE_DIR})
	set(DOXYGEN_WARN_NO_PARAMDOC YES)
	set(DOXYGEN_WARN_AS_ERROR YES)
	set(DOXYGEN_QUIET YES)

	doxygen_add_docs(
		doxygen
		${zip_SOURCE_DIR}/doc/mainpage.cpp
		${zip_SOURCE_DIR}/zip.hpp
		WORKING_DIRECTORY ${zip_SOURCE_DIR}
	)

	add_dependencies(zip doxygen)
endif ()
