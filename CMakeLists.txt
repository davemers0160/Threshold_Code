# ----------------------------------------------------------------------------
#  Root CMake file for Threshold_Test_Project
# ----------------------------------------------------------------------------
#
# Example CMake build line for windows & VS2015
# windows: cmake -G "Visual Studio 14 2015 Win64"  ..
# linux: cmake ..

# To compile:
# windows: cmake --build . --config Release
# linux: cmake --build . --config Release -- -j8
#

cmake_minimum_required(VERSION 2.8.12)

PROJECT(Threshold_Test_Project)

set (exe_name "thresh_test")

include_directories("include")

file(GLOB source_files "src/*.c" 
		  source_files "src/*.cpp" 
          )	


message("")
message("--------------------------------------------------------")
message("SOURCES: ")
message(${source_files})
message("--------------------------------------------------------")
message("")


# find OpenCV
find_package(OpenCV REQUIRED)

if (OpenCV_FOUND)
	#list (APPEND DFD_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS})
	ADD_EXECUTABLE(${exe_name} ${source_files})
	TARGET_LINK_LIBRARIES(${exe_name} ${OpenCV_LIBS})

	if(MSVC AND (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.6.0"))
		set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${exe_name})
	endif()
	
else()
	message("OpenCV not found, so we won't build the project.")
endif()


message("Build Complete!")
message(" ")


