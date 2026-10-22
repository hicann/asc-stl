# asc::args::deferred_sequence::deferred_sequence

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

`asc::args::deferred_sequence::deferred_sequence` initializes an `asc::args::deferred_sequence` object with the caller-provided arguments.

## Function Prototype

Member of: [`asc::args::deferred_sequence`](args_deferred_sequence.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::args::deferred_sequence; template parameters and other members are provided by the owning class.
constexpr explicit deferred_sequence(const T* data, asc::std::size_t size) noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::args::deferred_sequence; template parameters and other members are provided by the owning class.
constexpr explicit deferred_sequence(const T* data, asc::std::size_t size, Bounds bounds) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `data` | Input | Pointer to the first element of the deferred sequence on the device side: the wrapper does not copy the data, the pointer must not be null during use, and the storage it points to must cover the entire period of use. |
| `size` | Input | Number of elements in the sequence (counted in elements, not bytes). |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `data` | Input | Pointer to the first element of the deferred sequence on the device side: the wrapper does not copy the data, the pointer must not be null during use, and the storage it points to must cover the entire period of use. |
| `size` | Input | Number of elements in the sequence (counted in elements, not bytes). |
| `bounds` | Input | Bounds object (no_bounds/static_bounds/runtime_bounds) for the sequence values: lets the backend make a safe selection without synchronously reading device data. |

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
    int values[] = {2, 4};
    asc::args::deferred_sequence<int> argument(values, 2);
    return argument.size() == 2 && argument.data() == values && argument.data()[1] == 4;
}
```

## Related APIs

- [`asc::args::deferred_sequence`](args_deferred_sequence.md)
- [API list for this header](asc_argument.md)
