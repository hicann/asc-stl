# asc::std::unique_lock::swap

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

Header: `<asc/std/mutex>`.

`asc::std::unique_lock::swap` swaps the locks and ownership states held by two lock wrappers.

Standard semantics reference: [cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex).

## Function Prototype

Member of: [`asc::std::unique_lock`](unique_lock.md).

```cpp
// Excerpt of the declaration inside the asc::std::unique_lock class; template parameters and other members are provided by the owning class.
void swap(unique_lock<Mutex>& other) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The other object whose state is swapped with the current object; after the swap, both hold each other's original state. |

## Return Value

No return value.

## Constraints

- unique_lock<Mutex>: mutex_type, default/plain/defer/try/adopt constructors, deleted copy, move construction/assignment, and destructor.
- lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool and the non-member swap on valid states.
- The explicit non-throwing Device Lockable domain.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host snippet demonstrates the call with standard lock objects; the caller must follow the lock ownership and lifetime constraints.

```cpp
#include <asc/std/mutex>

#include <mutex>

void example()
{
    asc::std::unique_lock<::std::mutex> left{}, right{};
    left.swap(right);
}
```

## Related APIs

- [`asc::std::unique_lock`](unique_lock.md)
- [API list for this header](asc_std_mutex.md)
