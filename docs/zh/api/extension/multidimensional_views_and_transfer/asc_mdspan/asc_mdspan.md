# 头文件 asc/mdspan

提供非拥有多维数据视图，覆盖 Host、GM 以及 AI Core SIMD 编程中的 UB；DLPack 可用时支持 Host 侧数据结构转换

## 使用方式

```cpp
#include <asc/mdspan>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::dlpack_tensor](dlpack_tensor.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::dstrides](dstrides.md) | 别名模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::dynamic_stride](dynamic_stride.md) | 变量 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::gm_accessor](gm_accessor.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::gm_mdspan](gm_mdspan.md) | 别名模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::host_accessor](host_accessor.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::host_mdspan](host_mdspan.md) | 别名模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_device_accessible_v](is_device_accessible_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_gm_accessor_v](is_gm_accessor_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_gm_mdspan_v](is_gm_mdspan_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_host_accessible_v](is_host_accessible_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_host_accessor_v](is_host_accessor_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_host_mdspan_v](is_host_mdspan_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_restrict_accessor_v](is_restrict_accessor_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_restrict_mdspan_v](is_restrict_mdspan_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_ub_accessor_v](is_ub_accessor_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::is_ub_mdspan_v](is_ub_mdspan_v.md) | 变量模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::layout_stride_relaxed](layout_stride_relaxed.md) | 类 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::restrict_accessor](restrict_accessor.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::restrict_mdspan](restrict_mdspan.md) | 别名模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::steps](steps.md) | 别名模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::strides](strides.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::to_dlpack_tensor](to_dlpack_tensor.md) | 函数模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::to_gm_mdspan](to_gm_mdspan.md) | 函数模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::to_host_mdspan](to_host_mdspan.md) | 函数模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::ub_accessor](ub_accessor.md) | 类模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::ub_mdspan](ub_mdspan.md) | 别名模板 | C++17+ | 见各成员或重载说明 | Ascend 950 |
