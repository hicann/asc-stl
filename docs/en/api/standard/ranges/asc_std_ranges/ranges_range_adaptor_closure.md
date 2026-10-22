# asc::std::ranges::range_adaptor_closure

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

`asc::std::ranges::range_adaptor_closure<Derived>` is the CRTP base class for custom range adaptor closures, enabling callable objects to participate in range pipelines and closure composition. It does not denote a dangling result.

## Declaration

The public CRTP base class has a single template parameter Derived; it is used to declare custom callable objects as range adaptor closures.

```cpp
namespace asc::std::ranges {
template<class Derived>
class range_adaptor_closure;
}
```

## Constraints

- Derived must be a class type without cv-qualifiers and must publicly derive from this base class with its own type; this base class is usable in both C++17 and C++20.
- The pipeline of a range with a closure and the composition between closures participate in overload resolution only when the corresponding closure call expression is valid.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>
#include <asc/std/utility>

struct first_two : asc::std::ranges::range_adaptor_closure<first_two> {
    template<class R>
    auto operator()(R&& range) const
    {
        return asc::std::ranges::views::take(asc::std::forward<R>(range), 2);
    }
};

bool example()
{
    int values[3] = {1, 2, 3};
    auto result = values | first_two{};
    return result.size() == 2 && *result.begin() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
