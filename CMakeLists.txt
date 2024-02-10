cmake_minimum_required(VERSION 3.17)
project(QmlScreenSaver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui qml Quick QuickControls2)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick Qt5::QuickControls2)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_subdirectory("core")
add_subdirectory("app")

