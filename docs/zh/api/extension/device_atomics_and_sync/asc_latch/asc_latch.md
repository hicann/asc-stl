# 头文件 asc/latch

提供基于一次性倒计数的设备线程同步功能

## 使用方式

```cpp
#include <asc/latch>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::latch](latch.md) | 类模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::latch::arrive_and_wait](latch_arrive_and_wait.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::latch::count_down](latch_count_down.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::latch::latch](latch_latch.md) | 构造函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::latch::max](latch_max.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::latch::try_wait](latch_try_wait.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::latch::wait](latch_wait.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
