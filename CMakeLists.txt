project(Br-Print)

cmake_minimum_required(VERSION 2.8.0)
set(CMAKE_AUTOMOC ON)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
endif()

find_package(VTK 6.0 REQUIRED vtkChartsCore vtkGUISupportQt vtkViewsContext2D vtkIOGeometry NO_MODULE)
find_package(OpenGL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Test LinguistTools OpenGL SerialPort)

include(${VTK_USE_FILE})
include_directories(.
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_BINARY_DIR}
	KI
        Dialogs
)

# compile the KI library for 3D printer communication
set(KI_SRCS
	KI/Arduino_Serial.cpp
	KI/File_Queue.cpp
	KI/Repetier.cpp
	KI/StringRepetierOps.cpp
)
add_library(KI STATIC ${KI_SRCS})
target_link_libraries(KI -lpthread)

set(Dialogs_UI
	Dialogs/help.ui
	Dialogs/legalwarning.ui
	Dialogs/aboutbrprint.ui
	Dialogs/warning.ui
	Dialogs/documentation.ui
)
qt5_wrap_ui(Dialog_UI_SRCS ${Dialogs_UI})

set(Dialogs_SRCS
	Dialogs/aboutbrprint.cpp
	Dialogs/documentation.cpp
	Dialogs/help.cpp
        Dialogs/legalwarning.cpp
	Dialogs/warning.cpp
	${Dialog_UI_SRCS}
)

add_library(BRPrintDialogs STATIC ${Dialogs_SRCS})
target_link_libraries(BRPrintDialogs Qt5::Widgets)

set(BRPrintInterface_UI
	PrinterSettingsWidget.ui
	ExtruderControlWidget.ui
	ManualControlWidget.ui
	MainWindow.ui
        widgets/extruderitem.ui
)
qt5_wrap_ui(BRPrintInterface_UI_SRCS ${BRPrintInterface_UI})
set(BRPrintInterface_SRCS
        MainWindow.cpp
        vtkWidget.cpp
        PrinterSettingsWidget.cpp
        ManualControlWidget.cpp
        ExtruderControlWidget.cpp
        BigButton.cpp
        FilCount.cpp
	widgets/colorslider.cpp
        widgets/extruderitem.cpp
	${BRPRintInterface_UI_SRCS}
)

add_library(BRPRintInterface STATIC ${BRPrintInterface_SRCS} ${BRPrintInterface_UI_SRCS})

target_link_libraries(BRPRintInterface BRPrintDialogs KI Qt5::Widgets Qt5::SerialPort ${VTK_LIBRARIES})

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

add_executable(BRPrint main.cpp ${Resources} ${Dialog_UI_SRCS})

target_link_libraries(BRPrint Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::SerialPort ${OPENGL_LIBRARIES} ${VTK_LIBRARIES} BRPrintDialogs BRPRintInterface -lpthread)

add_executable(BRPrintWidgets widgets/main.cpp widgets/colorslider.cpp widgets/extruderitem.cpp ${Resources})
target_link_libraries(BRPrintWidgets Qt5::Widgets)

enable_testing()
