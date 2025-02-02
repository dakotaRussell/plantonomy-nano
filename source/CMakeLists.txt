cmake_minimum_required(VERSION 3.10)
project(Plantonomy VERSION 1.0)

add_library(CompilerFlags INTERFACE)
target_compile_features(CompilerFlags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
target_compile_options(CompilerFlags INTERFACE
		 "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>")

add_subdirectory(comm)
add_subdirectory(devices)

add_executable(Plantonomy main.cpp)

target_link_libraries(Plantonomy 
			PUBLIC
			Comm
			CompilerFlags
			Device)

target_include_directories(Plantonomy PUBLIC
			   "${PROJECT_BINARY_DIR}"
			  )

set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "/Users/dakotarussell/Projects/Plantonomy/install")
install(TARGETS Plantonomy DESTINATION bin)
