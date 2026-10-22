# asc::std::construct_at

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

Header: `<asc/std/memory>`.

`asc::std::construct_at` constructs a `T` object with the forwarded arguments in caller-provided storage satisfying `T`'s alignment requirements. After successful construction the object can be accessed through the returned pointer; `destroy_at` can be called when the object's lifetime ends.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<class T, class ...Args> constexpr T* construct_at(T* location, Args&&... args);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of object to construct in the target storage. |
| `Args` | The list of argument types passed to `T`'s constructor. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `location` | Output | The address of uninitialized storage satisfying the target object's size and alignment; the call starts the object's lifetime there, and the construction arguments determine its initial value. |
| `args` | Input/Output | The list of arguments forwarded to the object construction or function call. |

## Return Value

| Return type | Description |
| --- | --- |
| `T *` | Returns a pointer to the newly constructed object, at the same address as `location`. |

## Constraints

- The storage is provided by the caller and satisfies the alignment requirements.
- When a rollback would throw, the related operations on the device side must not throw.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/memory>

void example()
{
    alignas(int) unsigned char storage[sizeof(int)];
    int* value = asc::std::construct_at(reinterpret_cast<int*>(storage), 23);
    asc::std::destroy_at(value);
}
```

## Related APIs

- [asc::std::destroy_at](destroy_at.md)
