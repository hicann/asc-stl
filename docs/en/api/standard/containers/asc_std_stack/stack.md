# asc::std::stack

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

Header: `<asc/std/stack>`.

`asc::std::stack` accesses the underlying container in last-in first-out order.

Standard semantics reference: [cppreference `stack`](https://en.cppreference.com/w/cpp/header/stack).

## Declaration

```cpp
namespace asc::std {
template<class T, class Container> class stack;
} // namespace asc::std
```

## Constraints

- T and Container must be specified explicitly, and T must be the same as Container::value_type.
- No standalone allocator construction, uses_allocator specialization, comparison operators, or explicit deduction guides are provided.
- On the device side, the Container, element operations, and Compare used must be callable at the corresponding execution location and satisfy its non-throwing requirements; on Host, exception behavior follows the invoked object, and non-throwing is not promised unless noexcept is explicitly declared.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <deque>
#include <asc/std/stack>

bool example()
{
    asc::std::stack<int, ::std::deque<int>> values;
    values.push(1);
    values.push(2);
    values.pop();
    return values.size() == 1 && values.top() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_stack.md)
