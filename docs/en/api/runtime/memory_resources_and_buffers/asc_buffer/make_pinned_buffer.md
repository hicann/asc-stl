# asc::make_pinned_buffer

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

`asc::make_pinned_buffer` creates a `pinned_buffer<T>` using the page-locked memory resource provided by the caller. The interface can allocate storage only, or initialize elements with a single value or a contiguous Host range.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <class T>
asc::execution_status make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource,
    asc::stream_ref stream, asc::std::size_t element_count) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <class T>
asc::execution_status make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource,
    asc::stream_ref stream, asc::std::size_t element_count, const T& value) noexcept;
}  // namespace asc
```

### Prototype 3

```cpp
namespace asc {
template <class T>
asc::execution_status make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource,
    asc::stream_ref stream, const T* first, const T* last) noexcept;
}  // namespace asc
```

### Prototype 4

```cpp
namespace asc {
template <class T>
asc::execution_status make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource,
    asc::stream_ref stream, const T* first, asc::std::size_t element_count) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the buffer; the element count multiplied by sizeof(T) gives the required number of bytes, and the product must be representable. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Reference to the pinned_buffer<T> object that receives the result: when entering the replacement phase, the old buffer is closed first; if the close fails, the original ownership is retained and an error is returned, and after a successful allocation the new buffer is held. |
| `resource` | Input | Reference to the page-locked memory resource (pinned_memory_resource_ref): the buffer storage is allocated by this resource, which must remain valid until the buffer is closed. |
| `stream` | Input | Reference to the Stream recorded in the buffer state: subsequent stream-ordered operations of the buffer are ordered on this Stream; it must remain valid for the buffer's lifetime. |
| `element_count` | Input | Number of elements (in elements): in Prototypes 1/2 it is the number of elements to allocate (0 returns an invalid-parameter status), and in Prototype 4 it is the number of elements copied from first. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the buffer; the element count multiplied by sizeof(T) gives the required number of bytes, and the product must be representable. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Reference to the pinned_buffer<T> object that receives the result: when entering the replacement phase, the old buffer is closed first; if the close fails, the original ownership is retained and an error is returned, and after a successful allocation the new buffer is held. |
| `resource` | Input | Reference to the page-locked memory resource (pinned_memory_resource_ref): the buffer storage is allocated by this resource, which must remain valid until the buffer is closed. |
| `stream` | Input | Reference to the Stream recorded in the buffer state: subsequent stream-ordered operations of the buffer are ordered on this Stream; it must remain valid for the buffer's lifetime. |
| `element_count` | Input | Number of elements (in elements): in Prototypes 1/2 it is the number of elements to allocate (0 returns an invalid-parameter status), and in Prototype 4 it is the number of elements copied from first. |
| `value` | Input | Fill value: page-locked memory is directly accessible from the Host, and after allocation a Host loop writes this value into every element. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the buffer; the element count multiplied by sizeof(T) gives the required number of bytes, and the product must be representable. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Reference to the pinned_buffer<T> object that receives the result: when entering the replacement phase, the old buffer is closed first; if the close fails, the original ownership is retained and an error is returned, and after a successful allocation the new buffer is held. |
| `resource` | Input | Reference to the page-locked memory resource (pinned_memory_resource_ref): the buffer storage is allocated by this resource, which must remain valid until the buffer is closed. |
| `stream` | Input | Reference to the Stream recorded in the buffer state: subsequent stream-ordered operations of the buffer are ordered on this Stream; it must remain valid for the buffer's lifetime. |
| `first` | Input | Pointer to the first element of the contiguous Host element range to copy: in Prototype 3 it delimits the range together with last, and in Prototype 4 it delimits the length together with element_count. |
| `last` | Input | Pointer to the end (exclusive) of the contiguous Host element range to copy: it must not be null and must not be less than first. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the buffer; the element count multiplied by sizeof(T) gives the required number of bytes, and the product must be representable. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Reference to the pinned_buffer<T> object that receives the result: when entering the replacement phase, the old buffer is closed first; if the close fails, the original ownership is retained and an error is returned, and after a successful allocation the new buffer is held. |
| `resource` | Input | Reference to the page-locked memory resource (pinned_memory_resource_ref): the buffer storage is allocated by this resource, which must remain valid until the buffer is closed. |
| `stream` | Input | Reference to the Stream recorded in the buffer state: subsequent stream-ordered operations of the buffer are ordered on this Stream; it must remain valid for the buffer's lifetime. |
| `first` | Input | Pointer to the first element of the contiguous Host element range to copy: in Prototype 3 it delimits the range together with last, and in Prototype 4 it delimits the length together with element_count. |
| `element_count` | Input | Number of elements (in elements): in Prototypes 1/2 it is the number of elements to allocate (0 returns an invalid-parameter status), and in Prototype 4 it is the number of elements copied from first. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::execution_status` | Returns the status of the synchronous allocation and Host initialization; on success the initialization has already completed. |
| Prototype 2 | `asc::execution_status` | Returns the status of the synchronous allocation and Host initialization; on success the initialization has already completed. |
| Prototype 3 | `asc::execution_status` | Returns the status of the synchronous allocation and Host initialization; on success the initialization has already completed. |
| Prototype 4 | `asc::execution_status` | Returns the status of the synchronous allocation and Host initialization; on success the initialization has already completed. |

## Constraints

- If close fails, the original allocation and the resource reference remain held by the current object; the caller may explicitly call close to retry. Move assignment transfers the source object only after the target is closed successfully; on failure, both objects retain their original ownership.
- When a factory enters the replacement phase, it first closes the old buffer; if the close fails, that status is returned directly and no new buffer is allocated. Before destruction or close, any asynchronous work that uses the storage must have completed.

- `T` must be a trivially copyable type.
- output, resource, and stream must be valid.
- The element count must be greater than zero.
- The input range must be contiguous and remain valid for the duration of the call.

## Example

This complete example uses the real CANN Runtime and selects device 0, which must be available before running. Asynchronous waits are limited to 10 seconds. Failure terminates the example process to avoid releasing resources still in use; the controller must stop subsequent tasks and recheck device health. On success, work completes before resources are closed, the device is reset, and the Runtime is finalized.

```cpp
#include <acl/acl.h>
#include <asc/stream>
#include <cstdlib>

