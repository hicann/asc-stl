# asc::std::allocate_at_least

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

Header: `<asc/std/memory>`.

`asc::std::allocate_at_least` asks the allocator to allocate memory for at least n objects and returns an `allocation_result` containing the pointer and the actual capacity; the capacity is not less than the requested value.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<class Alloc> [[nodiscard]] constexpr allocation_result<typename allocator_traits<Alloc>::pointer>
allocate_at_least(Alloc& __alloc, size_t __n);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Alloc` | The allocator type used for this allocation; must satisfy the allocation and quantity conventions of allocator_traits. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `__alloc` | Input/Output | The allocator object; must remain valid for the duration of the call, and the storage it allocates is managed according to that allocator's release rules. |
| `__n` | Input | The requested number of elements, in objects; must be within the range the allocator can handle. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::allocation_result<typename asc::std::allocator_traits<Alloc>::pointer>` | Returns the allocated address ptr and the actual number of elements that fit, count; count is not less than the requested quantity. |

## Constraints

- Both C++17 and C++20 prefer calling an available `allocate_at_least` member and keep the actual capacity it returns; when no matching member exists, `allocate` is called and the requested quantity is returned as the capacity.
- The allocator must satisfy the allocation and release conventions, and the capacity returned by the member must not be less than the requested quantity. The caller is responsible for releasing the obtained storage as required by the allocator.
- Whether execution on the device side is possible, whether device memory is allocated, and the error behavior are determined by the specific allocator. This template provides no implicit dynamic allocation on the device side.
- `constexpr` does not guarantee that an arbitrary allocator can allocate storage during constant evaluation.

## Example

The example allocator uses caller-reserved storage. The member provides one extra element of capacity, and the result is checked by both the pointer and the capacity.

```cpp
#include <asc/std/memory>

struct example_allocator {
    using value_type = int;
    int* storage;
    int* allocate(asc::std::size_t) { return storage; }
    asc::std::allocation_result<int*> allocate_at_least(asc::std::size_t count)
    {
        return {storage, count + 1};
    }
    void deallocate(int*, asc::std::size_t) noexcept {}
};

bool example()
{
    int storage[4] = {};
    example_allocator allocator{storage};
    const auto result = asc::std::allocate_at_least(allocator, 2);
    const bool valid = result.ptr == storage && result.count == 3;
    allocator.deallocate(result.ptr, result.count);
    return valid;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
