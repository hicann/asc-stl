# asc::std::vector::get_allocator

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

Header: `<asc/std/vector>`.

`asc::std::vector::get_allocator` returns the allocator currently used by the container.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Function Prototype

Member of: [`asc::std::vector`](vector.md).

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
allocator_type get_allocator() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `allocator_type` | Returns the allocator currently used by the container. |

## Constraints

- Returns a copy of the saved allocator without allocating element storage; allocator copy operations must not throw.
- When called on the device side, allocator copy operations must be available in the corresponding programming mode.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <memory>
#include <asc/std/vector>

bool example()
{
    asc::std::vector<int, ::std::allocator<int>> values(::std::allocator<int>{});
    values.push_back(1);
    values.push_back(3);

    auto allocator = values.get_allocator();
    auto* buffer = allocator.allocate(1);
    if (buffer == nullptr) return false;
    ::std::allocator_traits<decltype(allocator)>::construct(allocator, buffer, 7);
    const bool matched = *buffer == 7;
    ::std::allocator_traits<decltype(allocator)>::destroy(allocator, buffer);
    allocator.deallocate(buffer, 1);
    return matched;
}
```

## Related APIs

- [`asc::std::vector`](vector.md)
- [API list for this header](asc_std_vector.md)
