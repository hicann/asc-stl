# asc::std::optional::`operator=`

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

`asc::std::optional::operator=` updates the object with the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

Member of: [`asc::std::optional`](optional.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
constexpr asc::std::optional& operator=(asc::std::nullopt_t) noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
constexpr asc::std::optional& operator=(asc::std::optional&& other) noexcept(is_nothrow_move_constructible_v<T>&& is_nothrow_move_assignable_v<T>);
```

### Prototype 3

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
constexpr asc::std::optional& operator=(const asc::std::optional& other);
```

### Prototype 4

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
template<class U> constexpr asc::std::optional& operator=(U&& value);
```

### Prototype 5

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
template<class U> constexpr asc::std::optional& operator=(asc::std::optional<U>&& other);
```

### Prototype 6

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
template<class U> constexpr asc::std::optional& operator=(const asc::std::optional<U>& other);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `asc` | Input | The nullopt_t empty-state tag (the nullopt constant); after assignment the current object destroys the contained value and becomes empty. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source optional of move assignment; its value is moved into the current object and it ends up in a valid but unspecified state after the move. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source optional of copy assignment; its value is copied into the current object. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U` | The type of the source value of the assignment; it must not be an optional specialization. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The new value assigned to the current object; lvalues are copied and rvalues are moved, and an rvalue ends up in a valid but unspecified state after being moved. |

### Parameters of Prototype 5

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U` | The type of the value contained in the source optional; it may differ from T. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source optional of move assignment, whose contained value type may differ from T; its value is moved into the current object after conversion and it ends up in a valid but unspecified state after the move. |

### Parameters of Prototype 6

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U` | The type of the value contained in the source optional; it may differ from T. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source optional of copy assignment, whose contained value type may differ from T; its value is copied into the current object after conversion. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::std::optional&` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 2 | `asc::std::optional&` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 3 | `asc::std::optional&` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 4 | `asc::std::optional&` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 5 | `asc::std::optional&` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 6 | `asc::std::optional&` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |

## Constraints

- T must be an ordinary non-reference object type.
- Host follows the valid C++17 operations.
- The operations that construction, assignment, invocation, and swap rely on must not throw on the device side.

## Example

The following Host snippet demonstrates the call with concrete types; the object must be confirmed to be in the engaged state before accessing the value.

```cpp
#include <asc/std/optional>

void example()
{
    asc::std::optional<int> value(7);
    value = asc::std::nullopt;
}
```

## Related APIs

- [`asc::std::optional`](optional.md)
- [API list for this header](asc_std_optional.md)
