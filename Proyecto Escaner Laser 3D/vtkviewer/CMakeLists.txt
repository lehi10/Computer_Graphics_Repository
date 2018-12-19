cmake_minimum_required(VERSION 2.8)

PROJECT(GenericDataObjectReader)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(GenericDataObjectReader vtkviewer.cpp)

if(VTK_LIBRARIES)
  target_link_libraries(GenericDataObjectReader ${VTK_LIBRARIES})
else()
  target_link_libraries(GenericDataObjectReader vtkHybrid vtkWidgets)
endif()
