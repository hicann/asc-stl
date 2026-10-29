# ::operator new

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

Header: `<asc/std/new>`.

The global placement `operator new` returns the storage address provided by the caller for explicit object construction; the interface does not allocate memory.

Standard semantics reference: [cppreference `new`](https://en.cppreference.com/w/cpp/header/new).

## Function Prototype

```cpp
void* ::operator new(asc::std::size_t, void* ptr) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `asc::std::size_t` (unnamed) | Input | The first parameter of the placement form, an unnamed std::size_t size parameter that indicates the number of bytes occupied by the object to be constructed; this interface does not allocate memory and does not use this value. |
| `ptr` | Input | The raw storage address provided by the caller; it must satisfy the size and alignment requirements of the object to be constructed. This placement function returns this address directly and does not allocate storage. |

## Return Value

| Return type | Description |
| --- | --- |
| `void*` | Returns the placement storage address provided by the caller. |

## Constraints

- Provides placement object lifetime interfaces and interfaces without dynamic allocation.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/new>

decltype(auto) example(void* storage)
{
    void* address = ::operator new(sizeof(int), storage);
    return address;
}

bool verify_example()
{
    alignas(int) unsigned char storage[sizeof(int)];
    return example(static_cast<void*>(storage)) == static_cast<void*>(storage);
}
```

## Related APIs

- [API list for this header](asc_std_new.md)
