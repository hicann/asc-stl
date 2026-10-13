# 头文件asc/std/cwchar

提供宽字符类型、转换和宽字符串操作

## 使用方式

```cpp
#include <asc/std/cwchar>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::size_t](../../language_support/asc_std_cstddef/size_t.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mbstate_t](../asc_std_cuchar/mbstate_t.md) | 类型别名 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [NULL](null.md) | 宏 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [WCHAR_MAX](wchar_max.md) | 宏 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [WCHAR_MIN](wchar_min.md) | 宏 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [WEOF](weof.md) | 宏 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::btowc](btowc.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::mbrlen](mbrlen.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::mbrtowc](mbrtowc.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::mbsinit](mbsinit.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::mbsrtowcs](mbsrtowcs.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::wcrtomb](wcrtomb.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::wcscat](wcscat.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcschr](wcschr.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcscmp](wcscmp.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcscoll](wcscoll.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::wcscpy](wcscpy.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcscspn](wcscspn.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcslen](wcslen.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcsncat](wcsncat.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcsncmp](wcsncmp.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcsncpy](wcsncpy.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcspbrk](wcspbrk.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcsrchr](wcsrchr.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcsrtombs](wcsrtombs.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::wcsspn](wcsspn.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcsstr](wcsstr.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wcstok](wcstok.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::wcsxfrm](wcsxfrm.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::wctob](wctob.md) | 函数 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::wint_t](wint_t.md) | 类型别名 | C++17+ | Host（完整接口）、Device（C locale相关接口） | Ascend 950 |
| [asc::std::wmemchr](wmemchr.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wmemcmp](wmemcmp.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wmemcpy](wmemcpy.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wmemmove](wmemmove.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::wmemset](wmemset.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
