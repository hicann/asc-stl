# asc::std::priority_queue::reference

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

`asc::std::priority_queue::reference` denotes the writable element reference type.

Standard semantics reference: [cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue).

## Declaration

Member of: [`asc::std::priority_queue`](priority_queue.md).

```cpp
// Excerpt of the declaration inside class asc::std::priority_queue; template parameters and other members are provided by the owning class.
using reference = typename Container::reference;
```

## Constraints

- The type is taken from the same-named member of Container; the reference is valid only while the underlying element is still alive and not invalidated according to Container's rules.
- top() actually returns const_reference; no writable reference is provided through the top-of-heap interface.

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

using alias_type = typename asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>>::reference;
static_assert(::std::is_same_v<alias_type, int&>);
```

## Related APIs

- [`asc::std::priority_queue`](priority_queue.md)
- [API list for this header](asc_std_queue.md)
