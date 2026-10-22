# asc::std::priority_queue

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

Header: `<asc/std/queue>`.

`asc::std::priority_queue` accesses the underlying container by comparator-defined priority.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Declaration

```cpp
namespace asc::std {
template<class T, class Container, class Compare> class priority_queue;
} // namespace asc::std
```

## Constraints

- T and Container must be specified explicitly, and T must be the same as Container::value_type.
- The third template argument Compare may be omitted; the default comparison is equivalent to the element's less-than comparison, so the top of the heap is the largest element. Its exact type is queried through value_compare and must not be assumed to be identical to asc::std::less.
- Separate allocator construction, uses_allocator specializations, comparison operators, and explicit deduction guides are not provided.
- For device-side use, the Container, element operations, and Compare must be callable at the corresponding execution location and satisfy its non-throwing requirements; the exception behavior on Host follows the objects being called, and freedom from throwing is not promised unless noexcept is additionally declared.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <vector>
#include <functional>
#include <asc/std/queue>

bool example()
{
    asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>> values;
    values.push(1);
    values.push(3);
    values.push(2);
    return values.size() == 3 && values.top() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_queue.md)
