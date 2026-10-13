# 头文件asc/collectives

提供AI Core SIMT编程中的线程块归约、扫描、广播及条件判断，以及AI Core SIMD编程中的UB区间归约和扫描功能

## 使用方式

```cpp
#include <asc/collectives>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::block_all](block_all.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_any](block_any.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_broadcast](block_broadcast.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_collective_workspace](block_collective_workspace.md) | 类模板 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_collective_workspace::size](block_collective_workspace_size.md) | 成员函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_collective_workspace_bytes](block_collective_workspace_bytes.md) | 函数模板 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_exclusive_scan](block_exclusive_scan.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_inclusive_scan](block_inclusive_scan.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_reduce_add](block_reduce_add.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_reduce_max](block_reduce_max.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_reduce_min](block_reduce_min.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::make_block_collective_workspace](make_block_collective_workspace.md) | 函数模板 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::ub_exclusive_scan](ub_exclusive_scan.md) | 函数 | C++17+ | AI Core SIMD编程 | Ascend 950 |
| [asc::ub_inclusive_scan](ub_inclusive_scan.md) | 函数 | C++17+ | AI Core SIMD编程 | Ascend 950 |
| [asc::ub_reduce_add](ub_reduce_add.md) | 函数 | C++17+ | AI Core SIMD编程 | Ascend 950 |
| [asc::ub_reduce_max](ub_reduce_max.md) | 函数 | C++17+ | AI Core SIMD编程 | Ascend 950 |
| [asc::ub_reduce_min](ub_reduce_min.md) | 函数 | C++17+ | AI Core SIMD编程 | Ascend 950 |
