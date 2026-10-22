# asc::std::ranges::subrange::advance

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

`asc::std::ranges::subrange::advance` advances the start position of the current subrange by the specified distance.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`subrange`](ranges_subrange.md). SFINAE selection parameters are omitted below. The const lvalue form of next requires forward_iterator<It>; prev requires bidirectional_iterator<It>; It defaults to Iter. The distance type is ptrdiff_t of the implementation platform.

### Prototype 1

```cpp
constexpr subrange& advance(ptrdiff_t amount);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `amount` | Input | The signed position offset, in iterator steps; no default value. Positive values move forward, and negative values require the underlying iterator to support bidirectional movement. |

## Return Value

Returns *this, updating the start position and the applicable stored count in place.

## Constraints

- Moving in the positive direction stops at the original end; negative movement requires bidirectional_iterator and must not move past the reachable underlying start boundary.
- amount and the conversion to iter_difference_t<Iter> must be representable; prev additionally requires negation to be valid.
- The result still borrows the original storage and does not extend the lifetime of the elements.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::ranges::subrange<int*> view(values + 1, values + 4);
    view.advance(1);
    return *view.begin() == 3 && view.size() == 2;
}
```

## Related APIs

- [`asc::std::ranges::subrange`](ranges_subrange.md)
- [API list for this header](asc_std_ranges.md)
