# asc::std::ranges::common_view::size

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

`asc::std::ranges::common_view::size` returns the number of elements contained in the current object.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`common_view`](ranges_common_view.md). The following is a declaration summary listed by participation conditions; template defaults used for calls are kept, and implementation-selection parameters used only for SFINAE are omitted. When a private return type is involved, it is summarized as auto; this does not promise the type can be named directly.

### Prototype 1

```cpp
template<class View2 = View>
constexpr auto size();
```

Participation condition: `(sized_range<View2>)`.

### Prototype 2

```cpp
template<class View2 = View>
constexpr auto size() const;
```

Participation condition: `(sized_range<const View2>)`.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `View2` | The owning type or kind used to defer member checks, with the default value shown in the prototype; ordinary calls do not need to specify it explicitly. |

No function parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `View2` | The owning type or kind used to defer member checks, with the default value shown in the prototype; ordinary calls do not need to specify it explicitly. |

No function parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `auto` | Returns the number of elements in the current range; the exact integer type of auto is determined by the corresponding size computation and can be queried through decltype(object.size()). |
| Prototype 2 | `auto` | Returns the number of elements in the current range; the exact integer type of auto is determined by the corresponding size computation and can be queried through decltype(object.size()). |

## Constraints

- The participation condition of each form is shown in the prototype; no-argument queries are generally called directly without specifying a template selection type.

## Example

This example uses iterators and sentinels of different types; common_view converts them into first and last positions representable by the same type.

```cpp
#include <asc/std/ranges>
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6};
    using Iterator = asc::std::counted_iterator<int*>;
    using Base = asc::std::ranges::subrange<Iterator, asc::std::default_sentinel_t>;
    Base base(Iterator(values, 3), asc::std::default_sentinel);
    asc::std::ranges::common_view<Base> view(base);
    return view.size() == 3;
}
```

## Related APIs

- [`asc::std::ranges::common_view`](ranges_common_view.md)
- [API list for this header](asc_std_ranges.md)
