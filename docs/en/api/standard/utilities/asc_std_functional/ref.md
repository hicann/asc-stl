# asc::std::ref

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

`asc::std::ref` creates a copyable reference wrapper that does not own the object.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr reference_wrapper<T> ref(T& value) noexcept;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr reference_wrapper<T> ref(reference_wrapper<T> value) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the wrapped object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The wrapped lvalue object; the returned reference_wrapper<T> stores a reference to it, and the object's lifetime must cover the wrapper's period of use. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the wrapped object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | An existing reference_wrapper object; returns a reference_wrapper<T> referring to the same target. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `reference_wrapper<T>` | Returns the callable object or reference wrapper that stores the call target and the selected arguments. |
| Prototype 2 | `reference_wrapper<T>` | Returns the callable object or reference wrapper that stores the call target and the selected arguments. |

## Constraints

- Standard callable objects and pointer-to-member forms are supported.
- The returned reference, pointer, or non-owning wrapper does not extend the lifetime of the referenced object. The object must still be alive when used; it must not be accessed after the object is destroyed or after the lifetime of its value storage ends.

## Example

The following Host example checks the result while the referenced object is still alive.

```cpp
#include <asc/std/functional>

bool example()
{
    int value = 7;
    auto selected = asc::std::ref(value);
    selected.get() = 9;
    return value == 9 && &selected.get() == &value;
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
