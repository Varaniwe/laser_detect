cmake_minimum_required (VERSION 2.6)

project(laser_detect)

set (OpenCV_INCLUDEDIR    "$ENV{OPENCV_DIR}/include")
find_package(OpenCV REQUIRED)

add_subdirectory(src)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(laser_detect PROPERTIES FOLDER project)

if(${CMAKE_VERSION} VERSION_GREATER "3.6.0" OR ${CMAKE_VERSION} VERSION_EQUAL "3.6.0") 
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT laser_detect)
endif()