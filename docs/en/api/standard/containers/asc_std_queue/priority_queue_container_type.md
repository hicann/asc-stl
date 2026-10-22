# asc::std::priority_queue::container_type

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

`asc::std::priority_queue::container_type` denotes the underlying container type used by the container adaptor.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Declaration

Member of: [`asc::std::priority_queue`](priority_queue.md).

```cpp
// Excerpt of the declaration inside class asc::std::priority_queue; template parameters and other members are provided by the owning class.
using container_type = Container;
```

## Constraints

- This alias is taken from the selected Container or Compare; the alias query itself constructs no container and invokes no comparator.

## Example

The following Host snippet explicitly provides a standard container as the underlying storage; on the device side, a container callable at the target location must be provided.

```cpp
#include <asc/std/queue>
#include <deque>
#include <functional>
#include <vector>

void use_type()
{
    using alias_type = typename asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>>::container_type;
}
```

## Related APIs

- [`asc::std::priority_queue`](priority_queue.md)
- [API list for this header](asc_std_queue.md)
