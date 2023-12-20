add_library(main main.cc funciones.h)
target_link_libraries(main PUBLIC bd)
target_include_directories(main PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PROJECT_SOURCE_DIR}/src/bd)

add_executable(display main.cc)
target_link_libraries(display PUBLIC bd)