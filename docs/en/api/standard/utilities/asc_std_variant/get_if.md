# asc::std::get_if

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

Header: `<asc/std/variant>`.

`asc::std::get_if` returns a pointer to the active alternative when it matches the target, otherwise a null pointer.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class T, class ...Types> [[nodiscard]] constexpr add_pointer_t<T> get_if(variant<Types...>* value) noexcept;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T, class ...Types> [[nodiscard]] constexpr add_pointer_t<const T> get_if(const variant<Types...>* value) noexcept;
} // namespace asc::std
```

### Prototype 3

```cpp
namespace asc::std {
template<size_t Index, class ...Types> [[nodiscard]] constexpr add_pointer_t<const variant_alternative_t<Index, variant<Types...>>> get_if(const variant<Types...>* value) noexcept;
} // namespace asc::std
```

### Prototype 4

```cpp
namespace asc::std {
template<size_t Index, class ...Types> [[nodiscard]] constexpr add_pointer_t<variant_alternative_t<Index, variant<Types...>>> get_if(variant<Types...>* value) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target alternative type; it must occur exactly once in Types.... |
| `Types` | The list of alternative types of the variant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | A pointer to the variant object being accessed; returns a pointer to its alternative when the active alternative matches the target, otherwise a null pointer. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target alternative type; it must occur exactly once in Types.... |
| `Types` | The list of alternative types of the variant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | A pointer to the variant object being accessed; returns a pointer to its alternative when the active alternative matches the target, otherwise a null pointer. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The index of the target alternative (starting from 0); it must be less than the number of alternatives. |
| `Types` | The list of alternative types of the variant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | A pointer to the variant object being accessed; returns a pointer to its alternative when the active alternative matches the target, otherwise a null pointer. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The index of the target alternative (starting from 0); it must be less than the number of alternatives. |
| `Types` | The list of alternative types of the variant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | A pointer to the variant object being accessed; returns a pointer to its alternative when the active alternative matches the target, otherwise a null pointer. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `add_pointer_t<T>` | Returns its pointer, otherwise a null pointer. |
| Prototype 2 | `add_pointer_t<const T>` | Returns its pointer, otherwise a null pointer. |
| Prototype 3 | `add_pointer_t<const variant_alternative_t<Index, variant<Types...>>>` | Returns its pointer, otherwise a null pointer. |
| Prototype 4 | `add_pointer_t<variant_alternative_t<Index, variant<Types...>>>` | Returns its pointer, otherwise a null pointer. |

## Constraints

- A null pointer is returned when the object has no active alternative; this can be used to avoid accessing a nonexistent value.

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.
- The returned reference, pointer, or non-owning wrapper does not extend the lifetime of the referenced object. The caller must ensure the object is still alive when used; it must not be accessed after the object is destroyed or after the lifetime of its value storage ends.

## Example

The following Host example checks the result while the referenced object is still alive.

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, long> value(asc::std::in_place_index<0>, 7);
    int* selected = asc::std::get_if<0>(&value);
    return selected != nullptr && *selected == 7 && asc::std::get_if<1>(&value) == nullptr;
}
```

## Related APIs

- [API list for this header](asc_std_variant.md)
