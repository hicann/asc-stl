# asc::std::ranges::for_each_n_result

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

Header: `<asc/std/algorithm>`.

`asc::std::ranges::for_each_n_result<Iter, Func>` is an alias of `in_fun_result<Iter, Func>` available since C++17.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Declaration

```cpp
namespace asc::std::ranges {
template <class Iter, class Func>
using for_each_n_result = in_fun_result<Iter, Func>;
}  // namespace asc::std::ranges
```

## Constraints

- Follows the types and preconditions corresponding to this interface declaration.
- The caller must ensure that argument values, object lifetimes, address spaces, and availability are valid.

## Example

The following snippet shows the alias type with concrete template arguments.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {2, 4};
    asc::std::ranges::for_each_n_result<int*, void (*)(int)> result{values + 1, [](int) {}};
    return *result.in == 4;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
