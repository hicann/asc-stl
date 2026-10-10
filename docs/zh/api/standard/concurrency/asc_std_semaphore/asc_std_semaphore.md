# 头文件 asc/std/semaphore

提供基于计数控制并发访问数量的同步功能

## 使用方式

```cpp
#include <asc/std/semaphore>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::binary_semaphore](binary_semaphore.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore](counting_semaphore.md) | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore::acquire](counting_semaphore_acquire.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore::max](counting_semaphore_max.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore::release](counting_semaphore_release.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore::try_acquire](counting_semaphore_try_acquire.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
