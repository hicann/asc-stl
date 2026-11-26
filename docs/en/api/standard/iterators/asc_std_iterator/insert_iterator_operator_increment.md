# asc::std::insert_iterator::`operator++`

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

`asc::std::insert_iterator::operator++` provides the increment forms of the output iterator; the operation itself does not change the container or the insertion position.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::insert_iterator`](insert_iterator.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::std::insert_iterator; template parameters and other members are provided by the enclosing class.
constexpr insert_iterator<Container>& operator++() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::std::insert_iterator; template parameters and other members are provided by the enclosing class.
constexpr insert_iterator<Container>& operator++(int unused) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `unused` | Input | A placeholder parameter used to distinguish the postfix increment or postfix decrement form; written as the integer 0 at the call site. |

## Return Value

Both forms return a reference to the current adaptor. Increment preserves the stored insertion position. Assignment inserts the element.

## Constraints

- The target container must support the corresponding `insert(position, value)` operation; the insert iterator stores the container's address and does not own the container.
- The container must remain valid while the adaptor is in use; insertion operations must also follow the target container's own iterator invalidation rules.
- Dereference and increment serve to satisfy the output iterator call forms and do not themselves insert elements; insertion is performed through assignment.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <vector>

bool example()
{
    ::std::vector<int> values;
    asc::std::insert_iterator<::std::vector<int>> output(values, values.begin());
    auto& prefix = ++output;
    auto& postfix = output++;
    bool unchanged = &prefix == &output && &postfix == &output && values.empty();
    *output++ = 7;
    *output++ = 3;
    return unchanged && values.size() == 2 && values.front() == 7 && values.back() == 3;
}
```

## Related APIs

- [`asc::std::insert_iterator`](insert_iterator.md)
- [API list for this header](asc_std_iterator.md)
