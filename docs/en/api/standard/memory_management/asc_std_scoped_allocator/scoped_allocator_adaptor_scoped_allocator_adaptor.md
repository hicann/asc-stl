# asc::std::scoped_allocator_adaptor::scoped_allocator_adaptor

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

`asc::std::scoped_allocator_adaptor::scoped_allocator_adaptor` initializes a `scoped_allocator_adaptor` object in the construction form listed on this page.

Standard semantics reference: [cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator).

## Function Prototype

Member of: [`scoped_allocator_adaptor`](scoped_allocator_adaptor.md). Prototype 1 applies to both partial specializations; 2 and 3 apply only to the partial specialization without inner allocators; 4 applies only to the partial specialization with at least one inner allocator. The copy/move special members follow the implicit declaration rules, and no converting constructor template across outer types is provided.

### Prototype 1

```cpp
constexpr scoped_allocator_adaptor() = default;
```

### Prototype 2

```cpp
constexpr explicit scoped_allocator_adaptor(const OuterAllocator& outer) noexcept;
```

### Prototype 3

```cpp
constexpr explicit scoped_allocator_adaptor(OuterAllocator&& outer) noexcept;
```

### Prototype 4

```cpp
constexpr scoped_allocator_adaptor(const OuterAllocator& outer,
    const FirstInner& first, const RestInner&... rest) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototypes 2 and 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `outer` | Input | The allocator object used to copy- or move-initialize the outer base class; no exclusive ownership of its allocations is acquired. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `outer` | Input | Used to copy-initialize the outer allocator. |
| `first` | Input | The first inner allocator, used to initialize the inner adaptor. |
| `rest` | Input | The remaining inner allocators, copy-initialized in order. |

## Return Value

No return value.

## Constraints

- Whether default construction and the copy/move special members are available depends on the individual allocator types.
- The listed constructors that explicitly take allocators are `noexcept`; their internal copy/move operations must not throw.
- Construction only stores allocator state and neither allocates nor constructs elements.

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

- [API list for this header](asc_std_scoped_allocator.md)
