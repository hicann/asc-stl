# C++ 标准库接口

`asc::std` 提供面向 Host 与 Device 的 C++ 标准库接口。每个详情页同时说明标准来源和 ASC-STL 的实际可用范围。

## 分类总览

| 能力分类 | 说明 |
| --- | --- |
| [语言支持库](language_support/language_support.md) | 基础类型、特性宏、源码位置与语言设施。 |
| [概念库](concepts/concepts.md) | 用于表达模板参数要求的标准概念。 |
| [诊断库](diagnostics/diagnostics.md) | 断言、错误码与诊断相关接口。 |
| [内存管理库](memory_management/memory_management.md) | 对象生命周期、分配器与内存操作。 |
| [元编程库](metaprogramming/metaprogramming.md) | 类型特征、编译期计算与模板辅助设施。 |
| [通用工具库](utilities/utilities.md) | 通用对象、函数对象与值操作工具。 |
| [容器库](containers/containers.md) | 序列、关联容器及其适配器。 |
| [迭代器库](iterators/iterators.md) | 迭代器、哨兵和迭代器适配器。 |
| [范围库](ranges/ranges.md) | 范围视图、范围访问及范围适配器。 |
| [算法库](algorithms/algorithms.md) | 查找、排序、变换和数值算法。 |
| [字符串库](strings/strings.md) | 字符序列、字符串视图与字符串操作。 |
| [文本处理库](text_processing/text_processing.md) | 字符分类、转换和文本格式处理。 |
| [数值库](numerics/numerics.md) | 数学函数、复数、随机数及数值运算。 |
| [日期和时间库](chrono/chrono.md) | 时钟、时间段、日历与时间转换。 |
| [输入/输出库](input_output/input_output.md) | 输入输出相关的类型与工具。 |
| [并发支持库](concurrency/concurrency.md) | 原子、同步和并发操作设施。 |

## API 支持列表

