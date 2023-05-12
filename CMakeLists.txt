cmake_minimum_required(VERSION 3.0)
project(Type263)

set(FLTK_DIR "D:/LABS/CODE/0001C/external/gcc/FLTK/CMake")

find_package(FLTK REQUIRED NO_MODULE)

ADD_LIBRARY(
    ${PROJECT_NAME} 
    SHARED 
    Type263.cpp
    )

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE 
    ${FLTK_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_LIST_DIR}/include
    )
    
target_link_libraries(
    ${PROJECT_NAME} 
    fltk 
    ${CMAKE_CURRENT_LIST_DIR}/Libs/TRNDll64.lib
    )