cmake_minimum_required(VERSION 3.25)
project(CreatePanorama)

set(CMAKE_CXX_STANDARD 20)

# Find OpenCV package
set(OpenCV_DIR "C:/msys64/ucrt64/lib/cmake/opencv4/opencv2")
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(CreatePanorama main.cpp ImageStitcher.cpp ImageStitcher.h)

# Link OpenCV libraries to the executable
target_link_libraries(CreatePanorama ${OpenCV_LIBS})