| API | 头文件 | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- | --- |
| [asc::std::adjacent_find](algorithms/asc_std_algorithm/adjacent_find.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::all_of](algorithms/asc_std_algorithm/all_of.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::any_of](algorithms/asc_std_algorithm/any_of.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::binary_search](algorithms/asc_std_algorithm/binary_search.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::clamp](algorithms/asc_std_algorithm/clamp.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::copy](algorithms/asc_std_algorithm/copy.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::copy_backward](algorithms/asc_std_algorithm/copy_backward.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::copy_if](algorithms/asc_std_algorithm/copy_if.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::copy_n](algorithms/asc_std_algorithm/copy_n.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::count](algorithms/asc_std_algorithm/count.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::count_if](algorithms/asc_std_algorithm/count_if.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::equal](algorithms/asc_std_algorithm/equal.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::equal_range](algorithms/asc_std_algorithm/equal_range.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fill](algorithms/asc_std_algorithm/fill.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fill_n](algorithms/asc_std_algorithm/fill_n.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::find](algorithms/asc_std_algorithm/find.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::find_end](algorithms/asc_std_algorithm/find_end.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::find_first_of](algorithms/asc_std_algorithm/find_first_of.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::find_if](algorithms/asc_std_algorithm/find_if.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::find_if_not](algorithms/asc_std_algorithm/find_if_not.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::for_each](algorithms/asc_std_algorithm/for_each.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::for_each_n](algorithms/asc_std_algorithm/for_each_n.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::generate](algorithms/asc_std_algorithm/generate.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::generate_n](algorithms/asc_std_algorithm/generate_n.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::includes](algorithms/asc_std_algorithm/includes.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::inplace_merge](algorithms/asc_std_algorithm/inplace_merge.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程 | Ascend 950 |
| [asc::std::is_heap](algorithms/asc_std_algorithm/is_heap.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_heap_until](algorithms/asc_std_algorithm/is_heap_until.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_partitioned](algorithms/asc_std_algorithm/is_partitioned.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_permutation](algorithms/asc_std_algorithm/is_permutation.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_sorted](algorithms/asc_std_algorithm/is_sorted.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_sorted_until](algorithms/asc_std_algorithm/is_sorted_until.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iter_swap](algorithms/asc_std_algorithm/iter_swap.md) | asc/std/algorithm | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lexicographical_compare](algorithms/asc_std_algorithm/lexicographical_compare.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lower_bound](algorithms/asc_std_algorithm/lower_bound.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_heap](algorithms/asc_std_algorithm/make_heap.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::max](algorithms/asc_std_algorithm/max.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::max_element](algorithms/asc_std_algorithm/max_element.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::merge](algorithms/asc_std_algorithm/merge.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::min](algorithms/asc_std_algorithm/min.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::min_element](algorithms/asc_std_algorithm/min_element.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::minmax](algorithms/asc_std_algorithm/minmax.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::minmax_element](algorithms/asc_std_algorithm/minmax_element.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mismatch](algorithms/asc_std_algorithm/mismatch.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move](algorithms/asc_std_algorithm/move.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_backward](algorithms/asc_std_algorithm/move_backward.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::next_permutation](algorithms/asc_std_algorithm/next_permutation.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::none_of](algorithms/asc_std_algorithm/none_of.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nth_element](algorithms/asc_std_algorithm/nth_element.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::partial_sort](algorithms/asc_std_algorithm/partial_sort.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::partial_sort_copy](algorithms/asc_std_algorithm/partial_sort_copy.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::partition](algorithms/asc_std_algorithm/partition.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::partition_copy](algorithms/asc_std_algorithm/partition_copy.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::partition_point](algorithms/asc_std_algorithm/partition_point.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pop_heap](algorithms/asc_std_algorithm/pop_heap.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::prev_permutation](algorithms/asc_std_algorithm/prev_permutation.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::push_heap](algorithms/asc_std_algorithm/push_heap.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::find_if](algorithms/asc_std_algorithm/ranges_find_if.md) | asc/std/algorithm | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::find_if_not](algorithms/asc_std_algorithm/ranges_find_if_not.md) | asc/std/algorithm | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::for_each](algorithms/asc_std_algorithm/ranges_for_each.md) | asc/std/algorithm | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::for_each_n](algorithms/asc_std_algorithm/ranges_for_each_n.md) | asc/std/algorithm | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::for_each_n_result](algorithms/asc_std_algorithm/ranges_for_each_n_result.md) | asc/std/algorithm | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::for_each_result](algorithms/asc_std_algorithm/ranges_for_each_result.md) | asc/std/algorithm | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::in_fun_result](algorithms/asc_std_algorithm/ranges_in_fun_result.md) | asc/std/algorithm | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::min](algorithms/asc_std_algorithm/ranges_min.md) | asc/std/algorithm | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::min_element](algorithms/asc_std_algorithm/ranges_min_element.md) | asc/std/algorithm | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove](algorithms/asc_std_algorithm/remove.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_copy](algorithms/asc_std_algorithm/remove_copy.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_copy_if](algorithms/asc_std_algorithm/remove_copy_if.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_if](algorithms/asc_std_algorithm/remove_if.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::replace](algorithms/asc_std_algorithm/replace.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::replace_copy](algorithms/asc_std_algorithm/replace_copy.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::replace_copy_if](algorithms/asc_std_algorithm/replace_copy_if.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::replace_if](algorithms/asc_std_algorithm/replace_if.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse](algorithms/asc_std_algorithm/reverse.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_copy](algorithms/asc_std_algorithm/reverse_copy.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rotate](algorithms/asc_std_algorithm/rotate.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rotate_copy](algorithms/asc_std_algorithm/rotate_copy.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sample](algorithms/asc_std_algorithm/sample.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::search](algorithms/asc_std_algorithm/search.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::search_n](algorithms/asc_std_algorithm/search_n.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set_difference](algorithms/asc_std_algorithm/set_difference.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set_intersection](algorithms/asc_std_algorithm/set_intersection.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set_symmetric_difference](algorithms/asc_std_algorithm/set_symmetric_difference.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set_union](algorithms/asc_std_algorithm/set_union.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shift_left](algorithms/asc_std_algorithm/shift_left.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shift_right](algorithms/asc_std_algorithm/shift_right.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shuffle](algorithms/asc_std_algorithm/shuffle.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sort](algorithms/asc_std_algorithm/sort.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sort_heap](algorithms/asc_std_algorithm/sort_heap.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stable_partition](algorithms/asc_std_algorithm/stable_partition.md) | asc/std/algorithm | 函数模板 | C++17+ | Host；Host、AI Core SIMD 编程 | Ascend 950 |
| [asc::std::stable_sort](algorithms/asc_std_algorithm/stable_sort.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程 | Ascend 950 |
| [asc::std::swap_ranges](algorithms/asc_std_algorithm/swap_ranges.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::transform](algorithms/asc_std_algorithm/transform.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique](algorithms/asc_std_algorithm/unique.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_copy](algorithms/asc_std_algorithm/unique_copy.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::upper_bound](algorithms/asc_std_algorithm/upper_bound.md) | asc/std/algorithm | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::array](containers/asc_std_array/array.md) | asc/std/array | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::get](containers/asc_std_array/get.md) | asc/std/array | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator!=（函数模板）](containers/asc_std_array/operator_not_equal.md) | asc/std/array | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator==（函数模板）](containers/asc_std_array/operator_equal.md) | asc/std/array | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::to_array](containers/asc_std_array/to_array.md) | asc/std/array | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple_element](containers/asc_std_array/tuple_element.md) | asc/std/array | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple_size](containers/asc_std_array/tuple_size.md) | asc/std/array | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_BOOL_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_bool_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_CHAR16_T_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_char16_t_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_CHAR32_T_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_char32_t_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_CHAR8_T_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_char8_t_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_CHAR_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_char_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_FLAG_INIT](concurrency/asc_std_atomic/cann_asc_stl_atomic_flag_init.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_INT_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_int_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_LLONG_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_llong_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_LONG_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_long_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_POINTER_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_pointer_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_SHORT_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_short_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_VAR_INIT](concurrency/asc_std_atomic/cann_asc_stl_atomic_var_init.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_WCHAR_T_LOCK_FREE](concurrency/asc_std_atomic/cann_asc_stl_atomic_wchar_t_lock_free.md) | asc/std/atomic | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic](concurrency/asc_std_atomic/atomic.md) | asc/std/atomic | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::atomic](concurrency/asc_std_atomic/atomic_atomic.md) | asc/std/atomic | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::compare_exchange_strong](concurrency/asc_std_atomic/atomic_compare_exchange_strong_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::compare_exchange_weak](concurrency/asc_std_atomic/atomic_compare_exchange_weak_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::exchange](concurrency/asc_std_atomic/atomic_exchange_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_add](concurrency/asc_std_atomic/atomic_fetch_add_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_and](concurrency/asc_std_atomic/atomic_fetch_and_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_or](concurrency/asc_std_atomic/atomic_fetch_or_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_sub](concurrency/asc_std_atomic/atomic_fetch_sub_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_xor](concurrency/asc_std_atomic/atomic_fetch_xor_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::is_always_lock_free](concurrency/asc_std_atomic/atomic_is_always_lock_free.md) | asc/std/atomic | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::is_lock_free](concurrency/asc_std_atomic/atomic_is_lock_free_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::load](concurrency/asc_std_atomic/atomic_load_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::storage_type](concurrency/asc_std_atomic/atomic_storage_type.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::store](concurrency/asc_std_atomic/atomic_store_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::value_type](concurrency/asc_std_atomic/atomic_value_type.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_bool](concurrency/asc_std_atomic/atomic_bool.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_char](concurrency/asc_std_atomic/atomic_char.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_char16_t](concurrency/asc_std_atomic/atomic_char16_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_char32_t](concurrency/asc_std_atomic/atomic_char32_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_char8_t](concurrency/asc_std_atomic/atomic_char8_t.md) | asc/std/atomic | 类型别名 | C++20+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_compare_exchange_strong](concurrency/asc_std_atomic/atomic_compare_exchange_strong_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_compare_exchange_strong_explicit](concurrency/asc_std_atomic/atomic_compare_exchange_strong_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_compare_exchange_weak](concurrency/asc_std_atomic/atomic_compare_exchange_weak_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_compare_exchange_weak_explicit](concurrency/asc_std_atomic/atomic_compare_exchange_weak_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_exchange](concurrency/asc_std_atomic/atomic_exchange_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_exchange_explicit](concurrency/asc_std_atomic/atomic_exchange_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_add](concurrency/asc_std_atomic/atomic_fetch_add_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_add_explicit](concurrency/asc_std_atomic/atomic_fetch_add_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_and](concurrency/asc_std_atomic/atomic_fetch_and_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_and_explicit](concurrency/asc_std_atomic/atomic_fetch_and_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_or](concurrency/asc_std_atomic/atomic_fetch_or_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_or_explicit](concurrency/asc_std_atomic/atomic_fetch_or_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_sub](concurrency/asc_std_atomic/atomic_fetch_sub_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_sub_explicit](concurrency/asc_std_atomic/atomic_fetch_sub_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_xor](concurrency/asc_std_atomic/atomic_fetch_xor_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_xor_explicit](concurrency/asc_std_atomic/atomic_fetch_xor_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag](concurrency/asc_std_atomic/atomic_flag.md) | asc/std/atomic | 类 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag::atomic_flag](concurrency/asc_std_atomic/atomic_flag_atomic_flag.md) | asc/std/atomic | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag::clear](concurrency/asc_std_atomic/atomic_flag_clear_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag::test](concurrency/asc_std_atomic/atomic_flag_test_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag::test_and_set](concurrency/asc_std_atomic/atomic_flag_test_and_set_member_function.md) | asc/std/atomic | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_clear](concurrency/asc_std_atomic/atomic_flag_clear_function.md) | asc/std/atomic | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_clear_explicit](concurrency/asc_std_atomic/atomic_flag_clear_explicit.md) | asc/std/atomic | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_test](concurrency/asc_std_atomic/atomic_flag_test_function.md) | asc/std/atomic | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_test_and_set](concurrency/asc_std_atomic/atomic_flag_test_and_set_function.md) | asc/std/atomic | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_test_and_set_explicit](concurrency/asc_std_atomic/atomic_flag_test_and_set_explicit.md) | asc/std/atomic | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_test_explicit](concurrency/asc_std_atomic/atomic_flag_test_explicit.md) | asc/std/atomic | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_init](concurrency/asc_std_atomic/atomic_init.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int](concurrency/asc_std_atomic/atomic_int.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int16_t](concurrency/asc_std_atomic/atomic_int16_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int32_t](concurrency/asc_std_atomic/atomic_int32_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int64_t](concurrency/asc_std_atomic/atomic_int64_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int8_t](concurrency/asc_std_atomic/atomic_int8_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_fast16_t](concurrency/asc_std_atomic/atomic_int_fast16_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_fast32_t](concurrency/asc_std_atomic/atomic_int_fast32_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_fast64_t](concurrency/asc_std_atomic/atomic_int_fast64_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_fast8_t](concurrency/asc_std_atomic/atomic_int_fast8_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_least16_t](concurrency/asc_std_atomic/atomic_int_least16_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_least32_t](concurrency/asc_std_atomic/atomic_int_least32_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_least64_t](concurrency/asc_std_atomic/atomic_int_least64_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_least8_t](concurrency/asc_std_atomic/atomic_int_least8_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_intmax_t](concurrency/asc_std_atomic/atomic_intmax_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_intptr_t](concurrency/asc_std_atomic/atomic_intptr_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_is_lock_free](concurrency/asc_std_atomic/atomic_is_lock_free_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_llong](concurrency/asc_std_atomic/atomic_llong.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_load](concurrency/asc_std_atomic/atomic_load_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_load_explicit](concurrency/asc_std_atomic/atomic_load_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_long](concurrency/asc_std_atomic/atomic_long.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ptrdiff_t](concurrency/asc_std_atomic/atomic_ptrdiff_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ref](concurrency/asc_std_atomic/atomic_ref.md) | asc/std/atomic | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_schar](concurrency/asc_std_atomic/atomic_schar.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_short](concurrency/asc_std_atomic/atomic_short.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_signed_lock_free](concurrency/asc_std_atomic/atomic_signed_lock_free.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_size_t](concurrency/asc_std_atomic/atomic_size_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_store](concurrency/asc_std_atomic/atomic_store_function_template.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_store_explicit](concurrency/asc_std_atomic/atomic_store_explicit.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_thread_fence](concurrency/asc_std_atomic/atomic_thread_fence.md) | asc/std/atomic | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uchar](concurrency/asc_std_atomic/atomic_uchar.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint](concurrency/asc_std_atomic/atomic_uint.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint16_t](concurrency/asc_std_atomic/atomic_uint16_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint32_t](concurrency/asc_std_atomic/atomic_uint32_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint64_t](concurrency/asc_std_atomic/atomic_uint64_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint8_t](concurrency/asc_std_atomic/atomic_uint8_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_fast16_t](concurrency/asc_std_atomic/atomic_uint_fast16_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_fast32_t](concurrency/asc_std_atomic/atomic_uint_fast32_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_fast64_t](concurrency/asc_std_atomic/atomic_uint_fast64_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_fast8_t](concurrency/asc_std_atomic/atomic_uint_fast8_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_least16_t](concurrency/asc_std_atomic/atomic_uint_least16_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_least32_t](concurrency/asc_std_atomic/atomic_uint_least32_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_least64_t](concurrency/asc_std_atomic/atomic_uint_least64_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_least8_t](concurrency/asc_std_atomic/atomic_uint_least8_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uintmax_t](concurrency/asc_std_atomic/atomic_uintmax_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uintptr_t](concurrency/asc_std_atomic/atomic_uintptr_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ullong](concurrency/asc_std_atomic/atomic_ullong.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ulong](concurrency/asc_std_atomic/atomic_ulong.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_unsigned_lock_free](concurrency/asc_std_atomic/atomic_unsigned_lock_free.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ushort](concurrency/asc_std_atomic/atomic_ushort.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_wchar_t](concurrency/asc_std_atomic/atomic_wchar_t.md) | asc/std/atomic | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::kill_dependency](concurrency/asc_std_atomic/kill_dependency.md) | asc/std/atomic | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order](concurrency/asc_std_atomic/memory_order.md) | asc/std/atomic | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_acq_rel](concurrency/asc_std_atomic/memory_order_acq_rel.md) | asc/std/atomic | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_acquire](concurrency/asc_std_atomic/memory_order_acquire.md) | asc/std/atomic | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_consume](concurrency/asc_std_atomic/memory_order_consume.md) | asc/std/atomic | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_relaxed](concurrency/asc_std_atomic/memory_order_relaxed.md) | asc/std/atomic | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_release](concurrency/asc_std_atomic/memory_order_release.md) | asc/std/atomic | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_seq_cst](concurrency/asc_std_atomic/memory_order_seq_cst.md) | asc/std/atomic | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::barrier](concurrency/asc_std_barrier/barrier.md) | asc/std/barrier | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::barrier::arrival_token](concurrency/asc_std_barrier/barrier_arrival_token.md) | asc/std/barrier | 类 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::barrier::arrive](concurrency/asc_std_barrier/barrier_arrive.md) | asc/std/barrier | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::barrier::arrive_and_drop](concurrency/asc_std_barrier/barrier_arrive_and_drop.md) | asc/std/barrier | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::barrier::arrive_and_wait](concurrency/asc_std_barrier/barrier_arrive_and_wait.md) | asc/std/barrier | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::barrier::barrier](concurrency/asc_std_barrier/barrier_barrier.md) | asc/std/barrier | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::barrier::max](concurrency/asc_std_barrier/barrier_max.md) | asc/std/barrier | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::barrier::wait](concurrency/asc_std_barrier/barrier_wait.md) | asc/std/barrier | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_cast](utilities/asc_std_bit/bit_cast.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_ceil](utilities/asc_std_bit/bit_ceil.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_floor](utilities/asc_std_bit/bit_floor.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_width](utilities/asc_std_bit/bit_width.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::byteswap](utilities/asc_std_bit/byteswap.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::countl_one](utilities/asc_std_bit/countl_one.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::countl_zero](utilities/asc_std_bit/countl_zero.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::countr_one](utilities/asc_std_bit/countr_one.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::countr_zero](utilities/asc_std_bit/countr_zero.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::endian](utilities/asc_std_bit/endian.md) | asc/std/bit | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::has_single_bit](utilities/asc_std_bit/has_single_bit.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::popcount](utilities/asc_std_bit/popcount.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rotl](utilities/asc_std_bit/rotl.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rotr](utilities/asc_std_bit/rotr.md) | asc/std/bit | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset](utilities/asc_std_bitset/bitset.md) | asc/std/bitset | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::all](utilities/asc_std_bitset/bitset_all.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::any](utilities/asc_std_bitset/bitset_any.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::base](utilities/asc_std_bitset/bitset_base.md) | asc/std/bitset | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::bitset](utilities/asc_std_bitset/bitset_bitset.md) | asc/std/bitset | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::const_reference](utilities/asc_std_bitset/bitset_const_reference.md) | asc/std/bitset | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::count](utilities/asc_std_bitset/bitset_count.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::flip](utilities/asc_std_bitset/bitset_flip.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::none](utilities/asc_std_bitset/bitset_none.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator!=](utilities/asc_std_bitset/bitset_operator_not_equal.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator&=](utilities/asc_std_bitset/bitset_operator_bit_and_assign.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator<<](utilities/asc_std_bitset/bitset_operator_shift_left.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator<<=](utilities/asc_std_bitset/bitset_operator_shift_left_assign.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator==](utilities/asc_std_bitset/bitset_operator_equal.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator>>](utilities/asc_std_bitset/bitset_operator_shift_right.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator>>=](utilities/asc_std_bitset/bitset_operator_shift_right_assign.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator\[\]](utilities/asc_std_bitset/bitset_operator_subscript.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator^=](utilities/asc_std_bitset/bitset_operator_bit_xor_assign.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator\|=](utilities/asc_std_bitset/bitset_operator_bit_or_assign.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::operator~](utilities/asc_std_bitset/bitset_operator_bit_not.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::reference](utilities/asc_std_bitset/bitset_reference.md) | asc/std/bitset | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::reset](utilities/asc_std_bitset/bitset_reset.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::set](utilities/asc_std_bitset/bitset_set.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::size](utilities/asc_std_bitset/bitset_size.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::to_ullong](utilities/asc_std_bitset/bitset_to_ullong.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bitset::to_ulong](utilities/asc_std_bitset/bitset_to_ulong.md) | asc/std/bitset | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::hash](utilities/asc_std_bitset/hash.md) | asc/std/bitset | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator&（函数模板）](utilities/asc_std_bitset/operator_bit_and.md) | asc/std/bitset | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator^（函数模板）](utilities/asc_std_bitset/operator_bit_xor.md) | asc/std/bitset | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator\|（函数模板）](utilities/asc_std_bitset/operator_bit_or.md) | asc/std/bitset | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [assert](diagnostics/asc_std_cassert/assert.md) | asc/std/cassert | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isalnum](text_processing/asc_std_cctype/isalnum.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isalpha](text_processing/asc_std_cctype/isalpha.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isblank](text_processing/asc_std_cctype/isblank.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iscntrl](text_processing/asc_std_cctype/iscntrl.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isdigit](text_processing/asc_std_cctype/isdigit.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isgraph](text_processing/asc_std_cctype/isgraph.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::islower](text_processing/asc_std_cctype/islower.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isprint](text_processing/asc_std_cctype/isprint.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ispunct](text_processing/asc_std_cctype/ispunct.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isspace](text_processing/asc_std_cctype/isspace.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isupper](text_processing/asc_std_cctype/isupper.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isxdigit](text_processing/asc_std_cctype/isxdigit.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tolower](text_processing/asc_std_cctype/tolower.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::toupper](text_processing/asc_std_cctype/toupper.md) | asc/std/cctype | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [EDOM](diagnostics/asc_std_cerrno/edom.md) | asc/std/cerrno | 宏 | C++17+ | Host（完整接口）、Device（常量接口） | Ascend 950 |
| [EILSEQ](diagnostics/asc_std_cerrno/eilseq.md) | asc/std/cerrno | 宏 | C++17+ | Host（完整接口）、Device（常量接口） | Ascend 950 |
| [ERANGE](diagnostics/asc_std_cerrno/erange.md) | asc/std/cerrno | 宏 | C++17+ | Host（完整接口）、Device（常量接口） | Ascend 950 |
| [errno](diagnostics/asc_std_cerrno/errno.md) | asc/std/cerrno | 宏 | C++17+ | Host（完整接口）、Device（常量接口） | Ascend 950 |
| [DECIMAL_DIG](language_support/asc_std_cfloat/decimal_dig.md) | asc/std/cfloat | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [FLT_EVAL_METHOD](language_support/asc_std_cfloat/flt_eval_method.md) | asc/std/cfloat | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::errc](text_processing/asc_std_charconv/errc.md) | asc/std/charconv | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::from_chars（函数）](text_processing/asc_std_charconv/from_chars_function.md) | asc/std/charconv | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::from_chars（函数模板）](text_processing/asc_std_charconv/from_chars_function_template.md) | asc/std/charconv | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::from_chars_result](text_processing/asc_std_charconv/from_chars_result.md) | asc/std/charconv | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::to_chars（函数）](text_processing/asc_std_charconv/to_chars_function.md) | asc/std/charconv | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::to_chars（函数模板）](text_processing/asc_std_charconv/to_chars_function_template.md) | asc/std/charconv | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::to_chars_result](text_processing/asc_std_charconv/to_chars_result.md) | asc/std/charconv | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::April](chrono/asc_std_chrono/chrono_april.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::August](chrono/asc_std_chrono/chrono_august.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::December](chrono/asc_std_chrono/chrono_december.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::February](chrono/asc_std_chrono/chrono_february.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::January](chrono/asc_std_chrono/chrono_january.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::July](chrono/asc_std_chrono/chrono_july.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::June](chrono/asc_std_chrono/chrono_june.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::March](chrono/asc_std_chrono/chrono_march.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::May](chrono/asc_std_chrono/chrono_may.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::November](chrono/asc_std_chrono/chrono_november.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::October](chrono/asc_std_chrono/chrono_october.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::September](chrono/asc_std_chrono/chrono_september.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::abs](chrono/asc_std_chrono/chrono_abs.md) | asc/std/chrono | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::ceil](chrono/asc_std_chrono/chrono_ceil.md) | asc/std/chrono | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::day](chrono/asc_std_chrono/chrono_day.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::day::day](chrono/asc_std_chrono/chrono_day_day.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::day::ok](chrono/asc_std_chrono/chrono_day_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::day::operator++](chrono/asc_std_chrono/chrono_day_operator_increment.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::day::operator+=](chrono/asc_std_chrono/chrono_day_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::day::operator--](chrono/asc_std_chrono/chrono_day_operator_decrement.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::day::operator-=](chrono/asc_std_chrono/chrono_day_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::day::~day](chrono/asc_std_chrono/chrono_day_destructor_day.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::days](chrono/asc_std_chrono/chrono_days.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration](chrono/asc_std_chrono/chrono_duration.md) | asc/std/chrono | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::count](chrono/asc_std_chrono/chrono_duration_count.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::duration](chrono/asc_std_chrono/chrono_duration_duration.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::max](chrono/asc_std_chrono/chrono_duration_max.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::min](chrono/asc_std_chrono/chrono_duration_min.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::operator%=](chrono/asc_std_chrono/chrono_duration_operator_modulo_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::operator*=](chrono/asc_std_chrono/chrono_duration_operator_multiply_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::operator+](chrono/asc_std_chrono/chrono_duration_operator_plus.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::operator++](chrono/asc_std_chrono/chrono_duration_operator_increment.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::operator+=](chrono/asc_std_chrono/chrono_duration_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::operator-](chrono/asc_std_chrono/chrono_duration_operator_minus.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::operator--](chrono/asc_std_chrono/chrono_duration_operator_decrement.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::operator-=](chrono/asc_std_chrono/chrono_duration_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::operator/=](chrono/asc_std_chrono/chrono_duration_operator_divide_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::period](chrono/asc_std_chrono/chrono_duration_period.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::rep](chrono/asc_std_chrono/chrono_duration_rep.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration::zero](chrono/asc_std_chrono/chrono_duration_zero.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration_cast](chrono/asc_std_chrono/chrono_duration_cast.md) | asc/std/chrono | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration_values](chrono/asc_std_chrono/chrono_duration_values.md) | asc/std/chrono | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration_values::max](chrono/asc_std_chrono/chrono_duration_values_max.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration_values::min](chrono/asc_std_chrono/chrono_duration_values_min.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::duration_values::zero](chrono/asc_std_chrono/chrono_duration_values_zero.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::floor](chrono/asc_std_chrono/chrono_floor.md) | asc/std/chrono | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss](chrono/asc_std_chrono/chrono_hh_mm_ss.md) | asc/std/chrono | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss::fractional_width](chrono/asc_std_chrono/chrono_hh_mm_ss_fractional_width.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss::hh_mm_ss](chrono/asc_std_chrono/chrono_hh_mm_ss_hh_mm_ss.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss::hours](chrono/asc_std_chrono/chrono_hh_mm_ss_hours.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss::is_negative](chrono/asc_std_chrono/chrono_hh_mm_ss_is_negative.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss::minutes](chrono/asc_std_chrono/chrono_hh_mm_ss_minutes.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss::precision](chrono/asc_std_chrono/chrono_hh_mm_ss_precision.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss::seconds](chrono/asc_std_chrono/chrono_hh_mm_ss_seconds.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss::subseconds](chrono/asc_std_chrono/chrono_hh_mm_ss_subseconds.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hh_mm_ss::to_duration](chrono/asc_std_chrono/chrono_hh_mm_ss_to_duration.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::hours](chrono/asc_std_chrono/chrono_hours.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::is_am](chrono/asc_std_chrono/chrono_is_am.md) | asc/std/chrono | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::is_pm](chrono/asc_std_chrono/chrono_is_pm.md) | asc/std/chrono | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::last](chrono/asc_std_chrono/chrono_last.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::last_spec](chrono/asc_std_chrono/chrono_last_spec.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::last_spec::last_spec](chrono/asc_std_chrono/chrono_last_spec_last_spec.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::local_days](chrono/asc_std_chrono/chrono_local_days.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::local_seconds](chrono/asc_std_chrono/chrono_local_seconds.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::local_t](chrono/asc_std_chrono/chrono_local_t.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::local_time](chrono/asc_std_chrono/chrono_local_time.md) | asc/std/chrono | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::make12](chrono/asc_std_chrono/chrono_make12.md) | asc/std/chrono | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::make24](chrono/asc_std_chrono/chrono_make24.md) | asc/std/chrono | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::microseconds](chrono/asc_std_chrono/chrono_microseconds.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::milliseconds](chrono/asc_std_chrono/chrono_milliseconds.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::minutes](chrono/asc_std_chrono/chrono_minutes.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month](chrono/asc_std_chrono/chrono_month.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month::month](chrono/asc_std_chrono/chrono_month_month.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month::ok](chrono/asc_std_chrono/chrono_month_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month::operator++](chrono/asc_std_chrono/chrono_month_operator_increment.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month::operator+=](chrono/asc_std_chrono/chrono_month_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month::operator--](chrono/asc_std_chrono/chrono_month_operator_decrement.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month::operator-=](chrono/asc_std_chrono/chrono_month_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day](chrono/asc_std_chrono/chrono_month_day.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day::day](chrono/asc_std_chrono/chrono_month_day_day.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day::month](chrono/asc_std_chrono/chrono_month_day_month.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day::month_day](chrono/asc_std_chrono/chrono_month_day_month_day.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day::ok](chrono/asc_std_chrono/chrono_month_day_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day::~month_day](chrono/asc_std_chrono/chrono_month_day_destructor_month_day.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day_last](chrono/asc_std_chrono/chrono_month_day_last.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day_last::month](chrono/asc_std_chrono/chrono_month_day_last_month.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day_last::month_day_last](chrono/asc_std_chrono/chrono_month_day_last_month_day_last.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day_last::ok](chrono/asc_std_chrono/chrono_month_day_last_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_day_last::~month_day_last](chrono/asc_std_chrono/chrono_month_day_last_destructor_month_day_last.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday](chrono/asc_std_chrono/chrono_month_weekday.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday::month](chrono/asc_std_chrono/chrono_month_weekday_month.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday::month_weekday](chrono/asc_std_chrono/chrono_month_weekday_month_weekday.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday::ok](chrono/asc_std_chrono/chrono_month_weekday_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday::weekday_indexed](chrono/asc_std_chrono/chrono_month_weekday_weekday_indexed.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday::~month_weekday](chrono/asc_std_chrono/chrono_month_weekday_destructor_month_weekday.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday_last](chrono/asc_std_chrono/chrono_month_weekday_last.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday_last::month](chrono/asc_std_chrono/chrono_month_weekday_last_month.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday_last::month_weekday_last](chrono/asc_std_chrono/chrono_month_weekday_last_month_weekday_last.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday_last::ok](chrono/asc_std_chrono/chrono_month_weekday_last_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday_last::weekday_last](chrono/asc_std_chrono/chrono_month_weekday_last_weekday_last.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::month_weekday_last::~month_weekday_last](chrono/asc_std_chrono/chrono_month_weekday_last_destructor_month_weekday_last.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::months](chrono/asc_std_chrono/chrono_months.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::nanoseconds](chrono/asc_std_chrono/chrono_nanoseconds.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::round](chrono/asc_std_chrono/chrono_round.md) | asc/std/chrono | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::seconds](chrono/asc_std_chrono/chrono_seconds.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::sys_days](chrono/asc_std_chrono/chrono_sys_days.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::sys_seconds](chrono/asc_std_chrono/chrono_sys_seconds.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::sys_time](chrono/asc_std_chrono/chrono_sys_time.md) | asc/std/chrono | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::system_clock](chrono/asc_std_chrono/chrono_system_clock.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::system_clock::duration](chrono/asc_std_chrono/chrono_system_clock_duration.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::system_clock::is_steady](chrono/asc_std_chrono/chrono_system_clock_is_steady.md) | asc/std/chrono | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::system_clock::period](chrono/asc_std_chrono/chrono_system_clock_period.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::system_clock::rep](chrono/asc_std_chrono/chrono_system_clock_rep.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::system_clock::time_point](chrono/asc_std_chrono/chrono_system_clock_time_point.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point](chrono/asc_std_chrono/chrono_time_point.md) | asc/std/chrono | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::clock](chrono/asc_std_chrono/chrono_time_point_clock.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::duration](chrono/asc_std_chrono/chrono_time_point_duration.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::max](chrono/asc_std_chrono/chrono_time_point_max.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::min](chrono/asc_std_chrono/chrono_time_point_min.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::operator++](chrono/asc_std_chrono/chrono_time_point_operator_increment.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::operator+=](chrono/asc_std_chrono/chrono_time_point_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::operator--](chrono/asc_std_chrono/chrono_time_point_operator_decrement.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::operator-=](chrono/asc_std_chrono/chrono_time_point_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::period](chrono/asc_std_chrono/chrono_time_point_period.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::rep](chrono/asc_std_chrono/chrono_time_point_rep.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::time_point](chrono/asc_std_chrono/chrono_time_point_time_point.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point::time_since_epoch](chrono/asc_std_chrono/chrono_time_point_time_since_epoch.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::time_point_cast](chrono/asc_std_chrono/chrono_time_point_cast.md) | asc/std/chrono | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::treat_as_floating_point](chrono/asc_std_chrono/chrono_treat_as_floating_point.md) | asc/std/chrono | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::treat_as_floating_point_v](chrono/asc_std_chrono/chrono_treat_as_floating_point_v.md) | asc/std/chrono | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday](chrono/asc_std_chrono/chrono_weekday.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::c_encoding](chrono/asc_std_chrono/chrono_weekday_c_encoding.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::iso_encoding](chrono/asc_std_chrono/chrono_weekday_iso_encoding.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::ok](chrono/asc_std_chrono/chrono_weekday_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::operator++](chrono/asc_std_chrono/chrono_weekday_operator_increment.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::operator+=](chrono/asc_std_chrono/chrono_weekday_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::operator--](chrono/asc_std_chrono/chrono_weekday_operator_decrement.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::operator-=](chrono/asc_std_chrono/chrono_weekday_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::operator=](chrono/asc_std_chrono/chrono_weekday_operator_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::operator\[\]](chrono/asc_std_chrono/chrono_weekday_operator_subscript.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::weekday](chrono/asc_std_chrono/chrono_weekday_weekday.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday::~weekday](chrono/asc_std_chrono/chrono_weekday_destructor_weekday.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_indexed](chrono/asc_std_chrono/chrono_weekday_indexed.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_indexed::index](chrono/asc_std_chrono/chrono_weekday_indexed_index.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_indexed::ok](chrono/asc_std_chrono/chrono_weekday_indexed_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_indexed::weekday](chrono/asc_std_chrono/chrono_weekday_indexed_weekday.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_indexed::weekday_indexed](chrono/asc_std_chrono/chrono_weekday_indexed_weekday_indexed.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_indexed::~weekday_indexed](chrono/asc_std_chrono/chrono_weekday_indexed_destructor_weekday_indexed.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_last](chrono/asc_std_chrono/chrono_weekday_last.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_last::ok](chrono/asc_std_chrono/chrono_weekday_last_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_last::weekday](chrono/asc_std_chrono/chrono_weekday_last_weekday.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_last::weekday_last](chrono/asc_std_chrono/chrono_weekday_last_weekday_last.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weekday_last::~weekday_last](chrono/asc_std_chrono/chrono_weekday_last_destructor_weekday_last.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::weeks](chrono/asc_std_chrono/chrono_weeks.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year](chrono/asc_std_chrono/chrono_year.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::is_leap](chrono/asc_std_chrono/chrono_year_is_leap.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::max](chrono/asc_std_chrono/chrono_year_max.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::min](chrono/asc_std_chrono/chrono_year_min.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::ok](chrono/asc_std_chrono/chrono_year_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::operator+](chrono/asc_std_chrono/chrono_year_operator_plus.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::operator++](chrono/asc_std_chrono/chrono_year_operator_increment.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::operator+=](chrono/asc_std_chrono/chrono_year_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::operator-](chrono/asc_std_chrono/chrono_year_operator_minus.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::operator--](chrono/asc_std_chrono/chrono_year_operator_decrement.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::operator-=](chrono/asc_std_chrono/chrono_year_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::year](chrono/asc_std_chrono/chrono_year_year.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year::~year](chrono/asc_std_chrono/chrono_year_destructor_year.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month](chrono/asc_std_chrono/chrono_year_month.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month::month](chrono/asc_std_chrono/chrono_year_month_month.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month::ok](chrono/asc_std_chrono/chrono_year_month_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month::operator+=](chrono/asc_std_chrono/chrono_year_month_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month::operator-=](chrono/asc_std_chrono/chrono_year_month_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month::year](chrono/asc_std_chrono/chrono_year_month_year.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month::year_month](chrono/asc_std_chrono/chrono_year_month_year_month.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month::~year_month](chrono/asc_std_chrono/chrono_year_month_destructor_year_month.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day](chrono/asc_std_chrono/chrono_year_month_day.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day::day](chrono/asc_std_chrono/chrono_year_month_day_day.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day::month](chrono/asc_std_chrono/chrono_year_month_day_month.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day::ok](chrono/asc_std_chrono/chrono_year_month_day_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day::operator+=](chrono/asc_std_chrono/chrono_year_month_day_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day::operator-=](chrono/asc_std_chrono/chrono_year_month_day_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day::operator=](chrono/asc_std_chrono/chrono_year_month_day_operator_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day::year](chrono/asc_std_chrono/chrono_year_month_day_year.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day::year_month_day](chrono/asc_std_chrono/chrono_year_month_day_year_month_day.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day::~year_month_day](chrono/asc_std_chrono/chrono_year_month_day_destructor_year_month_day.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last](chrono/asc_std_chrono/chrono_year_month_day_last.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::day](chrono/asc_std_chrono/chrono_year_month_day_last_day.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::month](chrono/asc_std_chrono/chrono_year_month_day_last_month.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::month_day_last](chrono/asc_std_chrono/chrono_year_month_day_last_month_day_last.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::ok](chrono/asc_std_chrono/chrono_year_month_day_last_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::operator+=](chrono/asc_std_chrono/chrono_year_month_day_last_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::operator-=](chrono/asc_std_chrono/chrono_year_month_day_last_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::operator=](chrono/asc_std_chrono/chrono_year_month_day_last_operator_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::year](chrono/asc_std_chrono/chrono_year_month_day_last_year.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::year_month_day_last](chrono/asc_std_chrono/chrono_year_month_day_last_year_month_day_last.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_day_last::~year_month_day_last](chrono/asc_std_chrono/chrono_year_month_day_last_destructor_year_month_day_last.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday](chrono/asc_std_chrono/chrono_year_month_weekday.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::index](chrono/asc_std_chrono/chrono_year_month_weekday_index.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::month](chrono/asc_std_chrono/chrono_year_month_weekday_month.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::ok](chrono/asc_std_chrono/chrono_year_month_weekday_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::operator+=](chrono/asc_std_chrono/chrono_year_month_weekday_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::operator-=](chrono/asc_std_chrono/chrono_year_month_weekday_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::operator=](chrono/asc_std_chrono/chrono_year_month_weekday_operator_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::weekday](chrono/asc_std_chrono/chrono_year_month_weekday_weekday.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::weekday_indexed](chrono/asc_std_chrono/chrono_year_month_weekday_weekday_indexed.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::year](chrono/asc_std_chrono/chrono_year_month_weekday_year.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::year_month_weekday](chrono/asc_std_chrono/chrono_year_month_weekday_year_month_weekday.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday::~year_month_weekday](chrono/asc_std_chrono/chrono_year_month_weekday_destructor_year_month_weekday.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last](chrono/asc_std_chrono/chrono_year_month_weekday_last.md) | asc/std/chrono | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::month](chrono/asc_std_chrono/chrono_year_month_weekday_last_month.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::ok](chrono/asc_std_chrono/chrono_year_month_weekday_last_ok.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::operator+=](chrono/asc_std_chrono/chrono_year_month_weekday_last_operator_plus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::operator-=](chrono/asc_std_chrono/chrono_year_month_weekday_last_operator_minus_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::operator=](chrono/asc_std_chrono/chrono_year_month_weekday_last_operator_assign.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::weekday](chrono/asc_std_chrono/chrono_year_month_weekday_last_weekday.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::weekday_last](chrono/asc_std_chrono/chrono_year_month_weekday_last_weekday_last.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::year](chrono/asc_std_chrono/chrono_year_month_weekday_last_year.md) | asc/std/chrono | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::year_month_weekday_last](chrono/asc_std_chrono/chrono_year_month_weekday_last_year_month_weekday_last.md) | asc/std/chrono | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::year_month_weekday_last::~year_month_weekday_last](chrono/asc_std_chrono/chrono_year_month_weekday_last_destructor_year_month_weekday_last.md) | asc/std/chrono | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::chrono::years](chrono/asc_std_chrono/chrono_years.md) | asc/std/chrono | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::literals::chrono_literals::operator""d](chrono/asc_std_chrono/literals_chrono_literals_operator_literal_d.md) | asc/std/chrono | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::literals::chrono_literals::operator""y](chrono/asc_std_chrono/literals_chrono_literals_operator_literal_y.md) | asc/std/chrono | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [PRIdMAX](input_output/asc_std_cinttypes/pridmax.md) | asc/std/cinttypes | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [PRIuMAX](input_output/asc_std_cinttypes/priumax.md) | asc/std/cinttypes | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::imaxabs](input_output/asc_std_cinttypes/imaxabs.md) | asc/std/cinttypes | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::imaxdiv](input_output/asc_std_cinttypes/imaxdiv.md) | asc/std/cinttypes | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::imaxdiv_t](input_output/asc_std_cinttypes/imaxdiv_t.md) | asc/std/cinttypes | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::intmax_t](input_output/asc_std_cinttypes/intmax_t.md) | asc/std/cinttypes | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uintmax_t](input_output/asc_std_cinttypes/uintmax_t.md) | asc/std/cinttypes | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CHAR_BIT](language_support/asc_std_climits/char_bit.md) | asc/std/climits | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [UCHAR_MAX](language_support/asc_std_climits/uchar_max.md) | asc/std/climits | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [UINT_MAX](language_support/asc_std_climits/uint_max.md) | asc/std/climits | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [ULLONG_MAX](language_support/asc_std_climits/ullong_max.md) | asc/std/climits | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [ULONG_MAX](language_support/asc_std_climits/ulong_max.md) | asc/std/climits | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [USHRT_MAX](language_support/asc_std_climits/ushrt_max.md) | asc/std/climits | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [FP_ILOGB0](numerics/asc_std_cmath/fp_ilogb0.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [FP_ILOGBNAN](numerics/asc_std_cmath/fp_ilogbnan.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [FP_INFINITE](numerics/asc_std_cmath/fp_infinite.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [FP_LLOGB0](numerics/asc_std_cmath/fp_llogb0.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [FP_LLOGBNAN](numerics/asc_std_cmath/fp_llogbnan.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [FP_NAN](numerics/asc_std_cmath/fp_nan.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [FP_NORMAL](numerics/asc_std_cmath/fp_normal.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [FP_SUBNORMAL](numerics/asc_std_cmath/fp_subnormal.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [FP_ZERO](numerics/asc_std_cmath/fp_zero.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [INFINITY](numerics/asc_std_cmath/infinity.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [NAN](numerics/asc_std_cmath/nan.md) | asc/std/cmath | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::abs](numerics/asc_std_cmath/abs.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::acos（函数）](numerics/asc_std_cmath/acos.md) | asc/std/cmath | 函数 | C++17+ | 见各成员或重载说明 | Ascend 950 |
| [asc::std::acos（函数模板）](numerics/asc_std_cmath/acos_function_template.md) | asc/std/cmath | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::std::acosf](numerics/asc_std_cmath/acosf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::acosh](numerics/asc_std_cmath/acosh.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::acoshf](numerics/asc_std_cmath/acoshf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::acosl](numerics/asc_std_cmath/acosl.md) | asc/std/cmath | 函数 | C++17+ | Host | Ascend 950 |
| [asc::std::asin](numerics/asc_std_cmath/asin.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::asinf](numerics/asc_std_cmath/asinf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::asinh](numerics/asc_std_cmath/asinh.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::asinhf](numerics/asc_std_cmath/asinhf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atan](numerics/asc_std_cmath/atan.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atan2](numerics/asc_std_cmath/atan2.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atan2f](numerics/asc_std_cmath/atan2f.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atanf](numerics/asc_std_cmath/atanf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atanh](numerics/asc_std_cmath/atanh.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atanhf](numerics/asc_std_cmath/atanhf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cbrt](numerics/asc_std_cmath/cbrt.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cbrtf](numerics/asc_std_cmath/cbrtf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ceil](numerics/asc_std_cmath/ceil.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ceilf](numerics/asc_std_cmath/ceilf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::copysign](numerics/asc_std_cmath/copysign.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::copysignf](numerics/asc_std_cmath/copysignf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cos](numerics/asc_std_cmath/cos.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cosf](numerics/asc_std_cmath/cosf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cosh](numerics/asc_std_cmath/cosh.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::coshf](numerics/asc_std_cmath/coshf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::double_t](numerics/asc_std_cmath/double_t.md) | asc/std/cmath | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::erf](numerics/asc_std_cmath/erf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::erfc](numerics/asc_std_cmath/erfc.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::erfcf](numerics/asc_std_cmath/erfcf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::erff](numerics/asc_std_cmath/erff.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::exp](numerics/asc_std_cmath/exp.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::exp2](numerics/asc_std_cmath/exp2.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::exp2f](numerics/asc_std_cmath/exp2f.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expf](numerics/asc_std_cmath/expf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expm1](numerics/asc_std_cmath/expm1.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expm1f](numerics/asc_std_cmath/expm1f.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fabs](numerics/asc_std_cmath/fabs.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fabsf](numerics/asc_std_cmath/fabsf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fdim](numerics/asc_std_cmath/fdim.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fdimf](numerics/asc_std_cmath/fdimf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::float_t](numerics/asc_std_cmath/float_t.md) | asc/std/cmath | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::floor](numerics/asc_std_cmath/floor.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::floorf](numerics/asc_std_cmath/floorf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fma](numerics/asc_std_cmath/fma.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fmaf](numerics/asc_std_cmath/fmaf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fmax](numerics/asc_std_cmath/fmax.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fmaxf](numerics/asc_std_cmath/fmaxf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fmin](numerics/asc_std_cmath/fmin.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fminf](numerics/asc_std_cmath/fminf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fmod](numerics/asc_std_cmath/fmod.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fmodf](numerics/asc_std_cmath/fmodf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::fpclassify](numerics/asc_std_cmath/fpclassify.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::frexp](numerics/asc_std_cmath/frexp.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::frexpf](numerics/asc_std_cmath/frexpf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::hypot](numerics/asc_std_cmath/hypot.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::hypotf](numerics/asc_std_cmath/hypotf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ilogb](numerics/asc_std_cmath/ilogb.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ilogbf](numerics/asc_std_cmath/ilogbf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isfinite](numerics/asc_std_cmath/isfinite.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isgreater](numerics/asc_std_cmath/isgreater.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isgreaterequal](numerics/asc_std_cmath/isgreaterequal.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isinf](numerics/asc_std_cmath/isinf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isless](numerics/asc_std_cmath/isless.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::islessequal](numerics/asc_std_cmath/islessequal.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::islessgreater](numerics/asc_std_cmath/islessgreater.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isnan](numerics/asc_std_cmath/isnan.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isnormal](numerics/asc_std_cmath/isnormal.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::isunordered](numerics/asc_std_cmath/isunordered.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ldexp](numerics/asc_std_cmath/ldexp.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ldexpf](numerics/asc_std_cmath/ldexpf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lerp](numerics/asc_std_cmath/lerp.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lgamma](numerics/asc_std_cmath/lgamma.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lgammaf](numerics/asc_std_cmath/lgammaf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::llrint](numerics/asc_std_cmath/llrint.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::llrintf](numerics/asc_std_cmath/llrintf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::llround](numerics/asc_std_cmath/llround.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::llroundf](numerics/asc_std_cmath/llroundf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::log](numerics/asc_std_cmath/log.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::log10](numerics/asc_std_cmath/log10.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::log10f](numerics/asc_std_cmath/log10f.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::log1p](numerics/asc_std_cmath/log1p.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::log1pf](numerics/asc_std_cmath/log1pf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::log2](numerics/asc_std_cmath/log2.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::log2f](numerics/asc_std_cmath/log2f.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logb](numerics/asc_std_cmath/logb.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logbf](numerics/asc_std_cmath/logbf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logf](numerics/asc_std_cmath/logf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lrint](numerics/asc_std_cmath/lrint.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lrintf](numerics/asc_std_cmath/lrintf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lround](numerics/asc_std_cmath/lround.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lroundf](numerics/asc_std_cmath/lroundf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::modf](numerics/asc_std_cmath/modf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::modff](numerics/asc_std_cmath/modff.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nanf](numerics/asc_std_cmath/nanf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nearbyint](numerics/asc_std_cmath/nearbyint.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nearbyintf](numerics/asc_std_cmath/nearbyintf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nextafter](numerics/asc_std_cmath/nextafter.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nextafterf](numerics/asc_std_cmath/nextafterf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pow](numerics/asc_std_cmath/pow.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::powf](numerics/asc_std_cmath/powf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remainder](numerics/asc_std_cmath/remainder.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remainderf](numerics/asc_std_cmath/remainderf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remquo](numerics/asc_std_cmath/remquo.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remquof](numerics/asc_std_cmath/remquof.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rint](numerics/asc_std_cmath/rint.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rintf](numerics/asc_std_cmath/rintf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::round](numerics/asc_std_cmath/round.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::roundf](numerics/asc_std_cmath/roundf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scalbln](numerics/asc_std_cmath/scalbln.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scalblnf](numerics/asc_std_cmath/scalblnf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scalbn](numerics/asc_std_cmath/scalbn.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scalbnf](numerics/asc_std_cmath/scalbnf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::signbit](numerics/asc_std_cmath/signbit.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sin](numerics/asc_std_cmath/sin.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sinf](numerics/asc_std_cmath/sinf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sinh](numerics/asc_std_cmath/sinh.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sinhf](numerics/asc_std_cmath/sinhf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sqrt](numerics/asc_std_cmath/sqrt.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sqrtf](numerics/asc_std_cmath/sqrtf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tan](numerics/asc_std_cmath/tan.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tanf](numerics/asc_std_cmath/tanf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tanh](numerics/asc_std_cmath/tanh.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tanhf](numerics/asc_std_cmath/tanhf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tgamma](numerics/asc_std_cmath/tgamma.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tgammaf](numerics/asc_std_cmath/tgammaf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::trunc](numerics/asc_std_cmath/trunc.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::truncf](numerics/asc_std_cmath/truncf.md) | asc/std/cmath | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::compare_partial_order_fallback](language_support/asc_std_compare/compare_partial_order_fallback.md) | asc/std/compare | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::compare_strong_order_fallback](language_support/asc_std_compare/compare_strong_order_fallback.md) | asc/std/compare | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::compare_three_way](language_support/asc_std_compare/compare_three_way.md) | asc/std/compare | 类 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::compare_weak_order_fallback](language_support/asc_std_compare/compare_weak_order_fallback.md) | asc/std/compare | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_eq](language_support/asc_std_compare/is_eq.md) | asc/std/compare | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_gt](language_support/asc_std_compare/is_gt.md) | asc/std/compare | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_gteq](language_support/asc_std_compare/is_gteq.md) | asc/std/compare | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_lt](language_support/asc_std_compare/is_lt.md) | asc/std/compare | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_lteq](language_support/asc_std_compare/is_lteq.md) | asc/std/compare | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_neq](language_support/asc_std_compare/is_neq.md) | asc/std/compare | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::partial_ordering](language_support/asc_std_compare/partial_ordering.md) | asc/std/compare | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strong_ordering](language_support/asc_std_compare/strong_ordering.md) | asc/std/compare | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::weak_ordering](language_support/asc_std_compare/weak_ordering.md) | asc/std/compare | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::arg](numerics/asc_std_complex/arg.md) | asc/std/complex | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex](numerics/asc_std_complex/complex.md) | asc/std/complex | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex::complex](numerics/asc_std_complex/complex_complex.md) | asc/std/complex | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex::imag](numerics/asc_std_complex/complex_imag.md) | asc/std/complex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex::operator*=](numerics/asc_std_complex/complex_operator_multiply_assign.md) | asc/std/complex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex::operator+=](numerics/asc_std_complex/complex_operator_plus_assign.md) | asc/std/complex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex::operator-=](numerics/asc_std_complex/complex_operator_minus_assign.md) | asc/std/complex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex::operator/=](numerics/asc_std_complex/complex_operator_divide_assign.md) | asc/std/complex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex::operator=](numerics/asc_std_complex/complex_operator_assign.md) | asc/std/complex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex::real](numerics/asc_std_complex/complex_real.md) | asc/std/complex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::complex::value_type](numerics/asc_std_complex/complex_value_type.md) | asc/std/complex | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::conj](numerics/asc_std_complex/conj.md) | asc/std/complex | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::imag](numerics/asc_std_complex/imag.md) | asc/std/complex | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::norm](numerics/asc_std_complex/norm.md) | asc/std/complex | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator!=（函数）](numerics/asc_std_complex/operator_not_equal.md) | asc/std/complex | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator*](numerics/asc_std_complex/operator_dereference.md) | asc/std/complex | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator+](numerics/asc_std_complex/operator_plus.md) | asc/std/complex | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator-](numerics/asc_std_complex/operator_minus.md) | asc/std/complex | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator/](numerics/asc_std_complex/operator_divide.md) | asc/std/complex | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator==（函数）](numerics/asc_std_complex/operator_equal.md) | asc/std/complex | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::polar](numerics/asc_std_complex/polar.md) | asc/std/complex | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::proj](numerics/asc_std_complex/proj.md) | asc/std/complex | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::real](numerics/asc_std_complex/real.md) | asc/std/complex | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::assignable_from](concepts/asc_std_concepts/assignable_from.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_reference_with](concepts/asc_std_concepts/common_reference_with.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_with](concepts/asc_std_concepts/common_with.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::constructible_from](concepts/asc_std_concepts/constructible_from.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::convertible_to](concepts/asc_std_concepts/convertible_to.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::copy_constructible](concepts/asc_std_concepts/copy_constructible.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::copyable](concepts/asc_std_concepts/copyable.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_initializable](concepts/asc_std_concepts/default_initializable.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::derived_from](concepts/asc_std_concepts/derived_from.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::destructible](concepts/asc_std_concepts/destructible.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::equality_comparable](concepts/asc_std_concepts/equality_comparable.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::equality_comparable_with](concepts/asc_std_concepts/equality_comparable_with.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::equivalence_relation](concepts/asc_std_concepts/equivalence_relation.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::floating_point](concepts/asc_std_concepts/floating_point.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::integral](concepts/asc_std_concepts/integral.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::invocable](concepts/asc_std_concepts/invocable.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::movable](concepts/asc_std_concepts/movable.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_constructible](concepts/asc_std_concepts/move_constructible.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::predicate](concepts/asc_std_concepts/predicate.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::regular](concepts/asc_std_concepts/regular.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::regular_invocable](concepts/asc_std_concepts/regular_invocable.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::relation](concepts/asc_std_concepts/relation.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::same_as](concepts/asc_std_concepts/same_as.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::semiregular](concepts/asc_std_concepts/semiregular.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::signed_integral](concepts/asc_std_concepts/signed_integral.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strict_weak_order](concepts/asc_std_concepts/strict_weak_order.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::swappable](concepts/asc_std_concepts/swappable.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::swappable_with](concepts/asc_std_concepts/swappable_with.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::totally_ordered](concepts/asc_std_concepts/totally_ordered.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::totally_ordered_with](concepts/asc_std_concepts/totally_ordered_with.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unsigned_integral](concepts/asc_std_concepts/unsigned_integral.md) | asc/std/concepts | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::byte](language_support/asc_std_cstddef/byte.md) | asc/std/cstddef | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::max_align_t](language_support/asc_std_cstddef/max_align_t.md) | asc/std/cstddef | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nullptr_t](language_support/asc_std_cstddef/nullptr_t.md) | asc/std/cstddef | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator&（函数）](language_support/asc_std_cstddef/operator_bit_and.md) | asc/std/cstddef | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator&=](language_support/asc_std_cstddef/operator_bit_and_assign.md) | asc/std/cstddef | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator<<](language_support/asc_std_cstddef/operator_shift_left.md) | asc/std/cstddef | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator<<=](language_support/asc_std_cstddef/operator_shift_left_assign.md) | asc/std/cstddef | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator>>](language_support/asc_std_cstddef/operator_shift_right.md) | asc/std/cstddef | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator>>=](language_support/asc_std_cstddef/operator_shift_right_assign.md) | asc/std/cstddef | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator^（函数）](language_support/asc_std_cstddef/operator_bit_xor.md) | asc/std/cstddef | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator^=](language_support/asc_std_cstddef/operator_bit_xor_assign.md) | asc/std/cstddef | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator\|（函数）](language_support/asc_std_cstddef/operator_bit_or.md) | asc/std/cstddef | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator\|=](language_support/asc_std_cstddef/operator_bit_or_assign.md) | asc/std/cstddef | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator~](language_support/asc_std_cstddef/operator_bit_not.md) | asc/std/cstddef | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ptrdiff_t](language_support/asc_std_cstddef/ptrdiff_t.md) | asc/std/cstddef | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::size_t](language_support/asc_std_cstddef/size_t.md) | asc/std/cstddef | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::to_integer](language_support/asc_std_cstddef/to_integer.md) | asc/std/cstddef | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [offsetof](language_support/asc_std_cstddef/offsetof.md) | asc/std/cstddef | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [PTRDIFF_MAX](language_support/asc_std_cstdint/ptrdiff_max.md) | asc/std/cstdint | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [PTRDIFF_MIN](language_support/asc_std_cstdint/ptrdiff_min.md) | asc/std/cstdint | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [SIZE_MAX](language_support/asc_std_cstdint/size_max.md) | asc/std/cstdint | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::int16_t](language_support/asc_std_cstdint/int16_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::int32_t](language_support/asc_std_cstdint/int32_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::int64_t](language_support/asc_std_cstdint/int64_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::int8_t](language_support/asc_std_cstdint/int8_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::intptr_t](language_support/asc_std_cstdint/intptr_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uint16_t](language_support/asc_std_cstdint/uint16_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uint32_t](language_support/asc_std_cstdint/uint32_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uint64_t](language_support/asc_std_cstdint/uint64_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uint8_t](language_support/asc_std_cstdint/uint8_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uintptr_t](language_support/asc_std_cstdint/uintptr_t.md) | asc/std/cstdint | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::div](utilities/asc_std_cstdlib/div.md) | asc/std/cstdlib | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::div_t](utilities/asc_std_cstdlib/div_t.md) | asc/std/cstdlib | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::div_t::quot](utilities/asc_std_cstdlib/div_t_quot.md) | asc/std/cstdlib | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::div_t::rem](utilities/asc_std_cstdlib/div_t_rem.md) | asc/std/cstdlib | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::labs](utilities/asc_std_cstdlib/labs.md) | asc/std/cstdlib | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ldiv](utilities/asc_std_cstdlib/ldiv.md) | asc/std/cstdlib | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ldiv_t](utilities/asc_std_cstdlib/ldiv_t.md) | asc/std/cstdlib | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ldiv_t::quot](utilities/asc_std_cstdlib/ldiv_t_quot.md) | asc/std/cstdlib | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ldiv_t::rem](utilities/asc_std_cstdlib/ldiv_t_rem.md) | asc/std/cstdlib | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::llabs](utilities/asc_std_cstdlib/llabs.md) | asc/std/cstdlib | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lldiv](utilities/asc_std_cstdlib/lldiv.md) | asc/std/cstdlib | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lldiv_t](utilities/asc_std_cstdlib/lldiv_t.md) | asc/std/cstdlib | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lldiv_t::quot](utilities/asc_std_cstdlib/lldiv_t_quot.md) | asc/std/cstdlib | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lldiv_t::rem](utilities/asc_std_cstdlib/lldiv_t_rem.md) | asc/std/cstdlib | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memchr](strings/asc_std_cstring/memchr.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memcmp](strings/asc_std_cstring/memcmp.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memcpy](strings/asc_std_cstring/memcpy.md) | asc/std/cstring | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memmove](strings/asc_std_cstring/memmove.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memset](strings/asc_std_cstring/memset.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strcat](strings/asc_std_cstring/strcat.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strchr](strings/asc_std_cstring/strchr.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strcmp](strings/asc_std_cstring/strcmp.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strcpy](strings/asc_std_cstring/strcpy.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strcspn](strings/asc_std_cstring/strcspn.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strlen](strings/asc_std_cstring/strlen.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strncat](strings/asc_std_cstring/strncat.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strncmp](strings/asc_std_cstring/strncmp.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strncpy](strings/asc_std_cstring/strncpy.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strpbrk](strings/asc_std_cstring/strpbrk.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strrchr](strings/asc_std_cstring/strrchr.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strspn](strings/asc_std_cstring/strspn.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strstr](strings/asc_std_cstring/strstr.md) | asc/std/cstring | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CLOCKS_PER_SEC](chrono/asc_std_ctime/clocks_per_sec.md) | asc/std/ctime | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::clock](chrono/asc_std_ctime/clock.md) | asc/std/ctime | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::clock_t](chrono/asc_std_ctime/clock_t.md) | asc/std/ctime | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::difftime](chrono/asc_std_ctime/difftime.md) | asc/std/ctime | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::time_t](chrono/asc_std_ctime/time_t.md) | asc/std/ctime | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::timespec](chrono/asc_std_ctime/timespec.md) | asc/std/ctime | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::c16rtomb](text_processing/asc_std_cuchar/c16rtomb.md) | asc/std/cuchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::c32rtomb](text_processing/asc_std_cuchar/c32rtomb.md) | asc/std/cuchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::c8rtomb](text_processing/asc_std_cuchar/c8rtomb.md) | asc/std/cuchar | 函数 | C++20+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbrtoc16](text_processing/asc_std_cuchar/mbrtoc16.md) | asc/std/cuchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbrtoc32](text_processing/asc_std_cuchar/mbrtoc32.md) | asc/std/cuchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbrtoc8](text_processing/asc_std_cuchar/mbrtoc8.md) | asc/std/cuchar | 函数 | C++20+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbstate_t](text_processing/asc_std_cuchar/mbstate_t.md) | asc/std/cuchar | 类型别名 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [NULL](text_processing/asc_std_cwchar/null.md) | asc/std/cwchar | 宏 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [WCHAR_MAX](text_processing/asc_std_cwchar/wchar_max.md) | asc/std/cwchar | 宏 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [WCHAR_MIN](text_processing/asc_std_cwchar/wchar_min.md) | asc/std/cwchar | 宏 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [WEOF](text_processing/asc_std_cwchar/weof.md) | asc/std/cwchar | 宏 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::btowc](text_processing/asc_std_cwchar/btowc.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbrlen](text_processing/asc_std_cwchar/mbrlen.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbrtowc](text_processing/asc_std_cwchar/mbrtowc.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbsinit](text_processing/asc_std_cwchar/mbsinit.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::mbsrtowcs](text_processing/asc_std_cwchar/mbsrtowcs.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wcrtomb](text_processing/asc_std_cwchar/wcrtomb.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wcscat](text_processing/asc_std_cwchar/wcscat.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcschr](text_processing/asc_std_cwchar/wcschr.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcscmp](text_processing/asc_std_cwchar/wcscmp.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcscoll](text_processing/asc_std_cwchar/wcscoll.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wcscpy](text_processing/asc_std_cwchar/wcscpy.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcscspn](text_processing/asc_std_cwchar/wcscspn.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcslen](text_processing/asc_std_cwchar/wcslen.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcsncat](text_processing/asc_std_cwchar/wcsncat.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcsncmp](text_processing/asc_std_cwchar/wcsncmp.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcsncpy](text_processing/asc_std_cwchar/wcsncpy.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcspbrk](text_processing/asc_std_cwchar/wcspbrk.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcsrchr](text_processing/asc_std_cwchar/wcsrchr.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcsrtombs](text_processing/asc_std_cwchar/wcsrtombs.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wcsspn](text_processing/asc_std_cwchar/wcsspn.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcsstr](text_processing/asc_std_cwchar/wcsstr.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wcstok](text_processing/asc_std_cwchar/wcstok.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wcsxfrm](text_processing/asc_std_cwchar/wcsxfrm.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wctob](text_processing/asc_std_cwchar/wctob.md) | asc/std/cwchar | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wint_t](text_processing/asc_std_cwchar/wint_t.md) | asc/std/cwchar | 类型别名 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wmemchr](text_processing/asc_std_cwchar/wmemchr.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wmemcmp](text_processing/asc_std_cwchar/wmemcmp.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wmemcpy](text_processing/asc_std_cwchar/wmemcpy.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wmemmove](text_processing/asc_std_cwchar/wmemmove.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wmemset](text_processing/asc_std_cwchar/wmemset.md) | asc/std/cwchar | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iswalnum](text_processing/asc_std_cwctype/iswalnum.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswalpha](text_processing/asc_std_cwctype/iswalpha.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswblank](text_processing/asc_std_cwctype/iswblank.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswcntrl](text_processing/asc_std_cwctype/iswcntrl.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswctype](text_processing/asc_std_cwctype/iswctype.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswdigit](text_processing/asc_std_cwctype/iswdigit.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswgraph](text_processing/asc_std_cwctype/iswgraph.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswlower](text_processing/asc_std_cwctype/iswlower.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswprint](text_processing/asc_std_cwctype/iswprint.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswpunct](text_processing/asc_std_cwctype/iswpunct.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswspace](text_processing/asc_std_cwctype/iswspace.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswupper](text_processing/asc_std_cwctype/iswupper.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::iswxdigit](text_processing/asc_std_cwctype/iswxdigit.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::towctrans](text_processing/asc_std_cwctype/towctrans.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::towlower](text_processing/asc_std_cwctype/towlower.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::towupper](text_processing/asc_std_cwctype/towupper.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wctrans](text_processing/asc_std_cwctype/wctrans.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wctrans_t](text_processing/asc_std_cwctype/wctrans_t.md) | asc/std/cwctype | 类型别名 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wctype](text_processing/asc_std_cwctype/wctype.md) | asc/std/cwctype | 函数 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::wctype_t](text_processing/asc_std_cwctype/wctype_t.md) | asc/std/cwctype | 类型别名 | C++17+ | Host（完整接口）、Device（C locale 相关接口） | Ascend 950 |
| [asc::std::deque](containers/asc_std_deque/deque.md) | asc/std/deque | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::allocator_type](containers/asc_std_deque/deque_allocator_type.md) | asc/std/deque | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::back](containers/asc_std_deque/deque_back.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::begin](containers/asc_std_deque/deque_begin.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::clear](containers/asc_std_deque/deque_clear.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::const_reference](containers/asc_std_deque/deque_const_reference.md) | asc/std/deque | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::deque](containers/asc_std_deque/deque_deque.md) | asc/std/deque | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::difference_type](containers/asc_std_deque/deque_difference_type.md) | asc/std/deque | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::emplace_back](containers/asc_std_deque/deque_emplace_back.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::emplace_front](containers/asc_std_deque/deque_emplace_front.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::empty](containers/asc_std_deque/deque_empty.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::end](containers/asc_std_deque/deque_end.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::front](containers/asc_std_deque/deque_front.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::iterator](containers/asc_std_deque/deque_iterator.md) | asc/std/deque | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::operator\[\]](containers/asc_std_deque/deque_operator_subscript.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::pop_back](containers/asc_std_deque/deque_pop_back.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::pop_front](containers/asc_std_deque/deque_pop_front.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::push_back](containers/asc_std_deque/deque_push_back.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::push_front](containers/asc_std_deque/deque_push_front.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::reference](containers/asc_std_deque/deque_reference.md) | asc/std/deque | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::size](containers/asc_std_deque/deque_size.md) | asc/std/deque | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::size_type](containers/asc_std_deque/deque_size_type.md) | asc/std/deque | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::value_type](containers/asc_std_deque/deque_value_type.md) | asc/std/deque | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deque::~deque](containers/asc_std_deque/deque_destructor_deque.md) | asc/std/deque | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::terminate](language_support/asc_std_exception/terminate.md) | asc/std/exception | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::execution::par](algorithms/asc_std_execution/execution_par.md) | asc/std/execution | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::execution::par_unseq](algorithms/asc_std_execution/execution_par_unseq.md) | asc/std/execution | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::execution::parallel_policy](algorithms/asc_std_execution/execution_parallel_policy.md) | asc/std/execution | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::execution::parallel_unsequenced_policy](algorithms/asc_std_execution/execution_parallel_unsequenced_policy.md) | asc/std/execution | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::execution::seq](algorithms/asc_std_execution/execution_seq.md) | asc/std/execution | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::execution::sequenced_policy](algorithms/asc_std_execution/execution_sequenced_policy.md) | asc/std/execution | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::execution::unseq](algorithms/asc_std_execution/execution_unseq.md) | asc/std/execution | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::execution::unsequenced_policy](algorithms/asc_std_execution/execution_unsequenced_policy.md) | asc/std/execution | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_execution_policy](algorithms/asc_std_execution/is_execution_policy.md) | asc/std/execution | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_execution_policy_v](algorithms/asc_std_execution/is_execution_policy_v.md) | asc/std/execution | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected](utilities/asc_std_expected/expected.md) | asc/std/expected | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::and_then](utilities/asc_std_expected/expected_and_then.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::error](utilities/asc_std_expected/expected_error.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::error_or](utilities/asc_std_expected/expected_error_or.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::error_type](utilities/asc_std_expected/expected_error_type.md) | asc/std/expected | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::expected](utilities/asc_std_expected/expected_expected.md) | asc/std/expected | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::has_value](utilities/asc_std_expected/expected_has_value.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::operator bool](utilities/asc_std_expected/expected_operator_bool.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::operator*](utilities/asc_std_expected/expected_operator_dereference.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::operator->](utilities/asc_std_expected/expected_operator_arrow.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::or_else](utilities/asc_std_expected/expected_or_else.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::transform](utilities/asc_std_expected/expected_transform.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::transform_error](utilities/asc_std_expected/expected_transform_error.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::value_or](utilities/asc_std_expected/expected_value_or.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::value_type](utilities/asc_std_expected/expected_value_type.md) | asc/std/expected | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::expected::~expected](utilities/asc_std_expected/expected_destructor_expected.md) | asc/std/expected | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unexpect](utilities/asc_std_expected/unexpect.md) | asc/std/expected | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unexpect_t](utilities/asc_std_expected/unexpect_t.md) | asc/std/expected | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unexpect_t::unexpect_t](utilities/asc_std_expected/unexpect_t_unexpect_t.md) | asc/std/expected | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unexpected](utilities/asc_std_expected/unexpected.md) | asc/std/expected | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unexpected::error](utilities/asc_std_expected/unexpected_error.md) | asc/std/expected | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unexpected::unexpected](utilities/asc_std_expected/unexpected_unexpected.md) | asc/std/expected | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_format_string](text_processing/asc_std_format/basic_format_string.md) | asc/std/format | 类模板 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::format_string](text_processing/asc_std_format/format_string.md) | asc/std/format | 别名模板 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::format_to](text_processing/asc_std_format/format_to.md) | asc/std/format | 函数模板 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::format_to_n](text_processing/asc_std_format/format_to_n.md) | asc/std/format | 函数模板 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::format_to_n_result](text_processing/asc_std_format/format_to_n_result.md) | asc/std/format | 类模板 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::formatted_size](text_processing/asc_std_format/formatted_size.md) | asc/std/format | 函数模板 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list](containers/asc_std_forward_list/forward_list.md) | asc/std/forward_list | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::allocator_type](containers/asc_std_forward_list/forward_list_allocator_type.md) | asc/std/forward_list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::begin](containers/asc_std_forward_list/forward_list_begin.md) | asc/std/forward_list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::clear](containers/asc_std_forward_list/forward_list_clear.md) | asc/std/forward_list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::const_reference](containers/asc_std_forward_list/forward_list_const_reference.md) | asc/std/forward_list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::emplace_front](containers/asc_std_forward_list/forward_list_emplace_front.md) | asc/std/forward_list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::empty](containers/asc_std_forward_list/forward_list_empty.md) | asc/std/forward_list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::end](containers/asc_std_forward_list/forward_list_end.md) | asc/std/forward_list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::forward_list](containers/asc_std_forward_list/forward_list_forward_list.md) | asc/std/forward_list | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::front](containers/asc_std_forward_list/forward_list_front.md) | asc/std/forward_list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::iterator](containers/asc_std_forward_list/forward_list_iterator.md) | asc/std/forward_list | 类 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::operator=](containers/asc_std_forward_list/forward_list_operator_assign.md) | asc/std/forward_list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::pop_front](containers/asc_std_forward_list/forward_list_pop_front.md) | asc/std/forward_list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::push_front](containers/asc_std_forward_list/forward_list_push_front.md) | asc/std/forward_list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::reference](containers/asc_std_forward_list/forward_list_reference.md) | asc/std/forward_list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::size_type](containers/asc_std_forward_list/forward_list_size_type.md) | asc/std/forward_list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::value_type](containers/asc_std_forward_list/forward_list_value_type.md) | asc/std/forward_list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_list::~forward_list](containers/asc_std_forward_list/forward_list_destructor_forward_list.md) | asc/std/forward_list | 析构函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bind](utilities/asc_std_functional/bind.md) | asc/std/functional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bind_front](utilities/asc_std_functional/bind_front.md) | asc/std/functional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_and](utilities/asc_std_functional/bit_and.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_and::is_transparent](utilities/asc_std_functional/bit_and_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_and::operator()](utilities/asc_std_functional/bit_and_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_not](utilities/asc_std_functional/bit_not.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_not::is_transparent](utilities/asc_std_functional/bit_not_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_not::operator()](utilities/asc_std_functional/bit_not_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_or](utilities/asc_std_functional/bit_or.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_or::is_transparent](utilities/asc_std_functional/bit_or_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_or::operator()](utilities/asc_std_functional/bit_or_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_xor](utilities/asc_std_functional/bit_xor.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_xor::is_transparent](utilities/asc_std_functional/bit_xor_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bit_xor::operator()](utilities/asc_std_functional/bit_xor_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cref](utilities/asc_std_functional/cref.md) | asc/std/functional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_searcher](utilities/asc_std_functional/default_searcher.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_searcher::default_searcher](utilities/asc_std_functional/default_searcher_default_searcher.md) | asc/std/functional | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_searcher::operator()](utilities/asc_std_functional/default_searcher_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::divides](utilities/asc_std_functional/divides.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::divides::is_transparent](utilities/asc_std_functional/divides_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::divides::operator()](utilities/asc_std_functional/divides_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::equal_to](utilities/asc_std_functional/equal_to.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::equal_to::is_transparent](utilities/asc_std_functional/equal_to_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::equal_to::operator()](utilities/asc_std_functional/equal_to_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::greater](utilities/asc_std_functional/greater.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::greater::is_transparent](utilities/asc_std_functional/greater_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::greater::operator()](utilities/asc_std_functional/greater_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::greater_equal](utilities/asc_std_functional/greater_equal.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::greater_equal::is_transparent](utilities/asc_std_functional/greater_equal_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::greater_equal::operator()](utilities/asc_std_functional/greater_equal_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::identity](utilities/asc_std_functional/identity.md) | asc/std/functional | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::identity::is_transparent](utilities/asc_std_functional/identity_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::identity::operator()](utilities/asc_std_functional/identity_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::invoke](utilities/asc_std_functional/invoke.md) | asc/std/functional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::invoke_r](utilities/asc_std_functional/invoke_r.md) | asc/std/functional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_bind_expression](utilities/asc_std_functional/is_bind_expression.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_bind_expression_v](utilities/asc_std_functional/is_bind_expression_v.md) | asc/std/functional | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_placeholder](utilities/asc_std_functional/is_placeholder.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_placeholder_v](utilities/asc_std_functional/is_placeholder_v.md) | asc/std/functional | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::less](utilities/asc_std_functional/less.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::less::is_transparent](utilities/asc_std_functional/less_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::less::operator()](utilities/asc_std_functional/less_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::less_equal](utilities/asc_std_functional/less_equal.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::less_equal::is_transparent](utilities/asc_std_functional/less_equal_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::less_equal::operator()](utilities/asc_std_functional/less_equal_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logical_and](utilities/asc_std_functional/logical_and.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logical_and::is_transparent](utilities/asc_std_functional/logical_and_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logical_and::operator()](utilities/asc_std_functional/logical_and_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logical_not](utilities/asc_std_functional/logical_not.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logical_not::is_transparent](utilities/asc_std_functional/logical_not_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logical_not::operator()](utilities/asc_std_functional/logical_not_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logical_or](utilities/asc_std_functional/logical_or.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logical_or::is_transparent](utilities/asc_std_functional/logical_or_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::logical_or::operator()](utilities/asc_std_functional/logical_or_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mem_fn](utilities/asc_std_functional/mem_fn.md) | asc/std/functional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::minus](utilities/asc_std_functional/minus.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::minus::is_transparent](utilities/asc_std_functional/minus_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::minus::operator()](utilities/asc_std_functional/minus_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::modulus](utilities/asc_std_functional/modulus.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::modulus::is_transparent](utilities/asc_std_functional/modulus_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::modulus::operator()](utilities/asc_std_functional/modulus_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::multiplies](utilities/asc_std_functional/multiplies.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::multiplies::is_transparent](utilities/asc_std_functional/multiplies_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::multiplies::operator()](utilities/asc_std_functional/multiplies_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::negate](utilities/asc_std_functional/negate.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::negate::is_transparent](utilities/asc_std_functional/negate_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::negate::operator()](utilities/asc_std_functional/negate_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::not_equal_to](utilities/asc_std_functional/not_equal_to.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::not_equal_to::is_transparent](utilities/asc_std_functional/not_equal_to_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::not_equal_to::operator()](utilities/asc_std_functional/not_equal_to_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::not_fn](utilities/asc_std_functional/not_fn.md) | asc/std/functional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_1](utilities/asc_std_functional/placeholders_1.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_10](utilities/asc_std_functional/placeholders_10.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_2](utilities/asc_std_functional/placeholders_2.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_3](utilities/asc_std_functional/placeholders_3.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_4](utilities/asc_std_functional/placeholders_4.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_5](utilities/asc_std_functional/placeholders_5.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_6](utilities/asc_std_functional/placeholders_6.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_7](utilities/asc_std_functional/placeholders_7.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_8](utilities/asc_std_functional/placeholders_8.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::placeholders::_9](utilities/asc_std_functional/placeholders_9.md) | asc/std/functional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::plus](utilities/asc_std_functional/plus.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::plus::is_transparent](utilities/asc_std_functional/plus_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::plus::operator()](utilities/asc_std_functional/plus_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::equal_to](utilities/asc_std_functional/ranges_equal_to.md) | asc/std/functional | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::equal_to::is_transparent](utilities/asc_std_functional/ranges_equal_to_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::equal_to::operator()](utilities/asc_std_functional/ranges_equal_to_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::greater](utilities/asc_std_functional/ranges_greater.md) | asc/std/functional | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::greater::is_transparent](utilities/asc_std_functional/ranges_greater_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::greater::operator()](utilities/asc_std_functional/ranges_greater_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::greater_equal](utilities/asc_std_functional/ranges_greater_equal.md) | asc/std/functional | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::greater_equal::is_transparent](utilities/asc_std_functional/ranges_greater_equal_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::greater_equal::operator()](utilities/asc_std_functional/ranges_greater_equal_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::less](utilities/asc_std_functional/ranges_less.md) | asc/std/functional | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::less::is_transparent](utilities/asc_std_functional/ranges_less_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::less::operator()](utilities/asc_std_functional/ranges_less_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::less_equal](utilities/asc_std_functional/ranges_less_equal.md) | asc/std/functional | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::less_equal::is_transparent](utilities/asc_std_functional/ranges_less_equal_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::less_equal::operator()](utilities/asc_std_functional/ranges_less_equal_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::not_equal_to](utilities/asc_std_functional/ranges_not_equal_to.md) | asc/std/functional | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::not_equal_to::is_transparent](utilities/asc_std_functional/ranges_not_equal_to_is_transparent.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::not_equal_to::operator()](utilities/asc_std_functional/ranges_not_equal_to_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ref](utilities/asc_std_functional/ref.md) | asc/std/functional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reference_wrapper](utilities/asc_std_functional/reference_wrapper.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reference_wrapper::get](utilities/asc_std_functional/reference_wrapper_get.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reference_wrapper::operator()](utilities/asc_std_functional/reference_wrapper_operator_call.md) | asc/std/functional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reference_wrapper::reference_wrapper](utilities/asc_std_functional/reference_wrapper_reference_wrapper.md) | asc/std/functional | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reference_wrapper::type](utilities/asc_std_functional/reference_wrapper_type.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unwrap_ref_decay](utilities/asc_std_functional/unwrap_ref_decay.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unwrap_ref_decay_t](utilities/asc_std_functional/unwrap_ref_decay_t.md) | asc/std/functional | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unwrap_reference](utilities/asc_std_functional/unwrap_reference.md) | asc/std/functional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unwrap_reference::type](utilities/asc_std_functional/unwrap_reference_type.md) | asc/std/functional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unwrap_reference_t](utilities/asc_std_functional/unwrap_reference_t.md) | asc/std/functional | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::erase](containers/asc_std_inplace_vector/erase.md) | asc/std/inplace_vector | 函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::erase_if](containers/asc_std_inplace_vector/erase_if.md) | asc/std/inplace_vector | 函数模板 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector](containers/asc_std_inplace_vector/inplace_vector.md) | asc/std/inplace_vector | 类模板 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::back](containers/asc_std_inplace_vector/inplace_vector_back.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::begin](containers/asc_std_inplace_vector/inplace_vector_begin.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::capacity](containers/asc_std_inplace_vector/inplace_vector_capacity.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::cbegin](containers/asc_std_inplace_vector/inplace_vector_cbegin.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::cend](containers/asc_std_inplace_vector/inplace_vector_cend.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::clear](containers/asc_std_inplace_vector/inplace_vector_clear.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::const_iterator](containers/asc_std_inplace_vector/inplace_vector_const_iterator.md) | asc/std/inplace_vector | 类型别名 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::const_pointer](containers/asc_std_inplace_vector/inplace_vector_const_pointer.md) | asc/std/inplace_vector | 类型别名 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::const_reference](containers/asc_std_inplace_vector/inplace_vector_const_reference.md) | asc/std/inplace_vector | 类型别名 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::data](containers/asc_std_inplace_vector/inplace_vector_data.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::difference_type](containers/asc_std_inplace_vector/inplace_vector_difference_type.md) | asc/std/inplace_vector | 类型别名 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::empty](containers/asc_std_inplace_vector/inplace_vector_empty.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::end](containers/asc_std_inplace_vector/inplace_vector_end.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::erase](containers/asc_std_inplace_vector/inplace_vector_erase.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::erase_if](containers/asc_std_inplace_vector/inplace_vector_erase_if.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::front](containers/asc_std_inplace_vector/inplace_vector_front.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::inplace_vector](containers/asc_std_inplace_vector/inplace_vector_inplace_vector.md) | asc/std/inplace_vector | 构造函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::iterator](containers/asc_std_inplace_vector/inplace_vector_iterator.md) | asc/std/inplace_vector | 类型别名 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::max_size](containers/asc_std_inplace_vector/inplace_vector_max_size.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::operator=](containers/asc_std_inplace_vector/inplace_vector_operator_assign.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::operator\[\]](containers/asc_std_inplace_vector/inplace_vector_operator_subscript.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::pointer](containers/asc_std_inplace_vector/inplace_vector_pointer.md) | asc/std/inplace_vector | 类型别名 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::pop_back](containers/asc_std_inplace_vector/inplace_vector_pop_back.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::reference](containers/asc_std_inplace_vector/inplace_vector_reference.md) | asc/std/inplace_vector | 类型别名 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::size](containers/asc_std_inplace_vector/inplace_vector_size.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::size_type](containers/asc_std_inplace_vector/inplace_vector_size_type.md) | asc/std/inplace_vector | 类型别名 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::swap](containers/asc_std_inplace_vector/inplace_vector_swap.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::try_emplace_back](containers/asc_std_inplace_vector/inplace_vector_try_emplace_back.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::try_push_back](containers/asc_std_inplace_vector/inplace_vector_try_push_back.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::unchecked_emplace_back](containers/asc_std_inplace_vector/inplace_vector_unchecked_emplace_back.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::unchecked_push_back](containers/asc_std_inplace_vector/inplace_vector_unchecked_push_back.md) | asc/std/inplace_vector | 成员函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::value_type](containers/asc_std_inplace_vector/inplace_vector_value_type.md) | asc/std/inplace_vector | 类型别名 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::inplace_vector::~inplace_vector](containers/asc_std_inplace_vector/inplace_vector_destructor_inplace_vector.md) | asc/std/inplace_vector | 析构函数 | C++17+ | Host（完整接口）、Device（非抛出子集） | Ascend 950 |
| [asc::std::advance](iterators/asc_std_iterator/advance.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator](iterators/asc_std_iterator/back_insert_iterator.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::back_insert_iterator](iterators/asc_std_iterator/back_insert_iterator_back_insert_iterator.md) | asc/std/iterator | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::container_type](iterators/asc_std_iterator/back_insert_iterator_container_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::difference_type](iterators/asc_std_iterator/back_insert_iterator_difference_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::iterator_category](iterators/asc_std_iterator/back_insert_iterator_iterator_category.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::operator*](iterators/asc_std_iterator/back_insert_iterator_operator_dereference.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::operator++](iterators/asc_std_iterator/back_insert_iterator_operator_increment.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::operator=](iterators/asc_std_iterator/back_insert_iterator_operator_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::pointer](iterators/asc_std_iterator/back_insert_iterator_pointer.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::reference](iterators/asc_std_iterator/back_insert_iterator_reference.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_insert_iterator::value_type](iterators/asc_std_iterator/back_insert_iterator_value_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::back_inserter](iterators/asc_std_iterator/back_inserter.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::begin](iterators/asc_std_iterator/begin.md) | asc/std/iterator | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bidirectional_iterator](iterators/asc_std_iterator/bidirectional_iterator.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bidirectional_iterator_tag](iterators/asc_std_iterator/bidirectional_iterator_tag.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cbegin](iterators/asc_std_iterator/cbegin.md) | asc/std/iterator | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cend](iterators/asc_std_iterator/cend.md) | asc/std/iterator | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_iterator](iterators/asc_std_iterator/common_iterator.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_iterator::common_iterator](iterators/asc_std_iterator/common_iterator_common_iterator.md) | asc/std/iterator | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_iterator::operator*](iterators/asc_std_iterator/common_iterator_operator_dereference.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_iterator::operator++](iterators/asc_std_iterator/common_iterator_operator_increment.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_iterator::operator->](iterators/asc_std_iterator/common_iterator_operator_arrow.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_iterator::operator=](iterators/asc_std_iterator/common_iterator_operator_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::contiguous_iterator](iterators/asc_std_iterator/contiguous_iterator.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::contiguous_iterator_tag](iterators/asc_std_iterator/contiguous_iterator_tag.md) | asc/std/iterator | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator](iterators/asc_std_iterator/counted_iterator.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::base](iterators/asc_std_iterator/counted_iterator_base.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::count](iterators/asc_std_iterator/counted_iterator_count.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::counted_iterator](iterators/asc_std_iterator/counted_iterator_counted_iterator.md) | asc/std/iterator | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::difference_type](iterators/asc_std_iterator/counted_iterator_difference_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::iterator_type](iterators/asc_std_iterator/counted_iterator_iterator_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator*](iterators/asc_std_iterator/counted_iterator_operator_dereference.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator+](iterators/asc_std_iterator/counted_iterator_operator_plus.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator++](iterators/asc_std_iterator/counted_iterator_operator_increment.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator+=](iterators/asc_std_iterator/counted_iterator_operator_plus_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator-](iterators/asc_std_iterator/counted_iterator_operator_minus.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator--](iterators/asc_std_iterator/counted_iterator_operator_decrement.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator-=](iterators/asc_std_iterator/counted_iterator_operator_minus_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator->](iterators/asc_std_iterator/counted_iterator_operator_arrow.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator=](iterators/asc_std_iterator/counted_iterator_operator_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counted_iterator::operator\[\]](iterators/asc_std_iterator/counted_iterator_operator_subscript.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::crbegin](iterators/asc_std_iterator/crbegin.md) | asc/std/iterator | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::crend](iterators/asc_std_iterator/crend.md) | asc/std/iterator | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::data](iterators/asc_std_iterator/data.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_sentinel](iterators/asc_std_iterator/default_sentinel.md) | asc/std/iterator | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_sentinel_t](iterators/asc_std_iterator/default_sentinel_t.md) | asc/std/iterator | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::disable_sized_sentinel_for](iterators/asc_std_iterator/disable_sized_sentinel_for.md) | asc/std/iterator | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::distance](iterators/asc_std_iterator/distance.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::empty](iterators/asc_std_iterator/empty.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::end](iterators/asc_std_iterator/end.md) | asc/std/iterator | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_iterator](iterators/asc_std_iterator/forward_iterator.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_iterator_tag](iterators/asc_std_iterator/forward_iterator_tag.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator](iterators/asc_std_iterator/front_insert_iterator.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::container_type](iterators/asc_std_iterator/front_insert_iterator_container_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::difference_type](iterators/asc_std_iterator/front_insert_iterator_difference_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::front_insert_iterator](iterators/asc_std_iterator/front_insert_iterator_front_insert_iterator.md) | asc/std/iterator | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::iterator_category](iterators/asc_std_iterator/front_insert_iterator_iterator_category.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::operator*](iterators/asc_std_iterator/front_insert_iterator_operator_dereference.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::operator++](iterators/asc_std_iterator/front_insert_iterator_operator_increment.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::operator=](iterators/asc_std_iterator/front_insert_iterator_operator_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::pointer](iterators/asc_std_iterator/front_insert_iterator_pointer.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::reference](iterators/asc_std_iterator/front_insert_iterator_reference.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_insert_iterator::value_type](iterators/asc_std_iterator/front_insert_iterator_value_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::front_inserter](iterators/asc_std_iterator/front_inserter.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::incrementable](iterators/asc_std_iterator/incrementable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::incrementable_traits](iterators/asc_std_iterator/incrementable_traits.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::incrementable_traits::difference_type](iterators/asc_std_iterator/incrementable_traits_difference_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirect_binary_predicate](iterators/asc_std_iterator/indirect_binary_predicate.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirect_equivalence_relation](iterators/asc_std_iterator/indirect_equivalence_relation.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirect_result_t](iterators/asc_std_iterator/indirect_result_t.md) | asc/std/iterator | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirect_strict_weak_order](iterators/asc_std_iterator/indirect_strict_weak_order.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirect_unary_predicate](iterators/asc_std_iterator/indirect_unary_predicate.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_comparable](iterators/asc_std_iterator/indirectly_comparable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_copyable](iterators/asc_std_iterator/indirectly_copyable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_copyable_storable](iterators/asc_std_iterator/indirectly_copyable_storable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_movable](iterators/asc_std_iterator/indirectly_movable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_movable_storable](iterators/asc_std_iterator/indirectly_movable_storable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_readable](iterators/asc_std_iterator/indirectly_readable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_readable_traits](iterators/asc_std_iterator/indirectly_readable_traits.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_readable_traits::value_type](iterators/asc_std_iterator/indirectly_readable_traits_value_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_regular_unary_invocable](iterators/asc_std_iterator/indirectly_regular_unary_invocable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_swappable](iterators/asc_std_iterator/indirectly_swappable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_unary_invocable](iterators/asc_std_iterator/indirectly_unary_invocable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::indirectly_writable](iterators/asc_std_iterator/indirectly_writable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::input_iterator](iterators/asc_std_iterator/input_iterator.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::input_iterator_tag](iterators/asc_std_iterator/input_iterator_tag.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::input_or_output_iterator](iterators/asc_std_iterator/input_or_output_iterator.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator](iterators/asc_std_iterator/insert_iterator.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::container_type](iterators/asc_std_iterator/insert_iterator_container_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::difference_type](iterators/asc_std_iterator/insert_iterator_difference_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::insert_iterator](iterators/asc_std_iterator/insert_iterator_insert_iterator.md) | asc/std/iterator | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::iterator_category](iterators/asc_std_iterator/insert_iterator_iterator_category.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::operator*](iterators/asc_std_iterator/insert_iterator_operator_dereference.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::operator++](iterators/asc_std_iterator/insert_iterator_operator_increment.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::operator=](iterators/asc_std_iterator/insert_iterator_operator_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::pointer](iterators/asc_std_iterator/insert_iterator_pointer.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::reference](iterators/asc_std_iterator/insert_iterator_reference.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::insert_iterator::value_type](iterators/asc_std_iterator/insert_iterator_value_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::inserter](iterators/asc_std_iterator/inserter.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iter_common_reference_t](iterators/asc_std_iterator/iter_common_reference_t.md) | asc/std/iterator | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iter_difference_t](iterators/asc_std_iterator/iter_difference_t.md) | asc/std/iterator | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iter_move](iterators/asc_std_iterator/iter_move.md) | asc/std/iterator | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iter_reference_t](iterators/asc_std_iterator/iter_reference_t.md) | asc/std/iterator | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iter_rvalue_reference_t](iterators/asc_std_iterator/iter_rvalue_reference_t.md) | asc/std/iterator | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iter_value_t](iterators/asc_std_iterator/iter_value_t.md) | asc/std/iterator | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator](iterators/asc_std_iterator/iterator.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator::difference_type](iterators/asc_std_iterator/iterator_difference_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator::iterator_category](iterators/asc_std_iterator/iterator_iterator_category.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator::pointer](iterators/asc_std_iterator/iterator_pointer.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator::reference](iterators/asc_std_iterator/iterator_reference.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator::value_type](iterators/asc_std_iterator/iterator_value_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator_traits](iterators/asc_std_iterator/iterator_traits.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator_traits::difference_type](iterators/asc_std_iterator/iterator_traits_difference_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator_traits::iterator_category](iterators/asc_std_iterator/iterator_traits_iterator_category.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator_traits::iterator_concept](iterators/asc_std_iterator/iterator_traits_iterator_concept.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator_traits::pointer](iterators/asc_std_iterator/iterator_traits_pointer.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator_traits::reference](iterators/asc_std_iterator/iterator_traits_reference.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iterator_traits::value_type](iterators/asc_std_iterator/iterator_traits_value_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_move_iterator](iterators/asc_std_iterator/make_move_iterator.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_reverse_iterator](iterators/asc_std_iterator/make_reverse_iterator.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mergeable](iterators/asc_std_iterator/mergeable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator](iterators/asc_std_iterator/move_iterator.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::base](iterators/asc_std_iterator/move_iterator_base.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::difference_type](iterators/asc_std_iterator/move_iterator_difference_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::iterator_concept](iterators/asc_std_iterator/move_iterator_iterator_concept.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::iterator_type](iterators/asc_std_iterator/move_iterator_iterator_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::move_iterator](iterators/asc_std_iterator/move_iterator_move_iterator.md) | asc/std/iterator | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator*](iterators/asc_std_iterator/move_iterator_operator_dereference.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator+](iterators/asc_std_iterator/move_iterator_operator_plus.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator++](iterators/asc_std_iterator/move_iterator_operator_increment.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator+=](iterators/asc_std_iterator/move_iterator_operator_plus_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator-](iterators/asc_std_iterator/move_iterator_operator_minus.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator--](iterators/asc_std_iterator/move_iterator_operator_decrement.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator-=](iterators/asc_std_iterator/move_iterator_operator_minus_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator->](iterators/asc_std_iterator/move_iterator_operator_arrow.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator=](iterators/asc_std_iterator/move_iterator_operator_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::operator\[\]](iterators/asc_std_iterator/move_iterator_operator_subscript.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::pointer](iterators/asc_std_iterator/move_iterator_pointer.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::reference](iterators/asc_std_iterator/move_iterator_reference.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_iterator::value_type](iterators/asc_std_iterator/move_iterator_value_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_sentinel](iterators/asc_std_iterator/move_sentinel.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_sentinel::base](iterators/asc_std_iterator/move_sentinel_base.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_sentinel::move_sentinel](iterators/asc_std_iterator/move_sentinel_move_sentinel.md) | asc/std/iterator | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_sentinel::operator=](iterators/asc_std_iterator/move_sentinel_operator_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::next](iterators/asc_std_iterator/next.md) | asc/std/iterator | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::output_iterator](iterators/asc_std_iterator/output_iterator.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::output_iterator_tag](iterators/asc_std_iterator/output_iterator_tag.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::permutable](iterators/asc_std_iterator/permutable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::prev](iterators/asc_std_iterator/prev.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::projected](iterators/asc_std_iterator/projected.md) | asc/std/iterator | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::random_access_iterator](iterators/asc_std_iterator/random_access_iterator.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::random_access_iterator_tag](iterators/asc_std_iterator/random_access_iterator_tag.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rbegin](iterators/asc_std_iterator/rbegin.md) | asc/std/iterator | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rend](iterators/asc_std_iterator/rend.md) | asc/std/iterator | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator](iterators/asc_std_iterator/reverse_iterator.md) | asc/std/iterator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::base](iterators/asc_std_iterator/reverse_iterator_base.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::difference_type](iterators/asc_std_iterator/reverse_iterator_difference_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::iterator_category](iterators/asc_std_iterator/reverse_iterator_iterator_category.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::iterator_concept](iterators/asc_std_iterator/reverse_iterator_iterator_concept.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::iterator_type](iterators/asc_std_iterator/reverse_iterator_iterator_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator*](iterators/asc_std_iterator/reverse_iterator_operator_dereference.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator+](iterators/asc_std_iterator/reverse_iterator_operator_plus.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator++](iterators/asc_std_iterator/reverse_iterator_operator_increment.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator+=](iterators/asc_std_iterator/reverse_iterator_operator_plus_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator-](iterators/asc_std_iterator/reverse_iterator_operator_minus.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator--](iterators/asc_std_iterator/reverse_iterator_operator_decrement.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator-=](iterators/asc_std_iterator/reverse_iterator_operator_minus_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator->](iterators/asc_std_iterator/reverse_iterator_operator_arrow.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator=](iterators/asc_std_iterator/reverse_iterator_operator_assign.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::operator\[\]](iterators/asc_std_iterator/reverse_iterator_operator_subscript.md) | asc/std/iterator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::pointer](iterators/asc_std_iterator/reverse_iterator_pointer.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::reference](iterators/asc_std_iterator/reverse_iterator_reference.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::reverse_iterator](iterators/asc_std_iterator/reverse_iterator_reverse_iterator.md) | asc/std/iterator | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reverse_iterator::value_type](iterators/asc_std_iterator/reverse_iterator_value_type.md) | asc/std/iterator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sentinel_for](iterators/asc_std_iterator/sentinel_for.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::size](iterators/asc_std_iterator/size.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sized_sentinel_for](iterators/asc_std_iterator/sized_sentinel_for.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sortable](iterators/asc_std_iterator/sortable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ssize](iterators/asc_std_iterator/ssize.md) | asc/std/iterator | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unreachable_sentinel](iterators/asc_std_iterator/unreachable_sentinel.md) | asc/std/iterator | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unreachable_sentinel_t](iterators/asc_std_iterator/unreachable_sentinel_t.md) | asc/std/iterator | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::weakly_incrementable](iterators/asc_std_iterator/weakly_incrementable.md) | asc/std/iterator | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch](concurrency/asc_std_latch/latch.md) | asc/std/latch | 类 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::arrive_and_wait](concurrency/asc_std_latch/latch_arrive_and_wait.md) | asc/std/latch | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::count_down](concurrency/asc_std_latch/latch_count_down.md) | asc/std/latch | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::latch](concurrency/asc_std_latch/latch_latch.md) | asc/std/latch | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::max](concurrency/asc_std_latch/latch_max.md) | asc/std/latch | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::try_wait](concurrency/asc_std_latch/latch_try_wait.md) | asc/std/latch | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::latch::wait](concurrency/asc_std_latch/latch_wait.md) | asc/std/latch | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::float_denorm_style](language_support/asc_std_limits/float_denorm_style.md) | asc/std/limits | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::float_round_style](language_support/asc_std_limits/float_round_style.md) | asc/std/limits | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numeric_limits](language_support/asc_std_limits/numeric_limits.md) | asc/std/limits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugate_transposed](numerics/asc_std_linalg/linalg_conjugate_transposed.md) | asc/std/linalg | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated](numerics/asc_std_linalg/linalg_conjugated.md) | asc/std/linalg | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor](numerics/asc_std_linalg/linalg_conjugated_accessor.md) | asc/std/linalg | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::access](numerics/asc_std_linalg/linalg_conjugated_accessor_access.md) | asc/std/linalg | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::conjugated_accessor](numerics/asc_std_linalg/linalg_conjugated_accessor_conjugated_accessor.md) | asc/std/linalg | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::data_handle_type](numerics/asc_std_linalg/linalg_conjugated_accessor_data_handle_type.md) | asc/std/linalg | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::element_type](numerics/asc_std_linalg/linalg_conjugated_accessor_element_type.md) | asc/std/linalg | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::nested_accessor](numerics/asc_std_linalg/linalg_conjugated_accessor_nested_accessor.md) | asc/std/linalg | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::offset](numerics/asc_std_linalg/linalg_conjugated_accessor_offset.md) | asc/std/linalg | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::offset_policy](numerics/asc_std_linalg/linalg_conjugated_accessor_offset_policy.md) | asc/std/linalg | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::reference](numerics/asc_std_linalg/linalg_conjugated_accessor_reference.md) | asc/std/linalg | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::layout_transpose](numerics/asc_std_linalg/linalg_layout_transpose.md) | asc/std/linalg | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::layout_transpose::mapping](numerics/asc_std_linalg/linalg_layout_transpose_mapping.md) | asc/std/linalg | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::layout_transpose::nested_layout_type](numerics/asc_std_linalg/linalg_layout_transpose_nested_layout_type.md) | asc/std/linalg | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled](numerics/asc_std_linalg/linalg_scaled.md) | asc/std/linalg | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor](numerics/asc_std_linalg/linalg_scaled_accessor.md) | asc/std/linalg | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::access](numerics/asc_std_linalg/linalg_scaled_accessor_access.md) | asc/std/linalg | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::data_handle_type](numerics/asc_std_linalg/linalg_scaled_accessor_data_handle_type.md) | asc/std/linalg | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::element_type](numerics/asc_std_linalg/linalg_scaled_accessor_element_type.md) | asc/std/linalg | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::nested_accessor](numerics/asc_std_linalg/linalg_scaled_accessor_nested_accessor.md) | asc/std/linalg | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::offset](numerics/asc_std_linalg/linalg_scaled_accessor_offset.md) | asc/std/linalg | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::offset_policy](numerics/asc_std_linalg/linalg_scaled_accessor_offset_policy.md) | asc/std/linalg | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::reference](numerics/asc_std_linalg/linalg_scaled_accessor_reference.md) | asc/std/linalg | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::scaled_accessor](numerics/asc_std_linalg/linalg_scaled_accessor_scaled_accessor.md) | asc/std/linalg | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::scaling_factor](numerics/asc_std_linalg/linalg_scaled_accessor_scaling_factor.md) | asc/std/linalg | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linalg::transposed](numerics/asc_std_linalg/linalg_transposed.md) | asc/std/linalg | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list](containers/asc_std_list/list.md) | asc/std/list | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::allocator_type](containers/asc_std_list/list_allocator_type.md) | asc/std/list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::back](containers/asc_std_list/list_back.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::begin](containers/asc_std_list/list_begin.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::clear](containers/asc_std_list/list_clear.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::const_reference](containers/asc_std_list/list_const_reference.md) | asc/std/list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::emplace_back](containers/asc_std_list/list_emplace_back.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::emplace_front](containers/asc_std_list/list_emplace_front.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::empty](containers/asc_std_list/list_empty.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::end](containers/asc_std_list/list_end.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::front](containers/asc_std_list/list_front.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::iterator](containers/asc_std_list/list_iterator.md) | asc/std/list | 类 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::list](containers/asc_std_list/list_list.md) | asc/std/list | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::operator=](containers/asc_std_list/list_operator_assign.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::pop_back](containers/asc_std_list/list_pop_back.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::pop_front](containers/asc_std_list/list_pop_front.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::push_back](containers/asc_std_list/list_push_back.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::push_front](containers/asc_std_list/list_push_front.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::reference](containers/asc_std_list/list_reference.md) | asc/std/list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::size](containers/asc_std_list/list_size.md) | asc/std/list | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::size_type](containers/asc_std_list/list_size_type.md) | asc/std/list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::value_type](containers/asc_std_list/list_value_type.md) | asc/std/list | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::list::~list](containers/asc_std_list/list_destructor_list.md) | asc/std/list | 析构函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map](containers/asc_std_map/map.md) | asc/std/map | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::begin](containers/asc_std_map/map_begin.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::clear](containers/asc_std_map/map_clear.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::count](containers/asc_std_map/map_count.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::empty](containers/asc_std_map/map_empty.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::end](containers/asc_std_map/map_end.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::find](containers/asc_std_map/map_find.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::insert](containers/asc_std_map/map_insert.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::iterator](containers/asc_std_map/map_iterator.md) | asc/std/map | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::map](containers/asc_std_map/map_map.md) | asc/std/map | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::operator=](containers/asc_std_map/map_operator_assign.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::operator\[\]](containers/asc_std_map/map_operator_subscript.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::size](containers/asc_std_map/map_size.md) | asc/std/map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::size_type](containers/asc_std_map/map_size_type.md) | asc/std/map | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::map::value_type](containers/asc_std_map/map_value_type.md) | asc/std/map | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_accessor](containers/asc_std_mdspan/aligned_accessor.md) | asc/std/mdspan | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_accessor::access](containers/asc_std_mdspan/aligned_accessor_access.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_accessor::aligned_accessor](containers/asc_std_mdspan/aligned_accessor_aligned_accessor.md) | asc/std/mdspan | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_accessor::byte_alignment](containers/asc_std_mdspan/aligned_accessor_byte_alignment.md) | asc/std/mdspan | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_accessor::data_handle_type](containers/asc_std_mdspan/aligned_accessor_data_handle_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_accessor::element_type](containers/asc_std_mdspan/aligned_accessor_element_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_accessor::offset](containers/asc_std_mdspan/aligned_accessor_offset.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_accessor::offset_policy](containers/asc_std_mdspan/aligned_accessor_offset_policy.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_accessor::reference](containers/asc_std_mdspan/aligned_accessor_reference.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_accessor](containers/asc_std_mdspan/default_accessor.md) | asc/std/mdspan | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_accessor::access](containers/asc_std_mdspan/default_accessor_access.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_accessor::data_handle_type](containers/asc_std_mdspan/default_accessor_data_handle_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_accessor::default_accessor](containers/asc_std_mdspan/default_accessor_default_accessor.md) | asc/std/mdspan | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_accessor::element_type](containers/asc_std_mdspan/default_accessor_element_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_accessor::offset](containers/asc_std_mdspan/default_accessor_offset.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_accessor::offset_policy](containers/asc_std_mdspan/default_accessor_offset_policy.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::default_accessor::reference](containers/asc_std_mdspan/default_accessor_reference.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::dextents](containers/asc_std_mdspan/dextents.md) | asc/std/mdspan | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::dims](containers/asc_std_mdspan/dims.md) | asc/std/mdspan | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::dynamic_extent](containers/asc_std_mdspan/dynamic_extent.md) | asc/std/mdspan | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extents](containers/asc_std_mdspan/extents.md) | asc/std/mdspan | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extents::extent](containers/asc_std_mdspan/extents_extent.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extents::extents](containers/asc_std_mdspan/extents_extents.md) | asc/std/mdspan | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extents::index_type](containers/asc_std_mdspan/extents_index_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extents::rank](containers/asc_std_mdspan/extents_rank.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extents::rank_dynamic](containers/asc_std_mdspan/extents_rank_dynamic.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extents::rank_type](containers/asc_std_mdspan/extents_rank_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extents::size_type](containers/asc_std_mdspan/extents_size_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extents::static_extent](containers/asc_std_mdspan/extents_static_extent.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::full_extent](containers/asc_std_mdspan/full_extent.md) | asc/std/mdspan | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::full_extent_t](containers/asc_std_mdspan/full_extent_t.md) | asc/std/mdspan | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::layout_left](containers/asc_std_mdspan/layout_left.md) | asc/std/mdspan | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::layout_left::mapping](containers/asc_std_mdspan/layout_left_mapping.md) | asc/std/mdspan | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::layout_right](containers/asc_std_mdspan/layout_right.md) | asc/std/mdspan | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::layout_right::mapping](containers/asc_std_mdspan/layout_right_mapping.md) | asc/std/mdspan | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::layout_stride](containers/asc_std_mdspan/layout_stride.md) | asc/std/mdspan | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::layout_stride::mapping](containers/asc_std_mdspan/layout_stride_mapping.md) | asc/std/mdspan | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan](containers/asc_std_mdspan/mdspan.md) | asc/std/mdspan | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::accessor](containers/asc_std_mdspan/mdspan_accessor.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::accessor_type](containers/asc_std_mdspan/mdspan_accessor_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::data_handle](containers/asc_std_mdspan/mdspan_data_handle.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::data_handle_type](containers/asc_std_mdspan/mdspan_data_handle_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::element_type](containers/asc_std_mdspan/mdspan_element_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::empty](containers/asc_std_mdspan/mdspan_empty.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::extent](containers/asc_std_mdspan/mdspan_extent.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::extents](containers/asc_std_mdspan/mdspan_extents.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::extents_type](containers/asc_std_mdspan/mdspan_extents_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::index_type](containers/asc_std_mdspan/mdspan_index_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::is_always_exhaustive](containers/asc_std_mdspan/mdspan_is_always_exhaustive.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::is_always_strided](containers/asc_std_mdspan/mdspan_is_always_strided.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::is_always_unique](containers/asc_std_mdspan/mdspan_is_always_unique.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::is_exhaustive](containers/asc_std_mdspan/mdspan_is_exhaustive.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::is_strided](containers/asc_std_mdspan/mdspan_is_strided.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::is_unique](containers/asc_std_mdspan/mdspan_is_unique.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::layout_type](containers/asc_std_mdspan/mdspan_layout_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::mapping](containers/asc_std_mdspan/mdspan_mapping.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::mapping_type](containers/asc_std_mdspan/mdspan_mapping_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::mdspan](containers/asc_std_mdspan/mdspan_mdspan.md) | asc/std/mdspan | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::operator=](containers/asc_std_mdspan/mdspan_operator_assign.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::operator\[\]](containers/asc_std_mdspan/mdspan_operator_subscript.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::rank](containers/asc_std_mdspan/mdspan_rank.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::rank_dynamic](containers/asc_std_mdspan/mdspan_rank_dynamic.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::rank_type](containers/asc_std_mdspan/mdspan_rank_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::reference](containers/asc_std_mdspan/mdspan_reference.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::size](containers/asc_std_mdspan/mdspan_size.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::size_type](containers/asc_std_mdspan/mdspan_size_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::static_extent](containers/asc_std_mdspan/mdspan_static_extent.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::stride](containers/asc_std_mdspan/mdspan_stride.md) | asc/std/mdspan | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mdspan::value_type](containers/asc_std_mdspan/mdspan_value_type.md) | asc/std/mdspan | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::strided_slice](containers/asc_std_mdspan/strided_slice.md) | asc/std/mdspan | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::submdspan](containers/asc_std_mdspan/submdspan.md) | asc/std/mdspan | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::submdspan_extents](containers/asc_std_mdspan/submdspan_extents.md) | asc/std/mdspan | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::submdspan_mapping](containers/asc_std_mdspan/submdspan_mapping.md) | asc/std/mdspan | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::submdspan_mapping_result](containers/asc_std_mdspan/submdspan_mapping_result.md) | asc/std/mdspan | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::addressof](memory_management/asc_std_memory/addressof.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::align](memory_management/asc_std_memory/align.md) | asc/std/memory | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocation_result](memory_management/asc_std_memory/allocation_result.md) | asc/std/memory | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocation_result::count](memory_management/asc_std_memory/allocation_result_count.md) | asc/std/memory | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocation_result::ptr](memory_management/asc_std_memory/allocation_result_ptr.md) | asc/std/memory | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_arg](memory_management/asc_std_memory/allocator_arg.md) | asc/std/memory | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_arg_t](memory_management/asc_std_memory/allocator_arg_t.md) | asc/std/memory | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_arg_t::allocator_arg_t](memory_management/asc_std_memory/allocator_arg_t_allocator_arg_t.md) | asc/std/memory | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_arg_t::~allocator_arg_t](memory_management/asc_std_memory/allocator_arg_t_destructor_allocator_arg_t.md) | asc/std/memory | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits](memory_management/asc_std_memory/allocator_traits.md) | asc/std/memory | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::allocate](memory_management/asc_std_memory/allocator_traits_allocate.md) | asc/std/memory | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::allocate_at_least](memory_management/asc_std_memory/allocator_traits_allocate_at_least.md) | asc/std/memory | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::allocator_type](memory_management/asc_std_memory/allocator_traits_allocator_type.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::const_pointer](memory_management/asc_std_memory/allocator_traits_const_pointer.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::const_void_pointer](memory_management/asc_std_memory/allocator_traits_const_void_pointer.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::construct](memory_management/asc_std_memory/allocator_traits_construct.md) | asc/std/memory | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::deallocate](memory_management/asc_std_memory/allocator_traits_deallocate.md) | asc/std/memory | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::destroy](memory_management/asc_std_memory/allocator_traits_destroy.md) | asc/std/memory | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::difference_type](memory_management/asc_std_memory/allocator_traits_difference_type.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::is_always_equal](memory_management/asc_std_memory/allocator_traits_is_always_equal.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::max_size](memory_management/asc_std_memory/allocator_traits_max_size.md) | asc/std/memory | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::pointer](memory_management/asc_std_memory/allocator_traits_pointer.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::propagate_on_container_copy_assignment](memory_management/asc_std_memory/allocator_traits_propagate_on_container_copy_assignment.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::propagate_on_container_move_assignment](memory_management/asc_std_memory/allocator_traits_propagate_on_container_move_assignment.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::propagate_on_container_swap](memory_management/asc_std_memory/allocator_traits_propagate_on_container_swap.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::rebind_alloc](memory_management/asc_std_memory/allocator_traits_rebind_alloc.md) | asc/std/memory | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::rebind_traits](memory_management/asc_std_memory/allocator_traits_rebind_traits.md) | asc/std/memory | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::select_on_container_copy_construction](memory_management/asc_std_memory/allocator_traits_select_on_container_copy_construction.md) | asc/std/memory | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::size_type](memory_management/asc_std_memory/allocator_traits_size_type.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::value_type](memory_management/asc_std_memory/allocator_traits_value_type.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::void_pointer](memory_management/asc_std_memory/allocator_traits_void_pointer.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::assume_aligned](memory_management/asc_std_memory/assume_aligned.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::construct_at](memory_management/asc_std_memory/construct_at.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::destroy](memory_management/asc_std_memory/destroy.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::destroy_at](memory_management/asc_std_memory/destroy_at.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::destroy_n](memory_management/asc_std_memory/destroy_n.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_sufficiently_aligned](memory_management/asc_std_memory/is_sufficiently_aligned.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::launder](memory_management/asc_std_memory/launder.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_obj_using_allocator](memory_management/asc_std_memory/make_obj_using_allocator.md) | asc/std/memory | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits](memory_management/asc_std_memory/pointer_traits.md) | asc/std/memory | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::difference_type](memory_management/asc_std_memory/pointer_traits_difference_type.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::element_type](memory_management/asc_std_memory/pointer_traits_element_type.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::pointer](memory_management/asc_std_memory/pointer_traits_pointer.md) | asc/std/memory | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::pointer_to](memory_management/asc_std_memory/pointer_traits_pointer_to.md) | asc/std/memory | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::rebind](memory_management/asc_std_memory/pointer_traits_rebind.md) | asc/std/memory | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::to_address](memory_management/asc_std_memory/to_address.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_construct_using_allocator](memory_management/asc_std_memory/uninitialized_construct_using_allocator.md) | asc/std/memory | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_copy](memory_management/asc_std_memory/uninitialized_copy.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_copy_n](memory_management/asc_std_memory/uninitialized_copy_n.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_default_construct](memory_management/asc_std_memory/uninitialized_default_construct.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_default_construct_n](memory_management/asc_std_memory/uninitialized_default_construct_n.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_fill](memory_management/asc_std_memory/uninitialized_fill.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_fill_n](memory_management/asc_std_memory/uninitialized_fill_n.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_move](memory_management/asc_std_memory/uninitialized_move.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_move_n](memory_management/asc_std_memory/uninitialized_move_n.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_value_construct](memory_management/asc_std_memory/uninitialized_value_construct.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_value_construct_n](memory_management/asc_std_memory/uninitialized_value_construct_n.md) | asc/std/memory | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uses_allocator](memory_management/asc_std_memory/uses_allocator.md) | asc/std/memory | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uses_allocator_construction_args](memory_management/asc_std_memory/uses_allocator_construction_args.md) | asc/std/memory | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uses_allocator_v](memory_management/asc_std_memory/uses_allocator_v.md) | asc/std/memory | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::adopt_lock](concurrency/asc_std_mutex/adopt_lock.md) | asc/std/mutex | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::adopt_lock_t](concurrency/asc_std_mutex/adopt_lock_t.md) | asc/std/mutex | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::defer_lock](concurrency/asc_std_mutex/defer_lock.md) | asc/std/mutex | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::defer_lock_t](concurrency/asc_std_mutex/defer_lock_t.md) | asc/std/mutex | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lock_guard](concurrency/asc_std_mutex/lock_guard.md) | asc/std/mutex | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_lock](concurrency/asc_std_mutex/scoped_lock.md) | asc/std/mutex | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::swap](concurrency/asc_std_mutex/swap.md) | asc/std/mutex | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::try_lock](concurrency/asc_std_mutex/try_lock.md) | asc/std/mutex | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::try_to_lock](concurrency/asc_std_mutex/try_to_lock.md) | asc/std/mutex | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::try_to_lock_t](concurrency/asc_std_mutex/try_to_lock_t.md) | asc/std/mutex | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock](concurrency/asc_std_mutex/unique_lock.md) | asc/std/mutex | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::lock](concurrency/asc_std_mutex/unique_lock_lock.md) | asc/std/mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::mutex](concurrency/asc_std_mutex/unique_lock_mutex.md) | asc/std/mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::mutex_type](concurrency/asc_std_mutex/unique_lock_mutex_type.md) | asc/std/mutex | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::operator=](concurrency/asc_std_mutex/unique_lock_operator_assign.md) | asc/std/mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::owns_lock](concurrency/asc_std_mutex/unique_lock_owns_lock.md) | asc/std/mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::release](concurrency/asc_std_mutex/unique_lock_release.md) | asc/std/mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::swap](concurrency/asc_std_mutex/unique_lock_swap.md) | asc/std/mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::try_lock](concurrency/asc_std_mutex/unique_lock_try_lock.md) | asc/std/mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::unique_lock](concurrency/asc_std_mutex/unique_lock_unique_lock.md) | asc/std/mutex | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::unlock](concurrency/asc_std_mutex/unique_lock_unlock.md) | asc/std/mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unique_lock::~unique_lock](concurrency/asc_std_mutex/unique_lock_destructor_unique_lock.md) | asc/std/mutex | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [::operator new](language_support/asc_std_new/operator_new.md) | asc/std/new | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [::operator new\[\]](language_support/asc_std_new/operator_new_array.md) | asc/std/new | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::align_val_t](language_support/asc_std_new/align_val_t.md) | asc/std/new | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::destroying_delete_t](language_support/asc_std_new/destroying_delete_t.md) | asc/std/new | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nothrow](language_support/asc_std_new/nothrow.md) | asc/std/new | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nothrow_t](language_support/asc_std_new/nothrow_t.md) | asc/std/new | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::e_v](numerics/asc_std_numbers/e_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::egamma_v](numerics/asc_std_numbers/egamma_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::inv_pi_v](numerics/asc_std_numbers/inv_pi_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::inv_sqrt3_v](numerics/asc_std_numbers/inv_sqrt3_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::inv_sqrtpi_v](numerics/asc_std_numbers/inv_sqrtpi_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ln10_v](numerics/asc_std_numbers/ln10_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ln2_v](numerics/asc_std_numbers/ln2_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::log10e_v](numerics/asc_std_numbers/log10e_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::log2e_v](numerics/asc_std_numbers/log2e_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::e](numerics/asc_std_numbers/numbers_e.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::egamma](numerics/asc_std_numbers/numbers_egamma.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::inv_pi](numerics/asc_std_numbers/numbers_inv_pi.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::inv_sqrt3](numerics/asc_std_numbers/numbers_inv_sqrt3.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::inv_sqrtpi](numerics/asc_std_numbers/numbers_inv_sqrtpi.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::ln10](numerics/asc_std_numbers/numbers_ln10.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::ln2](numerics/asc_std_numbers/numbers_ln2.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::log10e](numerics/asc_std_numbers/numbers_log10e.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::log2e](numerics/asc_std_numbers/numbers_log2e.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::phi](numerics/asc_std_numbers/numbers_phi.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::pi](numerics/asc_std_numbers/numbers_pi.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::sqrt2](numerics/asc_std_numbers/numbers_sqrt2.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::numbers::sqrt3](numerics/asc_std_numbers/numbers_sqrt3.md) | asc/std/numbers | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::phi_v](numerics/asc_std_numbers/phi_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pi_v](numerics/asc_std_numbers/pi_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sqrt2_v](numerics/asc_std_numbers/sqrt2_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::sqrt3_v](numerics/asc_std_numbers/sqrt3_v.md) | asc/std/numbers | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::accumulate](numerics/asc_std_numeric/accumulate.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::adjacent_difference](numerics/asc_std_numeric/adjacent_difference.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::exclusive_scan](numerics/asc_std_numeric/exclusive_scan.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::gcd](numerics/asc_std_numeric/gcd.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::inclusive_scan](numerics/asc_std_numeric/inclusive_scan.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::inner_product](numerics/asc_std_numeric/inner_product.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::iota](numerics/asc_std_numeric/iota.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::lcm](numerics/asc_std_numeric/lcm.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::midpoint](numerics/asc_std_numeric/midpoint.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::partial_sum](numerics/asc_std_numeric/partial_sum.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::reduce](numerics/asc_std_numeric/reduce.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::saturating_add](numerics/asc_std_numeric/saturating_add.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::saturating_cast](numerics/asc_std_numeric/saturating_cast.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::saturating_div](numerics/asc_std_numeric/saturating_div.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::saturating_mul](numerics/asc_std_numeric/saturating_mul.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::saturating_sub](numerics/asc_std_numeric/saturating_sub.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::transform_exclusive_scan](numerics/asc_std_numeric/transform_exclusive_scan.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::transform_inclusive_scan](numerics/asc_std_numeric/transform_inclusive_scan.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::transform_reduce](numerics/asc_std_numeric/transform_reduce.md) | asc/std/numeric | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_optional](utilities/asc_std_optional/make_optional.md) | asc/std/optional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nullopt](utilities/asc_std_optional/nullopt.md) | asc/std/optional | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nullopt_t](utilities/asc_std_optional/nullopt_t.md) | asc/std/optional | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator<（函数模板）](utilities/asc_std_optional/operator_less.md) | asc/std/optional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator<=（函数模板）](utilities/asc_std_optional/operator_less_equal.md) | asc/std/optional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator>（函数模板）](utilities/asc_std_optional/operator_greater.md) | asc/std/optional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator>=（函数模板）](utilities/asc_std_optional/operator_greater_equal.md) | asc/std/optional | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional](utilities/asc_std_optional/optional.md) | asc/std/optional | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::emplace](utilities/asc_std_optional/optional_emplace.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::has_value](utilities/asc_std_optional/optional_has_value.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::operator bool](utilities/asc_std_optional/optional_operator_bool.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::operator*](utilities/asc_std_optional/optional_operator_dereference.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::operator->](utilities/asc_std_optional/optional_operator_arrow.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::operator=](utilities/asc_std_optional/optional_operator_assign.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::optional](utilities/asc_std_optional/optional_optional.md) | asc/std/optional | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::reset](utilities/asc_std_optional/optional_reset.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::swap](utilities/asc_std_optional/optional_swap.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::value_or](utilities/asc_std_optional/optional_value_or.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional::value_type](utilities/asc_std_optional/optional_value_type.md) | asc/std/optional | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional<T&>::has_value](utilities/asc_std_optional/optional_t_has_value.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional<T&>::operator bool](utilities/asc_std_optional/optional_t_operator_bool.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional<T&>::operator*](utilities/asc_std_optional/optional_t_operator_dereference.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional<T&>::operator->](utilities/asc_std_optional/optional_t_operator_arrow.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional<T&>::operator=](utilities/asc_std_optional/optional_t_operator_assign.md) | asc/std/optional | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::optional<T&>::optional](utilities/asc_std_optional/optional_t_optional.md) | asc/std/optional | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue](containers/asc_std_queue/priority_queue.md) | asc/std/queue | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::const_reference](containers/asc_std_queue/priority_queue_const_reference.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::container_type](containers/asc_std_queue/priority_queue_container_type.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::emplace](containers/asc_std_queue/priority_queue_emplace.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::empty](containers/asc_std_queue/priority_queue_empty.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::pop](containers/asc_std_queue/priority_queue_pop.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::priority_queue](containers/asc_std_queue/priority_queue_priority_queue.md) | asc/std/queue | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::push](containers/asc_std_queue/priority_queue_push.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::reference](containers/asc_std_queue/priority_queue_reference.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::size](containers/asc_std_queue/priority_queue_size.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::size_type](containers/asc_std_queue/priority_queue_size_type.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::swap](containers/asc_std_queue/priority_queue_swap.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::top](containers/asc_std_queue/priority_queue_top.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::value_compare](containers/asc_std_queue/priority_queue_value_compare.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::priority_queue::value_type](containers/asc_std_queue/priority_queue_value_type.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue](containers/asc_std_queue/queue.md) | asc/std/queue | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::back](containers/asc_std_queue/queue_back.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::const_reference](containers/asc_std_queue/queue_const_reference.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::container_type](containers/asc_std_queue/queue_container_type.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::emplace](containers/asc_std_queue/queue_emplace.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::empty](containers/asc_std_queue/queue_empty.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::front](containers/asc_std_queue/queue_front.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::pop](containers/asc_std_queue/queue_pop.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::push](containers/asc_std_queue/queue_push.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::queue](containers/asc_std_queue/queue_queue.md) | asc/std/queue | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::reference](containers/asc_std_queue/queue_reference.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::size](containers/asc_std_queue/queue_size.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::size_type](containers/asc_std_queue/queue_size_type.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::swap](containers/asc_std_queue/queue_swap.md) | asc/std/queue | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::queue::value_type](containers/asc_std_queue/queue_value_type.md) | asc/std/queue | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::generate_canonical](numerics/asc_std_random/generate_canonical.md) | asc/std/random | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine](numerics/asc_std_random/linear_congruential_engine.md) | asc/std/random | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::default_seed](numerics/asc_std_random/linear_congruential_engine_default_seed.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::discard](numerics/asc_std_random/linear_congruential_engine_discard.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::increment](numerics/asc_std_random/linear_congruential_engine_increment.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::linear_congruential_engine](numerics/asc_std_random/linear_congruential_engine_linear_congruential_engine.md) | asc/std/random | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::max](numerics/asc_std_random/linear_congruential_engine_max.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::min](numerics/asc_std_random/linear_congruential_engine_min.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::modulus](numerics/asc_std_random/linear_congruential_engine_modulus.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::multiplier](numerics/asc_std_random/linear_congruential_engine_multiplier.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::operator()](numerics/asc_std_random/linear_congruential_engine_operator_call.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::result_type](numerics/asc_std_random/linear_congruential_engine_result_type.md) | asc/std/random | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::seed](numerics/asc_std_random/linear_congruential_engine_seed.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::minstd_rand](numerics/asc_std_random/minstd_rand.md) | asc/std/random | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::minstd_rand0](numerics/asc_std_random/minstd_rand0.md) | asc/std/random | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox4x32](numerics/asc_std_random/philox4x32.md) | asc/std/random | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox4x64](numerics/asc_std_random/philox4x64.md) | asc/std/random | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine](numerics/asc_std_random/philox_engine.md) | asc/std/random | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::default_seed](numerics/asc_std_random/philox_engine_default_seed.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::discard](numerics/asc_std_random/philox_engine_discard.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::max](numerics/asc_std_random/philox_engine_max.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::min](numerics/asc_std_random/philox_engine_min.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::multipliers](numerics/asc_std_random/philox_engine_multipliers.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::operator()](numerics/asc_std_random/philox_engine_operator_call.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::philox_engine](numerics/asc_std_random/philox_engine_philox_engine.md) | asc/std/random | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::result_type](numerics/asc_std_random/philox_engine_result_type.md) | asc/std/random | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::round_consts](numerics/asc_std_random/philox_engine_round_consts.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::round_count](numerics/asc_std_random/philox_engine_round_count.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::seed](numerics/asc_std_random/philox_engine_seed.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::set_counter](numerics/asc_std_random/philox_engine_set_counter.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::word_count](numerics/asc_std_random/philox_engine_word_count.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::philox_engine::word_size](numerics/asc_std_random/philox_engine_word_size.md) | asc/std/random | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution](numerics/asc_std_random/uniform_int_distribution.md) | asc/std/random | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::a](numerics/asc_std_random/uniform_int_distribution_a.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::b](numerics/asc_std_random/uniform_int_distribution_b.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::max](numerics/asc_std_random/uniform_int_distribution_max.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::min](numerics/asc_std_random/uniform_int_distribution_min.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::operator()](numerics/asc_std_random/uniform_int_distribution_operator_call.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::param](numerics/asc_std_random/uniform_int_distribution_param.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::param_type](numerics/asc_std_random/uniform_int_distribution_param_type.md) | asc/std/random | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::reset](numerics/asc_std_random/uniform_int_distribution_reset.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::result_type](numerics/asc_std_random/uniform_int_distribution_result_type.md) | asc/std/random | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::uniform_int_distribution](numerics/asc_std_random/uniform_int_distribution_uniform_int_distribution.md) | asc/std/random | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution](numerics/asc_std_random/uniform_real_distribution.md) | asc/std/random | 类特化 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::a](numerics/asc_std_random/uniform_real_distribution_a.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::b](numerics/asc_std_random/uniform_real_distribution_b.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::max](numerics/asc_std_random/uniform_real_distribution_max.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::min](numerics/asc_std_random/uniform_real_distribution_min.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::operator()](numerics/asc_std_random/uniform_real_distribution_operator_call.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param](numerics/asc_std_random/uniform_real_distribution_param.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type](numerics/asc_std_random/uniform_real_distribution_param_type.md) | asc/std/random | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type::a](numerics/asc_std_random/uniform_real_distribution_param_type_a.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type::b](numerics/asc_std_random/uniform_real_distribution_param_type_b.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type::param_type](numerics/asc_std_random/uniform_real_distribution_param_type_param_type.md) | asc/std/random | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::reset](numerics/asc_std_random/uniform_real_distribution_reset.md) | asc/std/random | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::result_type](numerics/asc_std_random/uniform_real_distribution_result_type.md) | asc/std/random | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::uniform_real_distribution](numerics/asc_std_random/uniform_real_distribution_uniform_real_distribution.md) | asc/std/random | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::from_range](ranges/asc_std_ranges/from_range.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::from_range_t](ranges/asc_std_ranges/from_range_t.md) | asc/std/ranges | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::begin](ranges/asc_std_ranges/ranges_begin.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::bidirectional_range](ranges/asc_std_ranges/ranges_bidirectional_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::borrowed_iterator_t](ranges/asc_std_ranges/ranges_borrowed_iterator_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::borrowed_range](ranges/asc_std_ranges/ranges_borrowed_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::borrowed_subrange_t](ranges/asc_std_ranges/ranges_borrowed_subrange_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::cbegin](ranges/asc_std_ranges/ranges_cbegin.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::cdata](ranges/asc_std_ranges/ranges_cdata.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::cend](ranges/asc_std_ranges/ranges_cend.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::common_range](ranges/asc_std_ranges/ranges_common_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::common_view](ranges/asc_std_ranges/ranges_common_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::common_view::base](ranges/asc_std_ranges/ranges_common_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::common_view::begin](ranges/asc_std_ranges/ranges_common_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::common_view::common_view](ranges/asc_std_ranges/ranges_common_view_common_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::common_view::end](ranges/asc_std_ranges/ranges_common_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::common_view::size](ranges/asc_std_ranges/ranges_common_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::contiguous_range](ranges/asc_std_ranges/ranges_contiguous_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::crbegin](ranges/asc_std_ranges/ranges_crbegin.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::crend](ranges/asc_std_ranges/ranges_crend.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::dangling](ranges/asc_std_ranges/ranges_dangling.md) | asc/std/ranges | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::dangling::dangling](ranges/asc_std_ranges/ranges_dangling_dangling.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::data](ranges/asc_std_ranges/ranges_data.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::disable_sized_range](ranges/asc_std_ranges/ranges_disable_sized_range.md) | asc/std/ranges | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_view](ranges/asc_std_ranges/ranges_drop_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_view::base](ranges/asc_std_ranges/ranges_drop_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_view::begin](ranges/asc_std_ranges/ranges_drop_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_view::drop_view](ranges/asc_std_ranges/ranges_drop_view_drop_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_view::end](ranges/asc_std_ranges/ranges_drop_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_view::size](ranges/asc_std_ranges/ranges_drop_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_while_view](ranges/asc_std_ranges/ranges_drop_while_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_while_view::base](ranges/asc_std_ranges/ranges_drop_while_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_while_view::begin](ranges/asc_std_ranges/ranges_drop_while_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_while_view::drop_while_view](ranges/asc_std_ranges/ranges_drop_while_view_drop_while_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_while_view::end](ranges/asc_std_ranges/ranges_drop_while_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::drop_while_view::pred](ranges/asc_std_ranges/ranges_drop_while_view_pred.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::empty](ranges/asc_std_ranges/ranges_empty.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::empty_view](ranges/asc_std_ranges/ranges_empty_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::empty_view::begin](ranges/asc_std_ranges/ranges_empty_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::empty_view::data](ranges/asc_std_ranges/ranges_empty_view_data.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::empty_view::empty](ranges/asc_std_ranges/ranges_empty_view_empty.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::empty_view::end](ranges/asc_std_ranges/ranges_empty_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::empty_view::size](ranges/asc_std_ranges/ranges_empty_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::enable_borrowed_range](ranges/asc_std_ranges/ranges_enable_borrowed_range.md) | asc/std/ranges | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::enable_view](ranges/asc_std_ranges/ranges_enable_view.md) | asc/std/ranges | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::end](ranges/asc_std_ranges/ranges_end.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::filter_view](ranges/asc_std_ranges/ranges_filter_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::filter_view::base](ranges/asc_std_ranges/ranges_filter_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::filter_view::begin](ranges/asc_std_ranges/ranges_filter_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::filter_view::end](ranges/asc_std_ranges/ranges_filter_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::filter_view::filter_view](ranges/asc_std_ranges/ranges_filter_view_filter_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::filter_view::pred](ranges/asc_std_ranges/ranges_filter_view_pred.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::forward_range](ranges/asc_std_ranges/ranges_forward_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::input_range](ranges/asc_std_ranges/ranges_input_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::iota_view](ranges/asc_std_ranges/ranges_iota_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::iota_view::begin](ranges/asc_std_ranges/ranges_iota_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::iota_view::end](ranges/asc_std_ranges/ranges_iota_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::iota_view::iota_view](ranges/asc_std_ranges/ranges_iota_view_iota_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::iota_view::size](ranges/asc_std_ranges/ranges_iota_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::iterator_t](ranges/asc_std_ranges/ranges_iterator_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::output_range](ranges/asc_std_ranges/ranges_output_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::owning_view](ranges/asc_std_ranges/ranges_owning_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::owning_view::base](ranges/asc_std_ranges/ranges_owning_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::owning_view::begin](ranges/asc_std_ranges/ranges_owning_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::owning_view::data](ranges/asc_std_ranges/ranges_owning_view_data.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::owning_view::empty](ranges/asc_std_ranges/ranges_owning_view_empty.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::owning_view::end](ranges/asc_std_ranges/ranges_owning_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::owning_view::operator=](ranges/asc_std_ranges/ranges_owning_view_operator_assign.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::owning_view::owning_view](ranges/asc_std_ranges/ranges_owning_view_owning_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::owning_view::size](ranges/asc_std_ranges/ranges_owning_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::random_access_range](ranges/asc_std_ranges/ranges_random_access_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::range](ranges/asc_std_ranges/ranges_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::range_adaptor_closure](ranges/asc_std_ranges/ranges_range_adaptor_closure.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::range_common_reference_t](ranges/asc_std_ranges/ranges_range_common_reference_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::range_difference_t](ranges/asc_std_ranges/ranges_range_difference_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::range_reference_t](ranges/asc_std_ranges/ranges_range_reference_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::range_rvalue_reference_t](ranges/asc_std_ranges/ranges_range_rvalue_reference_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::range_size_t](ranges/asc_std_ranges/ranges_range_size_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::range_value_t](ranges/asc_std_ranges/ranges_range_value_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::rbegin](ranges/asc_std_ranges/ranges_rbegin.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::ref_view](ranges/asc_std_ranges/ranges_ref_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::ref_view::base](ranges/asc_std_ranges/ranges_ref_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::ref_view::begin](ranges/asc_std_ranges/ranges_ref_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::ref_view::data](ranges/asc_std_ranges/ranges_ref_view_data.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::ref_view::empty](ranges/asc_std_ranges/ranges_ref_view_empty.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::ref_view::end](ranges/asc_std_ranges/ranges_ref_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::ref_view::ref_view](ranges/asc_std_ranges/ranges_ref_view_ref_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::ref_view::size](ranges/asc_std_ranges/ranges_ref_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::rend](ranges/asc_std_ranges/ranges_rend.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::repeat_view](ranges/asc_std_ranges/ranges_repeat_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::repeat_view::begin](ranges/asc_std_ranges/ranges_repeat_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::repeat_view::end](ranges/asc_std_ranges/ranges_repeat_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::repeat_view::repeat_view](ranges/asc_std_ranges/ranges_repeat_view_repeat_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::repeat_view::size](ranges/asc_std_ranges/ranges_repeat_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::reverse_view](ranges/asc_std_ranges/ranges_reverse_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::reverse_view::base](ranges/asc_std_ranges/ranges_reverse_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::reverse_view::begin](ranges/asc_std_ranges/ranges_reverse_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::reverse_view::end](ranges/asc_std_ranges/ranges_reverse_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::reverse_view::reverse_view](ranges/asc_std_ranges/ranges_reverse_view_reverse_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::reverse_view::size](ranges/asc_std_ranges/ranges_reverse_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::sentinel_t](ranges/asc_std_ranges/ranges_sentinel_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::single_view](ranges/asc_std_ranges/ranges_single_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::single_view::begin](ranges/asc_std_ranges/ranges_single_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::single_view::data](ranges/asc_std_ranges/ranges_single_view_data.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::single_view::end](ranges/asc_std_ranges/ranges_single_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::single_view::single_view](ranges/asc_std_ranges/ranges_single_view_single_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::single_view::size](ranges/asc_std_ranges/ranges_single_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::size](ranges/asc_std_ranges/ranges_size.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::sized_range](ranges/asc_std_ranges/ranges_sized_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::ssize](ranges/asc_std_ranges/ranges_ssize.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange](ranges/asc_std_ranges/ranges_subrange.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange::advance](ranges/asc_std_ranges/ranges_subrange_advance.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange::begin](ranges/asc_std_ranges/ranges_subrange_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange::empty](ranges/asc_std_ranges/ranges_subrange_empty.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange::end](ranges/asc_std_ranges/ranges_subrange_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange::next](ranges/asc_std_ranges/ranges_subrange_next.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange::prev](ranges/asc_std_ranges/ranges_subrange_prev.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange::size](ranges/asc_std_ranges/ranges_subrange_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange::subrange](ranges/asc_std_ranges/ranges_subrange_subrange.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::subrange_kind](ranges/asc_std_ranges/ranges_subrange_kind.md) | asc/std/ranges | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_view](ranges/asc_std_ranges/ranges_take_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_view::base](ranges/asc_std_ranges/ranges_take_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_view::begin](ranges/asc_std_ranges/ranges_take_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_view::end](ranges/asc_std_ranges/ranges_take_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_view::size](ranges/asc_std_ranges/ranges_take_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_view::take_view](ranges/asc_std_ranges/ranges_take_view_take_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_while_view](ranges/asc_std_ranges/ranges_take_while_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_while_view::base](ranges/asc_std_ranges/ranges_take_while_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_while_view::begin](ranges/asc_std_ranges/ranges_take_while_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_while_view::end](ranges/asc_std_ranges/ranges_take_while_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_while_view::pred](ranges/asc_std_ranges/ranges_take_while_view_pred.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::take_while_view::take_while_view](ranges/asc_std_ranges/ranges_take_while_view_take_while_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::transform_view](ranges/asc_std_ranges/ranges_transform_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::transform_view::base](ranges/asc_std_ranges/ranges_transform_view_base.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::transform_view::begin](ranges/asc_std_ranges/ranges_transform_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::transform_view::end](ranges/asc_std_ranges/ranges_transform_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::transform_view::size](ranges/asc_std_ranges/ranges_transform_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::transform_view::transform_view](ranges/asc_std_ranges/ranges_transform_view_transform_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::view](ranges/asc_std_ranges/ranges_view.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::view_base](ranges/asc_std_ranges/ranges_view_base.md) | asc/std/ranges | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::view_interface](ranges/asc_std_ranges/ranges_view_interface.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::view_interface::back](ranges/asc_std_ranges/ranges_view_interface_back.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::view_interface::data](ranges/asc_std_ranges/ranges_view_interface_data.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::view_interface::empty](ranges/asc_std_ranges/ranges_view_interface_empty.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::view_interface::front](ranges/asc_std_ranges/ranges_view_interface_front.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::view_interface::operator\[\]](ranges/asc_std_ranges/ranges_view_interface_operator_subscript.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::view_interface::size](ranges/asc_std_ranges/ranges_view_interface_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::viewable_range](ranges/asc_std_ranges/ranges_viewable_range.md) | asc/std/ranges | 概念 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::all](ranges/asc_std_ranges/ranges_views_all.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::all_t](ranges/asc_std_ranges/ranges_views_all_t.md) | asc/std/ranges | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::common](ranges/asc_std_ranges/ranges_views_common.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::counted](ranges/asc_std_ranges/ranges_views_counted.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::drop](ranges/asc_std_ranges/ranges_views_drop.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::drop_while](ranges/asc_std_ranges/ranges_views_drop_while.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::empty](ranges/asc_std_ranges/ranges_views_empty.md) | asc/std/ranges | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::filter](ranges/asc_std_ranges/ranges_views_filter.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::iota](ranges/asc_std_ranges/ranges_views_iota.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::repeat](ranges/asc_std_ranges/ranges_views_repeat.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::reverse](ranges/asc_std_ranges/ranges_views_reverse.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::single](ranges/asc_std_ranges/ranges_views_single.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::take](ranges/asc_std_ranges/ranges_views_take.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::take_while](ranges/asc_std_ranges/ranges_views_take_while.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::transform](ranges/asc_std_ranges/ranges_views_transform.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::views::zip](ranges/asc_std_ranges/ranges_views_zip.md) | asc/std/ranges | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::zip_view](ranges/asc_std_ranges/ranges_zip_view.md) | asc/std/ranges | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::zip_view::begin](ranges/asc_std_ranges/ranges_zip_view_begin.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::zip_view::end](ranges/asc_std_ranges/ranges_zip_view_end.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::zip_view::size](ranges/asc_std_ranges/ranges_zip_view_size.md) | asc/std/ranges | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ranges::zip_view::zip_view](ranges/asc_std_ranges/ranges_zip_view_zip_view.md) | asc/std/ranges | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atto](metaprogramming/asc_std_ratio/atto.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::centi](metaprogramming/asc_std_ratio/centi.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deca](metaprogramming/asc_std_ratio/deca.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::deci](metaprogramming/asc_std_ratio/deci.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::exa](metaprogramming/asc_std_ratio/exa.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::femto](metaprogramming/asc_std_ratio/femto.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::giga](metaprogramming/asc_std_ratio/giga.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::hecto](metaprogramming/asc_std_ratio/hecto.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::kilo](metaprogramming/asc_std_ratio/kilo.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::mega](metaprogramming/asc_std_ratio/mega.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::micro](metaprogramming/asc_std_ratio/micro.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::milli](metaprogramming/asc_std_ratio/milli.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::nano](metaprogramming/asc_std_ratio/nano.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::peta](metaprogramming/asc_std_ratio/peta.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pico](metaprogramming/asc_std_ratio/pico.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio](metaprogramming/asc_std_ratio/ratio.md) | asc/std/ratio | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio::den](metaprogramming/asc_std_ratio/ratio_den.md) | asc/std/ratio | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio::num](metaprogramming/asc_std_ratio/ratio_num.md) | asc/std/ratio | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio::type](metaprogramming/asc_std_ratio/ratio_type.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_add](metaprogramming/asc_std_ratio/ratio_add.md) | asc/std/ratio | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_divide](metaprogramming/asc_std_ratio/ratio_divide.md) | asc/std/ratio | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_equal](metaprogramming/asc_std_ratio/ratio_equal.md) | asc/std/ratio | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_equal_v](metaprogramming/asc_std_ratio/ratio_equal_v.md) | asc/std/ratio | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_greater](metaprogramming/asc_std_ratio/ratio_greater.md) | asc/std/ratio | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_greater_equal](metaprogramming/asc_std_ratio/ratio_greater_equal.md) | asc/std/ratio | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_greater_equal_v](metaprogramming/asc_std_ratio/ratio_greater_equal_v.md) | asc/std/ratio | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_greater_v](metaprogramming/asc_std_ratio/ratio_greater_v.md) | asc/std/ratio | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_less](metaprogramming/asc_std_ratio/ratio_less.md) | asc/std/ratio | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_less_equal](metaprogramming/asc_std_ratio/ratio_less_equal.md) | asc/std/ratio | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_less_equal_v](metaprogramming/asc_std_ratio/ratio_less_equal_v.md) | asc/std/ratio | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_less_v](metaprogramming/asc_std_ratio/ratio_less_v.md) | asc/std/ratio | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_multiply](metaprogramming/asc_std_ratio/ratio_multiply.md) | asc/std/ratio | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_not_equal](metaprogramming/asc_std_ratio/ratio_not_equal.md) | asc/std/ratio | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_not_equal_v](metaprogramming/asc_std_ratio/ratio_not_equal_v.md) | asc/std/ratio | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ratio_subtract](metaprogramming/asc_std_ratio/ratio_subtract.md) | asc/std/ratio | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tera](metaprogramming/asc_std_ratio/tera.md) | asc/std/ratio | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor.md) | asc/std/scoped_allocator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::allocate](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_allocate.md) | asc/std/scoped_allocator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::const_pointer](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_const_pointer.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::const_void_pointer](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_const_void_pointer.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::construct](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_construct.md) | asc/std/scoped_allocator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::deallocate](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_deallocate.md) | asc/std/scoped_allocator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::destroy](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_destroy.md) | asc/std/scoped_allocator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::difference_type](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_difference_type.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::inner_allocator](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_inner_allocator.md) | asc/std/scoped_allocator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::inner_allocator_type](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_inner_allocator_type.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::is_always_equal](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_is_always_equal.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::max_size](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_max_size.md) | asc/std/scoped_allocator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::operator=](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_operator_assign.md) | asc/std/scoped_allocator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::outer_allocator](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_outer_allocator.md) | asc/std/scoped_allocator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::outer_allocator_type](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_outer_allocator_type.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::outer_traits](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_outer_traits.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::pointer](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_pointer.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::propagate_on_container_copy_assignment](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_propagate_on_container_copy_assignment.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::propagate_on_container_move_assignment](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_propagate_on_container_move_assignment.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::propagate_on_container_swap](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_propagate_on_container_swap.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::rebind](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_rebind.md) | asc/std/scoped_allocator | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::scoped_allocator_adaptor](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_scoped_allocator_adaptor.md) | asc/std/scoped_allocator | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::select_on_container_copy_construction](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_select_on_container_copy_construction.md) | asc/std/scoped_allocator | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::size_type](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_size_type.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::value_type](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_value_type.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::void_pointer](memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor_void_pointer.md) | asc/std/scoped_allocator | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::binary_semaphore](concurrency/asc_std_semaphore/binary_semaphore.md) | asc/std/semaphore | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore](concurrency/asc_std_semaphore/counting_semaphore.md) | asc/std/semaphore | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore::acquire](concurrency/asc_std_semaphore/counting_semaphore_acquire.md) | asc/std/semaphore | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore::max](concurrency/asc_std_semaphore/counting_semaphore_max.md) | asc/std/semaphore | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore::release](concurrency/asc_std_semaphore/counting_semaphore_release.md) | asc/std/semaphore | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::counting_semaphore::try_acquire](concurrency/asc_std_semaphore/counting_semaphore_try_acquire.md) | asc/std/semaphore | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set](containers/asc_std_set/set.md) | asc/std/set | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::begin](containers/asc_std_set/set_begin.md) | asc/std/set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::clear](containers/asc_std_set/set_clear.md) | asc/std/set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::count](containers/asc_std_set/set_count.md) | asc/std/set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::empty](containers/asc_std_set/set_empty.md) | asc/std/set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::end](containers/asc_std_set/set_end.md) | asc/std/set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::find](containers/asc_std_set/set_find.md) | asc/std/set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::insert](containers/asc_std_set/set_insert.md) | asc/std/set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::iterator](containers/asc_std_set/set_iterator.md) | asc/std/set | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::operator=](containers/asc_std_set/set_operator_assign.md) | asc/std/set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::set](containers/asc_std_set/set_set.md) | asc/std/set | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::size](containers/asc_std_set/set_size.md) | asc/std/set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::size_type](containers/asc_std_set/set_size_type.md) | asc/std/set | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::set::value_type](containers/asc_std_set/set_value_type.md) | asc/std/set | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock](concurrency/asc_std_shared_mutex/shared_lock.md) | asc/std/shared_mutex | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::lock](concurrency/asc_std_shared_mutex/shared_lock_lock.md) | asc/std/shared_mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::mutex](concurrency/asc_std_shared_mutex/shared_lock_mutex.md) | asc/std/shared_mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::mutex_type](concurrency/asc_std_shared_mutex/shared_lock_mutex_type.md) | asc/std/shared_mutex | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::operator=](concurrency/asc_std_shared_mutex/shared_lock_operator_assign.md) | asc/std/shared_mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::owns_lock](concurrency/asc_std_shared_mutex/shared_lock_owns_lock.md) | asc/std/shared_mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::release](concurrency/asc_std_shared_mutex/shared_lock_release.md) | asc/std/shared_mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::shared_lock](concurrency/asc_std_shared_mutex/shared_lock_shared_lock.md) | asc/std/shared_mutex | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::swap](concurrency/asc_std_shared_mutex/shared_lock_swap.md) | asc/std/shared_mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::try_lock](concurrency/asc_std_shared_mutex/shared_lock_try_lock.md) | asc/std/shared_mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::unlock](concurrency/asc_std_shared_mutex/shared_lock_unlock.md) | asc/std/shared_mutex | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::shared_lock::~shared_lock](concurrency/asc_std_shared_mutex/shared_lock_destructor_shared_lock.md) | asc/std/shared_mutex | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::source_location](language_support/asc_std_source_location/source_location.md) | asc/std/source_location | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::source_location::column](language_support/asc_std_source_location/source_location_column.md) | asc/std/source_location | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::source_location::current](language_support/asc_std_source_location/source_location_current.md) | asc/std/source_location | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::source_location::file_name](language_support/asc_std_source_location/source_location_file_name.md) | asc/std/source_location | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::source_location::function_name](language_support/asc_std_source_location/source_location_function_name.md) | asc/std/source_location | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::source_location::line](language_support/asc_std_source_location/source_location_line.md) | asc/std/source_location | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::source_location::source_location](language_support/asc_std_source_location/source_location_source_location.md) | asc/std/source_location | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::source_location::~source_location](language_support/asc_std_source_location/source_location_destructor_source_location.md) | asc/std/source_location | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::as_bytes](containers/asc_std_span/as_bytes.md) | asc/std/span | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::as_writable_bytes](containers/asc_std_span/as_writable_bytes.md) | asc/std/span | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::span](containers/asc_std_span/span.md) | asc/std/span | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack](containers/asc_std_stack/stack.md) | asc/std/stack | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::const_reference](containers/asc_std_stack/stack_const_reference.md) | asc/std/stack | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::container_type](containers/asc_std_stack/stack_container_type.md) | asc/std/stack | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::emplace](containers/asc_std_stack/stack_emplace.md) | asc/std/stack | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::empty](containers/asc_std_stack/stack_empty.md) | asc/std/stack | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::pop](containers/asc_std_stack/stack_pop.md) | asc/std/stack | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::push](containers/asc_std_stack/stack_push.md) | asc/std/stack | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::reference](containers/asc_std_stack/stack_reference.md) | asc/std/stack | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::size](containers/asc_std_stack/stack_size.md) | asc/std/stack | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::size_type](containers/asc_std_stack/stack_size_type.md) | asc/std/stack | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::stack](containers/asc_std_stack/stack_stack.md) | asc/std/stack | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::swap](containers/asc_std_stack/stack_swap.md) | asc/std/stack | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::top](containers/asc_std_stack/stack_top.md) | asc/std/stack | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::stack::value_type](containers/asc_std_stack/stack_value_type.md) | asc/std/stack | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string](strings/asc_std_string/basic_string.md) | asc/std/string | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::allocator_type](strings/asc_std_string/basic_string_allocator_type.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::append](strings/asc_std_string/basic_string_append.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::back](strings/asc_std_string/basic_string_back.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::basic_string](strings/asc_std_string/basic_string_basic_string.md) | asc/std/string | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::begin](strings/asc_std_string/basic_string_begin.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::c_str](strings/asc_std_string/basic_string_c_str.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::capacity](strings/asc_std_string/basic_string_capacity.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::clear](strings/asc_std_string/basic_string_clear.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::const_iterator](strings/asc_std_string/basic_string_const_iterator.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::const_pointer](strings/asc_std_string/basic_string_const_pointer.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::const_reference](strings/asc_std_string/basic_string_const_reference.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::data](strings/asc_std_string/basic_string_data.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::empty](strings/asc_std_string/basic_string_empty.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::end](strings/asc_std_string/basic_string_end.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::front](strings/asc_std_string/basic_string_front.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::get_allocator](strings/asc_std_string/basic_string_get_allocator.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::iterator](strings/asc_std_string/basic_string_iterator.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::length](strings/asc_std_string/basic_string_length.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::operator+=](strings/asc_std_string/basic_string_operator_plus_assign.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::operator\[\]](strings/asc_std_string/basic_string_operator_subscript.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::pointer](strings/asc_std_string/basic_string_pointer.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::push_back](strings/asc_std_string/basic_string_push_back.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::reference](strings/asc_std_string/basic_string_reference.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::reserve](strings/asc_std_string/basic_string_reserve.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::size](strings/asc_std_string/basic_string_size.md) | asc/std/string | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::size_type](strings/asc_std_string/basic_string_size_type.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::traits_type](strings/asc_std_string/basic_string_traits_type.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string::value_type](strings/asc_std_string/basic_string_value_type.md) | asc/std/string | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_string_view](strings/asc_std_string_view/basic_string_view.md) | asc/std/string_view | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::char_traits](strings/asc_std_string_view/char_traits.md) | asc/std/string_view | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::literals::string_view_literals](strings/asc_std_string_view/literals_string_view_literals.md) | asc/std/string_view | 命名空间 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator<（函数）](strings/asc_std_string_view/operator_less.md) | asc/std/string_view | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator<=（函数）](strings/asc_std_string_view/operator_less_equal.md) | asc/std/string_view | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator>（函数）](strings/asc_std_string_view/operator_greater.md) | asc/std/string_view | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::operator>=（函数）](strings/asc_std_string_view/operator_greater_equal.md) | asc/std/string_view | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::string_view](strings/asc_std_string_view/string_view.md) | asc/std/string_view | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::u16string_view](strings/asc_std_string_view/u16string_view.md) | asc/std/string_view | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::u32string_view](strings/asc_std_string_view/u32string_view.md) | asc/std/string_view | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::u8string_view](strings/asc_std_string_view/u8string_view.md) | asc/std/string_view | 类型别名 | C++20+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::wstring_view](strings/asc_std_string_view/wstring_view.md) | asc/std/string_view | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_error_code_enum](diagnostics/asc_std_system_error/is_error_code_enum.md) | asc/std/system_error | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_error_condition_enum](diagnostics/asc_std_system_error/is_error_condition_enum.md) | asc/std/system_error | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::apply](utilities/asc_std_tuple/apply.md) | asc/std/tuple | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_as_tuple](utilities/asc_std_tuple/forward_as_tuple.md) | asc/std/tuple | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::ignore](utilities/asc_std_tuple/ignore.md) | asc/std/tuple | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_from_tuple](utilities/asc_std_tuple/make_from_tuple.md) | asc/std/tuple | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_tuple](utilities/asc_std_tuple/make_tuple.md) | asc/std/tuple | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tie](utilities/asc_std_tuple/tie.md) | asc/std/tuple | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple](utilities/asc_std_tuple/tuple.md) | asc/std/tuple | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple::operator!=](utilities/asc_std_tuple/tuple_operator_not_equal.md) | asc/std/tuple | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple::operator<](utilities/asc_std_tuple/tuple_operator_less.md) | asc/std/tuple | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple::operator<=](utilities/asc_std_tuple/tuple_operator_less_equal.md) | asc/std/tuple | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple::operator=](utilities/asc_std_tuple/tuple_operator_assign.md) | asc/std/tuple | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple::operator==](utilities/asc_std_tuple/tuple_operator_equal.md) | asc/std/tuple | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple::operator>](utilities/asc_std_tuple/tuple_operator_greater.md) | asc/std/tuple | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple::operator>=](utilities/asc_std_tuple/tuple_operator_greater_equal.md) | asc/std/tuple | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple::swap](utilities/asc_std_tuple/tuple_swap.md) | asc/std/tuple | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple::tuple](utilities/asc_std_tuple/tuple_tuple.md) | asc/std/tuple | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple_cat（函数）](utilities/asc_std_tuple/tuple_cat_function.md) | asc/std/tuple | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple_cat（函数模板）](utilities/asc_std_tuple/tuple_cat_function_template.md) | asc/std/tuple | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple_element::type](utilities/asc_std_tuple/tuple_element_type.md) | asc/std/tuple | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple_element_t](utilities/asc_std_tuple/tuple_element_t.md) | asc/std/tuple | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::tuple_size_v](utilities/asc_std_tuple/tuple_size_v.md) | asc/std/tuple | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_const](metaprogramming/asc_std_type_traits/add_const.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_const::type](metaprogramming/asc_std_type_traits/add_const_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_const_t](metaprogramming/asc_std_type_traits/add_const_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_cv](metaprogramming/asc_std_type_traits/add_cv.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_cv::type](metaprogramming/asc_std_type_traits/add_cv_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_cv_t](metaprogramming/asc_std_type_traits/add_cv_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_lvalue_reference](metaprogramming/asc_std_type_traits/add_lvalue_reference.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_lvalue_reference::type](metaprogramming/asc_std_type_traits/add_lvalue_reference_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_lvalue_reference_t](metaprogramming/asc_std_type_traits/add_lvalue_reference_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_pointer](metaprogramming/asc_std_type_traits/add_pointer.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_pointer::type](metaprogramming/asc_std_type_traits/add_pointer_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_pointer_t](metaprogramming/asc_std_type_traits/add_pointer_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_rvalue_reference](metaprogramming/asc_std_type_traits/add_rvalue_reference.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_rvalue_reference::type](metaprogramming/asc_std_type_traits/add_rvalue_reference_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_rvalue_reference_t](metaprogramming/asc_std_type_traits/add_rvalue_reference_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_volatile](metaprogramming/asc_std_type_traits/add_volatile.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_volatile::type](metaprogramming/asc_std_type_traits/add_volatile_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::add_volatile_t](metaprogramming/asc_std_type_traits/add_volatile_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_storage](metaprogramming/asc_std_type_traits/aligned_storage.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_storage::type](metaprogramming/asc_std_type_traits/aligned_storage_type.md) | asc/std/type_traits | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_storage_t](metaprogramming/asc_std_type_traits/aligned_storage_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_union](metaprogramming/asc_std_type_traits/aligned_union.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_union::alignment_value](metaprogramming/asc_std_type_traits/aligned_union_alignment_value.md) | asc/std/type_traits | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_union::type](metaprogramming/asc_std_type_traits/aligned_union_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::aligned_union_t](metaprogramming/asc_std_type_traits/aligned_union_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::alignment_of](metaprogramming/asc_std_type_traits/alignment_of.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::alignment_of_v](metaprogramming/asc_std_type_traits/alignment_of_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::basic_common_reference](metaprogramming/asc_std_type_traits/basic_common_reference.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::bool_constant](metaprogramming/asc_std_type_traits/bool_constant.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_reference](metaprogramming/asc_std_type_traits/common_reference.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_reference::type](metaprogramming/asc_std_type_traits/common_reference_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_reference_t](metaprogramming/asc_std_type_traits/common_reference_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_type](metaprogramming/asc_std_type_traits/common_type.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::common_type_t](metaprogramming/asc_std_type_traits/common_type_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::conditional](metaprogramming/asc_std_type_traits/conditional.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::conditional::type](metaprogramming/asc_std_type_traits/conditional_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::conditional_t](metaprogramming/asc_std_type_traits/conditional_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::conjunction](metaprogramming/asc_std_type_traits/conjunction.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::conjunction_v](metaprogramming/asc_std_type_traits/conjunction_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::decay](metaprogramming/asc_std_type_traits/decay.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::decay::type](metaprogramming/asc_std_type_traits/decay_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::decay_t](metaprogramming/asc_std_type_traits/decay_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::disjunction](metaprogramming/asc_std_type_traits/disjunction.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::disjunction_v](metaprogramming/asc_std_type_traits/disjunction_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::enable_if](metaprogramming/asc_std_type_traits/enable_if.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::enable_if::type](metaprogramming/asc_std_type_traits/enable_if_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::enable_if_t](metaprogramming/asc_std_type_traits/enable_if_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extent](metaprogramming/asc_std_type_traits/extent.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::extent_v](metaprogramming/asc_std_type_traits/extent_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::false_type](metaprogramming/asc_std_type_traits/false_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::has_unique_object_representations](metaprogramming/asc_std_type_traits/has_unique_object_representations.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::has_unique_object_representations_v](metaprogramming/asc_std_type_traits/has_unique_object_representations_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::has_virtual_destructor](metaprogramming/asc_std_type_traits/has_virtual_destructor.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::has_virtual_destructor_v](metaprogramming/asc_std_type_traits/has_virtual_destructor_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::integral_constant](metaprogramming/asc_std_type_traits/integral_constant.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::integral_constant::operator()](metaprogramming/asc_std_type_traits/integral_constant_operator_call.md) | asc/std/type_traits | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::integral_constant::type](metaprogramming/asc_std_type_traits/integral_constant_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::integral_constant::value](metaprogramming/asc_std_type_traits/integral_constant_value.md) | asc/std/type_traits | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::integral_constant::value_type](metaprogramming/asc_std_type_traits/integral_constant_value_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::invoke_result](metaprogramming/asc_std_type_traits/invoke_result.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::invoke_result_t](metaprogramming/asc_std_type_traits/invoke_result_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_abstract](metaprogramming/asc_std_type_traits/is_abstract.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_abstract_v](metaprogramming/asc_std_type_traits/is_abstract_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_aggregate](metaprogramming/asc_std_type_traits/is_aggregate.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_aggregate_v](metaprogramming/asc_std_type_traits/is_aggregate_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_arithmetic](metaprogramming/asc_std_type_traits/is_arithmetic.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_arithmetic_v](metaprogramming/asc_std_type_traits/is_arithmetic_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_array](metaprogramming/asc_std_type_traits/is_array.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_array_v](metaprogramming/asc_std_type_traits/is_array_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_assignable](metaprogramming/asc_std_type_traits/is_assignable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_assignable_v](metaprogramming/asc_std_type_traits/is_assignable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_base_of](metaprogramming/asc_std_type_traits/is_base_of.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_base_of_v](metaprogramming/asc_std_type_traits/is_base_of_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_bounded_array](metaprogramming/asc_std_type_traits/is_bounded_array.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_bounded_array_v](metaprogramming/asc_std_type_traits/is_bounded_array_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_class](metaprogramming/asc_std_type_traits/is_class.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_class_v](metaprogramming/asc_std_type_traits/is_class_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_compound](metaprogramming/asc_std_type_traits/is_compound.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_compound_v](metaprogramming/asc_std_type_traits/is_compound_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_const](metaprogramming/asc_std_type_traits/is_const.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_const_v](metaprogramming/asc_std_type_traits/is_const_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_constant_evaluated](metaprogramming/asc_std_type_traits/is_constant_evaluated.md) | asc/std/type_traits | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_constructible](metaprogramming/asc_std_type_traits/is_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_constructible_v](metaprogramming/asc_std_type_traits/is_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_convertible](metaprogramming/asc_std_type_traits/is_convertible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_convertible_v](metaprogramming/asc_std_type_traits/is_convertible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_copy_assignable](metaprogramming/asc_std_type_traits/is_copy_assignable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_copy_assignable_v](metaprogramming/asc_std_type_traits/is_copy_assignable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_copy_constructible](metaprogramming/asc_std_type_traits/is_copy_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_copy_constructible_v](metaprogramming/asc_std_type_traits/is_copy_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_default_constructible](metaprogramming/asc_std_type_traits/is_default_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_default_constructible_v](metaprogramming/asc_std_type_traits/is_default_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_destructible](metaprogramming/asc_std_type_traits/is_destructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_destructible_v](metaprogramming/asc_std_type_traits/is_destructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_empty](metaprogramming/asc_std_type_traits/is_empty.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_empty_v](metaprogramming/asc_std_type_traits/is_empty_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_enum](metaprogramming/asc_std_type_traits/is_enum.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_enum_v](metaprogramming/asc_std_type_traits/is_enum_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_final](metaprogramming/asc_std_type_traits/is_final.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_final_v](metaprogramming/asc_std_type_traits/is_final_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_floating_point](metaprogramming/asc_std_type_traits/is_floating_point.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_floating_point_v](metaprogramming/asc_std_type_traits/is_floating_point_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_function](metaprogramming/asc_std_type_traits/is_function.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_function_v](metaprogramming/asc_std_type_traits/is_function_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_fundamental](metaprogramming/asc_std_type_traits/is_fundamental.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_fundamental_v](metaprogramming/asc_std_type_traits/is_fundamental_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_integral](metaprogramming/asc_std_type_traits/is_integral.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_integral_v](metaprogramming/asc_std_type_traits/is_integral_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_invocable](metaprogramming/asc_std_type_traits/is_invocable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_invocable_r](metaprogramming/asc_std_type_traits/is_invocable_r.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_invocable_r_v](metaprogramming/asc_std_type_traits/is_invocable_r_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_invocable_v](metaprogramming/asc_std_type_traits/is_invocable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_lvalue_reference](metaprogramming/asc_std_type_traits/is_lvalue_reference.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_lvalue_reference_v](metaprogramming/asc_std_type_traits/is_lvalue_reference_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_member_function_pointer](metaprogramming/asc_std_type_traits/is_member_function_pointer.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_member_function_pointer_v](metaprogramming/asc_std_type_traits/is_member_function_pointer_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_member_object_pointer](metaprogramming/asc_std_type_traits/is_member_object_pointer.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_member_object_pointer_v](metaprogramming/asc_std_type_traits/is_member_object_pointer_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_member_pointer](metaprogramming/asc_std_type_traits/is_member_pointer.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_member_pointer_v](metaprogramming/asc_std_type_traits/is_member_pointer_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_move_assignable](metaprogramming/asc_std_type_traits/is_move_assignable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_move_assignable_v](metaprogramming/asc_std_type_traits/is_move_assignable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_move_constructible](metaprogramming/asc_std_type_traits/is_move_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_move_constructible_v](metaprogramming/asc_std_type_traits/is_move_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_assignable](metaprogramming/asc_std_type_traits/is_nothrow_assignable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_assignable_v](metaprogramming/asc_std_type_traits/is_nothrow_assignable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_constructible](metaprogramming/asc_std_type_traits/is_nothrow_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_constructible_v](metaprogramming/asc_std_type_traits/is_nothrow_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_convertible](metaprogramming/asc_std_type_traits/is_nothrow_convertible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_convertible_v](metaprogramming/asc_std_type_traits/is_nothrow_convertible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_copy_assignable](metaprogramming/asc_std_type_traits/is_nothrow_copy_assignable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_copy_assignable_v](metaprogramming/asc_std_type_traits/is_nothrow_copy_assignable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_copy_constructible](metaprogramming/asc_std_type_traits/is_nothrow_copy_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_copy_constructible_v](metaprogramming/asc_std_type_traits/is_nothrow_copy_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_default_constructible](metaprogramming/asc_std_type_traits/is_nothrow_default_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_default_constructible_v](metaprogramming/asc_std_type_traits/is_nothrow_default_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_destructible](metaprogramming/asc_std_type_traits/is_nothrow_destructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_destructible_v](metaprogramming/asc_std_type_traits/is_nothrow_destructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_invocable](metaprogramming/asc_std_type_traits/is_nothrow_invocable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_invocable_r](metaprogramming/asc_std_type_traits/is_nothrow_invocable_r.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_invocable_r_v](metaprogramming/asc_std_type_traits/is_nothrow_invocable_r_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_invocable_v](metaprogramming/asc_std_type_traits/is_nothrow_invocable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_move_assignable](metaprogramming/asc_std_type_traits/is_nothrow_move_assignable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_move_assignable_v](metaprogramming/asc_std_type_traits/is_nothrow_move_assignable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_move_constructible](metaprogramming/asc_std_type_traits/is_nothrow_move_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_move_constructible_v](metaprogramming/asc_std_type_traits/is_nothrow_move_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_swappable](metaprogramming/asc_std_type_traits/is_nothrow_swappable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_swappable_v](metaprogramming/asc_std_type_traits/is_nothrow_swappable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_swappable_with](metaprogramming/asc_std_type_traits/is_nothrow_swappable_with.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_nothrow_swappable_with_v](metaprogramming/asc_std_type_traits/is_nothrow_swappable_with_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_null_pointer](metaprogramming/asc_std_type_traits/is_null_pointer.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_null_pointer_v](metaprogramming/asc_std_type_traits/is_null_pointer_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_object](metaprogramming/asc_std_type_traits/is_object.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_object_v](metaprogramming/asc_std_type_traits/is_object_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_pointer](metaprogramming/asc_std_type_traits/is_pointer.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_pointer_v](metaprogramming/asc_std_type_traits/is_pointer_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_polymorphic](metaprogramming/asc_std_type_traits/is_polymorphic.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_polymorphic_v](metaprogramming/asc_std_type_traits/is_polymorphic_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_reference](metaprogramming/asc_std_type_traits/is_reference.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_reference_v](metaprogramming/asc_std_type_traits/is_reference_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_rvalue_reference](metaprogramming/asc_std_type_traits/is_rvalue_reference.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_rvalue_reference_v](metaprogramming/asc_std_type_traits/is_rvalue_reference_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_same](metaprogramming/asc_std_type_traits/is_same.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_same_v](metaprogramming/asc_std_type_traits/is_same_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_scalar](metaprogramming/asc_std_type_traits/is_scalar.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_scalar_v](metaprogramming/asc_std_type_traits/is_scalar_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_scoped_enum](metaprogramming/asc_std_type_traits/is_scoped_enum.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_scoped_enum_v](metaprogramming/asc_std_type_traits/is_scoped_enum_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_signed](metaprogramming/asc_std_type_traits/is_signed.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_signed_v](metaprogramming/asc_std_type_traits/is_signed_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_standard_layout](metaprogramming/asc_std_type_traits/is_standard_layout.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_standard_layout_v](metaprogramming/asc_std_type_traits/is_standard_layout_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_swappable](metaprogramming/asc_std_type_traits/is_swappable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_swappable_v](metaprogramming/asc_std_type_traits/is_swappable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_swappable_with](metaprogramming/asc_std_type_traits/is_swappable_with.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_swappable_with_v](metaprogramming/asc_std_type_traits/is_swappable_with_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivial](metaprogramming/asc_std_type_traits/is_trivial.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivial_v](metaprogramming/asc_std_type_traits/is_trivial_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_assignable](metaprogramming/asc_std_type_traits/is_trivially_assignable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_assignable_v](metaprogramming/asc_std_type_traits/is_trivially_assignable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_constructible](metaprogramming/asc_std_type_traits/is_trivially_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_constructible_v](metaprogramming/asc_std_type_traits/is_trivially_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_copy_assignable](metaprogramming/asc_std_type_traits/is_trivially_copy_assignable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_copy_assignable_v](metaprogramming/asc_std_type_traits/is_trivially_copy_assignable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_copy_constructible](metaprogramming/asc_std_type_traits/is_trivially_copy_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_copy_constructible_v](metaprogramming/asc_std_type_traits/is_trivially_copy_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_copyable](metaprogramming/asc_std_type_traits/is_trivially_copyable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_copyable_v](metaprogramming/asc_std_type_traits/is_trivially_copyable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_default_constructible](metaprogramming/asc_std_type_traits/is_trivially_default_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_default_constructible_v](metaprogramming/asc_std_type_traits/is_trivially_default_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_destructible](metaprogramming/asc_std_type_traits/is_trivially_destructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_destructible_v](metaprogramming/asc_std_type_traits/is_trivially_destructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_move_assignable](metaprogramming/asc_std_type_traits/is_trivially_move_assignable.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_move_assignable_v](metaprogramming/asc_std_type_traits/is_trivially_move_assignable_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_move_constructible](metaprogramming/asc_std_type_traits/is_trivially_move_constructible.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_trivially_move_constructible_v](metaprogramming/asc_std_type_traits/is_trivially_move_constructible_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_unbounded_array](metaprogramming/asc_std_type_traits/is_unbounded_array.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_unbounded_array_v](metaprogramming/asc_std_type_traits/is_unbounded_array_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_union](metaprogramming/asc_std_type_traits/is_union.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_union_v](metaprogramming/asc_std_type_traits/is_union_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_unsigned](metaprogramming/asc_std_type_traits/is_unsigned.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_unsigned_v](metaprogramming/asc_std_type_traits/is_unsigned_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_void](metaprogramming/asc_std_type_traits/is_void.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_void_v](metaprogramming/asc_std_type_traits/is_void_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_volatile](metaprogramming/asc_std_type_traits/is_volatile.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_volatile_v](metaprogramming/asc_std_type_traits/is_volatile_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_signed](metaprogramming/asc_std_type_traits/make_signed.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_signed::type](metaprogramming/asc_std_type_traits/make_signed_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_signed_t](metaprogramming/asc_std_type_traits/make_signed_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_unsigned](metaprogramming/asc_std_type_traits/make_unsigned.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_unsigned::type](metaprogramming/asc_std_type_traits/make_unsigned_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_unsigned_t](metaprogramming/asc_std_type_traits/make_unsigned_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::negation](metaprogramming/asc_std_type_traits/negation.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::negation_v](metaprogramming/asc_std_type_traits/negation_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rank](metaprogramming/asc_std_type_traits/rank.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::rank_v](metaprogramming/asc_std_type_traits/rank_v.md) | asc/std/type_traits | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_all_extents](metaprogramming/asc_std_type_traits/remove_all_extents.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_all_extents::type](metaprogramming/asc_std_type_traits/remove_all_extents_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_all_extents_t](metaprogramming/asc_std_type_traits/remove_all_extents_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_const](metaprogramming/asc_std_type_traits/remove_const.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_const::type](metaprogramming/asc_std_type_traits/remove_const_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_const_t](metaprogramming/asc_std_type_traits/remove_const_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_cv](metaprogramming/asc_std_type_traits/remove_cv.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_cv::type](metaprogramming/asc_std_type_traits/remove_cv_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_cv_t](metaprogramming/asc_std_type_traits/remove_cv_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_cvref](metaprogramming/asc_std_type_traits/remove_cvref.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_cvref::type](metaprogramming/asc_std_type_traits/remove_cvref_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_cvref_t](metaprogramming/asc_std_type_traits/remove_cvref_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_extent](metaprogramming/asc_std_type_traits/remove_extent.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_extent::type](metaprogramming/asc_std_type_traits/remove_extent_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_extent_t](metaprogramming/asc_std_type_traits/remove_extent_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_pointer](metaprogramming/asc_std_type_traits/remove_pointer.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_pointer::type](metaprogramming/asc_std_type_traits/remove_pointer_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_pointer_t](metaprogramming/asc_std_type_traits/remove_pointer_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_reference](metaprogramming/asc_std_type_traits/remove_reference.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_reference::type](metaprogramming/asc_std_type_traits/remove_reference_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_reference_t](metaprogramming/asc_std_type_traits/remove_reference_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_volatile](metaprogramming/asc_std_type_traits/remove_volatile.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_volatile::type](metaprogramming/asc_std_type_traits/remove_volatile_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::remove_volatile_t](metaprogramming/asc_std_type_traits/remove_volatile_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::true_type](metaprogramming/asc_std_type_traits/true_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::type_identity](metaprogramming/asc_std_type_traits/type_identity.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::type_identity::type](metaprogramming/asc_std_type_traits/type_identity_type.md) | asc/std/type_traits | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::type_identity_t](metaprogramming/asc_std_type_traits/type_identity_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::underlying_type](metaprogramming/asc_std_type_traits/underlying_type.md) | asc/std/type_traits | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::underlying_type_t](metaprogramming/asc_std_type_traits/underlying_type_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::void_t](metaprogramming/asc_std_type_traits/void_t.md) | asc/std/type_traits | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map](containers/asc_std_unordered_map/unordered_map.md) | asc/std/unordered_map | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::begin](containers/asc_std_unordered_map/unordered_map_begin.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::bucket_count](containers/asc_std_unordered_map/unordered_map_bucket_count.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::clear](containers/asc_std_unordered_map/unordered_map_clear.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::count](containers/asc_std_unordered_map/unordered_map_count.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::empty](containers/asc_std_unordered_map/unordered_map_empty.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::end](containers/asc_std_unordered_map/unordered_map_end.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::find](containers/asc_std_unordered_map/unordered_map_find.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::insert](containers/asc_std_unordered_map/unordered_map_insert.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::iterator](containers/asc_std_unordered_map/unordered_map_iterator.md) | asc/std/unordered_map | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::operator=](containers/asc_std_unordered_map/unordered_map_operator_assign.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::operator\[\]](containers/asc_std_unordered_map/unordered_map_operator_subscript.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::size](containers/asc_std_unordered_map/unordered_map_size.md) | asc/std/unordered_map | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::size_type](containers/asc_std_unordered_map/unordered_map_size_type.md) | asc/std/unordered_map | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::unordered_map](containers/asc_std_unordered_map/unordered_map_unordered_map.md) | asc/std/unordered_map | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_map::value_type](containers/asc_std_unordered_map/unordered_map_value_type.md) | asc/std/unordered_map | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set](containers/asc_std_unordered_set/unordered_set.md) | asc/std/unordered_set | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::begin](containers/asc_std_unordered_set/unordered_set_begin.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::bucket_count](containers/asc_std_unordered_set/unordered_set_bucket_count.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::clear](containers/asc_std_unordered_set/unordered_set_clear.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::count](containers/asc_std_unordered_set/unordered_set_count.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::empty](containers/asc_std_unordered_set/unordered_set_empty.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::end](containers/asc_std_unordered_set/unordered_set_end.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::find](containers/asc_std_unordered_set/unordered_set_find.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::insert](containers/asc_std_unordered_set/unordered_set_insert.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::iterator](containers/asc_std_unordered_set/unordered_set_iterator.md) | asc/std/unordered_set | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::operator=](containers/asc_std_unordered_set/unordered_set_operator_assign.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::size](containers/asc_std_unordered_set/unordered_set_size.md) | asc/std/unordered_set | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::size_type](containers/asc_std_unordered_set/unordered_set_size_type.md) | asc/std/unordered_set | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unordered_set::unordered_set](containers/asc_std_unordered_set/unordered_set_unordered_set.md) | asc/std/unordered_set | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::as_const](utilities/asc_std_utility/as_const.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cmp_equal](utilities/asc_std_utility/cmp_equal.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cmp_greater](utilities/asc_std_utility/cmp_greater.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cmp_greater_equal](utilities/asc_std_utility/cmp_greater_equal.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cmp_less](utilities/asc_std_utility/cmp_less.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cmp_less_equal](utilities/asc_std_utility/cmp_less_equal.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::cmp_not_equal](utilities/asc_std_utility/cmp_not_equal.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::declval](utilities/asc_std_utility/declval.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::exchange](utilities/asc_std_utility/exchange.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward](utilities/asc_std_utility/forward.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::forward_like](utilities/asc_std_utility/forward_like.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_place](utilities/asc_std_utility/in_place.md) | asc/std/utility | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_place_index](utilities/asc_std_utility/in_place_index.md) | asc/std/utility | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_place_index_t](utilities/asc_std_utility/in_place_index_t.md) | asc/std/utility | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_place_index_t::in_place_index_t](utilities/asc_std_utility/in_place_index_t_in_place_index_t.md) | asc/std/utility | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_place_t](utilities/asc_std_utility/in_place_t.md) | asc/std/utility | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_place_t::in_place_t](utilities/asc_std_utility/in_place_t_in_place_t.md) | asc/std/utility | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_place_type](utilities/asc_std_utility/in_place_type.md) | asc/std/utility | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_place_type_t](utilities/asc_std_utility/in_place_type_t.md) | asc/std/utility | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_place_type_t::in_place_type_t](utilities/asc_std_utility/in_place_type_t_in_place_type_t.md) | asc/std/utility | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::in_range](utilities/asc_std_utility/in_range.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::index_sequence](utilities/asc_std_utility/index_sequence.md) | asc/std/utility | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::index_sequence_for](utilities/asc_std_utility/index_sequence_for.md) | asc/std/utility | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::integer_sequence](utilities/asc_std_utility/integer_sequence.md) | asc/std/utility | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::integer_sequence::size](utilities/asc_std_utility/integer_sequence_size.md) | asc/std/utility | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::integer_sequence::value_type](utilities/asc_std_utility/integer_sequence_value_type.md) | asc/std/utility | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_index_sequence](utilities/asc_std_utility/make_index_sequence.md) | asc/std/utility | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_integer_sequence](utilities/asc_std_utility/make_integer_sequence.md) | asc/std/utility | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_pair](utilities/asc_std_utility/make_pair.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::move_if_noexcept](utilities/asc_std_utility/move_if_noexcept.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pair](utilities/asc_std_utility/pair.md) | asc/std/utility | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pair::first_type](utilities/asc_std_utility/pair_first_type.md) | asc/std/utility | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pair::operator=](utilities/asc_std_utility/pair_operator_assign.md) | asc/std/utility | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pair::pair](utilities/asc_std_utility/pair_pair.md) | asc/std/utility | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pair::second_type](utilities/asc_std_utility/pair_second_type.md) | asc/std/utility | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pair::swap](utilities/asc_std_utility/pair_swap.md) | asc/std/utility | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::piecewise_construct](utilities/asc_std_utility/piecewise_construct.md) | asc/std/utility | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::piecewise_construct_t](utilities/asc_std_utility/piecewise_construct_t.md) | asc/std/utility | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::piecewise_construct_t::piecewise_construct_t](utilities/asc_std_utility/piecewise_construct_t_piecewise_construct_t.md) | asc/std/utility | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::piecewise_construct_t::~piecewise_construct_t](utilities/asc_std_utility/piecewise_construct_t_destructor_piecewise_construct_t.md) | asc/std/utility | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::to_underlying](utilities/asc_std_utility/to_underlying.md) | asc/std/utility | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::unreachable](utilities/asc_std_utility/unreachable.md) | asc/std/utility | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::get_if](utilities/asc_std_variant/get_if.md) | asc/std/variant | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::holds_alternative](utilities/asc_std_variant/holds_alternative.md) | asc/std/variant | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::monostate](utilities/asc_std_variant/monostate.md) | asc/std/variant | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant](utilities/asc_std_variant/variant.md) | asc/std/variant | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant::emplace](utilities/asc_std_variant/variant_emplace.md) | asc/std/variant | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant::index](utilities/asc_std_variant/variant_index.md) | asc/std/variant | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant::operator=](utilities/asc_std_variant/variant_operator_assign.md) | asc/std/variant | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant::swap](utilities/asc_std_variant/variant_swap.md) | asc/std/variant | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant::valueless_by_exception](utilities/asc_std_variant/variant_valueless_by_exception.md) | asc/std/variant | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant::variant](utilities/asc_std_variant/variant_variant.md) | asc/std/variant | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant::~variant](utilities/asc_std_variant/variant_destructor_variant.md) | asc/std/variant | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant_alternative](utilities/asc_std_variant/variant_alternative.md) | asc/std/variant | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant_alternative::type](utilities/asc_std_variant/variant_alternative_type.md) | asc/std/variant | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant_alternative_t](utilities/asc_std_variant/variant_alternative_t.md) | asc/std/variant | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant_npos](utilities/asc_std_variant/variant_npos.md) | asc/std/variant | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant_size](utilities/asc_std_variant/variant_size.md) | asc/std/variant | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::variant_size_v](utilities/asc_std_variant/variant_size_v.md) | asc/std/variant | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::visit](utilities/asc_std_variant/visit.md) | asc/std/variant | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector](containers/asc_std_vector/vector.md) | asc/std/vector | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::allocator_type](containers/asc_std_vector/vector_allocator_type.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::back](containers/asc_std_vector/vector_back.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::begin](containers/asc_std_vector/vector_begin.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::capacity](containers/asc_std_vector/vector_capacity.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::clear](containers/asc_std_vector/vector_clear.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::const_iterator](containers/asc_std_vector/vector_const_iterator.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::const_pointer](containers/asc_std_vector/vector_const_pointer.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::const_reference](containers/asc_std_vector/vector_const_reference.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::data](containers/asc_std_vector/vector_data.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::difference_type](containers/asc_std_vector/vector_difference_type.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::emplace_back](containers/asc_std_vector/vector_emplace_back.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::empty](containers/asc_std_vector/vector_empty.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::end](containers/asc_std_vector/vector_end.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::front](containers/asc_std_vector/vector_front.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::get_allocator](containers/asc_std_vector/vector_get_allocator.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::iterator](containers/asc_std_vector/vector_iterator.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::operator=](containers/asc_std_vector/vector_operator_assign.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::operator\[\]](containers/asc_std_vector/vector_operator_subscript.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::pointer](containers/asc_std_vector/vector_pointer.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::pop_back](containers/asc_std_vector/vector_pop_back.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::push_back](containers/asc_std_vector/vector_push_back.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::reference](containers/asc_std_vector/vector_reference.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::reserve](containers/asc_std_vector/vector_reserve.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::size](containers/asc_std_vector/vector_size.md) | asc/std/vector | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::size_type](containers/asc_std_vector/vector_size_type.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::value_type](containers/asc_std_vector/vector_value_type.md) | asc/std/vector | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::vector](containers/asc_std_vector/vector_vector.md) | asc/std/vector | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::vector::~vector](containers/asc_std_vector/vector_destructor_vector.md) | asc/std/vector | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
