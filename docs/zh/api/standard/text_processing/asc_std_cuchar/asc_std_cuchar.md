# 头文件 asc/std/cuchar

提供多字节字符与UTF-16、UTF-32字符之间的转换

## 使用方式

```cpp
#include <asc/std/cuchar>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::size_t](../../language_support/asc_std_cstddef/size_t.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::c16rtomb](c16rtomb.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::c32rtomb](c32rtomb.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::c8rtomb](c8rtomb.md) | 函数 | C++20+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbrtoc16](mbrtoc16.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbrtoc32](mbrtoc32.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbrtoc8](mbrtoc8.md) | 函数 | C++20+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbstate_t](mbstate_t.md) | 类型别名 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