void check(bool condition)
{
    if (!condition) {
        std::_Exit(2);
    }
}

void finish(asc::stream_ref stream)
{
    check(aclrtSynchronizeStreamWithTimeout(stream.native_handle(), 10000) == ACL_SUCCESS);
}
#include <asc/buffer>


void run_example()
{
    asc::stream stream;
    check(asc::make_stream(stream));
    asc::pinned_memory_resource resource;
    const asc::pinned_memory_resource_ref reference(resource);
    const int values[4] = {2, 4, 6, 8};
    asc::pinned_buffer<int> buffers[4];
    check(asc::make_pinned_buffer(buffers[0], reference, stream, 4).success());
    for (int i = 0; i < 4; ++i) {
        buffers[0].data()[i] = 0;
    }
    check(asc::make_pinned_buffer(buffers[1], reference, stream, 4, 7).success());
    check(asc::make_pinned_buffer(buffers[2], reference, stream, values, values + 4).success());
    check(asc::make_pinned_buffer(buffers[3], reference, stream, values, asc::std::size_t(4)).success());
    for (int i = 0; i < 4; ++i) {
        check(buffers[i].size() == 4 && buffers[i].size_bytes() == 4 * sizeof(int));
        for (int j = 0; j < 4; ++j) {
            const int expected = i == 0 ? 0 : (i == 1 ? 7 : values[j]);
            check(buffers[i].data()[j] == expected);
        }
        check(buffers[i].close().success());
    }
    finish(stream);
    check(stream.close());
}

int main()
{
    if (aclInit(nullptr) != ACL_SUCCESS) {
        return 1;
    }
    if (!asc::set_current_device(asc::device_ref(0))) {
        check(aclFinalize() == ACL_SUCCESS);
        return 1;
    }
    run_example();
    const bool reset = aclrtResetDevice(0) == ACL_SUCCESS;
    const bool finalized = aclFinalize() == ACL_SUCCESS;
    return reset && finalized ? 0 : 1;
}
```

## Related APIs

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md): Parameter-validation and task-submission status; a successful submission does not mean the asynchronous work has completed.
