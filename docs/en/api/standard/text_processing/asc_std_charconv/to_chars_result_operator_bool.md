# asc::std::to_chars_result::operator bool

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

Header: `<asc/std/charconv>`.

`asc::std::to_chars_result::operator bool` returns whether the conversion completed without an error: true when `ec == errc{}`, supporting the conditional-check idiom.

Standard semantics reference: [cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv).

## Function Prototype

```cpp
explicit asc::std::to_chars_result::operator bool() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | true when ec equals errc{} (no conversion error). |

## Constraints

- The result is true if and only if the error code equals a default-constructed errc.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/charconv>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.operator bool(static_cast<Args&&>(args)...);
}

bool verify_example()
{
    char storage[2] = {};
    asc::std::to_chars_result success{storage, asc::std::errc{}};
    asc::std::to_chars_result failure{storage, asc::std::errc::invalid_argument};
    return example(success) && !example(failure);
}
```

## Related APIs

- [API list for this header](asc_std_charconv.md)
