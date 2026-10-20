# 头文件asc/std/version

提供ASC-STL自身的能力查询宏。宏均可在C++17起使用；值为0或1，表示当前配置下已选接口子集的能力。Host标准库能力仍由Host自己的标准特性宏描述。

宏的迁移与使用方式见[语言模式与兼容性](../../../../guide/cpp_compatibility.md)。

## 使用方式

```cpp
#include <asc/std/version>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [CANN_ASC_STL_HAS_SOURCE_LOCATION](has_source_location.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_UNREACHABLE](has_unreachable.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_TYPE_IDENTITY](has_type_identity.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_ENDIAN](has_endian.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_IS_CONSTANT_EVALUATED](has_is_constant_evaluated.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_CONCEPT_PREDICATES](has_concept_predicates.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_NATIVE_CONCEPTS](has_native_concepts.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_SPAN](has_span.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_TO_ARRAY](has_to_array.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_MDSPAN](has_mdspan.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_SUBMDSPAN](has_submdspan.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_EXPECTED](has_expected.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_OPTIONAL_REFERENCE](has_optional_reference.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_INPLACE_VECTOR](has_inplace_vector.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_PHILOX](has_philox.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_ALLOCATE_AT_LEAST](has_allocate_at_least.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_FORMAT_TO_N_RESULT](has_format_to_n_result.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [CANN_ASC_STL_HAS_FORMAT](has_format.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
