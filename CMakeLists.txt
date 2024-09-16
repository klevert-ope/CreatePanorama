cmake_minimum_required(VERSION 3.25)
project(CreatePanorama)

set(CMAKE_CXX_STANDARD 20)

# Find OpenCV package
set(OpenCV_DIR "C:\\tools\\opencv\\mingw_build")
find_package(OpenCV REQUIRED)

# Include directories

include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(CreatePanorama main.cpp ImageStitcher.cpp ImageStitcher.h)

# Link OpenCV libraries to the executable
target_link_libraries(CreatePanorama
        ${OpenCV_LIBS}
        opencv_core
        opencv_imgcodecs
        opencv_imgproc
        opencv_stitching
        )

