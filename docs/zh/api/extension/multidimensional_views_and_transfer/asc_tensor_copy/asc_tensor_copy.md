# 头文件asc/tensor_copy

提供AI Core SIMD编程中支持1至5维形状、步长和填充的GM与UB异步数据搬运功能

## 使用方式

```cpp
#include <asc/tensor_copy>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::make_tensor_copy_descriptor](make_tensor_copy_descriptor.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor](tensor_copy_descriptor.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::destination_stride](tensor_copy_descriptor_destination_stride.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::extent](tensor_copy_descriptor_extent.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::left_padding](tensor_copy_descriptor_left_padding.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::rank](tensor_copy_descriptor_rank.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::required_alignment](tensor_copy_descriptor_required_alignment.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::required_elements](tensor_copy_descriptor_required_elements.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::right_padding](tensor_copy_descriptor_right_padding.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::set_dimension](tensor_copy_descriptor_set_dimension.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::size_type](tensor_copy_descriptor_size_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::source_stride](tensor_copy_descriptor_source_stride.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::tensor_copy_descriptor](tensor_copy_descriptor_tensor_copy_descriptor.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_descriptor::validate](tensor_copy_descriptor_validate.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_required_alignment](tensor_copy_required_alignment.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_required_elements](tensor_copy_required_elements.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_status](tensor_copy_status.md) | 枚举 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_status::insufficient_destination](tensor_copy_status_insufficient_destination.md) | 枚举值 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_status::insufficient_source](tensor_copy_status_insufficient_source.md) | 枚举值 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_status::invalid_stage](tensor_copy_status_invalid_stage.md) | 枚举值 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_status::size_overflow](tensor_copy_status_size_overflow.md) | 枚举值 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_status::success](tensor_copy_status_success.md) | 枚举值 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_status::zero_extent](tensor_copy_status_zero_extent.md) | 枚举值 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_copy_status::zero_stride](tensor_copy_status_zero_stride.md) | 枚举值 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tensor_load_async](tensor_load_async.md) | 函数模板 | C++17+ | AI Core SIMD编程 | Ascend 950 |
| [asc::tensor_store_async](tensor_store_async.md) | 函数模板 | C++17+ | AI Core SIMD编程 | Ascend 950 |
| [asc::validate_tensor_copy_descriptor](validate_tensor_copy_descriptor.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
