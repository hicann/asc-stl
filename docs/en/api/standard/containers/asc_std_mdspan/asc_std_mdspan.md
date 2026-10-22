# Header asc/std/mdspan

Provides a non-owning indexed view of existing multidimensional data

## Usage

```cpp
#include <asc/std/mdspan>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::std::aligned_accessor](aligned_accessor.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::aligned_accessor::access](aligned_accessor_access.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::aligned_accessor::aligned_accessor](aligned_accessor_aligned_accessor.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::aligned_accessor::byte_alignment](aligned_accessor_byte_alignment.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::aligned_accessor::data_handle_type](aligned_accessor_data_handle_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::aligned_accessor::element_type](aligned_accessor_element_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::aligned_accessor::offset](aligned_accessor_offset.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::aligned_accessor::offset_policy](aligned_accessor_offset_policy.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::aligned_accessor::reference](aligned_accessor_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_accessor](default_accessor.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_accessor::access](default_accessor_access.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_accessor::data_handle_type](default_accessor_data_handle_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_accessor::default_accessor](default_accessor_default_accessor.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_accessor::element_type](default_accessor_element_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_accessor::offset](default_accessor_offset.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_accessor::offset_policy](default_accessor_offset_policy.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_accessor::reference](default_accessor_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::dextents](dextents.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::dims](dims.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::dynamic_extent](dynamic_extent.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::extents](extents.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::extents::extent](extents_extent.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::extents::extents](extents_extents.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::extents::index_type](extents_index_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::extents::rank](extents_rank.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::extents::rank_dynamic](extents_rank_dynamic.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::extents::rank_type](extents_rank_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::extents::size_type](extents_size_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::extents::static_extent](extents_static_extent.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::full_extent](full_extent.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::full_extent_t](full_extent_t.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_left](layout_left.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_left::mapping](layout_left_mapping.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_left::mapping::`operator!=`](layout_left_mapping_operator_not_equal.md) | Member function | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_right](layout_right.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_right::mapping](layout_right_mapping.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_right::mapping::`operator!=`](layout_right_mapping_operator_not_equal.md) | Member function | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_stride](layout_stride.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_stride::mapping](layout_stride_mapping.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_stride::mapping::`operator!=`](layout_stride_mapping_operator_not_equal.md) | Member function | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_stride::mapping::`operator==`](layout_stride_mapping_operator_equal.md) | Member function | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::layout_stride::mapping::strides](layout_stride_mapping_strides.md) | Member function | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan](mdspan.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::accessor](mdspan_accessor.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::accessor_type](mdspan_accessor_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::data_handle](mdspan_data_handle.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::data_handle_type](mdspan_data_handle_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::element_type](mdspan_element_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::empty](mdspan_empty.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::extent](mdspan_extent.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::extents](mdspan_extents.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::extents_type](mdspan_extents_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::index_type](mdspan_index_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::is_always_exhaustive](mdspan_is_always_exhaustive.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::is_always_strided](mdspan_is_always_strided.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::is_always_unique](mdspan_is_always_unique.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::is_exhaustive](mdspan_is_exhaustive.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::is_strided](mdspan_is_strided.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::is_unique](mdspan_is_unique.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::layout_type](mdspan_layout_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::mapping](mdspan_mapping.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::mapping_type](mdspan_mapping_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::mdspan](mdspan_mdspan.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::`operator()`](mdspan_operator_call.md) | Member function | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::`operator=`](mdspan_operator_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::operator\[\]](mdspan_operator_subscript.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::rank](mdspan_rank.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::rank_dynamic](mdspan_rank_dynamic.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::rank_type](mdspan_rank_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::reference](mdspan_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::size](mdspan_size.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::size_type](mdspan_size_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::static_extent](mdspan_static_extent.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::stride](mdspan_stride.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mdspan::value_type](mdspan_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::strided_slice](strided_slice.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::submdspan](submdspan.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::submdspan_extents](submdspan_extents.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::submdspan_mapping](submdspan_mapping.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::submdspan_mapping_result](submdspan_mapping_result.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
