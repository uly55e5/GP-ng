set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)

set(EXECUTABLE_NAME GPQt)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

file(GLOB UI_SRCS *.ui)
aux_source_directory(. QAPP_SRC_LIST)
qt5_wrap_ui(QAPP_UI_HEADERS ${UI_SRCS})



add_executable(${EXECUTABLE_NAME} ${QAPP_SRC_LIST} ${QAPP_UI_HEADERS})
target_link_libraries(${EXECUTABLE_NAME} GPng Qt5::Widgets)
