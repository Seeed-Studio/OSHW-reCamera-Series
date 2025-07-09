link_directories("${CMAKE_CURRENT_LIST_DIR}")

component_register(
    COMPONENT_NAME main
    SRCS ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    PRIVATE_REQUIREDS cvi_rtsp sophgo

    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/"
    SRCS "${CMAKE_CURRENT_LIST_DIR}/rtsp_demo.c"
)
