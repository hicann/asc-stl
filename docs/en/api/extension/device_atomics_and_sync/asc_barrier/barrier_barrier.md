# asc::barrier::barrier

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

Header: `<asc/barrier>`.

`asc::barrier::barrier` initializes an `asc::barrier` object with the arguments provided by the caller.

## Function Prototype

Member of: [`asc::barrier`](barrier.md).

```cpp
// Excerpt of the declaration inside the asc::barrier class; template parameters and other members are provided by the owning class.
constexpr explicit barrier(asc::std::ptrdiff_t expected, CompletionFunction completion = CompletionFunction()) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `expected` | Input | The number of participants expected to arrive in each phase: after all of them have arrived, the completion function is triggered and the next phase is entered; must be within [0, max()]. |
| `completion` | Input | The phase completion function: invoked after all participants of this phase have arrived and before entering the next phase; defaults to an empty implementation. |

## Return Value

No return value.

## Constraints

- The initial expected must be within `[0, max()]`; the update of arrive must be non-negative and must not exceed the remaining count of the current phase. When expected is 0, arrival with a positive update is not allowed; arrive_and_drop additionally requires the subsequent expected count to be currently positive.

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following AI Core SIMT snippet uses a caller-managed GM synchronization object; the participant count and progress conditions must satisfy the constraints on this page.

```cpp
#include <asc/barrier>

#include <asc/std/new>

__aicore__ void example(asc::barrier<asc::memory_scope::block>* gm_storage)
{
    // gm_storage is caller-provided, aligned GM storage.
    ::new (static_cast<void*>(gm_storage)) asc::barrier<asc::memory_scope::block>(1);
}
```

## Related APIs

- [`asc::barrier`](barrier.md)
- [API list for this header](asc_barrier.md)
