# 头文件 asc/std/latch

提供一次性倒计数同步功能；计数递减至零后，等待的线程可以继续执行

## 使用方式

```cpp
#include <asc/std/latch>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::latch](latch.md) | 类 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::arrive_and_wait](latch_arrive_and_wait.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::count_down](latch_count_down.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::latch](latch_latch.md) | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::max](latch_max.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::try_wait](latch_try_wait.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::wait](latch_wait.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
