# assert

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

Header: `<asc/std/cassert>`.

`assert` checks the condition in debug builds and triggers an assertion failure when the condition is false.

Standard semantics reference: [cppreference `cassert`](https://en.cppreference.com/w/cpp/header/cassert).

## Declaration

Host follows the macro definition from `<assert.h>`. The following is the device-side branch:

```cpp
#if defined(NDEBUG)
#define assert(expression) ((void)0)
#else
#define assert(expression) ((expression) ? (void)0 : __builtin_trap())
#endif
```

## Constraints

- The expansion result is a void expression and cannot be used as a condition such as in an if.
- When NDEBUG is not defined, the condition is checked; on failure, Host performs a platform diagnostic and terminates, and the device side triggers a trap.
- When NDEBUG is defined, expression is not evaluated; normal logic must not rely on side effects inside assertions.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/cassert>

bool example()
{
    const int value = 2 + 3;
    assert(value == 5);
    return value == 5;
}
```

## Related APIs

- [API list for this header](asc_std_cassert.md)
