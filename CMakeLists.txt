project(brprint3d)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_AUTOMOC ON)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
endif()

find_package(Qt5 REQUIRED COMPONENTS
                Core
                Test
                Quick
                Widgets
            )

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(qtModels_SRCS
    qt-models/bedmodel.cpp
    qt-models/bedobject.cpp
    qt-models/extruderobject.cpp
    qt-models/extrudermodel.cpp
    qt-models/connectobject.cpp
    qt-models/connectionmodel.cpp
    )
set(controllers_SRCS
    controllers/printercontroller.cpp
    )

set(brprint3d_SRCS
    src/brprint3d.cpp
    src/main.cpp
    src/gcodehighlighter.cpp
    src/gcodehandler.cpp
    )
qt5_add_resources(RESOURCES src/resources.qrc icons/icons.qrc)

add_executable(brprint3d ${brprint3d_SRCS} ${qtModels_SRCS} ${controllers_SRCS} ${RESOURCES})
qt5_use_modules(brprint3d Quick Core)
target_link_libraries(brprint3d Qt5::Core Qt5::Quick Qt5::Widgets)

#install(TARGETS brprint3d RUNTIME DESTINATION bin)
