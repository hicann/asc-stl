# asc::std::vector::pop_back

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

Header: `<asc/std/vector>`.

`asc::std::vector::pop_back` removes the element at the end of the container; the object must be non-empty.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Function Prototype

Member of: [`asc::std::vector`](vector.md).

```cpp
// Excerpt of the declaration inside class asc::std::vector; template parameters and other members are provided by the owning class.
void pop_back();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- The container must be non-empty before the call; this interface destroys the last element and decreases `size()` by `1` without freeing the allocated capacity.
- Pointers, references, and iterators to the removed element are invalidated. Element destruction on the device side must be available in the corresponding programming mode and must not throw.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <memory>
#include <asc/std/vector>

bool example()
{
    asc::std::vector<int, ::std::allocator<int>> values(::std::allocator<int>{});
    values.push_back(1);
    values.push_back(3);

    values.pop_back();
    return values.back() == 1;
}
```

## Related APIs

- [`asc::std::vector`](vector.md)
- [API list for this header](asc_std_vector.md)
