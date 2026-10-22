# asc::proclaim_copyable_arguments

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

Header: `<asc/functional>`.

`asc::proclaim_copyable_arguments` wraps a function object and explicitly declares that its arguments can be safely copied by value.

## Function Prototype

The following is a declaration summary; the concrete return type is implementation-defined and is a wrapper object that can be stored and invoked.

```cpp
namespace asc {
template<class Function> constexpr auto proclaim_copyable_arguments(Function&& function) noexcept;
} // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Function` | The type of the callable object that performs this page's operation on the input values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `function` | Input (may be moved) | The function object to be wrapped; the wrapper stores a value copy of the object type after reference removal, and resources borrowed by the function object itself must remain valid. |

## Return Value

| Return type | Description |
| --- | --- |
| An implementation-defined callable wrapper type | Stores the function object, forwards calls, and preserves the result type of the underlying call. |

## Constraints

- The function object must be copyable into the wrapper and invocable with the given arguments through a const function object.
- Copying, moving, and wrap-construction of the function object must not throw exceptions; the returned wrapper does not extend the lifetime of any external references it captures.
- The caller must ensure on its own that copying the arguments fits the use case; the wrapping performs no runtime checks and does not modify the argument objects.

## Example

The following Host example constructs the wrapper and checks the returned result.

```cpp
#include <asc/functional>

bool example()
{
    const auto wrapped = asc::proclaim_copyable_arguments([](int value) { return value + 1; });
    return wrapped(3) == 4;
}
```

## Related APIs

- [API list for this header](asc_functional.md)
