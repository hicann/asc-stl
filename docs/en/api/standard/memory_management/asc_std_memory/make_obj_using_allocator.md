# asc::std::make_obj_using_allocator

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

This page keeps the original entry for compatibility notes. `<asc/std/memory>` currently does not provide `asc::std::make_obj_using_allocator`.

Ordinary objects can be constructed with [`construct_at`](construct_at.md) and destroyed with [`destroy_at`](destroy_at.md); this does not automatically inject an allocator. Types requiring allocator construction must have the arguments their constructors require passed explicitly by the caller.

## Function Prototype

The current product does not declare the interface named in this page's title. Use the provided interface described below.

## Parameters

This page declares no callable interface parameters.

## Return Value

This page declares no interface return value; see the Example section for the result of the alternative call.

## Constraints

- `<asc/std/memory>` currently does not provide `asc::std::make_obj_using_allocator`.
- Ordinary objects can be constructed with [`construct_at`](construct_at.md) and destroyed with [`destroy_at`](destroy_at.md); this does not automatically inject an allocator. Types requiring allocator construction must have the arguments their constructors require passed explicitly by the caller.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>
#include <memory>

bool example()
{
    std::allocator<int> allocator;
    int* storage = allocator.allocate(1);
    int* object = asc::std::construct_at(storage, 7);
    const bool valid = object == storage && *object == 7;
    asc::std::destroy_at(object);
    allocator.deallocate(storage, 1);
    return valid;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
