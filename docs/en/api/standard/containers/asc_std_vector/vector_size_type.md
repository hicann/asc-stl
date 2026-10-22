# asc::std::vector::size_type

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

`asc::std::vector::size_type` identifies the unsigned type for container sizes.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Declaration

Member of: [`asc::std::vector`](vector.md).

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
using size_type = asc::std::size_t;
```

## Constraints

In generic code, size variables can be declared through `size_type` of the owning type without hard-coding the underlying integer type; see the owning type's page for how this alias relates to the other member types.

- This alias is the unsigned integer type the owning type uses for element counts or sizes; reading the type itself allocates no memory and accesses no elements.
- For the runtime conditions for construction, allocation, and access, see the owning type [asc::std::vector](vector.md).

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <memory>
#include <asc/std/vector>
#include <asc/std/cstddef>
#include <asc/std/type_traits>

bool example()
{
    using Vector = asc::std::vector<int, ::std::allocator<int>>;
    static_assert(asc::std::is_same_v<Vector::size_type, asc::std::size_t>);
    Vector values(::std::allocator<int>{});
    values.push_back(7);
    const Vector::size_type count = values.size();
    return count == 1;
}
```

## Related APIs

- [`asc::std::vector`](vector.md)
- [API list for this header](asc_std_vector.md)
