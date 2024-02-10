set ( RSC
        qml.qrc
        )


set(APP_SRC
        main.cpp
        )

QT5_ADD_RESOURCES(RSCS ${RSC})
add_executable(${PROJECT_NAME} ${APP_SRC} ${RSCS})
target_link_libraries(${PROJECT_NAME} core)
target_include_directories(${PROJECT_NAME} PRIVATE ../core)
