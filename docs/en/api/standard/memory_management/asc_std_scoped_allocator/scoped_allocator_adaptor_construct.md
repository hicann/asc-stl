# asc::std::scoped_allocator_adaptor::construct

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

Header: `<asc/std/scoped_allocator>`.

`construct` performs in-place construction at `pointer` directly with `args...` as the arguments. It currently does not add allocator arguments based on `uses_allocator`, nor does it call the outer allocator's `construct` hook.

## Function Prototype

Member of: [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md).

```cpp
// Declaration excerpt from inside the asc::std::scoped_allocator_adaptor class; template parameters and other members are provided by the enclosing class.
template<class Type, class ...Args> void construct(Type* pointer, Args&&... args);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Type` | The type of object constructed or destroyed by the allocator. |
| `Args` | The list of argument types passed to the constructor or callable object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Output | The address of uninitialized storage satisfying the target object's size and alignment; the call starts the object's lifetime there, and the construction arguments determine its initial value. |
| `args` | Input/Output | The list of arguments forwarded to the object construction or function call. |

## Return Value

No return value.

## Constraints

- `pointer` must be uninitialized storage satisfying `Type`'s size and alignment, and `Type` must be constructible from the forwarded `args...`.
- This interface does not inject inner allocators. For constructors requiring an allocator, all parameters must be provided explicitly by the caller.
- After successful construction, the object must be destroyed before the storage is released; construction on the device side must be callable and must not throw.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>
#include <asc/std/scoped_allocator>
#include <memory>
#include <limits>

template<class T>
struct example_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    template<class U> struct rebind { using other = example_allocator<U>; };
    int identity = 0;
    T* allocate(size_type count) { return std::allocator<T>{}.allocate(count); }
    void deallocate(T* address, size_type count) { std::allocator<T>{}.deallocate(address, count); }
    size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(T); }
};

bool example()
{
    using adaptor = asc::std::scoped_allocator_adaptor<example_allocator<int>>;
    adaptor allocator(example_allocator<int>{7});
    int* pointer = allocator.allocate(1);
    allocator.construct(pointer, 9);
    const bool valid = allocator.outer_allocator().identity == 7 && *pointer == 9;
    allocator.destroy(pointer);
    allocator.deallocate(pointer, 1);
    return valid;
}
```

## Related APIs

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [API list for this header](asc_std_scoped_allocator.md)
