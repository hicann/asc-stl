# 头文件 asc/std/new

提供内存分配函数声明、placement new和相关类型

## 使用方式

```cpp
#include <asc/std/new>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::launder](../../memory_management/asc_std_memory/launder.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [::operator new](operator_new.md) | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [::operator new\[\]](operator_new_array.md) | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::align_val_t](align_val_t.md) | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::destroying_delete_t](destroying_delete_t.md) | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nothrow](nothrow.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nothrow_t](nothrow_t.md) | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
