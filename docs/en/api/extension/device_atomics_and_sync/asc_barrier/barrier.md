# asc::barrier

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

`asc::barrier` provides a reusable phased thread barrier and invokes the completion function when each phase completes.

## Declaration

```cpp
namespace asc {
// Declaration summary: the default template argument of CompletionFunction is described below.
template<asc::memory_scope Scope, class CompletionFunction> class barrier;
} // namespace asc
```

`CompletionFunction` defaults to the empty completion function type provided by the library; therefore `asc::barrier<asc::memory_scope::block>` can be written directly. A custom completion function must be callable with no arguments and must not throw, and is invoked in each phase by the thread that completes that phase.

## Constraints

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following snippet is compiled for AI Core SIMT programming. The barrier is located in initialized shared GM storage; the expected count matches the number of participating threads in this round, and all participants of the same block must arrive. The next phase can be entered only after completion.

```cpp
#include <asc/barrier>

__aicore__ void example(asc::barrier<asc::memory_scope::block>& barrier)
{
    barrier.arrive_and_wait();
}
```

## Related APIs

- [API list for this header](asc_barrier.md)
