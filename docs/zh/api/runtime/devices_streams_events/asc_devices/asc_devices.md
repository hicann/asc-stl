# 头文件asc/devices

用于枚举可用设备、查询和选择当前设备，以及查询设备属性

## 使用方式

```cpp
#include <asc/devices>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::current_device](current_device.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::device_count](device_count.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::device_properties](device_properties.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::device_properties::aicore_count](device_properties_aicore_count.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::device_properties::architecture](device_properties_architecture.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::device_properties::l2_cache_bytes](device_properties_l2_cache_bytes.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::device_properties::maximum_threads_per_block](device_properties_maximum_threads_per_block.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::device_properties::total_global_memory_bytes](device_properties_total_global_memory_bytes.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::device_properties::unified_buffer_bytes_per_vector_core](device_properties_unified_buffer_bytes_per_vector_core.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::device_properties::vector_core_count](device_properties_vector_core_count.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::device_properties::warp_size](device_properties_warp_size.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::device_ref](device_ref.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::device_ref::device_ref](device_ref_device_ref.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::device_ref::ordinal](device_ref_ordinal.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_ref::properties](device_ref_properties.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::devices](devices.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::npu_arch](npu_arch.md) | 枚举 | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::ascend_2201](npu_arch_ascend_2201.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::ascend_3101](npu_arch_ascend_3101.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::ascend_3510](npu_arch_ascend_3510.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::unknown](npu_arch_unknown.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [`asc::operator!=`（函数）](operator_not_equal.md) | 函数 | C++17+ | Host | Ascend 950 |
| [`asc::operator==`（函数）](operator_equal.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::set_current_device](set_current_device.md) | 函数 | C++17+ | Host | Ascend 950 |
