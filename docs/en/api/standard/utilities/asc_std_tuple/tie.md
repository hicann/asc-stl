# asc::std::tie

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

Header: `<asc/std/tuple>`.

`asc::std::tie` creates a tuple holding lvalue references supplied by the caller.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

```cpp
namespace asc::std {
template<class ...T> [[nodiscard]] constexpr tuple<T&...> tie(T&... values) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The types of the bound lvalue objects. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `values` | Input/Output | The bound lvalue objects; the returned tuple holds lvalue references to them, and the objects' lifetimes must cover the tuple's period of use. |

## Return Value

| Return type | Description |
| --- | --- |
| `tuple<T &...>` | Returns a tuple holding lvalue references supplied by the caller. |

## Constraints

- The utility itself allocates no additional container storage; element construction, assignment, swapping, or passing into a callable body may still allocate or throw according to their own semantics, so the whole call is not guaranteed to be allocation-free on this basis. The returned tuple borrows the original objects; these objects must cover the entire period of use of the references, and a result borrowing local objects must not be returned.

## Example

The following Host example checks the result while the referenced object is still alive.

```cpp
#include <asc/std/tuple>

bool example()
{
    int left = 3;
    int right = 5;
    auto selected = asc::std::tie(left, right);
    asc::std::get<0>(selected) = 7;
    return left == 7 && asc::std::get<1>(selected) == 5;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
