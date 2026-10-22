# `asc::std::operator==` (move_iterator overload) (Function template)

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

Header: `<asc/std/iterator>`.

`asc::std::operator==(const move_sentinel<Sentinel>&, const move_iterator<Iter>&)` is provided by `<asc/std/iterator>`; it is the reversed equality comparison between a move sentinel and a move iterator. The interface follows the semantics of the corresponding C++ standard facility; ASC-STL's language modes and call positions are governed by the declaration on this page.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

```cpp
namespace asc::std {
template<class Iter, class Sentinel> constexpr bool operator==(const move_sentinel<Sentinel>& sentinel, const move_iterator<Iter>& iterator);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Iter` | The underlying iterator type. |
| `Sentinel` | The end sentinel type paired with Iter. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `sentinel` | Input | The object reference participating in the operation; the referenced object must remain valid during the call. |
| `iterator` | Input | The object reference participating in the operation; the referenced object must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | true when the underlying iterator equals the sentinel. |

## Constraints

- The comparison checks whether the underlying positions stored on both sides are the same, and requires the underlying iterator and the sentinel to be comparable.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/iterator>

template <class Iter, class Sentinel>
decltype(auto) example(const asc::std::move_sentinel<Sentinel>& sentinel, const asc::std::move_iterator<Iter>& iterator)
{
    return asc::std::operator==(sentinel, iterator);
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
