# asc::std::erase_if

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

Header: `<asc/std/inplace_vector>`.

`asc::std::erase_if` currently has no free function overload accepting inplace_vector. This page keeps the original entry for compatibility notes; the member [`erase_if`](inplace_vector_erase_if.md) can be used to remove elements by condition.

## Function Prototype

This free function overload is not provided. The replacement interface is the container's member erase_if; its prototype and conditions are described on the [member page](inplace_vector_erase_if.md).

## Parameters

This page declares no free function parameters. The example calls the member erase_if on an existing container.

## Return Value

This page declares no free function return value; the replacement member erase_if returns the number of removed elements.

## Constraints

- The replacement member `erase_if` is provided from C++17 onward; both Host and device-side use must satisfy that member's non-throwing operation conditions.

- Use the linked member's predicate, element-operation, and lifetime conditions; do not call a free function that does not exist.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(2) || !values.try_push_back(3)) return false;
    const auto removed = values.erase_if([](int value) { return value % 2 == 0; });
    return removed == 1 && values.size() == 1 && values[0] == 3;
}
```

## Related APIs

- [API list for this header](asc_std_inplace_vector.md)
