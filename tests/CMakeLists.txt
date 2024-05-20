include(GoogleTest)

file(GLOB test_sources src/*.cpp)

add_executable(tests ${test_sources})

target_link_libraries(tests PUBLIC
    GTest::gtest_main
)

gtest_discover_tests(tests)
