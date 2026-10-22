# asc::zip_function

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

`asc::zip_function` expands the reference proxy produced by dereferencing an asc::zip_iterator and then invokes the user function.

## Declaration

```cpp
namespace asc {
template <class Function>
class zip_function;
}  // namespace asc
```

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/iterator>

int add_values(int left, int right)
{
    return left + right;
}

bool example()
{
    int left = 2;
    int right = 3;
    auto zipped = asc::make_zip_iterator(&left, &right);
    asc::zip_function<int (*)(int, int)> add(add_values);
    return add(*zipped) == 5;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
