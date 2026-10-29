# asc::std::optional<T&>::`operator*`

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

`asc::std::optional<T&>::operator*` dereferences the current iterator or engaged object.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

```cpp
// Excerpt of the declaration inside class asc::std::optional<T&>; template parameters and other members are provided by the owning class.
constexpr T& operator*() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `T&` | Returns the object referenced by the current iterator or wrapper. |

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
    return *reference;
}

bool verify_example()
{
    int value = 7;
    int& result = example(value);
    result = 9;
    return &result == &value && value == 9;
}
```

## Related APIs

- [API list for this header](asc_std_optional.md)
