cmake_minimum_required(VERSION 2.8.0)

project(nevil)

option(DEBUG "Enable debugging flags" OFF)
option(O "Enable optimization" OFF)
option(GUI "Build with GUI tools" OFF)

if(DEBUG)
  MESSAGE("Enabling Debugging")
  add_definitions(-g)
endif(DEBUG)

if(O)
  MESSAGE("Enabling Optimization")
  add_definitions(-O3 -DNDEBUG)
endif(O)

add_definitions(-std=c++11 -Wall)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
add_subdirectory(include/enki)
link_directories (${enki_BINARY_DIR})

include_directories(${enki_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)
file(GLOB JSON ${CMAKE_SOURCE_DIR}/include/json/jsoncpp.cpp)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*)
file(GLOB ARENA_SOURCES ${CMAKE_SOURCE_DIR}/src/arena/*)
file(GLOB CONTROLLER_SOURCES ${CMAKE_SOURCE_DIR}/src/robot_controller/*)
file(GLOB UTIL_SOURCES ${CMAKE_SOURCE_DIR}/src/util/*)


if (GUI)
  message("Building GUI mode")
  add_definitions(-DGUI)
  set(QT_USE_QTOPENGL TRUE)
  find_package(Qt4)
  if (QT4_FOUND)
    find_package(OpenGL REQUIRED)
    include(${QT_USE_FILE})
    add_definitions(${QT_DEFINITIONS})
    file(GLOB GUI_SOURCES "${CMAKE_SOURCE_DIR}/src/gui/*")
    add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${GUI_SOURCES} ${ARENA_SOURCES} ${CONTROLLER_SOURCES} ${UTIL_SOURCES} ${JSON})
    target_link_libraries(${CMAKE_PROJECT_NAME} enki enkiviewer ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
  endif (QT4_FOUND)
else(GUI)
  message("Building command line mode")
  find_package (Threads REQUIRED)
  file(GLOB PARALLEL_SOURCES "${CMAKE_SOURCE_DIR}/src/parallel/*")
  add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${PARALLEL_SOURCES} ${ARENA_SOURCES} ${CONTROLLER_SOURCES} ${UTIL_SOURCES} ${JSON})
  target_link_libraries(${CMAKE_PROJECT_NAME} enki ${CMAKE_THREAD_LIBS_INIT})
endif(GUI)
