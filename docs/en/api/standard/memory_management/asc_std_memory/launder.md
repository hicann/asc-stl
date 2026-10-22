# asc::std::launder

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

Header: `<asc/std/new>`. Including only `<asc/std/memory>` does not provide this function.

`asc::std::launder` obtains a pointer usable for accessing the new object after an object lifetime transition.

Standard semantics reference: [cppreference `launder`](https://en.cppreference.com/w/cpp/utility/launder).

## Function Prototype

```cpp
namespace asc::std {
template<class T> constexpr T* launder(T* pointer) noexcept;
}
```

This single template has been provided since C++17 and can be used in the corresponding pointer domains of Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of the currently live object; must satisfy the object type and reachable-storage requirements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | Points to the address of a live object of the corresponding type and must satisfy the object type and storage reachability conditions; creates no object and extends no lifetime. |

## Return Value

| Return type | Description |
| --- | --- |
| `T*` | A pointer to the currently live object at the same storage address. |

## Constraints

- Before the call, a type-compatible live object must already exist at the given address and the storage reachability conditions must hold; this function allocates no storage and starts no object lifetime.
- The returned pointer's usable period is limited by the lifetimes of the current object and the underlying storage; after destroying the object it must not be used for access again.
- The header and the pointer's execution location and address space must match; this call performs no GM/UB address-space conversion.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>
#include <asc/std/new>

struct example_value {
    int value;
    explicit example_value(int initial) : value(initial) {}
};

bool example()
{
    alignas(example_value) unsigned char storage[sizeof(example_value)];
    auto* pointer = reinterpret_cast<example_value*>(storage);
    asc::std::construct_at(pointer, 3);
    asc::std::destroy_at(pointer);
    asc::std::construct_at(pointer, 7);
    const bool valid = asc::std::launder(pointer)->value == 7;
    asc::std::destroy_at(pointer);
    return valid;
}
```

## Related APIs

- [API list of the new header this interface belongs to](../../language_support/asc_std_new/asc_std_new.md)
- [Object construction and destruction interfaces](asc_std_memory.md)
