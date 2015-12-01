project(Br-Print)

cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
endif()

find_package(VTK 6.0 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Test LinguistTools OpenGL)
include(${VTK_USE_FILE})
include_directories(.
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_BINARY_DIR}
	KI
	Windows
)

# compile the KI library for 3D printer communication
set(KI_SRCS
	KI/Arduino_Serial.cpp
	KI/File_Queue.cpp
	KI/Repetier.cpp
	KI/StringRepetierOps.cpp
)
add_library(KI STATIC ${KI_SRCS})

set(Dialogs_SRCS
	Dialogs/aboutbrprint.cpp
	Dialogs/documentation.cpp
	Dialogs/help.cpp
	Dialogs/legalwarning.cpp
	Dialogs/loading.cpp
	Dialogs/warning.cpp
)
add_library(BRPrintDialogs STATIC ${Dialogs_SRCS})
target_link_libraries(BRPrintDialogs Qt5::Widgets)

set(BRPrintInterface_SRCS
	arduinolistener.cpp
	brprint3d.cpp
	vtkWidget.cpp
        PrinterSettingsWidget.cpp
        PrinterSettings.cpp
        ManualControlWidget.cpp
        ExtruderControlWidget.cpp
        BigButton.cpp
        FilCount.cpp
)
add_library(BRPRintInterface STATIC ${BRPrintInterface_SRCS})
target_link_libraries(BRPRintInterface KI Qt5::Widgets)

#qt5_add_translation(TRANSLATIONS EN_english.ts PT_portuguese.ts)

if(LINUX)
	install_files(TRANSLATIONS DESTINATION share/br-print/translations)
	add_custom_target(translations ALL DEPENDS ${TRANSLATIONS})
endif()

qt5_add_resources(Resources
    resources.qrc
)
add_custom_target(resources ALL DEPENDS ${Resources})

#add_dependencies(resources translations)

add_executable(BRPrint main.cpp ${Resources})

target_link_libraries(BRPrint Qt5::Core Qt5::Widgets Qt5::OpenGL ${OPENGL_LIBRARIES} ${VTK_LIBRARIES} BRPrintDialogs BRPRintInterface)

enable_testing()
