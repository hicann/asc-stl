# ASC-STL API List

Find ASC-STL interfaces by functional category. Each category page lists the available headers, interfaces, and support scope. The current version supports the Ascend 950 series; the other listed product series are not supported.

## API Category Overview

| Top-level category | Subcategory | Description |
| --- | --- | --- |
| [C++ Standard Library Interfaces](standard/standard.md) | [Language Support Library](standard/language_support/language_support.md) | Fundamental types, feature macros, source locations, and language facilities. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Concepts Library](standard/concepts/concepts.md) | Standard concepts for expressing template parameter requirements. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Diagnostics Library](standard/diagnostics/diagnostics.md) | Assertions, error codes, and diagnostics-related interfaces. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Memory Management Library](standard/memory_management/memory_management.md) | Object lifetimes, allocators, and memory operations. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Metaprogramming Library](standard/metaprogramming/metaprogramming.md) | Type traits, compile-time computation, and template helper facilities. |
| [C++ Standard Library Interfaces](standard/standard.md) | [General Utilities Library](standard/utilities/utilities.md) | General objects, function objects, and value manipulation utilities. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Containers Library](standard/containers/containers.md) | Sequence containers, associative containers, and their adaptors. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Iterators Library](standard/iterators/iterators.md) | Iterators, sentinels, and iterator adaptors. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Ranges Library](standard/ranges/ranges.md) | Range views, range access, and range adaptors. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Algorithms Library](standard/algorithms/algorithms.md) | Searching, sorting, transformation, and numeric algorithms. |
| [C++ Standard Library Interfaces](standard/standard.md) | [String Library](standard/strings/strings.md) | Character sequences, string views, and string operations. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Text Processing Library](standard/text_processing/text_processing.md) | Character classification, conversion, and text formatting. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Numerics Library](standard/numerics/numerics.md) | Mathematical functions, complex numbers, random numbers, and numeric operations. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Date and Time Library](standard/chrono/chrono.md) | Clocks, time durations, calendars, and time conversions. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Input/Output Library](standard/input_output/input_output.md) | Input/output related types and utilities. |
| [C++ Standard Library Interfaces](standard/standard.md) | [Concurrency Support Library](standard/concurrency/concurrency.md) | Atomics, synchronization, and concurrency facilities. |
| [Ascend Extension Interfaces](extension/extension.md) | [Device Atomics and Thread Synchronization](extension/device_atomics_and_sync/device_atomics_and_sync.md) | Device-side atomics, barriers, and thread synchronization. |
| [Ascend Extension Interfaces](extension/extension.md) | [Asynchronous Data Transfer Pipeline](extension/async_data_pipeline/async_data_pipeline.md) | Asynchronous transfers and their completion state management. |
| [Ascend Extension Interfaces](extension/extension.md) | [Address Spaces and Memory Views](extension/address_spaces_and_memory_views/address_spaces_and_memory_views.md) | Device memory address spaces, non-owning views, and allocation helpers. |
| [Ascend Extension Interfaces](extension/extension.md) | [Multidimensional Views and Transfer](extension/multidimensional_views_and_transfer/multidimensional_views_and_transfer.md) | Multidimensional indexing, data views, and tensor transfer. |
| [Ascend Extension Interfaces](extension/extension.md) | [Device Execution Hierarchy, Collective Operations, and Dynamic Work Acquisition](extension/execution_hierarchy_and_collectives/execution_hierarchy_and_collectives.md) | Thread-hierarchy queries, collective operations, and work acquisition. |
| [Ascend Extension Interfaces](extension/extension.md) | [Device-Side Parallel Algorithms and Argument Wrappers](extension/device_parallel_algorithms_and_arguments/device_parallel_algorithms_and_arguments.md) | Asynchronous parallel algorithms and their execution arguments. |
| [Ascend Extension Interfaces](extension/extension.md) | [Algorithm Function Objects, Operation Properties, and Iterator Adaptors](extension/function_objects_and_iterators/function_objects_and_iterators.md) | Algorithm callable objects, operation properties, and iterator adaptors. |
| [Ascend Extension Interfaces](extension/extension.md) | [Bit Operations, Math and Numeric Computation, Pseudorandom Numbers](extension/bit_math_numeric_random/bit_math_numeric_random.md) | Bit operations, math helpers, numeric computation, and random numbers. |
| [Ascend Extension Interfaces](extension/extension.md) | [Type Traits, Utilities and Version Detection](extension/type_traits_and_utilities/type_traits_and_utilities.md) | Extended type traits, utilities, and version detection. |
| [Runtime Interfaces](runtime/runtime.md) | [Device, Stream, and Event Management](runtime/devices_streams_events/devices_streams_events.md) | Device queries and stream/event lifecycle management. |
| [Runtime Interfaces](runtime/runtime.md) | [Kernel Function Invocation](runtime/kernel_launch/kernel_launch.md) | Submitting device kernel functions from the Host. |
| [Runtime Interfaces](runtime/runtime.md) | [Device-Side Execution Policies, Execution Requirements, and Submission Status](runtime/execution_policies_and_status/execution_policies_and_status.md) | Execution policies, execution requirements, and asynchronous submission status. |
| [Runtime Interfaces](runtime/runtime.md) | [Memory Resources, Memory Pools, and Buffers](runtime/memory_resources_and_buffers/memory_resources_and_buffers.md) | Device memory resources, memory pools, and owning buffers. |

## Headers Required to Call the Interfaces

| Interface category | Header form | Description |
| --- | --- | --- |
| C++ Standard Library Interfaces | `<asc/std/...>` | Standard library interfaces in the `asc::std` namespace. |
| Ascend Extension Interfaces | `<asc/...>` | Device and parallel extensions in the `asc` namespace. |
| Runtime Interfaces | `<asc/...>` | Manage device resources and submit asynchronous work on the Host side. |
