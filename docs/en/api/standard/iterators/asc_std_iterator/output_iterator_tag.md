# asc::std::output_iterator_tag

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

Header: `<asc/std/iterator>`.

`asc::std::output_iterator_tag` identifies the standard tag type for the corresponding iterator capability level.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

Host uses the standard library tag alias; Device defines ASC's own tag structure.

### Host

```cpp
namespace asc::std {
using output_iterator_tag = ::std::output_iterator_tag;
}
```

### Device

```cpp
namespace asc::std {
struct output_iterator_tag {};
}
```

## Constraints

- Provides the C++20 public iterator concepts and traits interfaces.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_empty_v<asc::std::output_iterator_tag>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
