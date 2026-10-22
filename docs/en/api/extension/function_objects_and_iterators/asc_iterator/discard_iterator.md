# asc::discard_iterator

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

Header: `<asc/iterator>`.

`asc::discard_iterator` is an output iterator that accepts writes but discards the assignment results.

## Declaration

```cpp
namespace asc {
class discard_iterator;
} // namespace asc
```

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/iterator>
#include <asc/std/algorithm>
#include <asc/std/type_traits>

bool example()
{
    int values[] = {2, 4};
    asc::discard_iterator output;
    auto result = asc::std::copy(values, values + 2, output);
    static_assert(asc::std::is_same_v<decltype(result), asc::discard_iterator>);
    // Discarding output does not modify the input.
    return values[0] == 2 && values[1] == 4;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
