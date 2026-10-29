# asc::std::queue::value_type

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

`asc::std::queue::value_type` denotes the value type of elements or results.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Declaration

Member of: [`asc::std::queue`](queue.md).

```cpp
// Excerpt of the declaration inside class asc::std::queue; template parameters and other members are provided by the owning class.
using value_type = typename Container::value_type;
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
#include <type_traits>
#include <cstddef>
#include <utility>

using alias_type = typename asc::std::queue<int, ::std::deque<int>>::value_type;
static_assert(::std::is_same_v<alias_type, int>);
```

## Related APIs

- [`asc::std::queue`](queue.md)
- [API list for this header](asc_std_queue.md)
