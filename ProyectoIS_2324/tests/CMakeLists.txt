include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
# End GTest include code 

# Testing usuario library
add_executable(usuario_test usuario_test.cc)
target_link_libraries(usuario_test
 PRIVATE GTest::GTest usuario)
add_test(usuario_gtests usuario_test)

# Testing curso library
add_executable(curso_test curso_test.cc)
target_link_libraries(curso_test
 PRIVATE GTest::GTest curso)
add_test(curso_gtests curso_test)

# Testing bd library
add_executable(bd_test bd_test.cc)
target_link_libraries(bd_test
 PRIVATE GTest::GTest bd)
add_test(curso_gtests bd_test)

