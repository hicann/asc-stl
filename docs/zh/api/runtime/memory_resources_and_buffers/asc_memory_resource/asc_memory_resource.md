# 头文件 asc/memory_resource

提供Device内存和Host锁页内存（Pinned Memory）的资源对象、非拥有引用及显式申请、释放接口

## 使用方式

```cpp
#include <asc/memory_resource>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::device_memory_resource](device_memory_resource.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::allocate](device_memory_resource_allocate.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::deallocate](device_memory_resource_deallocate.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::device_memory_resource](device_memory_resource_device_memory_resource.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::device_ordinal](device_memory_resource_device_ordinal.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::properties](device_memory_resource_properties.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref](device_memory_resource_ref.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::allocate](device_memory_resource_ref_allocate.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::deallocate](device_memory_resource_ref_deallocate.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::device_memory_resource_ref](device_memory_resource_ref_device_memory_resource_ref.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::device_ordinal](device_memory_resource_ref_device_ordinal.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::operator!=](device_memory_resource_ref_operator_not_equal.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::operator==](device_memory_resource_ref_operator_equal.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::properties](device_memory_resource_ref_properties.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::valid](device_memory_resource_ref_valid.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties](memory_resource_properties.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::device_accessible](memory_resource_properties_device_accessible.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::host_accessible](memory_resource_properties_host_accessible.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::maximum_alignment](memory_resource_properties_maximum_alignment.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::memory_resource_properties](memory_resource_properties_memory_resource_properties.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource](pinned_memory_resource.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::allocate](pinned_memory_resource_allocate.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::deallocate](pinned_memory_resource_deallocate.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::pinned_memory_resource](pinned_memory_resource_pinned_memory_resource.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::properties](pinned_memory_resource_properties.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref](pinned_memory_resource_ref.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::allocate](pinned_memory_resource_ref_allocate.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::deallocate](pinned_memory_resource_ref_deallocate.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::operator!=](pinned_memory_resource_ref_operator_not_equal.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::operator==](pinned_memory_resource_ref_operator_equal.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::pinned_memory_resource_ref](pinned_memory_resource_ref_pinned_memory_resource_ref.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::properties](pinned_memory_resource_ref_properties.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::valid](pinned_memory_resource_ref_valid.md) | 成员函数 | C++17+ | Host | Ascend 950 |
