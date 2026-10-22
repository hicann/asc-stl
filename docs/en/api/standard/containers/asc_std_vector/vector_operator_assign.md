# asc::std::vector::`operator=`

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

`asc::std::vector::operator=` updates the object through the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Function Prototype

Member of: [`asc::std::vector`](vector.md).

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
vector<T, Allocator>& operator=(vector<T, Allocator>&& other) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | Source object of the assignment; the lvalue form copies its state, and the rvalue form transfers the state via the move operations of the corresponding members. |

## Return Value

| Return type | Description |
| --- | --- |
| `vector<T, Allocator> &` | Returns a reference to the updated current object, which can be used for further assignment or compound operations. |

## Constraints

- Only move assignment is provided; copy assignment is deleted; self-move-assignment leaves the object unchanged.
- A non-self move assignment first destroys the target elements and frees the target storage, then copies the source allocator and takes over the source storage, leaving the source container empty; it does not select an element-by-element move path based on allocator propagation traits.
- Allocator assignment, element destruction, and storage deallocation must not throw; pointers, references, and iterators to the original target elements are invalidated.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/vector>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.operator=(static_cast<Args&&>(args)...);
}
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [explicit_allocator_vector.cpp](../../../../../zh/examples/explicit_allocator_vector.cpp).

## Related APIs

- [`asc::std::vector`](vector.md)
- [API list for this header](asc_std_vector.md)
