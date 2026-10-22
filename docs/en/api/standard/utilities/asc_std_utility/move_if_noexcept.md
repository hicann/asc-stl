# asc::std::move_if_noexcept

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

Header: `<asc/std/utility>`.

`asc::std::move_if_noexcept` returns an rvalue reference when move construction does not throw or copying is unavailable, otherwise a const lvalue reference, letting the caller choose the move or copy path according to its exception guarantee. The returned reference is valid only while the original object is alive.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

```cpp
namespace asc::std {
template<class T> constexpr asc::std::conditional_t<asc::std::is_nothrow_move_constructible_v<T> || !asc::std::is_copy_constructible_v<T>, T&&, const T&> move_if_noexcept(T& value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The object type; this call only selects the returned reference and does not copy- or move-construct the object. Any subsequent construction is performed by the caller and must satisfy the type's requirements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The object to be conditionally moved; when T is nothrow-movable or not copyable, its rvalue reference is returned (if it is then moved, it ends up in a valid but unspecified state), otherwise a const lvalue reference is returned to take the copy path. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::conditional_t<asc::std::is_nothrow_move_constructible_v<T> \|\| !asc::std::is_copy_constructible_v<T>, T&&, const T&>` | Returns an rvalue reference, otherwise a const lvalue reference, letting the caller choose the move or copy path according to its exception guarantee. |

## Constraints

- T must satisfy the requirements of the selected move or copy construction path.
- The returned reference does not extend the lifetime of the original object.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

bool example()
{
    int value = 3;
    auto&& reference = asc::std::move_if_noexcept(value);
    static_assert(asc::std::is_same_v<decltype(reference), int&&>);
    // Check the reference while value is still alive; the function only returns a boolean value.
    return &reference == &value && reference == 3;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
