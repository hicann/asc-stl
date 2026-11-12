# CANN_ASC_STL_LIB_*

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Query the standard feature revision implemented by ASC-STL. The [inventory](../../../../guide/std_feature_test.md) lists requirements, conditions and withheld revisions.

## Declaration

Object-like integer macros use standard year/month values and remain undefined when unsupported. Map __cpp_lib_x to CANN_ASC_STL_LIB_x.

## Constraints

Describes this translation unit's language, compiler and execution configuration, independently of Host std and product releases.

## Example

```cpp
#include <asc/std/version>
#include <asc/std/array>

#if defined(CANN_ASC_STL_LIB_to_array) && CANN_ASC_STL_LIB_to_array >= 201907L
constexpr auto values = asc::std::to_array({2, 4});
static_assert(values[0] == 2 && values[1] == 4);
#else
#error "ASC-STL to_array revision 201907 is required"
#endif
```

## Related APIs

- [Header API list](asc_std_version.md)
