# asc::std::optional::`operator*`

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

Header: `<asc/std/optional>`.

`asc::std::optional::operator*` dereferences the current iterator or engaged object.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

Member of: [`asc::std::optional`](optional.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
constexpr T& operator*()& noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
constexpr T&& operator*()&& noexcept;
```

### Prototype 3

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
constexpr const T& operator*() const& noexcept;
```

### Prototype 4

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
constexpr const T&& operator*() const&& noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

No parameters.

### Parameters of Prototype 3

No parameters.

### Parameters of Prototype 4

No parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T&` | Returns the object referenced by the current iterator or wrapper. |
| Prototype 2 | `T&&` | Returns the object referenced by the current iterator or wrapper. |
| Prototype 3 | `const T&` | Returns the object referenced by the current iterator or wrapper. |
| Prototype 4 | `const T&&` | Returns the object referenced by the current iterator or wrapper. |

## Constraints

- T must be an ordinary non-reference object type.
- Host follows the valid C++17 operations.
- The operations that construction, assignment, invocation, and swap rely on must not throw on the device side.
- The returned reference, pointer, or non-owning wrapper does not extend the lifetime of the referenced object. The caller must ensure the object is still alive when used; it must not be accessed after the object is destroyed or after the lifetime of its value storage ends.

## Example

The following Host example checks the result while the referenced object is still alive.

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> value(7);
    int* selected = &*value;
    *selected = 9;
    return value.has_value() && *value == 9;
}
```

## Related APIs

- [`asc::std::optional`](optional.md)
- [API list for this header](asc_std_optional.md)
