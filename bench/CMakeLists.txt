add_executable(cpparm_bench
    bench_memcpy.cpp
    bench_vector_add.cpp
    bench_thunk.cpp
)

target_link_libraries(cpparm_bench PRIVATE
    arm_ops
    stl_ops
    benchmark::benchmark
    benchmark::benchmark_main
)
