# `asc::std::operator!=` (move_iterator overload) (Function template)

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

The expression `sentinel != iterator` is provided by `<asc/std/iterator>`; it is the reversed inequality comparison between a move sentinel and a move iterator. The interface follows the semantics of the corresponding C++ standard facility; ASC-STL's language modes and call positions are governed by the declaration on this page.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

The explicit overload below is used in compatibility branches. C++20 Host supports the same comparison expression through equality operator rewriting.

```cpp
namespace asc::std {
template<class Iter, class Sentinel, asc::std::enable_if_t<sentinel_for<Sentinel, Iter> && __move_iter_comparable<Iter, Sentinel>, int> = 0> constexpr bool operator!=(const move_sentinel<Sentinel>& sentinel, const move_iterator<Iter>& iterator);
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
| `bool` | true when the underlying iterator differs from the sentinel. |

## Constraints

- Use `sentinel != iterator`. The underlying iterator and sentinel must be comparable; the result negates equality.
- C++20 Host does not expose an explicitly named reverse `operator!=` call. Use the operator expression above.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/iterator>

template <class Iter, class Sentinel>
decltype(auto) example(const asc::std::move_sentinel<Sentinel>& sentinel, const asc::std::move_iterator<Iter>& iterator)
{
    return sentinel != iterator;
}

bool verify_example()
{
    int values[] = {1, 2};
    asc::std::move_sentinel<int*> sentinel(values + 2);
    asc::std::move_iterator<int*> iterator(values + 1);
    return example(sentinel, iterator);
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
