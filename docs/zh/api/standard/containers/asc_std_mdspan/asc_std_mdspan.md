# 头文件asc/std/mdspan

提供对已有多维数据的非拥有索引视图

## 使用方式

```cpp
#include <asc/std/mdspan>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::aligned_accessor](aligned_accessor.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::aligned_accessor::access](aligned_accessor_access.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::aligned_accessor::aligned_accessor](aligned_accessor_aligned_accessor.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::aligned_accessor::byte_alignment](aligned_accessor_byte_alignment.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::aligned_accessor::data_handle_type](aligned_accessor_data_handle_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::aligned_accessor::element_type](aligned_accessor_element_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::aligned_accessor::offset](aligned_accessor_offset.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::aligned_accessor::offset_policy](aligned_accessor_offset_policy.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::aligned_accessor::reference](aligned_accessor_reference.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::default_accessor](default_accessor.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::default_accessor::access](default_accessor_access.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::default_accessor::data_handle_type](default_accessor_data_handle_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::default_accessor::default_accessor](default_accessor_default_accessor.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::default_accessor::element_type](default_accessor_element_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::default_accessor::offset](default_accessor_offset.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::default_accessor::offset_policy](default_accessor_offset_policy.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::default_accessor::reference](default_accessor_reference.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::dextents](dextents.md) | 别名模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::dims](dims.md) | 别名模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::dynamic_extent](dynamic_extent.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::extents](extents.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::extents::extent](extents_extent.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::extents::extents](extents_extents.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::extents::index_type](extents_index_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::extents::rank](extents_rank.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::extents::rank_dynamic](extents_rank_dynamic.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::extents::rank_type](extents_rank_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::extents::size_type](extents_size_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::extents::static_extent](extents_static_extent.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::full_extent](full_extent.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::full_extent_t](full_extent_t.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_left](layout_left.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_left::mapping](layout_left_mapping.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_left::mapping::`operator!=`](layout_left_mapping_operator_not_equal.md) | 成员函数 | `C++17+` | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_right](layout_right.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_right::mapping](layout_right_mapping.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_right::mapping::`operator!=`](layout_right_mapping_operator_not_equal.md) | 成员函数 | `C++17+` | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_stride](layout_stride.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_stride::mapping](layout_stride_mapping.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_stride::mapping::`operator!=`](layout_stride_mapping_operator_not_equal.md) | 成员函数 | `C++17+` | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_stride::mapping::`operator==`](layout_stride_mapping_operator_equal.md) | 成员函数 | `C++17+` | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::layout_stride::mapping::strides](layout_stride_mapping_strides.md) | 成员函数 | `C++17+` | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan](mdspan.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::accessor](mdspan_accessor.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::accessor_type](mdspan_accessor_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::data_handle](mdspan_data_handle.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::data_handle_type](mdspan_data_handle_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::element_type](mdspan_element_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::empty](mdspan_empty.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::extent](mdspan_extent.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::extents](mdspan_extents.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::extents_type](mdspan_extents_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::index_type](mdspan_index_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::is_always_exhaustive](mdspan_is_always_exhaustive.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::is_always_strided](mdspan_is_always_strided.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::is_always_unique](mdspan_is_always_unique.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::is_exhaustive](mdspan_is_exhaustive.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::is_strided](mdspan_is_strided.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::is_unique](mdspan_is_unique.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::layout_type](mdspan_layout_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::mapping](mdspan_mapping.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::mapping_type](mdspan_mapping_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::mdspan](mdspan_mdspan.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::`operator()`](mdspan_operator_call.md) | 成员函数 | `C++17+` | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::`operator=`](mdspan_operator_assign.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::operator\[\]](mdspan_operator_subscript.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::rank](mdspan_rank.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::rank_dynamic](mdspan_rank_dynamic.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::rank_type](mdspan_rank_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::reference](mdspan_reference.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::size](mdspan_size.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::size_type](mdspan_size_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::static_extent](mdspan_static_extent.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::stride](mdspan_stride.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::mdspan::value_type](mdspan_value_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::strided_slice](strided_slice.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::submdspan](submdspan.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::submdspan_extents](submdspan_extents.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::submdspan_mapping](submdspan_mapping.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::submdspan_mapping_result](submdspan_mapping_result.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
