project(radioPlayer)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include( ${QT_USE_FILE} )

aux_source_directory(. SRC_LIST)

include_directories(
  /home/chorch/Proyectos/fmodstudioapi10601linux/api/lowlevel/inc
)

set(SOURCE_FILES
  #MainWindow.cpp
  ${SRC_LIST}
)

set(INCLUDE_FILES
  common.h
  common_platform.h
)

set(MOC_HEADER_FILES
  MainWindow.h
)

# this will run moc:
QT4_WRAP_CPP(MOC_SRC_FILES ${MOC_HEADER_FILES} )

link_directories(
  /home/chorch/Proyectos/fmodstudioapi10601linux/api/lowlevel/lib/x86
)

add_executable(${PROJECT_NAME}
  ${SRC_LIST}
  ${MOC_SRC_FILES}
)

target_link_libraries(${PROJECT_NAME}
  fmodL
  fmod
  pthread
  ${QT_LIBRARIES}
)
