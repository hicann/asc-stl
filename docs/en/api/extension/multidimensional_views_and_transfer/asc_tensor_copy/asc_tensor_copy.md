# Header asc/tensor_copy

Provides asynchronous GM and UB data transfer in AI Core SIMD programming, with support for shapes, strides, and padding of 1 to 5 dimensions

## Usage

```cpp
#include <asc/tensor_copy>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::make_tensor_copy_descriptor](make_tensor_copy_descriptor.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor](tensor_copy_descriptor.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::destination_stride](tensor_copy_descriptor_destination_stride.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::extent](tensor_copy_descriptor_extent.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::left_padding](tensor_copy_descriptor_left_padding.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::rank](tensor_copy_descriptor_rank.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::required_alignment](tensor_copy_descriptor_required_alignment.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::required_elements](tensor_copy_descriptor_required_elements.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::right_padding](tensor_copy_descriptor_right_padding.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::set_dimension](tensor_copy_descriptor_set_dimension.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::size_type](tensor_copy_descriptor_size_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::source_stride](tensor_copy_descriptor_source_stride.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::tensor_copy_descriptor](tensor_copy_descriptor_tensor_copy_descriptor.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::validate](tensor_copy_descriptor_validate.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_required_alignment](tensor_copy_required_alignment.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_required_elements](tensor_copy_required_elements.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status](tensor_copy_status.md) | Enum | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::insufficient_destination](tensor_copy_status_insufficient_destination.md) | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::insufficient_source](tensor_copy_status_insufficient_source.md) | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::invalid_stage](tensor_copy_status_invalid_stage.md) | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::size_overflow](tensor_copy_status_size_overflow.md) | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::success](tensor_copy_status_success.md) | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::zero_extent](tensor_copy_status_zero_extent.md) | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::zero_stride](tensor_copy_status_zero_stride.md) | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_load_async](tensor_load_async.md) | Function template | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::tensor_store_async](tensor_store_async.md) | Function template | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::validate_tensor_copy_descriptor](validate_tensor_copy_descriptor.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
