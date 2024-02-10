file(GLOB CORE_SRC
        *.cpp)

add_library(core ${CORE_SRC} Record.h RecordModel.cpp RecordModel.h)
target_link_libraries(core ${REQUIRED_LIBS_QUALIFIED})