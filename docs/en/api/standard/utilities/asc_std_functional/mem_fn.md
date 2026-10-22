# asc::std::mem_fn

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

Header: `<asc/std/functional>`.

`asc::std::mem_fn` wraps a member pointer as a callable object.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

The following is a summary of the call forms; it returns a callable member pointer wrapper whose concrete implementation type is determined by the header.

```cpp
namespace asc::std {
template<class R, class T>
constexpr auto mem_fn(R T::*member) noexcept;
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `R` | The member type of the member pointer; for function members it includes the function type. |
| `T` | The class type the member pointer belongs to. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `member` | Input | The member object or member function pointer; the returned function object accesses the member through the given object, object pointer, or reference_wrapper when invoked. |

## Return Value

Returns a callable object whose concrete implementation type is determined by the header. The object stores the member pointer and, when invoked, performs member access or the call on the provided object and arguments according to the invoke rules.

## Constraints

- Standard callable objects and member pointer forms are supported.

## Example

The following Host example demonstrates this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/functional>

struct widget { int read() const { return 3; } };

bool example()
{
    widget value;
    auto call = asc::std::mem_fn(&widget::read);
    return call(value) == 3;
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
