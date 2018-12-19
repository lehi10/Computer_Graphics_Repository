cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(main)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



find_package(PCL 1.2 REQUIRED)
find_package( OpenCV REQUIRED )


include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(${PCL_INCLUDE_DIRS})


link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (main main.cpp)

target_link_libraries (main ${PCL_LIBRARIES})
target_link_libraries( main ${OpenCV_LIBS} )




    



