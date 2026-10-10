# 头文件 asc/std/shared_mutex

提供共享锁和独占锁，允许多个线程同时以共享方式加锁，或者由一个线程以独占方式加锁

## 使用方式

```cpp
#include <asc/std/shared_mutex>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::swap](../asc_std_mutex/swap.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock](shared_lock.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::lock](shared_lock_lock.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::mutex](shared_lock_mutex.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::mutex_type](shared_lock_mutex_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::operator=](shared_lock_operator_assign.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::owns_lock](shared_lock_owns_lock.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::release](shared_lock_release.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::shared_lock](shared_lock_shared_lock.md) | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::swap](shared_lock_swap.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::try_lock](shared_lock_try_lock.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::unlock](shared_lock_unlock.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::~shared_lock](shared_lock_destructor_shared_lock.md) | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
