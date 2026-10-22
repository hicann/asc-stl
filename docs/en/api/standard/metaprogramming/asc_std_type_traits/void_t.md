# asc::std::void_t

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

Header: `<asc/std/type_traits>`.

`void_t<Types...>` yields `void` when all listed types are valid, and is used for C++17 detection-style constraints.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class... Types>
using void_t = void;
}
```

## Constraints

- Every template argument must be a valid type; when substitution succeeds the result is always `void`, which can be used to detect whether dependent types or expressions are valid.

## Example

The following Host snippet verifies the trait result with `static_assert` and demonstrates the typical use of `void_t` with the detection idiom.

```cpp
#include <asc/std/type_traits>

template <class T, class = asc::std::void_t<>>
struct has_value_type : asc::std::false_type
{};

template <class T>
struct has_value_type<T, asc::std::void_t<typename T::value_type>> : asc::std::true_type
{};

void use_void_t()
{
    // The result of void_t is exactly void
    static_assert(asc::std::is_same_v<asc::std::void_t<int>, void>);

    // Detection idiom: void_t routes arguments whose "expression is valid" to the true branch; when the member does not exist, it falls into false_type
    struct with_value_type
    {
        using value_type = int;
    };
    static_assert(has_value_type<with_value_type>::value);
    static_assert(!has_value_type<int>::value);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
