# `asc::std::operator!=` (scoped_allocator)

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

Header: `<asc/std/scoped_allocator>`.

Equality requires the outer allocators and all corresponding inner allocators to be equal; inequality is the negation of the equality result.

## Function Prototype

The following is the function template declaration in the `asc::std` namespace; execution-space macros are omitted.

```cpp
template<class LeftOuter, class RightOuter, class... Inner>
constexpr bool operator!=(const scoped_allocator_adaptor<LeftOuter, Inner...>& left,
                          const scoped_allocator_adaptor<RightOuter, Inner...>& right) noexcept;
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left operand of the comparison; the comparison does not modify it. |
| `right` | Input | The right operand of the comparison; the comparison does not modify it. |

`LeftOuter` and `RightOuter` are the outer allocator types of the two sides, and `Inner...` is the identical list of inner allocator types of both sides.

## Return Value

Returns `bool`, which is `true` when the comparison relation holds, otherwise `false`.

## Constraints

- The corresponding allocators must be equality-comparable. An empty `Inner...` compares only the outer allocators.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <memory>
#include <asc/std/scoped_allocator>

template<class T>
struct ExampleAllocator : ::std::allocator<T> {
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template<class U> struct rebind { using other = ExampleAllocator<U>; };
    ExampleAllocator() = default;
    template<class U> ExampleAllocator(const ExampleAllocator<U>&) noexcept {}
};

bool example()
{
    asc::std::scoped_allocator_adaptor<ExampleAllocator<int>> left, right;
    return !(left != right);
}
```

## Related APIs

- [API list for this header](asc_std_scoped_allocator.md)
