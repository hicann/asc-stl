# asc::std::ranges::operator|

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

`asc::std::ranges::operator|`, provided by `<asc/std/ranges>`, is the pipelined composition operation for two range adaptor closures, producing a composed closure equivalent to applying them in sequence. The interface follows the semantics of the corresponding C++ standard facility; ASC-STL's language modes and call locations are governed by the declarations on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

```cpp
namespace asc::std::ranges {
template<class Closure, class OtherClosure> constexpr auto operator|(Closure&& closure, OtherClosure&& other_closure) noexcept(asc::std::is_nothrow_constructible_v<asc::std::decay_t<Closure>, Closure> && asc::std::is_nothrow_constructible_v<asc::std::decay_t<OtherClosure>, OtherClosure>);
} // namespace asc::std::ranges
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Closure` | The type of the left range adaptor closure. |
| `OtherClosure` | The type of the right range adaptor closure. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `OtherClosure` | Input | A reference to the object participating in the operation; the referenced object must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `auto` | The view obtained by passing the range into the right closure, or the new closure obtained by composing the two closures. |

## Constraints

- Both arguments must be range adaptor closures; the composed result is still a closure, and applying it to a range is equivalent to calling left first and then right in sequence.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto view = values | asc::std::ranges::views::drop(1) | asc::std::ranges::views::take(2);
    return *view.begin() == 2 && view.size() == 2;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
