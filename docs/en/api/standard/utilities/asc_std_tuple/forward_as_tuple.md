# asc::std::forward_as_tuple

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

`asc::std::forward_as_tuple` combines the references and value categories of the arguments into a tuple that owns no objects.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

```cpp
namespace asc::std {
template<class ...T> [[nodiscard]] constexpr tuple<T&&...> forward_as_tuple(T&&... values) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The types of the arguments to be forwarded; the result tuple stores their references as T&& and preserves the original value categories. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `values` | Input/Output | The arguments to be forwarded; the returned tuple stores references to the arguments (preserving the original value categories), and the arguments' lifetimes must cover the tuple's period of use. |

## Return Value

| Return type | Description |
| --- | --- |
| `tuple<T &&...>` | Returns references to the objects; the referenced objects must remain valid for the duration the references are used. |

## Constraints

- The utility itself allocates no additional container storage; element construction, assignment, swapping, or passing into a callable body may still allocate or throw according to their own semantics, so the whole call is not guaranteed to be allocation-free on this basis. The returned tuple borrows the original objects; these objects must cover the entire period of use of the references, and a result borrowing local objects must not be returned.

## Example

The following Host example checks the result while the referenced object is still alive.

```cpp
#include <asc/std/tuple>

bool example()
{
    int value = 3;
    auto selected = asc::std::forward_as_tuple(value);
    asc::std::get<0>(selected) = 7;
    return value == 7;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
