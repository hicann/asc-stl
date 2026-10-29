# asc::std::variant::~variant

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

Header: `<asc/std/variant>`.

`asc::std::variant::~variant` destroys a `variant` object and ends its lifetime.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

```cpp
~variant();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- When there is no active alternative, no alternative object is destroyed; when an active alternative exists, only that one is destroyed, exactly once.

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following snippet assumes object points to a constructed object; the object must not be accessed again after explicit destruction, and releasing the storage is the caller's responsibility.

```cpp
#include <asc/std/new>
#include <asc/std/variant>

struct example_value {
    static inline int alive = 0;
    example_value() { ++alive; }
    ~example_value() { --alive; }
};

using example_object = asc::std::variant<example_value, float>;
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

- [API list for this header](asc_std_variant.md)
