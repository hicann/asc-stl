# asc::device_buffer

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

Header: `<asc/buffer>`.

`asc::device_buffer<T>` is a device-memory owner used on the Host side, managing a contiguous span of device storage whose element type is `T`. The type only supports trivially copyable elements; it is not copyable but is movable. Resource release is performed through the memory resource recorded when the object was created.

## Declaration

```cpp
namespace asc {
template <class T>
class device_buffer;
}  // namespace asc
```

## Constraints

- If close fails, the original allocation and the resource reference remain held by the current object; the caller may explicitly call close to retry. Move assignment transfers the source object only after the target is closed successfully; on failure, both objects retain their original ownership.
- When a factory enters the replacement phase, it first closes the old buffer; if the close fails, that status is returned directly and no new buffer is allocated. Before destruction or close, any asynchronous work that uses the storage must have completed.

- `T` must be a trivially copyable type.
- The object is not copyable but is movable.
- The Stream and memory resource used at creation must remain valid until the object is closed.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/buffer>

bool example()
{
    asc::device_buffer<int> buffer;
    return buffer.empty() && buffer.size() == 0 && buffer.data() == nullptr;
}
```

## Related APIs

- [API list for this header](asc_buffer.md)
