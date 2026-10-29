# asc::std::expected::~expected

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

Header: `<asc/std/expected>`.

`asc::std::expected::~expected` destroys an `expected` object and ends its lifetime.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

```cpp
constexpr ~expected();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- The owning expected<Value, Error> requires a valid non-void value type and an error object type; the current operation must also satisfy the prototype, parameter, and state requirements on this page.

## Example

The following snippet assumes object points to a constructed object; the object must not be accessed again after the explicit destruction, and releasing the storage is the caller's responsibility.

```cpp
#include <asc/std/new>
#include <asc/std/expected>

struct example_value {
    static inline int alive = 0;
    example_value() { ++alive; }
    ~example_value() { --alive; }
};

using example_object = asc::std::expected<example_value, int>;
void example(example_object* object)
{
    // object 指向已构造对象；析构后不得再访问该对象。
    object->~example_object();
}

bool verify_example()
{
    alignas(example_object) unsigned char storage[sizeof(example_object)];
    auto* object = ::new (static_cast<void*>(storage)) example_object();
    const bool constructed = example_value::alive == 1;
    example(object);
    return constructed && example_value::alive == 0;
}
```

## Related APIs

- [API list for this header](asc_std_expected.md)
