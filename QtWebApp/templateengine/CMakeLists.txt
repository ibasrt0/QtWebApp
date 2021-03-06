set(templateengine_HEADERS
		template.h
		templatecache.h
		templateengineconfig.h
		templateloader.h
	)
set(templateengine_SOURCES
		template.cpp
		templatecache.cpp
		templateengineconfig.cpp
		templateloader.cpp
	)

add_library(QtWebAppTemplateEngine SHARED ${templateengine_HEADERS} ${templateengine_SOURCES})
target_include_directories(QtWebAppTemplateEngine PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include/qtwebapp/templateengine>
)
if (Qt5_FOUND)
    target_link_libraries(QtWebAppTemplateEngine QtWebAppGlobal Qt5::Core Qt5::Network)
else()
    target_link_libraries(QtWebAppTemplateEngine QtWebAppGlobal Qt4::QtCore Qt4::QtNetwork)
endif()
set_target_properties(QtWebAppTemplateEngine PROPERTIES
		VERSION ${qtwebapp_VERSION}
		SOVERSION ${qtwebapp_MAJOR}
	)

install(TARGETS QtWebAppTemplateEngine
        EXPORT QtWebAppTargets
		LIBRARY DESTINATION lib
		RUNTIME DESTINATION bin
		ARCHIVE DESTINATION lib)
install(FILES ${templateengine_HEADERS}
        DESTINATION include/qtwebapp/templateengine)
