file(GLOB CORE_SRC
        *.cpp)

add_library(core ${CORE_SRC})
target_link_libraries(core ${REQUIRED_LIBS_QUALIFIED})