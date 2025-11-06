include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    tests.cpp

)

target_include_directories(tests PRIVATE ../include)

target_link_libraries(tests 
    PRIVATE 
    gtest_main
    gmock
)

include(GoogleTest)
gtest_discover_tests(tests)