# asc::std::chrono::treat_as_floating_point_v

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

Header: `<asc/std/chrono>`.

`asc::std::chrono::treat_as_floating_point_v` indicates whether the given duration representation type is treated as floating point.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

Located in the asc::std::chrono namespace; the variable template reads the trait value, including explicit specializations for user-defined Rep.

```cpp
template<class Rep>
inline constexpr bool treat_as_floating_point_v = treat_as_floating_point<Rep>::value;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep` | The count type whose corresponding treat_as_floating_point specialization is read. |

## Constraints

- Rep is the count representation type of a duration; by default it is determined by is_floating_point.
- A custom count type can explicitly specialize treat_as_floating_point before first use; _v reads the value of that specialization.
- duration construction uses this value to decide whether initialization from a floating-point count is allowed; the other convertibility and representability requirements must still be satisfied.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>
#include <asc/std/type_traits>

struct custom_rep {
    float value;
    constexpr custom_rep(float input) : value(input) {}
};

namespace asc::std::chrono {
template <> struct treat_as_floating_point<custom_rep> : true_type {};
}

static_assert(!asc::std::is_floating_point_v<custom_rep>);
static_assert(asc::std::chrono::treat_as_floating_point_v<custom_rep>);

bool example()
{
    const asc::std::chrono::duration<custom_rep> value(1.5F);
    return value.count().value == 1.5F;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
