# 头文件asc/algorithm

通过设备端执行策略异步提交并行变换、查找、归约、扫描、选择、分区、合并和排序等算法

## 使用方式

```cpp
#include <asc/algorithm>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::copy_bytes](copy_bytes.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::fill_bytes](fill_bytes.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::parallel::adjacent_difference](parallel_adjacent_difference.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::adjacent_find](parallel_adjacent_find.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::all_of](parallel_all_of.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::any_of](parallel_any_of.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::copy](parallel_copy.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::copy_if](parallel_copy_if.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::copy_n](parallel_copy_n.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::count](parallel_count.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::count_if](parallel_count_if.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::equal](parallel_equal.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::exclusive_scan](parallel_exclusive_scan.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::fill](parallel_fill.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::fill_n](parallel_fill_n.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::find](parallel_find.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::find_if](parallel_find_if.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::find_if_not](parallel_find_if_not.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::for_each](parallel_for_each.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::for_each_n](parallel_for_each_n.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::generate](parallel_generate.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::generate_n](parallel_generate_n.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::inclusive_scan](parallel_inclusive_scan.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_heap](parallel_is_heap.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_heap_until](parallel_is_heap_until.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_partitioned](parallel_is_partitioned.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_sorted](parallel_is_sorted.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_sorted_until](parallel_is_sorted_until.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::max_element](parallel_max_element.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::merge](parallel_merge.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::min_element](parallel_min_element.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::mismatch](parallel_mismatch.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::none_of](parallel_none_of.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::partition](parallel_partition.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::partition_copy](parallel_partition_copy.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::reduce](parallel_reduce.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove](parallel_remove.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove_copy](parallel_remove_copy.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove_copy_if](parallel_remove_copy_if.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove_if](parallel_remove_if.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace](parallel_replace.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace_copy](parallel_replace_copy.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace_copy_if](parallel_replace_copy_if.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace_if](parallel_replace_if.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::reverse](parallel_reverse.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::reverse_copy](parallel_reverse_copy.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::rotate](parallel_rotate.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::rotate_copy](parallel_rotate_copy.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::shift_left](parallel_shift_left.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::shift_right](parallel_shift_right.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::sort](parallel_sort.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::stable_partition](parallel_stable_partition.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::swap_ranges](parallel_swap_ranges.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform](parallel_transform.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform_exclusive_scan](parallel_transform_exclusive_scan.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform_inclusive_scan](parallel_transform_inclusive_scan.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform_reduce](parallel_transform_reduce.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::unique](parallel_unique.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::parallel::unique_copy](parallel_unique_copy.md) | 函数模板 | C++17+ | Host | Ascend 950 |
