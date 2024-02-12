cmake_minimum_required(VERSION 3.17)
project(QmlScreenSaver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
find_package(Qt${QT_VERSION} COMPONENTS Core qml Quick QuickControls2 Sql REQUIRED)

add_subdirectory("core")
add_subdirectory("app")

