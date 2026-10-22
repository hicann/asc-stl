# asc::tabulate_output_iterator

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

`asc::tabulate_output_iterator` is an output iterator that passes the written index and value to a user function.

## Declaration

```cpp
namespace asc {
template<class Function, class Index = asc::std::ptrdiff_t> class tabulate_output_iterator;
} // namespace asc
```

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/iterator>

struct write_at {
    int* values;
    void operator()(int index, int value) const { values[index] = value; }
};

bool example()
{
    int values[2] = {};
    asc::tabulate_output_iterator<write_at> iterator(write_at{values});
    *iterator = 3;
    ++iterator;
    *iterator = 7;
    return values[0] == 3 && values[1] == 7;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
