# 头文件 asc/semaphore

提供基于许可计数的设备线程同步功能

## 使用方式

```cpp
#include <asc/semaphore>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::binary_semaphore](binary_semaphore.md) | 别名模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::counting_semaphore](counting_semaphore.md) | 类模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::counting_semaphore::acquire](counting_semaphore_acquire.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::counting_semaphore::counting_semaphore](counting_semaphore_counting_semaphore.md) | 构造函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::counting_semaphore::max](counting_semaphore_max.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::counting_semaphore::release](counting_semaphore_release.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::counting_semaphore::try_acquire](counting_semaphore_try_acquire.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
