# asc::std::make_integer_sequence

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

Header: `<asc/std/utility>`.

`asc::std::make_integer_sequence` generates or holds an integer index sequence type at compile time.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Declaration

`asc::std::make_integer_sequence<T, N>` is equivalent to `integer_sequence<T, ...>` with values from 0 to N-1; when N is 0 the parameter pack is empty. T must be an integer type and N must be non-negative.

```cpp
using Sequence = asc::std::make_integer_sequence<int, 3>;
using Equivalent = asc::std::integer_sequence<int, 0, 1, 2>;
```

## Constraints

- Provides the complete standard form.

## Example

The following Host example checks the alias or tag result with concrete types and an independent expectation.

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

void use_type()
{
    using selected = asc::std::make_integer_sequence<int, 3>;
    static_assert(asc::std::is_same_v<selected, asc::std::integer_sequence<int, 0, 1, 2>>);
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
