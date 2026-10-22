# asc::std::shuffle

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

Header: `<asc/std/algorithm>`.

`asc::std::shuffle` rearranges the range using the random engine provided by the caller; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

```cpp
namespace asc::std {
template <class RandomAccessIterator, class UniformRandomNumberGenerator>
void shuffle(RandomAccessIterator first, RandomAccessIterator last, UniformRandomNumberGenerator&& g);
}  // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RandomAccessIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `UniformRandomNumberGenerator` | Uniform random bit generator type that provides random unsigned integers. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `g` | Input/Output | Reference to the object used to provide "rearranging the range using the random engine provided by the caller"; the referenced object must remain valid during the call. |

## Return Value

No return value.

## Constraints

- The random number engine is provided by the caller and must satisfy the URBG requirements.
- This function rearranges the elements in place and has no return value.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer of sufficient capacity.

```cpp
#include <asc/std/algorithm>

#include <asc/std/random>
void example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    asc::std::minstd_rand random_engine(9);
    asc::std::shuffle(values, values + 8, random_engine);
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
