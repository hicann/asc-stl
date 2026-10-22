# asc::temporary_storage_ref

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

Header: `<asc/memory>`.

`asc::temporary_storage_ref` is a non-owning reference to a byte range that also records the address, the byte count, and the associated `memory_space`; it is used to provide temporary workspace to execution policies.

## Declaration

```cpp
namespace asc {
class temporary_storage_ref;
} // namespace asc
```

## Constraints

- The reference does not manage the lifetime of the underlying storage.
- The underlying region must remain valid until the operation that uses the temporary storage completes, and the address space tag must match the actual storage.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory>

bool example()
{
    unsigned char storage[64]{};
    asc::temporary_storage_ref temporary(storage, sizeof(storage), asc::memory_space::host);
    return temporary.data() == storage && temporary.size_bytes() == 64 && temporary.space() == asc::memory_space::host;
}
```

## Related APIs

- [API list for this header](asc_memory.md)
