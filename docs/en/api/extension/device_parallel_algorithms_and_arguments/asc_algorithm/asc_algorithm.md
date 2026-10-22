# Header asc/algorithm

Asynchronously submits parallel algorithms such as transform, find, reduction, scan, selection, partition, merge, and sort through device-side execution policies

## Usage

```cpp
#include <asc/algorithm>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::copy_bytes](copy_bytes.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::fill_bytes](fill_bytes.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::parallel::adjacent_difference](parallel_adjacent_difference.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::adjacent_find](parallel_adjacent_find.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::all_of](parallel_all_of.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::any_of](parallel_any_of.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::copy](parallel_copy.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::copy_if](parallel_copy_if.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::copy_n](parallel_copy_n.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::count](parallel_count.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::count_if](parallel_count_if.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::equal](parallel_equal.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::exclusive_scan](parallel_exclusive_scan.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::fill](parallel_fill.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::fill_n](parallel_fill_n.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::find](parallel_find.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::find_if](parallel_find_if.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::find_if_not](parallel_find_if_not.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::for_each](parallel_for_each.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::for_each_n](parallel_for_each_n.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::generate](parallel_generate.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::generate_n](parallel_generate_n.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::inclusive_scan](parallel_inclusive_scan.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_heap](parallel_is_heap.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_heap_until](parallel_is_heap_until.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_partitioned](parallel_is_partitioned.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_sorted](parallel_is_sorted.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_sorted_until](parallel_is_sorted_until.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::max_element](parallel_max_element.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::merge](parallel_merge.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::min_element](parallel_min_element.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::mismatch](parallel_mismatch.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::none_of](parallel_none_of.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::partition](parallel_partition.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::partition_copy](parallel_partition_copy.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::reduce](parallel_reduce.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove](parallel_remove.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove_copy](parallel_remove_copy.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove_copy_if](parallel_remove_copy_if.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove_if](parallel_remove_if.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace](parallel_replace.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace_copy](parallel_replace_copy.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace_copy_if](parallel_replace_copy_if.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace_if](parallel_replace_if.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::reverse](parallel_reverse.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::reverse_copy](parallel_reverse_copy.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::rotate](parallel_rotate.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::rotate_copy](parallel_rotate_copy.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::shift_left](parallel_shift_left.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::shift_right](parallel_shift_right.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::sort](parallel_sort.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::stable_partition](parallel_stable_partition.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::swap_ranges](parallel_swap_ranges.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform](parallel_transform.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform_exclusive_scan](parallel_transform_exclusive_scan.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform_inclusive_scan](parallel_transform_inclusive_scan.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform_reduce](parallel_transform_reduce.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::unique](parallel_unique.md) | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::unique_copy](parallel_unique_copy.md) | Function template | C++17+ | Host | Ascend 950 |
