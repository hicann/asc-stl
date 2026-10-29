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

struct example_value {
    static inline int alive = 0;
    int value;
    example_value() : value(23) { ++alive; }
    ~example_value() { --alive; }
};

bool verify_example()
{
    alignas(example_value) unsigned char storage[sizeof(example_value) * 1];
    auto* values = reinterpret_cast<example_value*>(storage);
    for (int index = 0; index < 1; ++index) { asc::std::construct_at(values + index); }
    const bool correct = example_value::alive == 1 && values[0].value == 23;
    for (int index = 0; index < 1; ++index) { asc::std::destroy_at(values + index); }
    return correct && example_value::alive == 0;
}
```

## Related APIs

- [asc::std::construct_at](construct_at.md)
