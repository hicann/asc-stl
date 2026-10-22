# asc::args::deferred::deferred

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

Header: `<asc/argument>`.

`asc::args::deferred::deferred` initializes an `asc::args::deferred` object with the caller-provided arguments.

## Function Prototype

Member of: [`asc::args::deferred`](args_deferred.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::args::deferred; template parameters and other members are provided by the owning class.
constexpr explicit deferred(const T* data, Bounds bounds) noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::args::deferred; template parameters and other members are provided by the owning class.
constexpr explicit deferred(const T* data) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `data` | Input | Pointer to the deferred data on the device side: the value is readable only after the stream order reaches it; the wrapper does not copy the data, the pointer must not be null during use, and the storage it points to must cover the entire period of use. |
| `bounds` | Input | Bounds object (no_bounds/static_bounds/runtime_bounds) for the values of this deferred argument: lets the backend make a safe selection without synchronously reading device data. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `data` | Input | Pointer to the deferred data on the device side: the value is readable only after the stream order reaches it; the wrapper does not copy the data, the pointer must not be null during use, and the storage it points to must cover the entire period of use. |

## Return Value

No return value.

## Constraints

- Bounds is stored by value and may be a copyable bounds value such as no_bounds, static_bounds, or runtime_bounds; the wrapper does not automatically prove or validate that the data falls within the bounds.
- Deferred data only borrows the pointer; it must be accessible when actually read, and the storage must cover the entire period of use; the size of a sequence is counted in elements and must not exceed the valid range.

- Uses C++17 and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/argument>

bool example()
{
    int value = 7;
    asc::args::deferred<int> argument(&value, asc::args::no_bounds{});
    return argument.data() == &value && *argument.data() == 7;
}
```

## Related APIs

- [`asc::args::deferred`](args_deferred.md)
- [API list for this header](asc_argument.md)
