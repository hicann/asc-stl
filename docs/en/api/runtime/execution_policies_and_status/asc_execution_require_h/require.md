# asc::require

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

Header: `<asc/execution.require.h>`.

`asc::require` creates a combination of execution requirements, or replaces one of the determinism, output-ordering, or equal-key-value handling rule dimensions in an existing combination while keeping the other dimensions.

This interface is available on Host.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::determinism value) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::execution_requirements base, asc::determinism value) noexcept;
}  // namespace asc
```

### Prototype 3

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::execution_requirements base, asc::output_ordering value) noexcept;
}  // namespace asc
```

### Prototype 4

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::execution_requirements base, asc::tie_break value) noexcept;
}  // namespace asc
```

### Prototype 5

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::output_ordering value) noexcept;
}  // namespace asc
```

### Prototype 6

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::tie_break value) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The determinism requirement enumeration value (asc::determinism: device_to_device, run_to_run, not_guaranteed): sets this dimension on top of the default combination. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `base` | Input | An existing combination of execution requirements: the returned combination replaces only the determinism dimension, and the other dimensions keep their original values. |
| `value` | Input | The determinism requirement enumeration value (asc::determinism): replaces the determinism dimension in the base combination. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `base` | Input | An existing combination of execution requirements: the returned combination replaces only the output-ordering dimension, and the other dimensions keep their original values. |
| `value` | Input | The output-ordering requirement enumeration value (asc::output_ordering): replaces the output-ordering dimension in the base combination. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `base` | Input | An existing combination of execution requirements: the returned combination replaces only the equal-key-value handling dimension, and the other dimensions keep their original values. |
| `value` | Input | The equal-key-value handling rule enumeration value (asc::tie_break): replaces this dimension in the base combination. |

### Parameters of Prototype 5

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The output-ordering requirement enumeration value (asc::output_ordering: sorted, stable_sorted, unsorted): sets this dimension on top of the default combination. |

### Parameters of Prototype 6

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The equal-key-value handling rule enumeration value (asc::tie_break: unspecified, prefer_smaller_index, prefer_larger_index): sets this dimension on top of the default combination. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::execution_requirements` | Returns a combination of execution requirements, or replaces one of the determinism, output-ordering, or equal-key-value handling rule dimensions in an existing combination while keeping the other dimensions. |
| Prototype 2 | `asc::execution_requirements` | Returns a combination of execution requirements, or replaces one of the determinism, output-ordering, or equal-key-value handling rule dimensions in an existing combination while keeping the other dimensions. |
| Prototype 3 | `asc::execution_requirements` | Returns a combination of execution requirements, or replaces one of the determinism, output-ordering, or equal-key-value handling rule dimensions in an existing combination while keeping the other dimensions. |
| Prototype 4 | `asc::execution_requirements` | Returns a combination of execution requirements, or replaces one of the determinism, output-ordering, or equal-key-value handling rule dimensions in an existing combination while keeping the other dimensions. |
| Prototype 5 | `asc::execution_requirements` | Returns a combination of execution requirements, or replaces one of the determinism, output-ordering, or equal-key-value handling rule dimensions in an existing combination while keeping the other dimensions. |
| Prototype 6 | `asc::execution_requirements` | Returns a combination of execution requirements, or replaces one of the determinism, output-ordering, or equal-key-value handling rule dimensions in an existing combination while keeping the other dimensions. |

## Constraints

- Constructs or updates the execution requirements value synchronously on the Host and does not submit any task.
- The overloads with `base` replace only the determinism, output-ordering, or index preference passed in this time and keep the other two.
- The overloads without `base` construct from the default execution requirements; they do not bind or change the Stream or temporary storage.

## Example

This Host example submits no Runtime work and checks configuration or resource-reference results using concrete values. This checks only that requirements are recorded; consult each algorithm for the requirements its current backend honors.

```cpp
#include <asc/execution.require.h>

bool example()
{
    const auto deterministic = asc::require(asc::determinism::run_to_run);
    const auto ordered = asc::require(deterministic, asc::output_ordering::stable_sorted);
    const auto selected = asc::require(ordered, asc::tie_break::prefer_smaller_index);
    return selected.determinism_value() == asc::determinism::run_to_run &&
        selected.output_ordering_value() == asc::output_ordering::stable_sorted &&
        selected.tie_break_value() == asc::tie_break::prefer_smaller_index &&
        deterministic.output_ordering_value() == asc::output_ordering::unsorted;
}
```

## Related APIs

- [API list for this header](asc_execution_require_h.md)
