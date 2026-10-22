# Header asc/std/version

Provides capability-query macros of ASC-STL itself. All macros are available starting from C++17; each value is 0 or 1 and indicates the capability of the selected interface subset under the current configuration. Host standard library capabilities are still described by the Host's own standard feature macros.

For how to port to and use these macros, see [Language Modes and Compatibility](../../../../../zh/guide/cpp_compatibility.md).

## Usage

```cpp
#include <asc/std/version>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [CANN_ASC_STL_HAS_SOURCE_LOCATION](has_source_location.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_UNREACHABLE](has_unreachable.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_TYPE_IDENTITY](has_type_identity.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_ENDIAN](has_endian.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_IS_CONSTANT_EVALUATED](has_is_constant_evaluated.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_CONCEPT_PREDICATES](has_concept_predicates.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_NATIVE_CONCEPTS](has_native_concepts.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_SPAN](has_span.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_TO_ARRAY](has_to_array.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_MDSPAN](has_mdspan.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_SUBMDSPAN](has_submdspan.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_EXPECTED](has_expected.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_OPTIONAL_REFERENCE](has_optional_reference.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_INPLACE_VECTOR](has_inplace_vector.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_PHILOX](has_philox.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_ALLOCATE_AT_LEAST](has_allocate_at_least.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_FORMAT_TO_N_RESULT](has_format_to_n_result.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL_HAS_FORMAT](has_format.md) | Macro | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
