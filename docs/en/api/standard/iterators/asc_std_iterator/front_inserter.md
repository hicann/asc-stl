# asc::std::front_inserter

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

`asc::std::front_inserter` creates an output iterator that turns assignment operations into insertion at the front.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

```cpp
namespace asc::std {
template<class Container> constexpr front_insert_iterator<Container> front_inserter(Container& container) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Container` | The container type that receives the inserted elements; it must support the insertion operations invoked by this adaptor. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `container` | Input/Output | Reference to the object used by "creates an output iterator that turns assignment operations into insertion at the front"; the referenced object must remain valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `front_insert_iterator<Container>` | Returns an output iterator that turns assignment operations into insertion at the front. |

## Constraints

- The target container must support the corresponding `push_front(value)` operation; the insert iterator stores the container's address and does not own the container.
- The container must remain valid while the adaptor is in use; insertion operations must also follow the target container's own iterator invalidation rules.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <deque>

bool example()
{
    ::std::deque<int> values;
    auto output = asc::std::front_inserter(values);
    *output = 7;
    *output = 9;
    return values.size() == 2 && values[0] == 9 && values[1] == 7;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
