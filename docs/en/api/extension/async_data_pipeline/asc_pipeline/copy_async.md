# asc::copy_async

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

Header: `<asc/pipeline>`.

`asc::copy_async` submits a contiguous data transfer between GM (Global Memory) and the on-chip buffer (UB) on the specified pipeline stage. After the submission, the completion must be waited on according to the pipeline synchronization rules before the destination view is read or the source storage is reused.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int16_t> destination,
    asc::ub_span<const asc::std::int16_t> source) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int32_t> destination,
    asc::ub_span<const asc::std::int32_t> source) noexcept;
}  // namespace asc
```

### Prototype 3

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int8_t> destination,
    asc::ub_span<const asc::std::int8_t> source) noexcept;
}  // namespace asc
```

### Prototype 4

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::uint16_t> destination,
    asc::ub_span<const asc::std::uint16_t> source) noexcept;
}  // namespace asc
```

### Prototype 5

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::uint32_t> destination,
    asc::ub_span<const asc::std::uint32_t> source) noexcept;
}  // namespace asc
```

### Prototype 6

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::uint8_t> destination,
    asc::ub_span<const asc::std::uint8_t> source) noexcept;
}  // namespace asc
```

### Prototype 7

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<float> destination,
    asc::ub_span<const float> source) noexcept;
}  // namespace asc
```

### Prototype 8

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::int16_t> destination,
    asc::gm_span<const asc::std::int16_t> source) noexcept;
}  // namespace asc
```

### Prototype 9

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::int32_t> destination,
    asc::gm_span<const asc::std::int32_t> source) noexcept;
}  // namespace asc
```

### Prototype 10

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::int8_t> destination,
    asc::gm_span<const asc::std::int8_t> source) noexcept;
}  // namespace asc
```

### Prototype 11

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::uint16_t> destination,
    asc::gm_span<const asc::std::uint16_t> source) noexcept;
}  // namespace asc
```

### Prototype 12

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::uint32_t> destination,
    asc::gm_span<const asc::std::uint32_t> source) noexcept;
}  // namespace asc
```

### Prototype 13

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::uint8_t> destination,
    asc::gm_span<const asc::std::uint8_t> source) noexcept;
}  // namespace asc
```

### Prototype 14

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<float> destination,
    asc::gm_span<const float> source) noexcept;
}  // namespace asc
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pipeline` | Input | Pipeline reference that manages this asynchronous transfer; the pipeline must remain valid until the transfer completes. |
| `stage` | Input | Pipeline stage index; must be less than the number of stages of the pipeline. |
| `destination` | Output | Non-owning view that receives the transfer result; the selected prototype determines whether its storage is in GM or UB, and its length must be sufficient to hold the source data. |
| `source` | Input | Non-owning view that provides the data to transfer; the selected prototype determines whether its storage is in UB or GM, and the underlying storage must remain valid until the transfer completes. |

## Data Types

Two directions are supported: GM → UB and UB → GM. The two views must have the same element type, chosen from `int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t`, or `float`; each type and direction has its own prototype.

## Return Value

No return value.

## Constraints

- The storage at both ends must be 32-byte aligned, the destination capacity must be at least equal to the source capacity, and the source size in bytes must be representable by unsigned int; this interface is not responsible for allocation or capacity validation.
- Each round is ordered as producer_acquire, GM→UB copy, producer_commit, consumer_wait, compute, consumer_release, UB→GM copy, and wait is called after the final round. Returning does not indicate data completion; before the corresponding wait, the destination must not be read and the source must not be reused.

- Can only be called in AI Core SIMD programming.
- Parameter types, address spaces, value ranges, and object lifetimes must satisfy the declarations on this page.

## Example

Launched on 1 AI Core. input and output each contain at least 8 unsigned int elements, with GM start addresses 32-byte aligned; after Host synchronization, output[i] should equal input[i]+1. The complete stage pairing is as follows; for UB→GM, consumer_release must be called before copy_async.

For the complete project, see the [pipeline copy example](../../../../../zh/examples/pipeline_copy/README.md).

```cpp
#include <asc/pipeline>
__global__ __vector__ void example(__gm__ unsigned int* output, __gm__ const unsigned int* input)
{
    alignas(32) __ubuf__ unsigned int buffer[8];
    const auto pipeline = asc::make_pipeline(0, 1);
    pipeline.producer_acquire(0);
    asc::copy_async(pipeline, 0, asc::ub_span<unsigned int>(buffer, 8), asc::gm_span<const unsigned int>(input, 8));
    pipeline.producer_commit(0);
    pipeline.consumer_wait(0);
    for (unsigned index = 0; index < 8; ++index)
        buffer[index] += 1;
    pipeline.consumer_release(0);
    asc::copy_async(pipeline, 0, asc::gm_span<unsigned int>(output, 8), asc::ub_span<const unsigned int>(buffer, 8));
    pipeline.wait();
}
```

## Related APIs

- [asc::make_pipeline](make_pipeline.md)
- [asc::pipeline_ref::producer_commit](pipeline_ref_producer_commit.md)
- [asc::pipeline_ref::consumer_wait](pipeline_ref_consumer_wait.md)
