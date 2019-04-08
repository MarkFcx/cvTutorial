cmake_minimum_required(VERSION 2.8)
PROJECT(AIBone)

set(CMAKE_CXX_STANDARD 11)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

# Instruct CMake to run moc, rcc automatically when needed.

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED QUIET)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5PrintSupport)
find_package(Qt5OpenGL)
#find_package(Qt5Declarative)
#find_package(Qt5MacExtras)

# Find OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES src/**/*.ui)
file(GLOB QT_WRAP src/**/*.h)
file(GLOB CPP_FILES src/**/*.cpp src/main.cpp )

qt5_wrap_ui(UISrcs ${UI_FILES})

#add_executable(AIBone ${CPP_FILES} ${UISrcs} ${QT_WRAP})

add_executable(AIBone MACOSX_BUNDLE ${CPP_FILES} ${UISrcs} ${QT_WRAP} src/ui/icons.qrc)
qt5_use_modules(AIBone Core Gui Widgets OpenGL PrintSupport)

#target_link_libraries(AIBone ${Glue} ${VTK_LIBRARIES})

target_link_libraries(AIBone ${VTK_LIBRARIES} ${OpenCV_LIBS})
