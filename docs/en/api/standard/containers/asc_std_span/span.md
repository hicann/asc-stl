# asc::std::span

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

Header: `<asc/std/span>`.

`asc::std::span` observes a contiguous sequence of elements in a non-owning way.

Standard semantics reference: [cppreference `span`](https://en.cppreference.com/w/cpp/header/span).

## Declaration

```cpp
namespace asc::std {
template<class T, size_t Extent = dynamic_extent> class span;
} // namespace asc::std
```

## Constraints

- Both C++17 and C++20 support construction from a pointer or contiguous iterator plus a count, a contiguous iterator plus a sized sentinel, an array, another compatible span, and a contiguous sized range.
- The element reference of the iterator or range must be convertible to the element type corresponding to `T`; when constructing a writable span, the `const` of elements must not be removed, and derived-class elements must not be converted to base-class elements in array fashion.
- A non-borrowed range must be an lvalue, or the span's element type must be `const`. A span does not own the data; the original elements must remain valid for the whole duration of access.
- A fixed extent must match the input count. Arrays and fixed spans whose static extent does not match do not participate in construction; dynamic counts and range counts are guaranteed correct by the caller.
- A second argument convertible to a count is treated as the count; a heterogeneous sentinel must support two-way distance operations with the iterator.
- In AI Core SIMD programming, element pointers or ranges must be representable as standard plain pointers; this interface does not add GM/UB address-space pointer conversion.
- Template slicing of a dynamic-extent span requires valid runtime bounds. For `first<Count>()` and `last<Count>()`, `Count` must not exceed `size()`. For `subspan<Offset, Count>()`, `Offset` must not exceed `size()`, and an explicit `Count` must not exceed `size()` minus `Offset`.

## Key Features

On Host with C++20, the view can be constructed from a contiguous range from the system standard library, such as an lvalue `std::vector<T>`.

Both C++17 and C++20 provide class template argument deduction. Built-in arrays and `asc::std::array` deduce a fixed extent, and generic contiguous ranges deduce a dynamic extent. When an iterator is combined with an integral-constant-class count, the constant value of the count object can be used to deduce a fixed extent; an ordinary runtime count keeps a dynamic extent. Availability of these library interfaces does not require enabling the C++26 language mode.

## Example

The following Host example shows generic range construction and static extent deduction, and checks the view's access to the original array.

```cpp
#include <asc/std/span>
#include <asc/std/type_traits>

struct contiguous_values {
    int* first;
    asc::std::size_t count;
    int* begin() const { return first; }
    int* end() const { return first + count; }
    int* data() const { return first; }
    asc::std::size_t size() const { return count; }
};

bool example()
{
    int values[4] = {1, 2, 3, 4};
    contiguous_values range{values, 4};
    asc::std::span view(range);
    asc::std::span fixed(values, asc::std::integral_constant<asc::std::size_t, 4>{});
    static_assert(decltype(fixed)::extent == 4);
    view[1] = 8;
    auto tail = view.last<2>();
    static_assert(decltype(tail)::extent == 2);
    return fixed[1] == 8 && tail.size() == 2 && tail[0] == 3;
}
```

## Related APIs

- [API list for this header](asc_std_span.md)

[Complete usage example](../../../../../../examples/standard/span_subrange/README_en.md).
