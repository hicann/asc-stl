# asc::std::vector::emplace_back

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

`asc::std::vector::emplace_back` constructs an element in place at the end of the container.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Function Prototype

Member of: [`asc::std::vector`](vector.md).

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
template<class ...Args> reference emplace_back(Args&&... args);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Args` | List of argument types passed to the constructor or callable object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `args` | Input/Output | Argument list forwarded to the object construction or function call. |

## Return Value

| Return type | Description |
| --- | --- |
| `reference` | Returns a reference to the element constructed in place, or the insertion result specified by the selected prototype. |

## Constraints

- `T` must be constructible from the forwarded `Args...`; the current implementation also requires `T` to be constructible from `T&&` to satisfy the compilation requirements of the capacity-growth path, and reserving capacity in advance does not waive this requirement.
- After a successful construction, `size()` increases by `1` and a reference to the new element is returned; capacity growth invalidates the original pointers, references, and iterators.
- When called on the device side, the allocator and the related element operations must be available in the corresponding programming mode and must not throw, and allocation must be guaranteed to succeed or sufficient capacity must be reserved beforehand.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/vector>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.emplace_back(static_cast<Args&&>(args)...);
}
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [explicit_allocator_vector.cpp](../../../../../zh/examples/explicit_allocator_vector.cpp).

## Related APIs

- [`asc::std::vector`](vector.md)
- [API list for this header](asc_std_vector.md)
