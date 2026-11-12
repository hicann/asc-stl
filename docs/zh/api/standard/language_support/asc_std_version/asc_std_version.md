# 头文件asc/std/version

提供本库标准特性的修订版本宏 `CANN_ASC_STL_LIB_*`，以及已有的 `CANN_ASC_STL_HAS_*` 子集能力查询。版本宏在满足对应标准修订时定义为标准年月整数；未支持时不定义。

完整名称映射、49项修订、定义条件和未报告原因见[标准库特性修订检测](../../../../guide/std_feature_test.md)。HAS 宏仍为0或1；宿主标准库由其自己的 `__cpp_lib_*` 描述。

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

[标准特性版本宏 CANN_ASC_STL_LIB_*](feature_test_macros.md)
