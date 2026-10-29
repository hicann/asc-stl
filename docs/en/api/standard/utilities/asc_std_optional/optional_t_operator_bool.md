# asc::std::optional<T&>::operator bool

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

`asc::std::optional<T&>::operator bool` handles the current object and its operand according to the operators available for `optional<T&>`.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

The following is inside the corresponding expected or optional class.

```cpp
constexpr explicit operator bool() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the current object is in the valid or engaged state, `false` otherwise. |

## Constraints

- The reference specialization only allows safe same-type lvalue binding.
- Borrowed-pointer semantics are adopted; conversions that easily produce dangling references are not provided.

## Example

The following Host snippet demonstrates the call with concrete types; the object must be confirmed to be in the engaged state before accessing the value.

```cpp
#include <asc/std/optional>

decltype(auto) example(int& value)
{
    asc::std::optional<int&> reference(value);
    return static_cast<bool>(reference);
}

bool verify_example()
{
    int value = 7;
    return example(value);
}
```

## Related APIs

- [API list for this header](asc_std_optional.md)
