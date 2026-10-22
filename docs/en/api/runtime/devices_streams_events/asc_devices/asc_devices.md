# Header asc/devices

Enumerates available devices, queries and selects the current device, and queries device properties

## Usage

```cpp
#include <asc/devices>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::current_device](current_device.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::device_count](device_count.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::device_properties](device_properties.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::device_properties::aicore_count](device_properties_aicore_count.md) | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::architecture](device_properties_architecture.md) | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::l2_cache_bytes](device_properties_l2_cache_bytes.md) | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::maximum_threads_per_block](device_properties_maximum_threads_per_block.md) | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::total_global_memory_bytes](device_properties_total_global_memory_bytes.md) | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::unified_buffer_bytes_per_vector_core](device_properties_unified_buffer_bytes_per_vector_core.md) | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::vector_core_count](device_properties_vector_core_count.md) | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::warp_size](device_properties_warp_size.md) | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_ref](device_ref.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::device_ref::device_ref](device_ref_device_ref.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::device_ref::ordinal](device_ref_ordinal.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_ref::properties](device_ref_properties.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::devices](devices.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::npu_arch](npu_arch.md) | Enum | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::ascend_2201](npu_arch_ascend_2201.md) | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::ascend_3101](npu_arch_ascend_3101.md) | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::ascend_3510](npu_arch_ascend_3510.md) | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::unknown](npu_arch_unknown.md) | Enumerator | C++17+ | Host | Ascend 950 |
| [`asc::operator!=` (Function)](operator_not_equal.md) | Function | C++17+ | Host | Ascend 950 |
| [`asc::operator==` (Function)](operator_equal.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::set_current_device](set_current_device.md) | Function | C++17+ | Host | Ascend 950 |
