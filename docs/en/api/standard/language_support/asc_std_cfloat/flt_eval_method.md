# FLT_EVAL_METHOD

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

Header: `<asc/std/cfloat>`.

`FLT_EVAL_METHOD` indicates the precision method used for the evaluation of floating-point expressions.

Standard semantics reference: [cppreference `cfloat`](https://en.cppreference.com/w/cpp/header/cfloat).

## Declaration

This macro is provided by the platform header; the public header keeps its spelling and value and does not invent a substitute macro name.

```cpp
#include <asc/std/cfloat>
```

## Constraints

- Only macros actually supported by the compiler ABI are provided.

## Example

The following Host example uses concrete inputs and checks an observable result of the interface.

```cpp
#include <asc/std/cfloat>
#include <asc/std/type_traits>

static_assert(asc::std::is_same_v<decltype(FLT_EVAL_METHOD), int>);
```

## Related APIs

- [API list for this header](asc_std_cfloat.md)
