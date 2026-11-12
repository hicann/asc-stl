# Header asc/std/version

Provides standard feature revision macros CANN_ASC_STL_LIB_* and the existing 0/1 subset capability queries CANN_ASC_STL_HAS_*. Revision macros use the standard year/month integer and remain undefined when unsupported.

See [standard library feature revisions](../../../../guide/std_feature_test.md) for all 49 mappings, revision requirements, conditions and withheld features. Host std retains its own __cpp_lib_* vocabulary.

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

[Standard feature revision macros CANN_ASC_STL_LIB_*](feature_test_macros.md)
