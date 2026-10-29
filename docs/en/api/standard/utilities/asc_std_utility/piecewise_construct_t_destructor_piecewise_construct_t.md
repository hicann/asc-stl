# asc::std::piecewise_construct_t::~piecewise_construct_t

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

Header: `<asc/std/utility>`.

`asc::std::piecewise_construct_t::~piecewise_construct_t` destroys a `piecewise_construct_t` object and ends its lifetime.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

```cpp
constexpr ~piecewise_construct_t() noexcept;
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- The exception specification follows the corresponding declaration; element operations used on the device side must not throw.
- The direct free comparison entries for pair are `operator==` and `operator<`; the other relational helpers are in `rel_ops`.

## Example

The following snippet assumes object points to a constructed object; the object must not be accessed again after explicit destruction, and releasing the storage is the caller's responsibility.

```cpp
#include <asc/std/new>
#include <asc/std/utility>

using example_object = asc::std::piecewise_construct_t;
void example(example_object* object)
{
    // object 指向已构造对象；析构后不得再访问该对象。
    object->~example_object();
}

bool verify_example()
{
    alignas(example_object) unsigned char storage[sizeof(example_object)];
    auto* first = ::new (static_cast<void*>(storage)) example_object();
    example(first);
    auto* second = ::new (static_cast<void*>(storage)) example_object();
    const bool reused = static_cast<void*>(second) == static_cast<void*>(storage);
    example(second);
    return reused;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
