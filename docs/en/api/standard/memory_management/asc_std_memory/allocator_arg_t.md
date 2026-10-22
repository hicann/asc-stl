# asc::std::allocator_arg_t

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

`asc::std::allocator_arg_t` marks that an allocator is passed explicitly when constructing an object.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Declaration

```cpp
namespace asc::std {
struct allocator_arg_t;
} // namespace asc::std
```

## Constraints

- This is an empty tag that identifies the explicit-allocator construction form; it stores no allocator, requests no storage, and does not automatically select a constructor.

## Example

User types with allocators can place allocator_arg_t as the first constructor parameter to clearly distinguish the allocator from ordinary arguments.

```cpp
#include <asc/std/memory>
#include <memory>

struct Value {
    using allocator_type = ::std::allocator<int>;
    int number;
    Value(asc::std::allocator_arg_t, const allocator_type&, int input) : number(input) {}
};

bool example()
{
    static_assert(asc::std::uses_allocator_v<Value, ::std::allocator<int>>);
    asc::std::allocator_arg_t tag{};
    Value value(tag, ::std::allocator<int>{}, 7);
    return value.number == 7;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
