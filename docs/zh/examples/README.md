# API示例源码

本目录保存API参考页面引用的完整示例工程。API页面中的短调用片段用于说明单个接口；这里的完整源码用于验证对象生命周期、资源管理、Host与Device协作等需要完整上下文的场景。

- [allocator_traits与scoped_allocator_adaptor](allocator_traits.cpp)
- [显式分配器vector](explicit_allocator_vector.cpp)
- [指针对齐与pointer_traits](pointer_alignment.cpp)
- [Stream与Event](stream_event.cpp)
- [Warp集体操作](warp_collectives/CMakeLists.txt)
- [GM原子操作与屏障](atomic_operations/README.md)
- [GM与UB流水拷贝](pipeline_copy/README.md)
