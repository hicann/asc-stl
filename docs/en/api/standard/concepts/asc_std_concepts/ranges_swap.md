# asc::std::ranges::swap

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

Header: `<asc/std/concepts>`.

`asc::std::ranges::swap` is a customization point object that swaps two values: it prefers a `swap` found via ADL, then element-by-element swapping of equal-length arrays, and finally a move swap using `exchange`.

Standard semantics reference: [cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts).

## Declaration

swap is an inline constexpr customization point object whose actual implementation class is not part of the public interface. The following only queries the type of this object; swap_object_type is an example alias. The call form is asc::std::ranges::swap(left, right).

```cpp
using swap_object_type = decltype(asc::std::ranges::swap);
```

## Constraints

- A swap findable via ADL is preferred; whether the arguments are usable and the exception specification follow that customized call.
- Equal-length arrays are then supported for element-by-element swapping; finally, move swap is used for same-type lvalues that are move constructible and assignable from rvalues.
- The participating objects must remain valid for the entire call; the swap does not extend their lifetime, and the exception specification depends on the actual operation selected.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/concepts>

bool example()
{
    int left = 1;
    int right = 2;
    asc::std::ranges::swap(left, right);
    int first[2] = {3, 4};
    int second[2] = {5, 6};
    asc::std::ranges::swap(first, second);
    return left == 2 && right == 1 && first[0] == 5 && second[1] == 4;
}
```

## Related APIs

- [API list for this header](asc_std_concepts.md)
