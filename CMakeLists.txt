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

add_subdirectory("3rd party")
add_subdirectory("tests")
add_subdirectory("core")
add_subdirectory("app")

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt5_9/5.15.0/msvc2019_64/lib/cmake")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

