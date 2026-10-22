# asc::std::identity::`operator()`

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

Header: `<asc/std/functional>`.

`asc::std::identity::operator()` processes the current object and the operands according to the available operator rules of `identity`.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

Member of: [`asc::std::identity`](identity.md).

```cpp
// Excerpt of the declaration inside asc::std::identity; the template parameters and other members are provided by the enclosing class.
template<class T> [[nodiscard]] constexpr T&& operator()(T&& value) const noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of the argument forwarded unchanged; the return value preserves the cv-qualification and reference category. |

## Return Value

| Return type | Description |
| --- | --- |
| `T &&` | Returns the result of invoking the function object with the selected arguments. |

## Constraints

- Both the typed form and the transparent call form are provided.
- The returned reference, pointer, or non-owning wrapper does not extend the lifetime of the referenced object. When using it, the caller must ensure the object is still alive; the object must not be accessed after it is destroyed or after the lifetime of its storage ends.

## Example

The following Host example checks the result while the referenced object is still alive.

```cpp
#include <asc/std/functional>
#include <asc/std/type_traits>

bool example()
{
    int value = 7;
    auto&& selected = asc::std::identity{}(value);
    static_assert(asc::std::is_same_v<decltype(selected), int&>);
    selected = 9;
    const int copied = asc::std::identity{}(7);
    return value == 9 && copied == 7;
}
```

## Related APIs

- [`asc::std::identity`](identity.md)
- [API list for this header](asc_std_functional.md)
