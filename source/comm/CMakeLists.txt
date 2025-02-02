add_library(Comm CommunicationProtocol.cpp
		I2C.cpp)

target_include_directories(Comm 
			  INTERFACE 
			  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
			  $<INSTALL_INTERFACE:include>
			 )

target_link_libraries(Comm PUBLIC CompilerFlags)

set(InstallableLibs Comm CompilerFlags)
install(TARGETS ${InstallableLibs} DESTINATION lib)
install(FILES CommunicationProtocol.h
		I2C.h
		DESTINATION include)