# asc::std::insert_iterator::`operator=`

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

`asc::std::insert_iterator::operator=` updates the object through the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::insert_iterator`](insert_iterator.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::std::insert_iterator; template parameters and other members are provided by the enclosing class.
constexpr insert_iterator<Container>& operator=(const typename Container::value_type& value);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::std::insert_iterator; template parameters and other members are provided by the enclosing class.
constexpr insert_iterator<Container>& operator=(typename Container::value_type&& value);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The element value to be inserted at the container's current insertion position; it is inserted by copy by calling `container->insert(iter, value)`, and the stored position is updated to the position after the returned one. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The element value to be inserted at the container's current insertion position; it is inserted by move by calling `container->insert(iter, asc::std::move(value))`, and the stored position is updated to the position after the returned one; the moved-from state of the value follows its type's conventions. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `insert_iterator<Container> &` | Returns a reference to the updated current object; assignment or compound operations can continue on it. |
| Prototype 2 | `insert_iterator<Container> &` | Returns a reference to the updated current object; assignment or compound operations can continue on it. |

## Constraints

- The target container must support the corresponding `insert(position, value)` operation; the insert iterator stores the container's address and does not own the container.
- The container must remain valid while the adaptor is in use; insertion operations must also follow the target container's own iterator invalidation rules.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <vector>

bool example()
{
    ::std::vector<int> values;
    asc::std::insert_iterator<::std::vector<int>> output(values, values.begin());
    *output = 7;
    *output = 9;
    return values.size() == 2 && values[0] == 7 && values[1] == 9;
}
```

## Related APIs

- [`asc::std::insert_iterator`](insert_iterator.md)
- [API list for this header](asc_std_iterator.md)
