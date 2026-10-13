# 头文件asc/memory

提供GM和UB非拥有内存视图、内存空间属性查询以及对齐辅助功能

## 使用方式

```cpp
#include <asc/memory>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::aligned_size](aligned_size.md) | 函数模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::arena_allocator](arena_allocator.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::gm_span](gm_span.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_aligned](is_aligned.md) | 函数模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::memory_space](memory_space.md) | 枚举 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::memory_space_of](memory_space_of.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::memory_space_of_v](memory_space_of_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::monotonic_arena](monotonic_arena.md) | 类 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::pointer_attributes](pointer_attributes.md) | 类 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::temporary_storage_ref](temporary_storage_ref.md) | 类 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::ub_span](ub_span.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
