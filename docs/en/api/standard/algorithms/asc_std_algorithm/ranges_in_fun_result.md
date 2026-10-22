# asc::std::ranges::in_fun_result

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

`asc::std::ranges::in_fun_result<Iter, Func>` holds the algorithm's end iterator `in` and the function object after execution `fun`, available since C++17.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Declaration

### Prototype 1

```cpp
namespace asc::std::ranges {
template <class Iter, class Func>
struct in_fun_result;
}  // namespace asc::std::ranges
```

## Constraints

- Follows the types and preconditions corresponding to this interface declaration.
- The caller must ensure that argument values, object lifetimes, address spaces, and availability are valid.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {2, 4};
    auto twice = [](int value) { return 2 * value; };
    asc::std::ranges::in_fun_result<int*, decltype(twice)> result{values + 1, twice};
    return *result.in == 4 && result.fun(3) == 6;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
