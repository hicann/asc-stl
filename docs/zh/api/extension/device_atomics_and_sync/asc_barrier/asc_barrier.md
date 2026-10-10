# 头文件 asc/barrier

提供线程块（Block）或设备（Device）作用域内的屏障同步功能

## 使用方式

```cpp
#include <asc/barrier>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::barrier](barrier.md) | 类模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::barrier::arrive](barrier_arrive.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::barrier::arrive_and_drop](barrier_arrive_and_drop.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::barrier::arrive_and_wait](barrier_arrive_and_wait.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::barrier::barrier](barrier_barrier.md) | 构造函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::barrier::max](barrier_max.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::barrier::wait](barrier_wait.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::barrier_arrival_token](barrier_arrival_token.md) | 类 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::init](init.md) | 函数模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
