# 头文件asc/version

提供 ASC-STL 日期版本和三个扩展模块的接口交付标识，并转引标准层的 `CANN_ASC_STL_LIB_*` 特性宏。四个产品宏在同一发行包的 Host、SIMD、SIMT 和 C++17/C++20 编译中取值一致。

```cpp
#include <asc/version>
```

| API | 类型 | C++ 模式 | 可用位置 | 芯片相关性 |
| --- | --- | --- | --- | --- |
| [CANN_ASC_STL](cann_asc_stl.md) | 宏 | C++17/C++20 | Host、SIMD、SIMT | 无 |
| [CANN_ASC_STL_HAS_PIPELINE](cann_asc_stl_has_pipeline.md) | 宏 | C++17/C++20 | Host、SIMD、SIMT | 无 |
| [CANN_ASC_STL_HAS_NUMERIC_TYPES](cann_asc_stl_has_numeric_types.md) | 宏 | C++17/C++20 | Host、SIMD、SIMT | 无 |
| [CANN_ASC_STL_HAS_CACHE](cann_asc_stl_has_cache.md) | 宏 | C++17/C++20 | Host、SIMD、SIMT | 无 |

[Product version guide](../../../../guide/product_version.md)
