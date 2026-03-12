add_executable(cpparm_tests
    test_memcpy.cpp
    test_vector_add.cpp
    test_thunk.cpp
)

target_link_libraries(cpparm_tests PRIVATE
    arm_ops
    stl_ops
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cpparm_tests)
