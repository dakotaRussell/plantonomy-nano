add_library(Device Device.cpp)

target_include_directories(Device
			  INTERFACE
			  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
			  $<INSTALL_INTERFACE:include>
			)

target_link_libraries(Device PUBLIC CompilerFlags Comm)

set(InstallableLibs Device CompilerFlags)
install(TARGETS ${InstallableLibs} DESTINATION lib)
install(FILES Device.h
		DESTINATION include)
