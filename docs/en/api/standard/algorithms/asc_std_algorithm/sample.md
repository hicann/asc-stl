# asc::std::sample

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

`asc::std::sample` randomly selects a specified number of elements from the input range; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

```cpp
namespace asc::std {
template <class PopulationIterator, class SampleIterator, class Distance, class UniformRandomNumberGenerator>
SampleIterator sample(PopulationIterator first, PopulationIterator last, SampleIterator output_iter, Distance n,
    UniformRandomNumberGenerator&& g);
}  // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `PopulationIterator` | Iterator type used to traverse the population (input) range; must satisfy at least the input iterator traversal capability. |
| `SampleIterator` | Output iterator type used to write the sampling results; when the population is a forward iterator, the results preserve the original relative order. |
| `Distance` | Integer type representing the sample count and range distances. |
| `UniformRandomNumberGenerator` | Uniform random number generator type; invoked in the form g(), with a return value convertible to an unsigned integer. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the population (input) range. |
| `last` | Input | End position of the population (input) range, exclusive. |
| `output_iter` | Output | Output iterator for writing the sampling results; the destination range must have capacity for at least min(n, input range length) elements. |
| `n` | Input | Desired number of elements to sample; the actual number written does not exceed min(n, input range length). |
| `g` | Input/Output | Uniform random number generator object that produces random numbers when invoked in the form g(); its state is advanced during sampling. |

## Return Value

| Return type | Description |
| --- | --- |
| `SampleIterator` | Returns the position after the last written element in the output range. |

## Constraints

- `n >= 0`; the output range must be able to hold `min(n, input length)` elements.
- If the population satisfies only the input iterator requirements, the output iterator must support random access; when the population is a forward iterator, an ordinary output iterator may be used, and the relative order of the selected elements is preserved.

- The random number engine is provided by the caller and must satisfy the URBG requirements.
- Returns the end iterator of the sampled output range.

## Example

The following Host example checks the result and the output while the local ranges are still valid; the function returns a boolean value that can be checked independently.

```cpp
#include <asc/std/algorithm>

#include <asc/std/random>
bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    asc::std::minstd_rand random_engine(9);
    auto result = asc::std::sample(values, values + 8, output, 4, random_engine);
    for (int* current = output; current != result; ++current) {
        if (*current < 1 || *current > 8)
            return false;
        for (int* earlier = output; earlier != current; ++earlier) {
            if (*earlier == *current)
                return false;
        }
    }
    return result == output + 4;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
