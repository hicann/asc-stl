# 头文件asc/std/barrier

提供可重复使用的同步屏障，使多个线程到达同一同步点后再继续执行

## 使用方式

```cpp
#include <asc/std/barrier>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::barrier](barrier.md) | 类模板 | C++17+ | Host、AI Core SIMT编程 | Ascend 950 |
| [asc::std::barrier::arrival_token](barrier_arrival_token.md) | 类 | C++17+ | Host、AI Core SIMT编程 | Ascend 950 |
| [asc::std::barrier::arrive](barrier_arrive.md) | 成员函数 | C++17+ | Host、AI Core SIMT编程 | Ascend 950 |
| [asc::std::barrier::arrive_and_drop](barrier_arrive_and_drop.md) | 成员函数 | C++17+ | Host、AI Core SIMT编程 | Ascend 950 |
| [asc::std::barrier::arrive_and_wait](barrier_arrive_and_wait.md) | 成员函数 | C++17+ | Host、AI Core SIMT编程 | Ascend 950 |
| [asc::std::barrier::barrier](barrier_barrier.md) | 构造函数 | C++17+ | Host、AI Core SIMT编程 | Ascend 950 |
| [asc::std::barrier::max](barrier_max.md) | 成员函数 | C++17+ | Host、AI Core SIMT编程 | Ascend 950 |
| [asc::std::barrier::wait](barrier_wait.md) | 成员函数 | C++17+ | Host、AI Core SIMT编程 | Ascend 950 |
