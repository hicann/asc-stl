# asc::std::mbsinit

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

Header: `<asc/std/cwchar>`.

`asc::std::mbsinit` processes wide characters or multibyte sequences under a multibyte conversion state saved by the caller.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
int mbsinit(const mbstate_t* state) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `state` | Input | The mbstate_t object that stores the multibyte conversion progress; it is only queried for whether it is the initial state, and a null pointer is also treated as the initial state. |

## Return Value

| Return type | Description |
| --- | --- |
| `int` | Returns a non-zero value when the state is the initial conversion state or state is null, and returns 0 otherwise. |

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- Device is fixed to stateless single-byte conversion and supports only ASCII and the null character; out-of-range input reports failure as described in the return value of this interface.
- Different character sequences use independent state objects; string output buffers must have sufficient capacity.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>

decltype(auto) example(const asc::std::mbstate_t * state)
{
    return asc::std::mbsinit(state);
}

bool verify_example()
{
    asc::std::mbstate_t state{};
    return example(&state) != 0;
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
