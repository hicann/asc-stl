# asc::std::unordered_map::empty

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

Header: `<asc/std/unordered_map>`.

`asc::std::unordered_map::empty` checks whether the current object contains no elements.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `unordered_map`](https://en.cppreference.com/w/cpp/header/unordered_map).

## Function Prototype

Member of: [`asc::std::unordered_map`](unordered_map.md).

```cpp
// Excerpt of the declaration inside class asc::std::unordered_map; template parameters and other members are provided by the owning class.
bool empty() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` if the object contains no elements, otherwise `false`. |

## Constraints

- In Host and AI Core SIMT programming, unordered_map<Key,T,Hash,Equal,A> requires an explicit GM arena.
- empty/size/bucket_count/begin/end/insert/find/count/`operator[]`/clear.
- The allocator rebinds for the bucket array and automatically rehashes at the default load-factor threshold.
- Collision chains, duplicate-key rejection, stable node addresses across rehash, old iterators remaining valid after move, and destruction.
- Only in domains with sufficient capacity and no exceptions thrown.
- Host and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory>
#include <functional>
#include <asc/std/unordered_map>
#include <asc/std/utility>

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    using allocator = asc::arena_allocator<asc::std::pair<const int, int>>;
    asc::std::unordered_map<int, int, ::std::hash<int>, ::std::equal_to<int>, allocator> values(allocator{arena});
    values[1] = 7;
    values[3] = 9;
    return !values.empty();
}
```

## Related APIs

- [`asc::std::unordered_map`](unordered_map.md)
- [API list for this header](asc_std_unordered_map.md)
