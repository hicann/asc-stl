# asc::std::atomic::atomic

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

Header: `<asc/std/atomic>`.

`asc::std::atomic::atomic` initializes an `atomic` object with the construction forms listed on this page.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

### Prototype 1

```cpp
atomic() noexcept;
```

### Prototype 2

```cpp
constexpr atomic(T value) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Initial value of the atomic object; written during construction so the initial state is well-defined. |

## Return Value

No return value.

## Constraints

- `T` must be an integer or character type supported by [atomic](atomic.md), including `bool`; the copy constructor is deleted.
- Construction must take place in Host or AI Core SIMT programming; atomic objects shared by SIMT threads must be located in GM and constructed before concurrent access begins.
- Default construction initializes the storage to zero; construction with a value stores the passed-in value. Construction itself establishes no synchronization with other threads.

## Example

The following Host snippet demonstrates the atomic operation; device-side objects must be placed in a valid memory space as specified on this page.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> zero{};
    asc::std::atomic<int> seven{7};
    return zero.load() == 0 && seven.load() == 7;
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
