file(GLOB LIB_SOURCES *.cpp)

include(FindTIFF)

add_library(GPng SHARED ${LIB_SOURCES})

target_link_libraries(GPng ${TIFF_LIBRARIES})
