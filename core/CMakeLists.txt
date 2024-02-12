file(GLOB CORE_SRC
        *.cpp)

set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Qml Qt5::Quick Qt5::QuickControls2 Qt5::Sql)

add_library(core ${CORE_SRC})
target_link_libraries(core ${REQUIRED_LIBS_QUALIFIED})