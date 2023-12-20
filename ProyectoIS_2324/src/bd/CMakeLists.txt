add_library(bd bd.cc bd.h)
target_link_libraries(bd PUBLIC usuario curso)
target_include_directories(bd PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PROJECT_SOURCE_DIR}/src/usuario
    ${PROJECT_SOURCE_DIR}/src/curso)

target_link_libraries(bd PUBLIC usuario curso)