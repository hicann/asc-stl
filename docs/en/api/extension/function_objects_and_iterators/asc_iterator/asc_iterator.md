# Header asc/iterator

Provides independent constant, counting, index, strided, transformed and zipped access. Adaptors own their state and borrow data ranges.

## Usage

```cpp
#include <asc/iterator>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::constant_iterator](constant_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::counting_iterator](counting_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::discard_iterator](discard_iterator.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_constant_iterator](make_constant_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_counting_iterator](make_counting_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_discard_iterator](make_discard_iterator.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_permutation_iterator](make_permutation_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_shuffle_iterator](make_shuffle_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_strided_iterator](make_strided_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_tabulate_output_iterator](make_tabulate_output_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_transform_input_output_iterator](make_transform_input_output_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_transform_iterator](make_transform_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_transform_output_iterator](make_transform_output_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_zip_function](make_zip_function.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_zip_iterator](make_zip_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_zip_transform_iterator](make_zip_transform_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::permutation_iterator](permutation_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::shuffle_iterator](shuffle_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::strided_iterator](strided_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tabulate_output_iterator](tabulate_output_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::transform_input_output_iterator](transform_input_output_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::transform_iterator](transform_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::transform_output_iterator](transform_output_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::zip_function](zip_function.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::zip_iterator](zip_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::zip_transform_iterator](zip_transform_iterator.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |

## Iterator protocol

Adaptors expose value_type, reference, difference_type, pointer, iterator_category and iterator_concept. Differences are signed. They provide dereference and postfix/prefix increment. Bidirectional and random navigation additionally supplies decrement, +=/-=, both additions, offset subtraction, distance, subscript and all comparisons. Unsupported operations are constrained out.

| Adaptors | Legacy category | C++20 concept ceiling |
| --- | --- | --- |
| constant/counting/shuffle | input | random_access |
| permutation | input | follows the index iterator |
| strided | random_access for genuine references and a conforming legacy base; input otherwise | random_access |
| transform/input_output/zip_transform | input | follows the base |
| readable zip | input | weakest component |
| output adaptors/output zip | output | output, with independent navigation operations |

Concepts require actual common-reference, stable-read, multi-pass and complexity laws. No adaptor promises contiguity. Defaults are unbound except discard at position0. Unbound objects cannot be accessed or advanced. Capturing lambdas need not be default-constructible or assignable.

A const iterator does not make data const. Converting to a const base preserves address spaces. Actual data and callable access must be legal in Host, SIMT or scalar SIMD. Host inclusion needs no SDK. Packed elements remain storage elements, without implicit unpacking or conversion.

Read callables are stable and const-invoked. Write proxies own mutable callable snapshots and position snapshots; borrowed targets still need a valid lifetime. Value results own their values; references cannot escape temporary state. Arrow proxies last through the full expression.

iter_move uses the logical result. iter_swap/proxy swap are constrained to supported read/write, movement and swap protocols. Read/write transforms preserve the written logical value on readback. Rearrangement requires independent targets and stable addressing. Repeated indices and crossing aliases cannot gain semantic sorting guarantees from a static concept. Earlier writes are not rolled back on exceptions.

Strided ends store logical positions and never form invalid physical pointers. Zip callers supply a common length. Equality checks every position and distances must agree. There is no automatic shortest end, allocation or task submission.

## Migration

Replace unbounded iterator/stride construction with first/extent/stride. base() returns the physical anchor. Counting uses index() rather than base(); origin and position are separate. Use ==/!= instead of zip.equal. zip_transform is a composition alias. Complete protocols replace the old lightweight-operation limitations.
