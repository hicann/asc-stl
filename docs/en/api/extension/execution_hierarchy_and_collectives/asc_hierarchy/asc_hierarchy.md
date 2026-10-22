# Header asc/hierarchy

Provides dimension, size, and index queries for the grid, thread blocks, warps, and threads, as well as sub-block index and count queries in AI Core SIMD programming

## Usage

```cpp
#include <asc/hierarchy>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::block](block.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_count](block_count.md) | Function | C++17+ | AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_dims (Function)](block_dims_function.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_dims (Function template)](block_dims_function_template.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_extents_3d](block_extents_3d.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_index](block_index.md) | Function | C++17+ | AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_index_3d](block_index_3d.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_level](block_level.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d](extent3d.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::count](extent3d_count.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::extent3d](extent3d_extent3d.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::`operator!=`](extent3d_operator_not_equal.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::`operator==`](extent3d_operator_equal.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::x](extent3d_x.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::y](extent3d_y.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::z](extent3d_z.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::get_launch_dimensions](get_launch_dimensions.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::grid](grid.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::grid_dims (Function)](grid_dims_function.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::grid_dims (Function template)](grid_dims_function_template.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::grid_level](grid_level.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::lane_id](lane_id.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::launch_dimensions](launch_dimensions.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::launch_dimensions::block](launch_dimensions_block.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::launch_dimensions::grid](launch_dimensions_grid.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::level_dimensions](level_dimensions.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::level_dimensions::extents](level_dimensions_extents.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_hierarchy](make_hierarchy.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy](simt_hierarchy.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy::block_extents](simt_hierarchy_block_extents.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy::count](simt_hierarchy_count.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy::extents](simt_hierarchy_extents.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy::grid_extents](simt_hierarchy_grid_extents.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::sub_block_count](sub_block_count.md) | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::sub_block_index](sub_block_index.md) | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::thread](thread.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::thread_count](thread_count.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::thread_extents_3d](thread_extents_3d.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::thread_index](thread_index.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::thread_index_3d](thread_index_3d.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::thread_level](thread_level.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::warp](warp.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::warp_count](warp_count.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_index](warp_index.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_level](warp_level.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::warp_size](warp_size.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
