project(radioPlayer)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(Qt4 REQUIRED)
include( ${QT_USE_FILE} )

set(SRC_DIR ./src/)

aux_source_directory(./${SRC_DIR} SRC_LIST)

include_directories(
  /home/chorch/Proyectos/fmodstudioapi10601linux/api/lowlevel/inc
  .
)

set(SOURCE_FILES
  ${SRC_LIST}
)

set(FMOD_SOURCE_FILES
  ./fmod/common.cpp
  ./fmod/common_platform.cpp
)

set(MOC_HEADER_FILES
  ${SRC_DIR}MainWindow.h
  ${SRC_DIR}AddRadioDialog.h
)

# this will run moc:
QT4_WRAP_CPP(MOC_SRC_FILES ${MOC_HEADER_FILES} )

link_directories(
  /home/chorch/Proyectos/fmodstudioapi10601linux/api/lowlevel/lib/x86
)

add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${MOC_SRC_FILES}
  ${FMOD_SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}
  fmodL
  fmod
  pthread
  ${QT_LIBRARIES}
)
