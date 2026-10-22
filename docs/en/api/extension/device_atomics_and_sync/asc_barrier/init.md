# asc::init

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

`asc::init` initializes a barrier and its expected number of participants in caller-provided storage.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <asc::memory_scope Scope, class CompletionFunction>
void init(asc::barrier<Scope, CompletionFunction>* object, asc::std::ptrdiff_t expected) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <asc::memory_scope Scope, class CompletionFunction>
void init(asc::barrier<Scope, CompletionFunction>* object, asc::std::ptrdiff_t expected,
    CompletionFunction completion) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Scope` | The synchronization scope enumeration value (asc::memory_scope::block or device): limits the visibility and synchronization range of the fence's atomic operations. |
| `CompletionFunction` | The phase completion function type: invoked after all participants of this phase have arrived; defaults to an empty implementation. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input | Pointer to the barrier object in caller-provided GM storage: constructed in place with placement new; the storage lifetime must cover all concurrent accesses. |
| `expected` | Input | The number of participants expected to arrive in each phase: after all of them have arrived, the completion function is triggered and the next phase is entered; must be within [0, max()]. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Scope` | The synchronization scope enumeration value (asc::memory_scope::block or device): limits the visibility and synchronization range of the fence's atomic operations. |
| `CompletionFunction` | The phase completion function type: invoked after all participants of this phase have arrived; defaults to an empty implementation. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input | Pointer to the barrier object in caller-provided GM storage: constructed in place with placement new; the storage lifetime must cover all concurrent accesses. |
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

The following snippet initializes a caller-provided thread-block barrier in AI Core SIMT programming; the object storage must remain valid while all participants use it.

```cpp
#include <asc/barrier>

__aicore__ void example(asc::barrier<asc::memory_scope::block>* object)
{
    asc::init(object, 32);
}
```

## Related APIs

- [API list for this header](asc_barrier.md)
