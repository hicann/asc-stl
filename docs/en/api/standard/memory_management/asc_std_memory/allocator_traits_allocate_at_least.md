# asc::std::allocator_traits::allocate_at_least

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: This page is a compatibility note; the described interface is not provided
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

This page keeps the original entry for compatibility notes. `allocator_traits` has no `allocate_at_least` static member; this page does not promise the availability of the standard library member of the same name.

The provided free function is [`asc::std::allocate_at_least`](allocate_at_least.md), called in the form `asc::std::allocate_at_least(allocator, count)`.

## Function Prototype

The current product does not declare the interface named in this page's title. Use the provided interface described below.

## Parameters

This page declares no callable interface parameters.

## Return Value

This page declares no interface return value; see the Example section for the result of the alternative call.

## Constraints

- `allocator_traits` has no `allocate_at_least` static member; this page does not promise the availability of the standard library member of the same name.
- The provided free function is [`asc::std::allocate_at_least`](allocate_at_least.md), called in the form `asc::std::allocate_at_least(allocator, count)`.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>
#include <memory>

bool example()
{
    std::allocator<int> allocator;
    const auto result = asc::std::allocate_at_least(allocator, 2);
    const bool valid = result.ptr != nullptr && result.count >= 2;
    allocator.deallocate(result.ptr, result.count);
    return valid;
}
```

## Related APIs

- [`asc::std::allocator_traits`](allocator_traits.md)
- [API list for this header](asc_std_memory.md)
