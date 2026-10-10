# 头文件 asc/std/mutex

提供互斥访问接口和锁对象管理工具

## 使用方式

```cpp
#include <asc/std/mutex>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::adopt_lock](adopt_lock.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::adopt_lock_t](adopt_lock_t.md) | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::defer_lock](defer_lock.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::defer_lock_t](defer_lock_t.md) | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lock_guard](lock_guard.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_lock](scoped_lock.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::swap](swap.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::try_lock](try_lock.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::try_to_lock](try_to_lock.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::try_to_lock_t](try_to_lock_t.md) | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock](unique_lock.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::lock](unique_lock_lock.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::mutex](unique_lock_mutex.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::mutex_type](unique_lock_mutex_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::operator=](unique_lock_operator_assign.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::owns_lock](unique_lock_owns_lock.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::release](unique_lock_release.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::swap](unique_lock_swap.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::try_lock](unique_lock_try_lock.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::unique_lock](unique_lock_unique_lock.md) | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::unlock](unique_lock_unlock.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::~unique_lock](unique_lock_destructor_unique_lock.md) | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
