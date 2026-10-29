# asc::std::uninitialized_default_construct

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

`asc::std::uninitialized_default_construct` default-constructs objects in an uninitialized storage range.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<class ForwardIterator> void uninitialized_default_construct(ForwardIterator first, ForwardIterator last);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | The iterator type used to traverse the input range; must satisfy the traversal capabilities required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The start iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive. |

## Return Value

No return value.

## Constraints

- The storage is provided by the caller and satisfies the alignment requirements.
- When a rollback would throw, the related operations on the device side must not throw.

## Example

The following Host snippet uses valid objects or aligned storage; the constructed objects are destroyed at the end of the example.

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
    alignas(example_value) unsigned char storage[sizeof(example_value) * 4];
    auto* values = reinterpret_cast<example_value*>(storage);
    asc::std::uninitialized_default_construct(values, values + 4);
    const bool correct = example_value::alive == 4 && values[0].value == 23;
    for (int index = 0; index < 4; ++index) { asc::std::destroy_at(values + index); }
    return correct && example_value::alive == 0;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
