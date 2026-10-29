# asc::std::vector::value_type

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

`asc::std::vector::value_type` identifies the value type of elements or results.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Declaration

Member of: [`asc::std::vector`](vector.md).

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
using value_type = T;
```

## Constraints

- This alias is the container's element type `T`; reading the type itself neither accesses nor constructs elements.
- For the conditions for construction, allocation, and element access, see the owning type [vector](vector.md).

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/vector>
#include <functional>
#include <memory>
#include <string>
#include <utility>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = example_allocator<U>;
    };
    example_allocator() = default;
    template <class U>
    example_allocator(const example_allocator<U>&) noexcept
    {}
};
#include <type_traits>
#include <cstddef>
#include <utility>

using alias_type = typename asc::std::vector<int, example_allocator<int>>::value_type;
static_assert(::std::is_same_v<alias_type, int>);
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [explicit_allocator_vector.cpp](../../../../../zh/examples/explicit_allocator_vector.cpp).

## Related APIs

- [`asc::std::vector`](vector.md)
- [API list for this header](asc_std_vector.md)
