# asc::std::allocator_arg_t::~allocator_arg_t

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

`asc::std::allocator_arg_t::~allocator_arg_t` destroys an `allocator_arg_t` object and ends its lifetime.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

Member of: [`allocator_arg_t`](allocator_arg_t.md). This empty tag has no user-declared destructor; the following is a semantic summary of implicit destruction, understandable in C++17 without constexpr destructor syntax.

```cpp
~allocator_arg_t() = default;
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- This is an empty tag that identifies the explicit-allocator construction form; it stores no allocator, requests no storage, and does not automatically select a constructor.

## Example

The following snippet assumes object points to a constructed object; after explicit destruction the object must not be accessed again, and releasing the storage is the caller's responsibility.

```cpp
#include <asc/std/memory>

using example_object = asc::std::allocator_arg_t;
void example(example_object* object)
{
    // object points to a constructed object; after destruction the object must not be accessed again.
    object->~example_object();
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
