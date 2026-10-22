# asc::std::c32rtomb

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

Include the public header `<asc/std/cuchar>` and use `asc::std::c32rtomb` to convert one UTF code unit to multibyte output. Host uses the system conversion interface; the device side handles only ASCII and the null character.

Host semantics reference: [cppreference character conversion interface](https://en.cppreference.com/w/cpp/header/cuchar).

## Function Prototype

Host imports the system `std::c32rtomb` via `using`; the exception specification and parameter names follow the system declaration. The following is the device-side declaration; the execution-location macro is omitted. The `__SIZE_TYPE__` used by the device-side implementation is equivalent to the public `asc::std::size_t`.

```cpp
namespace asc::std {
size_t c32rtomb(char* output, char32_t value, mbstate_t* state) noexcept;
}
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | The writable destination buffer. Host requires it to hold the longest sequence of the current encoding; when non-null on the device side, it must hold at least 1 byte. When null on the device side, nothing is written, but the result is still determined by value. |
| `value` | Input | The char32_t code unit to convert. The device side accepts only 0 through 127; surrogate handling and multi-unit continuation on Host follow the system interface. |
| `state` | Input/Output | Host keeps the conversion state across calls; a null pointer uses the system internal state. The device side does not read or write this parameter. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::size_t` | Host: returns the number of bytes written on success; returns `size_t(-1)` and sets the error state on an encoding error. The specific continuation rules depend on this interface and the system locale. Device side: returns 1 when value is 0 through 127, otherwise returns `size_t(-1)`; it never returns an incomplete state. |

## Constraints

- The device side does not perform UTF multi-unit continuation and does not update state. Host keeps the same state object across consecutive conversions and reinitializes the state when converting a different sequence.
- The input and output storage must remain valid during the call; the input range and output capacity conform to the parameter descriptions.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cuchar>

bool example()
{
    char output[8] = {};
    asc::std::mbstate_t state{};
    auto count = asc::std::c32rtomb(output, U'A', &state);
    return count == 1 && output[0] == 'A';
}
```

## Related APIs

- [API list for this header](asc_std_cuchar.md)
