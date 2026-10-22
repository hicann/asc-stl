# asc::std::inplace_vector

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

Header: `<asc/std/inplace_vector>`.

`asc::std::inplace_vector` stores elements in fixed-capacity storage inside the object.

Both Host and the device side provide the listed non-throwing interface subset; basic value operations are available from C++17 onward.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Declaration

```cpp
namespace asc::std {
template<class T, asc::std::size_t Capacity> class inplace_vector;
} // namespace asc::std
```

## Constraints

- Element storage is inside the container object and is not dynamically allocated; Capacity is the compile-time fixed capacity.
- Both Host and the device side provide the listed non-throwing subset; `at`, `push_back`, `emplace_back`, `resize`, and `try_append_range` are not provided.
- `try_push_back` and `try_emplace_back` return `optional<T&>`; they return an empty object when capacity is insufficient. `unchecked` insertion requires the caller to guarantee remaining capacity in advance.
- The corresponding construction, assignment, and destruction of elements must satisfy the non-throwing usage domain; the constexpr declaration does not guarantee constant evaluation for every T and language mode.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(1)) return false;
    if (!values.try_push_back(3)) return false;
    return values.size() == 2 && values[0] == 1 && values[1] == 3;
}
```

## Related APIs

- [API list for this header](asc_std_inplace_vector.md)
