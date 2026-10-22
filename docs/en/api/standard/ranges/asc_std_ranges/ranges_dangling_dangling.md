# asc::std::ranges::dangling::dangling

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

Header: `<asc/std/ranges>`.

`asc::std::ranges::dangling::dangling` initializes a `dangling` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

### Prototype 1

```cpp
constexpr dangling();
```

### Prototype 2

```cpp
template<class ...Args> constexpr dangling(Args&&... args) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Args` | The list of argument types passed to the constructor or callable object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `args` | Input/Output | The list of arguments forwarded to object construction or a function call. |

## Return Value

No return value.

## Constraints

- Supports arrays and user-defined ranges; does not support initializer_list expressions formed only of braces.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/algorithm>
#include <asc/std/type_traits>

struct IsTwo { bool operator()(int value) const { return value == 2; } };

bool example()
{
    auto temporary_result = asc::std::ranges::find_if(asc::std::array<int, 2>{1, 2}, IsTwo{});
    static_assert(asc::std::is_same_v<decltype(temporary_result), asc::std::ranges::dangling>);
    // Find on a saved range object; only then can the returned position be used.
    asc::std::array<int, 2> values{1, 2};
    return *asc::std::ranges::find_if(values, IsTwo{}) == 2;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
