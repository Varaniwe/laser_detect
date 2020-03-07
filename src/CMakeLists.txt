cmake_minimum_required (VERSION 2.6)
project (laser_detect)

set (laser_detect_VERSION_MAJOR 1)
set (laser_detect_VERSION_MINOR 0)
set (OPENCV_DIR "$ENV{OPENCV_DIR}")

string(REGEX REPLACE "\\." "" CV_VER "${OpenCV_VERSION}")

include_directories("${PROJECT_SOURCE_DIR}/..")
include_directories("${OPENCV_DIR}/include")

LINK_DIRECTORIES("${OPENCV_DIR}/${OpenCV_ARCH}/${OpenCV_RUNTIME}/lib")

add_executable(laser_detect main.cpp
							detection.cpp detection.h
							hsv_detection.cpp hsv_detection.h
							parse_args.cpp parse_args.h)
							
TARGET_LINK_LIBRARIES(laser_detect	debug	opencv_world${CV_VER}d
									optimized	opencv_world${CV_VER})
									

set(FFMPEG_DLL ${OPENCV_DIR}/${OpenCV_ARCH}/${OpenCV_RUNTIME}/bin/opencv_videoio_ffmpeg${CV_VER}.dll)
if (EXISTS ${FFMPEG_DLL})
	ADD_CUSTOM_COMMAND (TARGET laser_detect POST_BUILD	COMMAND ${CMAKE_COMMAND} -E copy_if_different 
						${FFMPEG_DLL}
						"$<TARGET_FILE_DIR:${PROJECT_NAME}>")
else()
# You can also use other version of Ffmpeg plugin from ${OPENCV_DIR}/${OpenCV_ARCH}/${OpenCV_RUNTIME}/bin
	message(WARNING "${FFMPEG_DLL} not found. It can cause errors with video decoding.")
endif()			
				
ADD_CUSTOM_COMMAND (TARGET laser_detect POST_BUILD	COMMAND ${CMAKE_COMMAND} -E copy_if_different 
					${OPENCV_DIR}/${OpenCV_ARCH}/${OpenCV_RUNTIME}/bin/opencv_world${CV_VER}$<$<CONFIG:debug>:d>.dll
					"$<TARGET_FILE_DIR:${PROJECT_NAME}>")
