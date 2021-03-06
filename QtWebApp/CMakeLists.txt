cmake_minimum_required(VERSION 3.1)
project(QtWebApp CXX)

set(qtwebapp_MAJOR 1)
set(qtwebapp_MINOR 7)
set(qtwebapp_PATCH 3)
set(qtwebapp_VERSION ${qtwebapp_MAJOR}.${qtwebapp_MINOR}.${qtwebapp_PATCH})

find_package(Qt5 COMPONENTS Core Network)
if (NOT Qt5_FOUND)
    find_package(Qt4 REQUIRED COMPONENTS QtCore QtNetwork)
endif()

set(CMAKE_AUTOMOC ON)

add_definitions(-DQTWEBAPPLIB_EXPORT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
	set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Werror=format -Werror=return-type")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=format -Werror=return-type")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	if(MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
	else()
		# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=undefined")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
	endif()
	add_definitions("-D_GLIBCXX_DEBUG")
	add_definitions("-DQT_SHAREDPOINTER_TRACK_POINTERS")
	add_definitions("-DCMAKE_DEBUG")
	add_definitions("-DSUPERVERBOSE")
endif()
add_definitions("-DCMAKE_QTWEBAPP_SO")

configure_file(qtwebappglobal.h.in qtwebappglobal.h @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qtwebappglobal.h
	    DESTINATION include/qtwebapp/)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(QtWebAppGlobal SHARED qtwebappglobal.cpp)
target_include_directories(QtWebAppGlobal PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include/qtwebapp>
)
if (Qt5_FOUND)
    target_link_libraries(QtWebAppGlobal Qt5::Core)
else()
    target_link_libraries(QtWebAppGlobal Qt4::QtCore)
endif()
set_target_properties(QtWebAppGlobal PROPERTIES
		VERSION ${qtwebapp_VERSION}
		SOVERSION ${qtwebapp_MAJOR}
	)
install(TARGETS QtWebAppGlobal
		EXPORT QtWebAppTargets
		LIBRARY DESTINATION lib
		RUNTIME DESTINATION bin
		ARCHIVE DESTINATION lib)

add_subdirectory(logging)
add_subdirectory(httpserver)
add_subdirectory(templateengine)

configure_file(cmake/QtWebAppConfig.cmake.in        QtWebAppConfig.cmake        @ONLY)
configure_file(cmake/QtWebAppConfigVersion.cmake.in QtWebAppConfigVersion.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtWebAppConfig.cmake
	          ${CMAKE_CURRENT_BINARY_DIR}/QtWebAppConfigVersion.cmake
        DESTINATION lib/cmake/QtWebApp)


install(EXPORT QtWebAppTargets
		DESTINATION lib/cmake/QtWebApp)
