project(Br-Print)

cmake_minimum_required(VERSION 3.2.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Svg Test LinguistTools OpenGL)

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

set(Widgets_SRCS
	Windows/aboutbrprint.cpp
	Windows/documentation.cpp
	Windows/help.cpp
	Windows/legalwarning.cpp
	Windows/loading.cpp
	Windows/warning.cpp
)

set(Br-Print_SRCS
	arduinolistener.cpp
	brprint3d.cpp
	glwidget.cpp
	main.cpp
	points.cpp
	threadRotine.cpp
)

qt5_add_translation(TRANSLATIONS EN_english.ts PT_portuguese.ts)

if(LINUX)
	install_files(TRANSLATIONS DESTINATION share/br-print/translations)
	add_custom_target(translations ALL DEPENDS ${TRANSLATIONS})
endif()

qt5_add_resources(Resources
#	translations.qrc
	fonts.qrc
	images.qrc
)
add_custom_target(resources ALL DEPENDS ${Resources})

#add_dependencies(resources translations)

add_executable(BRPrint ${KI_SRCS} ${Widgets_SRCS} ${Br-Print_SRCS} ${Resources})
target_link_libraries(BRPrint Qt5::Core Qt5::Widgets Qt5::Svg Qt5::OpenGL pthread ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

enable_testing()
