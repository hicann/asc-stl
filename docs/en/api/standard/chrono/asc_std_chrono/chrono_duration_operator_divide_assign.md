# asc::std::chrono::duration::`operator/=`

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

`asc::std::chrono::duration::operator/=` processes the current object and the operand according to the rules of the available operators for `duration`.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::duration`](chrono_duration.md).

```cpp
// Declaration excerpt from inside the asc::std::chrono::duration class; template parameters and other members are provided by the enclosing class.
constexpr duration<Rep, Period>& operator/=(const rep& scalar);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `scalar` | Input | Provides the object reference used by "process the current object and the operand according to the rules of the available operators for `duration`"; the referenced object must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `duration<Rep, Period> &` | Returns a reference to the current object after the update, which can continue to take part in assignment or compound operations. |

## Constraints

- The scalar form uses a rep count; the duration form uses counts of the same duration type.
- For integer counts, the current implementation treats a divisor of 0 as 1; use a non-zero divisor when standard portable semantics are required.
- Must not be called when the signed minimum value divided by -1 is not representable; the result and intermediate values must be representable.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/chrono>

bool example()
{
    asc::std::chrono::duration<int> value{6};
    auto& updated = (value /= 2);
    return &updated == &value && value.count() == 3;
}
```

## Related APIs

- [`asc::std::chrono::duration`](chrono_duration.md)
- [API list for this header](asc_std_chrono.md)
