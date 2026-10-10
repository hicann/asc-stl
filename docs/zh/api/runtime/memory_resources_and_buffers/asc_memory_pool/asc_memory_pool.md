# 头文件 asc/memory_pool

仅在Event完成后复用内存块，并支持内存回收和状态统计

## 使用方式

```cpp
#include <asc/memory_pool>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::device_memory_pool](device_memory_pool.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_pool_ref](device_memory_pool_ref.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::memory_pool_statistics](memory_pool_statistics.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_pool](pinned_memory_pool.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_pool_ref](pinned_memory_pool_ref.md) | 类 | C++17+ | Host | Ascend 950 |
