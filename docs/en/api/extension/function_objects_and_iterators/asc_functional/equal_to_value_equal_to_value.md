# asc::equal_to_value::equal_to_value

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

Header: `<asc/functional>`. Forward the argument to directly construct the stored value.

## Declaration

```cpp
// Inside equal_to_value<T>; declaration constraints are omitted.
template<class U>
explicit constexpr equal_to_value(U&& value)
    noexcept(asc::std::is_nothrow_constructible_v<T, U&&>);

// Deduction guide; existing equal_to_value specializations are excluded.
template<class U>
equal_to_value(U&&) -> equal_to_value<asc::std::decay_t<U>>;
```

## Constraints

There is no default constructor. T must be constructible from U&&. The forwarding constructor does not intercept copy/move construction; copy deduction retains the predicate type. Constant evaluation is supported when the underlying operations permit it.

C++17 and C++20 are supported. Host, SIMT, and SIMD scalar calls require comparison, conversion, construction, and destruction in the current execution domain. Device calls follow the no-exception execution contract.

## Example

```cpp
#include <asc/functional>

bool example()
{
    int target = 7;
    const auto equal = asc::equal_to_value{target};
    target = 9;
    return equal(7) && !equal(target);
}
```

## Related APIs

- [Header API list and operation support table](asc_functional.md)
