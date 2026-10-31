# asc::std::pointer_traits::pointer_to

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

`asc::std::pointer_traits::pointer_to` constructs, from an object reference, a pointer compatible with the current pointer traits.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

Member of: [`asc::std::pointer_traits`](pointer_traits.md). The following declaration summaries show only the forms callable when `element_type` is not `void`, omitting the non-callable placeholder parameter types.

```cpp
// In-class declaration summary for pointer_traits<P>.
static constexpr pointer pointer_to(element_type& value);
```

```cpp
// In-class declaration summary for pointer_traits<T*>.
static constexpr pointer pointer_to(element_type& value) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | A reference to the object whose address is used to construct the pointer; the returned pointer points to that object. |

## Return Value

| Return type | Description |
| --- | --- |
| `pointer` | Returns the corresponding pointer type pointing to the given object. |

## Constraints

- Raw pointers and user-defined fancy pointers are supported; the interface itself allocates no memory, and the returned pointer's usable period is limited by the lifetime of the referenced object.
- The wrapper function can be used in constant evaluation in both C++17 and C++20; a custom pointer's `pointer_to`, construction, and return types must also satisfy the corresponding constant-expression requirements.
- The custom-pointer form delegates to that pointer type's static `pointer_to`, whose exception behavior is determined by the concrete implementation; the raw-pointer specialization is `noexcept`.

## Example

The following Host example invokes a custom pointer through the public traits and checks the constant-expression result in both C++17 and C++20.

```cpp
#include <asc/std/memory>

template<class T>
struct example_pointer {
    using element_type = T;
    T* value;
    static constexpr example_pointer pointer_to(T& object) noexcept { return {&object}; }
};

constexpr bool example()
{
    int object = 7;
    const auto pointer = asc::std::pointer_traits<example_pointer<int>>::pointer_to(object);
    return pointer.value == &object;
}

static_assert(example());
```

Complete example source: [pointer_alignment.cpp](../../../../../../examples/standard/pointer_alignment/main.cpp).

## Related APIs

- [`asc::std::pointer_traits`](pointer_traits.md)
- [API list for this header](asc_std_memory.md)
