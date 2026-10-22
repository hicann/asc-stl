# asc::make_device_buffer

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

`asc::make_device_buffer` creates a `device_buffer<T>` using the device memory resource provided by the caller. The interface can allocate storage only, or initialize elements with a single value or a contiguous Host range; the operation status is returned through `execution_status`.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <class T>
asc::execution_status make_device_buffer(asc::device_buffer<T>& output, const asc::device_memory_resource_ref& resource,
    asc::stream_ref stream, asc::std::size_t element_count) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <class T>
asc::execution_status make_device_buffer(asc::device_buffer<T>& output, const asc::device_memory_resource_ref& resource,
    asc::stream_ref stream, asc::std::size_t element_count, const T& value) noexcept;
}  // namespace asc
```

### Prototype 3

```cpp
namespace asc {
template <class T>
asc::execution_status make_device_buffer(asc::device_buffer<T>& output, const asc::device_memory_resource_ref& resource,
    asc::stream_ref stream, const T* first, const T* last) noexcept;
}  // namespace asc
```

### Prototype 4

```cpp
namespace asc {
template <class T>
asc::execution_status make_device_buffer(asc::device_buffer<T>& output, const asc::device_memory_resource_ref& resource,
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
| `output` | Output | Reference to the device_buffer<T> object that receives the result: when entering the replacement phase, the old buffer is closed first; if the close fails, the original ownership is retained and an error is returned, and after a successful allocation the new buffer is held. |
| `resource` | Input | Reference to the device memory resource (device_memory_resource_ref): the buffer storage is allocated by this resource, which must remain valid until the buffer is closed. |
| `stream` | Input | Reference to the Stream associated with the buffer: asynchronous operations such as initialization copies are submitted on this Stream; it must remain valid until the related asynchronous work completes. |
| `element_count` | Input | Number of elements (in elements): in Prototypes 1/2 it is the number of elements to allocate (0 returns an invalid-parameter status), and in Prototype 4 it is the number of elements copied from first. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the buffer; the element count multiplied by sizeof(T) gives the required number of bytes, and the product must be representable. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Reference to the device_buffer<T> object that receives the result: when entering the replacement phase, the old buffer is closed first; if the close fails, the original ownership is retained and an error is returned, and after a successful allocation the new buffer is held. |
| `resource` | Input | Reference to the device memory resource (device_memory_resource_ref): the buffer storage is allocated by this resource, which must remain valid until the buffer is closed. |
| `stream` | Input | Reference to the Stream associated with the buffer: asynchronous operations such as initialization copies are submitted on this Stream; it must remain valid until the related asynchronous work completes. |
| `element_count` | Input | Number of elements (in elements): in Prototypes 1/2 it is the number of elements to allocate (0 returns an invalid-parameter status), and in Prototype 4 it is the number of elements copied from first. |
| `value` | Input | Fill value: uploaded first through one Host→device copy, then all elements are filled by device-to-device copies that double in size in stream order. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the buffer; the element count multiplied by sizeof(T) gives the required number of bytes, and the product must be representable. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Reference to the device_buffer<T> object that receives the result: when entering the replacement phase, the old buffer is closed first; if the close fails, the original ownership is retained and an error is returned, and after a successful allocation the new buffer is held. |
| `resource` | Input | Reference to the device memory resource (device_memory_resource_ref): the buffer storage is allocated by this resource, which must remain valid until the buffer is closed. |
| `stream` | Input | Reference to the Stream associated with the buffer: asynchronous operations such as initialization copies are submitted on this Stream; it must remain valid until the related asynchronous work completes. |
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
| `output` | Output | Reference to the device_buffer<T> object that receives the result: when entering the replacement phase, the old buffer is closed first; if the close fails, the original ownership is retained and an error is returned, and after a successful allocation the new buffer is held. |
| `resource` | Input | Reference to the device memory resource (device_memory_resource_ref): the buffer storage is allocated by this resource, which must remain valid until the buffer is closed. |
| `stream` | Input | Reference to the Stream associated with the buffer: asynchronous operations such as initialization copies are submitted on this Stream; it must remain valid until the related asynchronous work completes. |
| `first` | Input | Pointer to the first element of the contiguous Host element range to copy: in Prototype 3 it delimits the range together with last, and in Prototype 4 it delimits the length together with element_count. |
| `element_count` | Input | Number of elements (in elements): in Prototypes 1/2 it is the number of elements to allocate (0 returns an invalid-parameter status), and in Prototype 4 it is the number of elements copied from first. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::execution_status` | Returns the parameter-validation or task-submission status; a successful submission does not mean the asynchronous work has completed. |
| Prototype 2 | `asc::execution_status` | Returns the parameter-validation or task-submission status; a successful submission does not mean the asynchronous work has completed. |
| Prototype 3 | `asc::execution_status` | Returns the parameter-validation or task-submission status; a successful submission does not mean the asynchronous work has completed. |
| Prototype 4 | `asc::execution_status` | Returns the parameter-validation or task-submission status; a successful submission does not mean the asynchronous work has completed. |

## Constraints

- Single-value device fill also borrows the address of value for the asynchronous Host→device copy. The storage of value (including temporaries) must remain until the copy on that Stream completes; a temporary that is destroyed immediately after return must not be passed while ignoring the wait.

- If close fails, the original allocation and the resource reference remain held by the current object; the caller may explicitly call close to retry. Move assignment transfers the source object only after the target is closed successfully; on failure, both objects retain their original ownership.
- When a factory enters the replacement phase, it first closes the old buffer; if the close fails, that status is returned directly and no new buffer is allocated. Before destruction or close, any asynchronous work that uses the storage must have completed.

- `T` must be a trivially copyable type.
- output, resource, and stream must be valid.
- The element count must be greater than zero.
- The input range, Stream, and memory resource must remain valid until the asynchronous initialization completes.

## Example

The following Host snippet has the caller provide a valid memory resource and Stream; the buffer owns the allocation result.

```cpp
#include <asc/buffer>

decltype(auto) example(const asc::device_memory_resource_ref& resource, asc::stream_ref stream)
{
    asc::device_buffer<int> output;
    return asc::make_device_buffer(output, resource, stream, 4);
}
```

## Related APIs

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md): Parameter-validation and task-submission status; a successful submission does not mean the asynchronous work has completed.
