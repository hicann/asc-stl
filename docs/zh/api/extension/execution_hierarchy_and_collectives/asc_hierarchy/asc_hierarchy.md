# 头文件asc/hierarchy

提供线程网格、线程块、线程束和线程的维度、规模与索引查询，以及AI Core SIMD编程中的子块索引与数量查询

## 使用方式

```cpp
#include <asc/hierarchy>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::block](block.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::block_count](block_count.md) | 函数 | C++17+ | AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::block_dims（函数）](block_dims_function.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::block_dims（函数模板）](block_dims_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::block_extents_3d](block_extents_3d.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_index](block_index.md) | 函数 | C++17+ | AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::block_index_3d](block_index_3d.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::block_level](block_level.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::extent3d](extent3d.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::extent3d::count](extent3d_count.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::extent3d::extent3d](extent3d_extent3d.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::extent3d::`operator!=`](extent3d_operator_not_equal.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::extent3d::`operator==`](extent3d_operator_equal.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::extent3d::x](extent3d_x.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::extent3d::y](extent3d_y.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::extent3d::z](extent3d_z.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::get_launch_dimensions](get_launch_dimensions.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::grid](grid.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::grid_dims（函数）](grid_dims_function.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::grid_dims（函数模板）](grid_dims_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::grid_level](grid_level.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::lane_id](lane_id.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::launch_dimensions](launch_dimensions.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::launch_dimensions::block](launch_dimensions_block.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::launch_dimensions::grid](launch_dimensions_grid.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::level_dimensions](level_dimensions.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::level_dimensions::extents](level_dimensions_extents.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_hierarchy](make_hierarchy.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::simt_hierarchy](simt_hierarchy.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::simt_hierarchy::block_extents](simt_hierarchy_block_extents.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::simt_hierarchy::count](simt_hierarchy_count.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::simt_hierarchy::extents](simt_hierarchy_extents.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::simt_hierarchy::grid_extents](simt_hierarchy_grid_extents.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::sub_block_count](sub_block_count.md) | 函数 | C++17+ | AI Core SIMD编程 | Ascend 950 |
| [asc::sub_block_index](sub_block_index.md) | 函数 | C++17+ | AI Core SIMD编程 | Ascend 950 |
| [asc::thread](thread.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::thread_count](thread_count.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::thread_extents_3d](thread_extents_3d.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::thread_index](thread_index.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::thread_index_3d](thread_index_3d.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::thread_level](thread_level.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::warp](warp.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::warp_count](warp_count.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::warp_index](warp_index.md) | 函数 | C++17+ | AI Core SIMT编程 | Ascend 950 |
| [asc::warp_level](warp_level.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::warp_size](warp_size.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
