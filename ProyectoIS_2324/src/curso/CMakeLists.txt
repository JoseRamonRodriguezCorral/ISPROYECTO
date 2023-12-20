add_library(curso curso.cc curso.h)
target_link_libraries(curso PUBLIC usuario)
target_include_directories(curso PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PROJECT_SOURCE_DIR}/src/usuario)

target_link_libraries(curso PUBLIC usuario)