project(GP-ng)
cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")
set(COMPILE_FLAGS "-std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(libGP)
add_subdirectory(Qt5Gui)


aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(GP-ng GPng)

