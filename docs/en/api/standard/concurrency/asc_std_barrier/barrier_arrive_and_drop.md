# asc::std::barrier::arrive_and_drop

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

Header: `<asc/std/barrier>`.

`asc::std::barrier::arrive_and_drop` arrives at the current phase and permanently reduces the expected participant count of subsequent phases.

This interface is available on the Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `barrier`](https://en.cppreference.com/w/cpp/header/barrier).

## Function Prototype

Member of: [`asc::std::barrier`](barrier.md).

```cpp
// Excerpt of the declaration inside the asc::std::barrier class; template parameters and other members are provided by the owning class.
void arrive_and_drop();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- Host objects use native ordinary memory and CPU atomic operations and do not manage NPU GM state. AI Core SIMT shared objects must be located in GM and must be initialized before concurrent access; calls in AI Core SIMD programming are not supported.
- All participants must be able to make progress concurrently, and operations that wait additionally require that the completion condition can be satisfied.

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <asc/std/barrier>

struct completion {
    int* phases;
    void operator()() noexcept { ++*phases; }
};

bool example()
{
    int phases = 0;
    asc::std::barrier<completion> barrier(1, completion{&phases});
    barrier.arrive_and_drop();
    return phases == 1;
}
```

## Related APIs

- [`asc::std::barrier`](barrier.md)
- [API list for this header](asc_std_barrier.md)
