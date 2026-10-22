# asc::std::destroy_at

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

`asc::std::destroy_at` calls the destructor of the specified object, ending its lifetime, but does not release the caller-provided storage.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<class T> constexpr void destroy_at(T* location);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of object whose lifetime is to be ended. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `location` | Input/Output | Points to an object whose lifetime has not yet ended; the call ends its lifetime and does not release the underlying storage. |

## Return Value

No return value.

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

- [asc::std::construct_at](construct_at.md)
