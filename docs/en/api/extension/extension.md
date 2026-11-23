# Ascend Extension Interfaces

The Ascend extension interfaces provide capabilities such as address spaces, the AI Core execution hierarchy, thread cooperation, and device-side parallel algorithms.

## Category Overview

| Category | Description |
| --- | --- |
| [Device Atomics and Thread Synchronization](device_atomics_and_sync/device_atomics_and_sync.md) | Device-side atomics, barriers, and thread synchronization. |
| [Asynchronous Data Transfer Pipeline](async_data_pipeline/async_data_pipeline.md) | Asynchronous transfers and their completion state management. |
| [Address Spaces and Memory Views](address_spaces_and_memory_views/address_spaces_and_memory_views.md) | Device memory address spaces, non-owning views, and allocation helpers. |
| [Multidimensional Views and Transfer](multidimensional_views_and_transfer/multidimensional_views_and_transfer.md) | Multidimensional indexing, data views, and tensor transfer. |
| [Device Execution Hierarchy, Collective Operations, and Dynamic Work Acquisition](execution_hierarchy_and_collectives/execution_hierarchy_and_collectives.md) | Thread-hierarchy queries, collective operations, and work acquisition. |
| [Device-Side Parallel Algorithms and Argument Wrappers](device_parallel_algorithms_and_arguments/device_parallel_algorithms_and_arguments.md) | Asynchronous parallel algorithms and their execution arguments. |
| [Algorithm Function Objects, Operation Properties, and Iterator Adaptors](function_objects_and_iterators/function_objects_and_iterators.md) | Algorithm callable objects, operation properties, and iterator adaptors. |
| [Bit Operations, Math and Numeric Computation, Pseudorandom Numbers](bit_math_numeric_random/bit_math_numeric_random.md) | Bit operations, math helpers, numeric computation, and random numbers. |
| [Type Traits, Utilities and Version Detection](type_traits_and_utilities/type_traits_and_utilities.md) | Extended type traits, utilities, and version detection. |

## API Support List

