# asc::std::basic_string::push_back

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

Header: `<asc/std/string>`.

`asc::std::basic_string::push_back` inserts one element at the end of the container.

Standard semantics reference: [cppreference `string`](https://en.cppreference.com/w/cpp/header/string).

## Function Prototype

Member of: [`asc::std::basic_string`](basic_string.md).

```cpp
// Excerpt of the declaration inside class asc::std::basic_string; template parameters and other members are provided by the owning class.
void push_back(CharT value);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Character value appended to the end of the string; the string length increases by one after the call. |

## Return Value

No return value.

## Constraints

- Explicit-allocator construction of basic_string<char,Traits,A>.
- append/push_back/clear for plain/local character sources.
- size/capacity/data/c_str/iteration/indexing and destruction.
- Only the sufficient-capacity and non-throwing exception domains.

## Example

The following Host snippet uses an explicitly provided allocator; the device side must use an allocator callable at the target execution location.

```cpp
#include <asc/std/string>
#include <functional>
#include <memory>
#include <string>
#include <utility>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

void example(asc::std::basic_string<char, ::std::char_traits<char>, example_allocator<char>>& value)
{
    value.push_back('a');
}

bool verify_example()
{
    asc::std::basic_string<char, ::std::char_traits<char>, example_allocator<char>> value(example_allocator<char>{});
    example(value);
    return value.size() == 1 && value[0] == 'a';
}
```

## Related APIs

- [`asc::std::basic_string`](basic_string.md)
- [API list for this header](asc_std_string.md)
