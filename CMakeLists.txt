cmake_minimum_required(VERSION 2.6)
project(brprint3d)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(brprint3d_SRCS brprint3d.cpp main.cpp)

qt4_automoc(${brprint3d_SRCS})
add_executable(brprint3d ${brprint3d_SRCS})
target_link_libraries(brprint3d ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS brprint3d RUNTIME DESTINATION bin)
