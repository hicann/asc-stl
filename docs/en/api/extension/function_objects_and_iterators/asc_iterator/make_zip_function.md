# asc::make_zip_function

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

Header: `<asc/iterator>`.

`asc::make_zip_function` creates an adaptor that expands the reference proxy produced by dereferencing an asc::zip_iterator and then invokes the target function.

## Function Prototype

```cpp
namespace asc {
template <class Function>
constexpr asc::zip_function<Function> make_zip_function(Function function);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Function` | The type of the callable object that performs this page's operation on the input values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `function` | Input | The target function object to be adapted: when it receives an asc::zip_iterator's reference proxy, it expands all the proxy's elements and invokes function(elements...). |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::zip_function<Function>` | Returns an adaptor that expands the reference proxy produced by dereferencing an asc::zip_iterator and then invokes the target function. |

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example uses concrete inputs and checks the result within the object's lifetime.

```cpp
#include <asc/iterator>
bool example()
{
    int left = 2;
    int right = 3;
    const auto callable = asc::make_zip_function([](int a, int b) { return a + b; });
    const auto iterator = asc::make_zip_iterator(&left, &right);
    return callable(*iterator) == 5;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