| API | Header | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- | --- |
| [asc::copy_bytes](device_parallel_algorithms_and_arguments/asc_algorithm/copy_bytes.md) | asc/algorithm | Function | C++17+ | Host | Ascend 950 |
| [asc::fill_bytes](device_parallel_algorithms_and_arguments/asc_algorithm/fill_bytes.md) | asc/algorithm | Function | C++17+ | Host | Ascend 950 |
| [asc::parallel::adjacent_difference](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_adjacent_difference.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::adjacent_find](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_adjacent_find.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::all_of](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_all_of.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::any_of](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_any_of.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::copy](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_copy.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::copy_if](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_copy_if.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::copy_n](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_copy_n.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::count](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_count.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::count_if](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_count_if.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::equal](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_equal.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::exclusive_scan](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_exclusive_scan.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::fill](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_fill.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::fill_n](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_fill_n.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::find](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_find.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::find_if](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_find_if.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::find_if_not](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_find_if_not.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::for_each](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_for_each.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::for_each_n](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_for_each_n.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::generate](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_generate.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::generate_n](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_generate_n.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::inclusive_scan](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_inclusive_scan.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_heap](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_is_heap.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_heap_until](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_is_heap_until.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_partitioned](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_is_partitioned.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_sorted](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_is_sorted.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::is_sorted_until](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_is_sorted_until.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::max_element](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_max_element.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::merge](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_merge.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::min_element](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_min_element.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::mismatch](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_mismatch.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::none_of](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_none_of.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::partition](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_partition.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::partition_copy](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_partition_copy.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::reduce](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_reduce.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_remove.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove_copy](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_remove_copy.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove_copy_if](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_remove_copy_if.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::remove_if](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_remove_if.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_replace.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace_copy](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_replace_copy.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace_copy_if](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_replace_copy_if.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::replace_if](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_replace_if.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::reverse](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_reverse.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::reverse_copy](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_reverse_copy.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::rotate](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_rotate.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::rotate_copy](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_rotate_copy.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::shift_left](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_shift_left.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::shift_right](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_shift_right.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::sort](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_sort.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::stable_partition](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_stable_partition.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::swap_ranges](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_swap_ranges.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_transform.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform_exclusive_scan](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_transform_exclusive_scan.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform_inclusive_scan](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_transform_inclusive_scan.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::transform_reduce](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_transform_reduce.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::unique](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_unique.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::parallel::unique_copy](device_parallel_algorithms_and_arguments/asc_algorithm/parallel_unique_copy.md) | asc/algorithm | Function template | C++17+ | Host | Ascend 950 |
| [asc::args::bounds](device_parallel_algorithms_and_arguments/asc_argument/args_bounds.md) | asc/argument | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::constant](device_parallel_algorithms_and_arguments/asc_argument/args_constant.md) | asc/argument | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::constant::value](device_parallel_algorithms_and_arguments/asc_argument/args_constant_value.md) | asc/argument | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::deferred](device_parallel_algorithms_and_arguments/asc_argument/args_deferred.md) | asc/argument | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::deferred::data](device_parallel_algorithms_and_arguments/asc_argument/args_deferred_data.md) | asc/argument | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::deferred::deferred](device_parallel_algorithms_and_arguments/asc_argument/args_deferred_deferred.md) | asc/argument | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::deferred_sequence](device_parallel_algorithms_and_arguments/asc_argument/args_deferred_sequence.md) | asc/argument | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::deferred_sequence::data](device_parallel_algorithms_and_arguments/asc_argument/args_deferred_sequence_data.md) | asc/argument | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::deferred_sequence::deferred_sequence](device_parallel_algorithms_and_arguments/asc_argument/args_deferred_sequence_deferred_sequence.md) | asc/argument | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::deferred_sequence::size](device_parallel_algorithms_and_arguments/asc_argument/args_deferred_sequence_size.md) | asc/argument | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::immediate](device_parallel_algorithms_and_arguments/asc_argument/args_immediate.md) | asc/argument | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::immediate::immediate](device_parallel_algorithms_and_arguments/asc_argument/args_immediate_immediate.md) | asc/argument | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::immediate::value](device_parallel_algorithms_and_arguments/asc_argument/args_immediate_value.md) | asc/argument | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::no_bounds](device_parallel_algorithms_and_arguments/asc_argument/args_no_bounds.md) | asc/argument | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::runtime_bounds](device_parallel_algorithms_and_arguments/asc_argument/args_runtime_bounds.md) | asc/argument | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::runtime_bounds::lower](device_parallel_algorithms_and_arguments/asc_argument/args_runtime_bounds_lower.md) | asc/argument | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::runtime_bounds::runtime_bounds](device_parallel_algorithms_and_arguments/asc_argument/args_runtime_bounds_runtime_bounds.md) | asc/argument | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::runtime_bounds::upper](device_parallel_algorithms_and_arguments/asc_argument/args_runtime_bounds_upper.md) | asc/argument | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::static_bounds](device_parallel_algorithms_and_arguments/asc_argument/args_static_bounds.md) | asc/argument | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::static_bounds::lower](device_parallel_algorithms_and_arguments/asc_argument/args_static_bounds_lower.md) | asc/argument | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::args::static_bounds::upper](device_parallel_algorithms_and_arguments/asc_argument/args_static_bounds_upper.md) | asc/argument | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::atomic](device_atomics_and_sync/asc_atomic/atomic.md) | asc/atomic | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::atomic](device_atomics_and_sync/asc_atomic/atomic_atomic.md) | asc/atomic | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::compare_exchange_strong](device_atomics_and_sync/asc_atomic/atomic_compare_exchange_strong.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::exchange](device_atomics_and_sync/asc_atomic/atomic_exchange.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_add](device_atomics_and_sync/asc_atomic/atomic_fetch_add.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_and](device_atomics_and_sync/asc_atomic/atomic_fetch_and.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_max](device_atomics_and_sync/asc_atomic/atomic_fetch_max.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_min](device_atomics_and_sync/asc_atomic/atomic_fetch_min.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_or](device_atomics_and_sync/asc_atomic/atomic_fetch_or.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_sub](device_atomics_and_sync/asc_atomic/atomic_fetch_sub.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_xor](device_atomics_and_sync/asc_atomic/atomic_fetch_xor.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::load](device_atomics_and_sync/asc_atomic/atomic_load.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::store](device_atomics_and_sync/asc_atomic/atomic_store.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref](device_atomics_and_sync/asc_atomic/atomic_ref.md) | asc/atomic | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::atomic_ref](device_atomics_and_sync/asc_atomic/atomic_ref_atomic_ref.md) | asc/atomic | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::compare_exchange_strong](device_atomics_and_sync/asc_atomic/atomic_ref_compare_exchange_strong.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::exchange](device_atomics_and_sync/asc_atomic/atomic_ref_exchange.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_add](device_atomics_and_sync/asc_atomic/atomic_ref_fetch_add.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_and](device_atomics_and_sync/asc_atomic/atomic_ref_fetch_and.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_max](device_atomics_and_sync/asc_atomic/atomic_ref_fetch_max.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_min](device_atomics_and_sync/asc_atomic/atomic_ref_fetch_min.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_or](device_atomics_and_sync/asc_atomic/atomic_ref_fetch_or.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_sub](device_atomics_and_sync/asc_atomic/atomic_ref_fetch_sub.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_xor](device_atomics_and_sync/asc_atomic/atomic_ref_fetch_xor.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::load](device_atomics_and_sync/asc_atomic/atomic_ref_load.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::store](device_atomics_and_sync/asc_atomic/atomic_ref_store.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_thread_fence](device_atomics_and_sync/asc_atomic/atomic_thread_fence.md) | asc/atomic | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::memory_scope](device_atomics_and_sync/asc_atomic/memory_scope.md) | asc/atomic | Enum | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::memory_scope::block](device_atomics_and_sync/asc_atomic/memory_scope_block.md) | asc/atomic | Enumerator | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::memory_scope::device](device_atomics_and_sync/asc_atomic/memory_scope_device.md) | asc/atomic | Enumerator | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref](device_atomics_and_sync/asc_atomic/relaxed_atomic_ref.md) | asc/atomic | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::compare_exchange_strong](device_atomics_and_sync/asc_atomic/relaxed_atomic_ref_compare_exchange_strong.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::exchange](device_atomics_and_sync/asc_atomic/relaxed_atomic_ref_exchange.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::fetch_add](device_atomics_and_sync/asc_atomic/relaxed_atomic_ref_fetch_add.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::fetch_sub](device_atomics_and_sync/asc_atomic/relaxed_atomic_ref_fetch_sub.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::load](device_atomics_and_sync/asc_atomic/relaxed_atomic_ref_load.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::relaxed_atomic_ref](device_atomics_and_sync/asc_atomic/relaxed_atomic_ref_relaxed_atomic_ref.md) | asc/atomic | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::store](device_atomics_and_sync/asc_atomic/relaxed_atomic_ref_store.md) | asc/atomic | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::barrier](device_atomics_and_sync/asc_barrier/barrier.md) | asc/barrier | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::barrier::arrive](device_atomics_and_sync/asc_barrier/barrier_arrive.md) | asc/barrier | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::barrier::arrive_and_drop](device_atomics_and_sync/asc_barrier/barrier_arrive_and_drop.md) | asc/barrier | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::barrier::arrive_and_wait](device_atomics_and_sync/asc_barrier/barrier_arrive_and_wait.md) | asc/barrier | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::barrier::barrier](device_atomics_and_sync/asc_barrier/barrier_barrier.md) | asc/barrier | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::barrier::max](device_atomics_and_sync/asc_barrier/barrier_max.md) | asc/barrier | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::barrier::wait](device_atomics_and_sync/asc_barrier/barrier_wait.md) | asc/barrier | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::barrier_arrival_token](device_atomics_and_sync/asc_barrier/barrier_arrival_token.md) | asc/barrier | Class | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::init](device_atomics_and_sync/asc_barrier/init.md) | asc/barrier | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::bit_reverse](bit_math_numeric_random/asc_bit/bit_reverse.md) | asc/bit | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::bitfield_extract](bit_math_numeric_random/asc_bit/bitfield_extract.md) | asc/bit | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::bitfield_insert](bit_math_numeric_random/asc_bit/bitfield_insert.md) | asc/bit | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::bitmask](bit_math_numeric_random/asc_bit/bitmask.md) | asc/bit | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::ceil_div](bit_math_numeric_random/asc_cmath/ceil_div.md) | asc/cmath | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::floor_div](bit_math_numeric_random/asc_cmath/floor_div.md) | asc/cmath | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::integer_log2](bit_math_numeric_random/asc_cmath/integer_log2.md) | asc/cmath | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::integer_pow](bit_math_numeric_random/asc_cmath/integer_pow.md) | asc/cmath | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::integer_sqrt](bit_math_numeric_random/asc_cmath/integer_sqrt.md) | asc/cmath | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::mul_hi](bit_math_numeric_random/asc_cmath/mul_hi.md) | asc/cmath | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::round_up](bit_math_numeric_random/asc_cmath/round_up.md) | asc/cmath | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::sincos](bit_math_numeric_random/asc_cmath/sincos.md) | asc/cmath | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::block_all](execution_hierarchy_and_collectives/asc_collectives/block_all.md) | asc/collectives | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_any](execution_hierarchy_and_collectives/asc_collectives/block_any.md) | asc/collectives | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_broadcast](execution_hierarchy_and_collectives/asc_collectives/block_broadcast.md) | asc/collectives | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_collective_workspace](execution_hierarchy_and_collectives/asc_collectives/block_collective_workspace.md) | asc/collectives | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_collective_workspace::size](execution_hierarchy_and_collectives/asc_collectives/block_collective_workspace_size.md) | asc/collectives | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_collective_workspace_bytes](execution_hierarchy_and_collectives/asc_collectives/block_collective_workspace_bytes.md) | asc/collectives | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_exclusive_scan](execution_hierarchy_and_collectives/asc_collectives/block_exclusive_scan.md) | asc/collectives | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_inclusive_scan](execution_hierarchy_and_collectives/asc_collectives/block_inclusive_scan.md) | asc/collectives | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_reduce_add](execution_hierarchy_and_collectives/asc_collectives/block_reduce_add.md) | asc/collectives | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_reduce_max](execution_hierarchy_and_collectives/asc_collectives/block_reduce_max.md) | asc/collectives | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_reduce_min](execution_hierarchy_and_collectives/asc_collectives/block_reduce_min.md) | asc/collectives | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::make_block_collective_workspace](execution_hierarchy_and_collectives/asc_collectives/make_block_collective_workspace.md) | asc/collectives | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::ub_exclusive_scan](execution_hierarchy_and_collectives/asc_collectives/ub_exclusive_scan.md) | asc/collectives | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::ub_inclusive_scan](execution_hierarchy_and_collectives/asc_collectives/ub_inclusive_scan.md) | asc/collectives | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::ub_reduce_add](execution_hierarchy_and_collectives/asc_collectives/ub_reduce_add.md) | asc/collectives | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::ub_reduce_max](execution_hierarchy_and_collectives/asc_collectives/ub_reduce_max.md) | asc/collectives | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::ub_reduce_min](execution_hierarchy_and_collectives/asc_collectives/ub_reduce_min.md) | asc/collectives | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::absorbing_element](function_objects_and_iterators/asc_functional/absorbing_element.md) | asc/functional | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::always_false](function_objects_and_iterators/asc_functional/always_false.md) | asc/functional | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::always_false::`operator()`](function_objects_and_iterators/asc_functional/always_false_operator_call.md) | asc/functional | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::always_true](function_objects_and_iterators/asc_functional/always_true.md) | asc/functional | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::always_true::`operator()`](function_objects_and_iterators/asc_functional/always_true_operator_call.md) | asc/functional | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::equal_to_value](function_objects_and_iterators/asc_functional/equal_to_value.md) | asc/functional | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::equal_to_value::equal_to_value](function_objects_and_iterators/asc_functional/equal_to_value_equal_to_value.md) | asc/functional | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::equal_to_value::`operator()`](function_objects_and_iterators/asc_functional/equal_to_value_operator_call.md) | asc/functional | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::has_absorbing_element_v](function_objects_and_iterators/asc_functional/has_absorbing_element_v.md) | asc/functional | Variable template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::has_identity_element_v](function_objects_and_iterators/asc_functional/has_identity_element_v.md) | asc/functional | Variable template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::identity_element](function_objects_and_iterators/asc_functional/identity_element.md) | asc/functional | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::is_associative_v](function_objects_and_iterators/asc_functional/is_associative_v.md) | asc/functional | Variable template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::is_commutative_v](function_objects_and_iterators/asc_functional/is_commutative_v.md) | asc/functional | Variable template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::maximum](function_objects_and_iterators/asc_functional/maximum.md) | asc/functional | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::maximum::`operator()`](function_objects_and_iterators/asc_functional/maximum_operator_call.md) | asc/functional | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::minimum](function_objects_and_iterators/asc_functional/minimum.md) | asc/functional | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::minimum::`operator()`](function_objects_and_iterators/asc_functional/minimum_operator_call.md) | asc/functional | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block](execution_hierarchy_and_collectives/asc_hierarchy/block.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_count](execution_hierarchy_and_collectives/asc_hierarchy/block_count.md) | asc/hierarchy | Function | C++17+ | AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_dims (Function)](execution_hierarchy_and_collectives/asc_hierarchy/block_dims_function.md) | asc/hierarchy | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_dims (Function template)](execution_hierarchy_and_collectives/asc_hierarchy/block_dims_function_template.md) | asc/hierarchy | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_extents_3d](execution_hierarchy_and_collectives/asc_hierarchy/block_extents_3d.md) | asc/hierarchy | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_index](execution_hierarchy_and_collectives/asc_hierarchy/block_index.md) | asc/hierarchy | Function | C++17+ | AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::block_index_3d](execution_hierarchy_and_collectives/asc_hierarchy/block_index_3d.md) | asc/hierarchy | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_level](execution_hierarchy_and_collectives/asc_hierarchy/block_level.md) | asc/hierarchy | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d](execution_hierarchy_and_collectives/asc_hierarchy/extent3d.md) | asc/hierarchy | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::count](execution_hierarchy_and_collectives/asc_hierarchy/extent3d_count.md) | asc/hierarchy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::extent3d](execution_hierarchy_and_collectives/asc_hierarchy/extent3d_extent3d.md) | asc/hierarchy | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::`operator!=`](execution_hierarchy_and_collectives/asc_hierarchy/extent3d_operator_not_equal.md) | asc/hierarchy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::`operator==`](execution_hierarchy_and_collectives/asc_hierarchy/extent3d_operator_equal.md) | asc/hierarchy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::x](execution_hierarchy_and_collectives/asc_hierarchy/extent3d_x.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::y](execution_hierarchy_and_collectives/asc_hierarchy/extent3d_y.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::extent3d::z](execution_hierarchy_and_collectives/asc_hierarchy/extent3d_z.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::get_launch_dimensions](execution_hierarchy_and_collectives/asc_hierarchy/get_launch_dimensions.md) | asc/hierarchy | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::grid](execution_hierarchy_and_collectives/asc_hierarchy/grid.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::grid_dims (Function)](execution_hierarchy_and_collectives/asc_hierarchy/grid_dims_function.md) | asc/hierarchy | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::grid_dims (Function template)](execution_hierarchy_and_collectives/asc_hierarchy/grid_dims_function_template.md) | asc/hierarchy | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::grid_level](execution_hierarchy_and_collectives/asc_hierarchy/grid_level.md) | asc/hierarchy | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::lane_id](execution_hierarchy_and_collectives/asc_hierarchy/lane_id.md) | asc/hierarchy | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::launch_dimensions](execution_hierarchy_and_collectives/asc_hierarchy/launch_dimensions.md) | asc/hierarchy | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::launch_dimensions::block](execution_hierarchy_and_collectives/asc_hierarchy/launch_dimensions_block.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::launch_dimensions::grid](execution_hierarchy_and_collectives/asc_hierarchy/launch_dimensions_grid.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::level_dimensions](execution_hierarchy_and_collectives/asc_hierarchy/level_dimensions.md) | asc/hierarchy | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::level_dimensions::extents](execution_hierarchy_and_collectives/asc_hierarchy/level_dimensions_extents.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_hierarchy](execution_hierarchy_and_collectives/asc_hierarchy/make_hierarchy.md) | asc/hierarchy | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy](execution_hierarchy_and_collectives/asc_hierarchy/simt_hierarchy.md) | asc/hierarchy | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy::block_extents](execution_hierarchy_and_collectives/asc_hierarchy/simt_hierarchy_block_extents.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy::count](execution_hierarchy_and_collectives/asc_hierarchy/simt_hierarchy_count.md) | asc/hierarchy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy::extents](execution_hierarchy_and_collectives/asc_hierarchy/simt_hierarchy_extents.md) | asc/hierarchy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::simt_hierarchy::grid_extents](execution_hierarchy_and_collectives/asc_hierarchy/simt_hierarchy_grid_extents.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::sub_block_count](execution_hierarchy_and_collectives/asc_hierarchy/sub_block_count.md) | asc/hierarchy | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::sub_block_index](execution_hierarchy_and_collectives/asc_hierarchy/sub_block_index.md) | asc/hierarchy | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::thread](execution_hierarchy_and_collectives/asc_hierarchy/thread.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::thread_count](execution_hierarchy_and_collectives/asc_hierarchy/thread_count.md) | asc/hierarchy | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::thread_extents_3d](execution_hierarchy_and_collectives/asc_hierarchy/thread_extents_3d.md) | asc/hierarchy | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::thread_index](execution_hierarchy_and_collectives/asc_hierarchy/thread_index.md) | asc/hierarchy | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::thread_index_3d](execution_hierarchy_and_collectives/asc_hierarchy/thread_index_3d.md) | asc/hierarchy | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::thread_level](execution_hierarchy_and_collectives/asc_hierarchy/thread_level.md) | asc/hierarchy | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::warp](execution_hierarchy_and_collectives/asc_hierarchy/warp.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::warp_count](execution_hierarchy_and_collectives/asc_hierarchy/warp_count.md) | asc/hierarchy | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_index](execution_hierarchy_and_collectives/asc_hierarchy/warp_index.md) | asc/hierarchy | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_level](execution_hierarchy_and_collectives/asc_hierarchy/warp_level.md) | asc/hierarchy | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::warp_size](execution_hierarchy_and_collectives/asc_hierarchy/warp_size.md) | asc/hierarchy | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::constant_iterator](function_objects_and_iterators/asc_iterator/constant_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::counting_iterator](function_objects_and_iterators/asc_iterator/counting_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::discard_iterator](function_objects_and_iterators/asc_iterator/discard_iterator.md) | asc/iterator | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_constant_iterator](function_objects_and_iterators/asc_iterator/make_constant_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_counting_iterator](function_objects_and_iterators/asc_iterator/make_counting_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_discard_iterator](function_objects_and_iterators/asc_iterator/make_discard_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_permutation_iterator](function_objects_and_iterators/asc_iterator/make_permutation_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_shuffle_iterator](function_objects_and_iterators/asc_iterator/make_shuffle_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_strided_iterator](function_objects_and_iterators/asc_iterator/make_strided_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_tabulate_output_iterator](function_objects_and_iterators/asc_iterator/make_tabulate_output_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_transform_input_output_iterator](function_objects_and_iterators/asc_iterator/make_transform_input_output_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_transform_iterator](function_objects_and_iterators/asc_iterator/make_transform_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_transform_output_iterator](function_objects_and_iterators/asc_iterator/make_transform_output_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_zip_function](function_objects_and_iterators/asc_iterator/make_zip_function.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_zip_iterator](function_objects_and_iterators/asc_iterator/make_zip_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_zip_transform_iterator](function_objects_and_iterators/asc_iterator/make_zip_transform_iterator.md) | asc/iterator | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::permutation_iterator](function_objects_and_iterators/asc_iterator/permutation_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::shuffle_iterator](function_objects_and_iterators/asc_iterator/shuffle_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::strided_iterator](function_objects_and_iterators/asc_iterator/strided_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tabulate_output_iterator](function_objects_and_iterators/asc_iterator/tabulate_output_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::transform_input_output_iterator](function_objects_and_iterators/asc_iterator/transform_input_output_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::transform_iterator](function_objects_and_iterators/asc_iterator/transform_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::transform_output_iterator](function_objects_and_iterators/asc_iterator/transform_output_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::zip_function](function_objects_and_iterators/asc_iterator/zip_function.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::zip_iterator](function_objects_and_iterators/asc_iterator/zip_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::zip_transform_iterator](function_objects_and_iterators/asc_iterator/zip_transform_iterator.md) | asc/iterator | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::latch](device_atomics_and_sync/asc_latch/latch.md) | asc/latch | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::latch::arrive_and_wait](device_atomics_and_sync/asc_latch/latch_arrive_and_wait.md) | asc/latch | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::latch::count_down](device_atomics_and_sync/asc_latch/latch_count_down.md) | asc/latch | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::latch::latch](device_atomics_and_sync/asc_latch/latch_latch.md) | asc/latch | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::latch::max](device_atomics_and_sync/asc_latch/latch_max.md) | asc/latch | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::latch::try_wait](device_atomics_and_sync/asc_latch/latch_try_wait.md) | asc/latch | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::latch::wait](device_atomics_and_sync/asc_latch/latch_wait.md) | asc/latch | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::dlpack_tensor](multidimensional_views_and_transfer/asc_mdspan/dlpack_tensor.md) | asc/mdspan | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::dstrides](multidimensional_views_and_transfer/asc_mdspan/dstrides.md) | asc/mdspan | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::dynamic_stride](multidimensional_views_and_transfer/asc_mdspan/dynamic_stride.md) | asc/mdspan | Variable | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::gm_accessor](multidimensional_views_and_transfer/asc_mdspan/gm_accessor.md) | asc/mdspan | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::gm_mdspan](multidimensional_views_and_transfer/asc_mdspan/gm_mdspan.md) | asc/mdspan | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::host_accessor](multidimensional_views_and_transfer/asc_mdspan/host_accessor.md) | asc/mdspan | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::host_mdspan](multidimensional_views_and_transfer/asc_mdspan/host_mdspan.md) | asc/mdspan | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_device_accessible_v](multidimensional_views_and_transfer/asc_mdspan/is_device_accessible_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_gm_accessor_v](multidimensional_views_and_transfer/asc_mdspan/is_gm_accessor_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_gm_mdspan_v](multidimensional_views_and_transfer/asc_mdspan/is_gm_mdspan_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_host_accessible_v](multidimensional_views_and_transfer/asc_mdspan/is_host_accessible_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_host_accessor_v](multidimensional_views_and_transfer/asc_mdspan/is_host_accessor_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_host_mdspan_v](multidimensional_views_and_transfer/asc_mdspan/is_host_mdspan_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_restrict_accessor_v](multidimensional_views_and_transfer/asc_mdspan/is_restrict_accessor_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_restrict_mdspan_v](multidimensional_views_and_transfer/asc_mdspan/is_restrict_mdspan_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_ub_accessor_v](multidimensional_views_and_transfer/asc_mdspan/is_ub_accessor_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_ub_mdspan_v](multidimensional_views_and_transfer/asc_mdspan/is_ub_mdspan_v.md) | asc/mdspan | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::layout_stride_relaxed](multidimensional_views_and_transfer/asc_mdspan/layout_stride_relaxed.md) | asc/mdspan | Class | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::restrict_accessor](multidimensional_views_and_transfer/asc_mdspan/restrict_accessor.md) | asc/mdspan | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::restrict_mdspan](multidimensional_views_and_transfer/asc_mdspan/restrict_mdspan.md) | asc/mdspan | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::steps](multidimensional_views_and_transfer/asc_mdspan/steps.md) | asc/mdspan | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::strides](multidimensional_views_and_transfer/asc_mdspan/strides.md) | asc/mdspan | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::to_dlpack_tensor](multidimensional_views_and_transfer/asc_mdspan/to_dlpack_tensor.md) | asc/mdspan | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::to_gm_mdspan](multidimensional_views_and_transfer/asc_mdspan/to_gm_mdspan.md) | asc/mdspan | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::to_host_mdspan](multidimensional_views_and_transfer/asc_mdspan/to_host_mdspan.md) | asc/mdspan | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::ub_accessor](multidimensional_views_and_transfer/asc_mdspan/ub_accessor.md) | asc/mdspan | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::ub_mdspan](multidimensional_views_and_transfer/asc_mdspan/ub_mdspan.md) | asc/mdspan | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::aligned_size](address_spaces_and_memory_views/asc_memory/aligned_size.md) | asc/memory | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::arena_allocator](address_spaces_and_memory_views/asc_memory/arena_allocator.md) | asc/memory | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::gm_span](address_spaces_and_memory_views/asc_memory/gm_span.md) | asc/memory | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_aligned](address_spaces_and_memory_views/asc_memory/is_aligned.md) | asc/memory | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::memory_space](address_spaces_and_memory_views/asc_memory/memory_space.md) | asc/memory | Enum | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::memory_space_of](address_spaces_and_memory_views/asc_memory/memory_space_of.md) | asc/memory | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::memory_space_of_v](address_spaces_and_memory_views/asc_memory/memory_space_of_v.md) | asc/memory | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::monotonic_arena](address_spaces_and_memory_views/asc_memory/monotonic_arena.md) | asc/memory | Class | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::pointer_attributes](address_spaces_and_memory_views/asc_memory/pointer_attributes.md) | asc/memory | Class | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::temporary_storage_ref](address_spaces_and_memory_views/asc_memory/temporary_storage_ref.md) | asc/memory | Class | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::ub_span](address_spaces_and_memory_views/asc_memory/ub_span.md) | asc/memory | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::add_overflow](bit_math_numeric_random/asc_numeric/add_overflow.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::div_overflow](bit_math_numeric_random/asc_numeric/div_overflow.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::mul_overflow](bit_math_numeric_random/asc_numeric/mul_overflow.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::narrow](bit_math_numeric_random/asc_numeric/narrow.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::narrow_cast](bit_math_numeric_random/asc_numeric/narrow_cast.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::overflow_cast](bit_math_numeric_random/asc_numeric/overflow_cast.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::overflow_result](bit_math_numeric_random/asc_numeric/overflow_result.md) | asc/numeric | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::overflow_result::overflow](bit_math_numeric_random/asc_numeric/overflow_result_overflow.md) | asc/numeric | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::overflow_result::value](bit_math_numeric_random/asc_numeric/overflow_result_value.md) | asc/numeric | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::saturating_add](bit_math_numeric_random/asc_numeric/saturating_add.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::saturating_div](bit_math_numeric_random/asc_numeric/saturating_div.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::saturating_mul](bit_math_numeric_random/asc_numeric/saturating_mul.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::saturating_overflow_cast](bit_math_numeric_random/asc_numeric/saturating_overflow_cast.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::saturating_sub](bit_math_numeric_random/asc_numeric/saturating_sub.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::sub_overflow](bit_math_numeric_random/asc_numeric/sub_overflow.md) | asc/numeric | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::copy_async](async_data_pipeline/asc_pipeline/copy_async.md) | asc/pipeline | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::make_pipeline](async_data_pipeline/asc_pipeline/make_pipeline.md) | asc/pipeline | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_event_id](async_data_pipeline/asc_pipeline/pipeline_event_id.md) | asc/pipeline | Type alias | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref](async_data_pipeline/asc_pipeline/pipeline_ref.md) | asc/pipeline | Class | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::consumer_release](async_data_pipeline/asc_pipeline/pipeline_ref_consumer_release.md) | asc/pipeline | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::consumer_wait](async_data_pipeline/asc_pipeline/pipeline_ref_consumer_wait.md) | asc/pipeline | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::load_event](async_data_pipeline/asc_pipeline/pipeline_ref_load_event.md) | asc/pipeline | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::`operator=`](async_data_pipeline/asc_pipeline/pipeline_ref_operator_assign.md) | asc/pipeline | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::pipeline_ref](async_data_pipeline/asc_pipeline/pipeline_ref_pipeline_ref.md) | asc/pipeline | Constructor | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::producer_acquire](async_data_pipeline/asc_pipeline/pipeline_ref_producer_acquire.md) | asc/pipeline | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::producer_commit](async_data_pipeline/asc_pipeline/pipeline_ref_producer_commit.md) | asc/pipeline | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::stages](async_data_pipeline/asc_pipeline/pipeline_ref_stages.md) | asc/pipeline | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::store_event](async_data_pipeline/asc_pipeline/pipeline_ref_store_event.md) | asc/pipeline | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::wait](async_data_pipeline/asc_pipeline/pipeline_ref_wait.md) | asc/pipeline | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [`asc::operator!=` (Function template)](bit_math_numeric_random/asc_random/operator_not_equal.md) | asc/random | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::operator==` (Function template)](bit_math_numeric_random/asc_random/operator_equal.md) | asc/random | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64](bit_math_numeric_random/asc_random/pcg64.md) | asc/random | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64_engine](bit_math_numeric_random/asc_random/pcg64_engine.md) | asc/random | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64_engine::default_seed](bit_math_numeric_random/asc_random/pcg64_engine_default_seed.md) | asc/random | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64_engine::discard](bit_math_numeric_random/asc_random/pcg64_engine_discard.md) | asc/random | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64_engine::max](bit_math_numeric_random/asc_random/pcg64_engine_max.md) | asc/random | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64_engine::min](bit_math_numeric_random/asc_random/pcg64_engine_min.md) | asc/random | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64_engine::`operator()`](bit_math_numeric_random/asc_random/pcg64_engine_operator_call.md) | asc/random | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64_engine::pcg64_engine](bit_math_numeric_random/asc_random/pcg64_engine_pcg64_engine.md) | asc/random | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64_engine::result_type](bit_math_numeric_random/asc_random/pcg64_engine_result_type.md) | asc/random | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::pcg64_engine::seed](bit_math_numeric_random/asc_random/pcg64_engine_seed.md) | asc/random | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::random_bijection](bit_math_numeric_random/asc_random/random_bijection.md) | asc/random | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::random_bijection::index_type](bit_math_numeric_random/asc_random/random_bijection_index_type.md) | asc/random | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::random_bijection::`operator()`](bit_math_numeric_random/asc_random/random_bijection_operator_call.md) | asc/random | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::random_bijection::random_bijection](bit_math_numeric_random/asc_random/random_bijection_random_bijection.md) | asc/random | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::random_bijection::size](bit_math_numeric_random/asc_random/random_bijection_size.md) | asc/random | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::binary_semaphore](device_atomics_and_sync/asc_semaphore/binary_semaphore.md) | asc/semaphore | Alias template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::counting_semaphore](device_atomics_and_sync/asc_semaphore/counting_semaphore.md) | asc/semaphore | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::counting_semaphore::acquire](device_atomics_and_sync/asc_semaphore/counting_semaphore_acquire.md) | asc/semaphore | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::counting_semaphore::counting_semaphore](device_atomics_and_sync/asc_semaphore/counting_semaphore_counting_semaphore.md) | asc/semaphore | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::counting_semaphore::max](device_atomics_and_sync/asc_semaphore/counting_semaphore_max.md) | asc/semaphore | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::counting_semaphore::release](device_atomics_and_sync/asc_semaphore/counting_semaphore_release.md) | asc/semaphore | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::counting_semaphore::try_acquire](device_atomics_and_sync/asc_semaphore/counting_semaphore_try_acquire.md) | asc/semaphore | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::make_tensor_copy_descriptor](multidimensional_views_and_transfer/asc_tensor_copy/make_tensor_copy_descriptor.md) | asc/tensor_copy | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor.md) | asc/tensor_copy | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::destination_stride](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_destination_stride.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::extent](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_extent.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::left_padding](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_left_padding.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::rank](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_rank.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::required_alignment](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_required_alignment.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::required_elements](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_required_elements.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::right_padding](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_right_padding.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::set_dimension](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_set_dimension.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::size_type](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_size_type.md) | asc/tensor_copy | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::source_stride](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_source_stride.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::tensor_copy_descriptor](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_tensor_copy_descriptor.md) | asc/tensor_copy | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_descriptor::validate](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_descriptor_validate.md) | asc/tensor_copy | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_required_alignment](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_required_alignment.md) | asc/tensor_copy | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_required_elements](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_required_elements.md) | asc/tensor_copy | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_status.md) | asc/tensor_copy | Enum | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::insufficient_destination](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_status_insufficient_destination.md) | asc/tensor_copy | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::insufficient_source](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_status_insufficient_source.md) | asc/tensor_copy | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::invalid_stage](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_status_invalid_stage.md) | asc/tensor_copy | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::size_overflow](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_status_size_overflow.md) | asc/tensor_copy | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::success](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_status_success.md) | asc/tensor_copy | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::zero_extent](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_status_zero_extent.md) | asc/tensor_copy | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_copy_status::zero_stride](multidimensional_views_and_transfer/asc_tensor_copy/tensor_copy_status_zero_stride.md) | asc/tensor_copy | Enumerator | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_load_async](multidimensional_views_and_transfer/asc_tensor_copy/tensor_load_async.md) | asc/tensor_copy | Function template | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::validate_tensor_copy_descriptor](multidimensional_views_and_transfer/asc_tensor_copy/validate_tensor_copy_descriptor.md) | asc/tensor_copy | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::is_bitwise_comparable](type_traits_and_utilities/asc_type_traits/is_bitwise_comparable.md) | asc/type_traits | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::is_bitwise_comparable_v](type_traits_and_utilities/asc_type_traits/is_bitwise_comparable_v.md) | asc/type_traits | Variable template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::is_extended_floating_point](type_traits_and_utilities/asc_type_traits/is_extended_floating_point.md) | asc/type_traits | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::is_extended_floating_point_v](type_traits_and_utilities/asc_type_traits/is_extended_floating_point_v.md) | asc/type_traits | Variable template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::is_trivially_relocatable](type_traits_and_utilities/asc_type_traits/is_trivially_relocatable.md) | asc/type_traits | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::is_trivially_relocatable_v](type_traits_and_utilities/asc_type_traits/is_trivially_relocatable_v.md) | asc/type_traits | Variable template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::in_range](type_traits_and_utilities/asc_utility/in_range.md) | asc/utility | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::static_for](type_traits_and_utilities/asc_utility/static_for.md) | asc/utility | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [CANN_ASC_STL](type_traits_and_utilities/asc_version/cann_asc_stl.md) | asc/version | Macro | C++17/C++20 | Host, SIMD, SIMT | Chip independent |
| [CANN_ASC_STL_HAS_PIPELINE](type_traits_and_utilities/asc_version/cann_asc_stl_has_pipeline.md) | asc/version | Macro | C++17/C++20 | Host, SIMD, SIMT | Chip independent |
| [CANN_ASC_STL_HAS_NUMERIC_TYPES](type_traits_and_utilities/asc_version/cann_asc_stl_has_numeric_types.md) | asc/version | Macro | C++17/C++20 | Host, SIMD, SIMT | Chip independent |
| [CANN_ASC_STL_HAS_CACHE](type_traits_and_utilities/asc_version/cann_asc_stl_has_cache.md) | asc/version | Macro | C++17/C++20 | Host, SIMD, SIMT | Chip independent |
| [asc::active_mask](execution_hierarchy_and_collectives/asc_warp/active_mask.md) | asc/warp | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask](execution_hierarchy_and_collectives/asc_warp/lane_mask.md) | asc/warp | Class | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all](execution_hierarchy_and_collectives/asc_warp/lane_mask_all.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_active](execution_hierarchy_and_collectives/asc_warp/lane_mask_all_active.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_greater](execution_hierarchy_and_collectives/asc_warp/lane_mask_all_greater.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_greater_equal](execution_hierarchy_and_collectives/asc_warp/lane_mask_all_greater_equal.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_less](execution_hierarchy_and_collectives/asc_warp/lane_mask_all_less.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_less_equal](execution_hierarchy_and_collectives/asc_warp/lane_mask_all_less_equal.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::all_not_equal](execution_hierarchy_and_collectives/asc_warp/lane_mask_all_not_equal.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::lane_mask](execution_hierarchy_and_collectives/asc_warp/lane_mask_lane_mask.md) | asc/warp | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::none](execution_hierarchy_and_collectives/asc_warp/lane_mask_none.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator unsigned int](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_unsigned_int.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator!=`](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_not_equal.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator&](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_bit_and.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator&=](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_bit_and_assign.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator<<`](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_shift_left.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator<<=`](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_shift_left_assign.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator==`](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_equal.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator>>`](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_shift_right.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::`operator>>=`](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_shift_right_assign.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator^](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_bit_xor.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator^=](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_bit_xor_assign.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator\|](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_bit_or.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator\|=](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_bit_or_assign.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::operator~](execution_hierarchy_and_collectives/asc_warp/lane_mask_operator_bit_not.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::this_lane](execution_hierarchy_and_collectives/asc_warp/lane_mask_this_lane.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::lane_mask::value](execution_hierarchy_and_collectives/asc_warp/lane_mask_value.md) | asc/warp | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_all](execution_hierarchy_and_collectives/asc_warp/warp_all.md) | asc/warp | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_any](execution_hierarchy_and_collectives/asc_warp/warp_any.md) | asc/warp | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_ballot](execution_hierarchy_and_collectives/asc_warp/warp_ballot.md) | asc/warp | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_match_all](execution_hierarchy_and_collectives/asc_warp/warp_match_all.md) | asc/warp | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_match_any](execution_hierarchy_and_collectives/asc_warp/warp_match_any.md) | asc/warp | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_reduce_add](execution_hierarchy_and_collectives/asc_warp/warp_reduce_add.md) | asc/warp | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_reduce_max](execution_hierarchy_and_collectives/asc_warp/warp_reduce_max.md) | asc/warp | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_reduce_min](execution_hierarchy_and_collectives/asc_warp/warp_reduce_min.md) | asc/warp | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_down](execution_hierarchy_and_collectives/asc_warp/warp_shuffle_down.md) | asc/warp | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_idx](execution_hierarchy_and_collectives/asc_warp/warp_shuffle_idx.md) | asc/warp | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_result](execution_hierarchy_and_collectives/asc_warp/warp_shuffle_result.md) | asc/warp | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_result::data](execution_hierarchy_and_collectives/asc_warp/warp_shuffle_result_data.md) | asc/warp | Variable | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_result::valid](execution_hierarchy_and_collectives/asc_warp/warp_shuffle_result_valid.md) | asc/warp | Variable | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_up](execution_hierarchy_and_collectives/asc_warp/warp_shuffle_up.md) | asc/warp | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::warp_shuffle_xor](execution_hierarchy_and_collectives/asc_warp/warp_shuffle_xor.md) | asc/warp | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::acquire_work](execution_hierarchy_and_collectives/asc_work_queue/acquire_work.md) | asc/work_queue | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_work_queue](execution_hierarchy_and_collectives/asc_work_queue/make_work_queue.md) | asc/work_queue | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::work_chunk](execution_hierarchy_and_collectives/asc_work_queue/work_chunk.md) | asc/work_queue | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::work_queue_ref](execution_hierarchy_and_collectives/asc_work_queue/work_queue_ref.md) | asc/work_queue | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::tensor_store_async](multidimensional_views_and_transfer/asc_tensor_copy/tensor_store_async.md) | asc/tensor_copy | Function template | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::work_cursor](execution_hierarchy_and_collectives/asc_work_queue/work_cursor.md) | asc/work_queue | Type alias | C++17+ | See individual members or overloads | Ascend 950 |
