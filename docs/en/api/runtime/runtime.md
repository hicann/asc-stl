# Runtime Interfaces

The runtime interfaces provide Host-side device resources, streams, asynchronous submission, and memory resource management capabilities.

## Category Overview

| Category | Description |
| --- | --- |
| [Device, Stream, and Event Management](devices_streams_events/devices_streams_events.md) | Device queries and stream/event lifecycle management. |
| [Kernel Function Invocation](kernel_launch/kernel_launch.md) | Submitting device kernel functions from the Host. |
| [Device-Side Execution Policies, Execution Requirements, and Submission Status](execution_policies_and_status/execution_policies_and_status.md) | Execution policies, execution requirements, and asynchronous submission status. |
| [Memory Resources, Memory Pools, and Buffers](memory_resources_and_buffers/memory_resources_and_buffers.md) | Device memory resources, memory pools, and owning buffers. |

## API Support List

| API | Header | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- | --- |
| [asc::device_buffer](memory_resources_and_buffers/asc_buffer/device_buffer.md) | asc/buffer | Class template | C++17+ | Host | Ascend 950 |
| [asc::make_device_buffer](memory_resources_and_buffers/asc_buffer/make_device_buffer.md) | asc/buffer | Function template | C++17+ | Host | Ascend 950 |
| [asc::make_pinned_buffer](memory_resources_and_buffers/asc_buffer/make_pinned_buffer.md) | asc/buffer | Function template | C++17+ | Host | Ascend 950 |
| [asc::pinned_buffer](memory_resources_and_buffers/asc_buffer/pinned_buffer.md) | asc/buffer | Class template | C++17+ | Host | Ascend 950 |
| [asc::current_device](devices_streams_events/asc_devices/current_device.md) | asc/devices | Function | C++17+ | Host | Ascend 950 |
| [asc::device_count](devices_streams_events/asc_devices/device_count.md) | asc/devices | Function | C++17+ | Host | Ascend 950 |
| [asc::device_properties](devices_streams_events/asc_devices/device_properties.md) | asc/devices | Class | C++17+ | Host | Ascend 950 |
| [asc::device_properties::aicore_count](devices_streams_events/asc_devices/device_properties_aicore_count.md) | asc/devices | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::architecture](devices_streams_events/asc_devices/device_properties_architecture.md) | asc/devices | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::l2_cache_bytes](devices_streams_events/asc_devices/device_properties_l2_cache_bytes.md) | asc/devices | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::maximum_threads_per_block](devices_streams_events/asc_devices/device_properties_maximum_threads_per_block.md) | asc/devices | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::total_global_memory_bytes](devices_streams_events/asc_devices/device_properties_total_global_memory_bytes.md) | asc/devices | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::unified_buffer_bytes_per_vector_core](devices_streams_events/asc_devices/device_properties_unified_buffer_bytes_per_vector_core.md) | asc/devices | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::vector_core_count](devices_streams_events/asc_devices/device_properties_vector_core_count.md) | asc/devices | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_properties::warp_size](devices_streams_events/asc_devices/device_properties_warp_size.md) | asc/devices | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_ref](devices_streams_events/asc_devices/device_ref.md) | asc/devices | Class | C++17+ | Host | Ascend 950 |
| [asc::device_ref::device_ref](devices_streams_events/asc_devices/device_ref_device_ref.md) | asc/devices | Constructor | C++17+ | Host | Ascend 950 |
| [asc::device_ref::ordinal](devices_streams_events/asc_devices/device_ref_ordinal.md) | asc/devices | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_ref::properties](devices_streams_events/asc_devices/device_ref_properties.md) | asc/devices | Member function | C++17+ | Host | Ascend 950 |
| [asc::devices](devices_streams_events/asc_devices/devices.md) | asc/devices | Function | C++17+ | Host | Ascend 950 |
| [asc::npu_arch](devices_streams_events/asc_devices/npu_arch.md) | asc/devices | Enum | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::ascend_2201](devices_streams_events/asc_devices/npu_arch_ascend_2201.md) | asc/devices | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::ascend_3101](devices_streams_events/asc_devices/npu_arch_ascend_3101.md) | asc/devices | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::ascend_3510](devices_streams_events/asc_devices/npu_arch_ascend_3510.md) | asc/devices | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::npu_arch::unknown](devices_streams_events/asc_devices/npu_arch_unknown.md) | asc/devices | Enumerator | C++17+ | Host | Ascend 950 |
| [`asc::operator!=` (Function)](devices_streams_events/asc_devices/operator_not_equal.md) | asc/devices | Function | C++17+ | Host | Ascend 950 |
| [`asc::operator==` (Function)](devices_streams_events/asc_devices/operator_equal.md) | asc/devices | Function | C++17+ | Host | Ascend 950 |
| [asc::set_current_device](devices_streams_events/asc_devices/set_current_device.md) | asc/devices | Function | C++17+ | Host | Ascend 950 |
| [asc::execution_errc](execution_policies_and_status/asc_execution/execution_errc.md) | asc/execution | Enum | C++17+ | Host | Ascend 950 |
| [asc::execution_errc::backend_error](execution_policies_and_status/asc_execution/execution_errc_backend_error.md) | asc/execution | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::execution_errc::insufficient_storage](execution_policies_and_status/asc_execution/execution_errc_insufficient_storage.md) | asc/execution | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::execution_errc::invalid_argument](execution_policies_and_status/asc_execution/execution_errc_invalid_argument.md) | asc/execution | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::execution_errc::success](execution_policies_and_status/asc_execution/execution_errc_success.md) | asc/execution | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::execution_status](execution_policies_and_status/asc_execution/execution_status.md) | asc/execution | Class | C++17+ | Host | Ascend 950 |
| [asc::execution_status::code](execution_policies_and_status/asc_execution/execution_status_code.md) | asc/execution | Member function | C++17+ | Host | Ascend 950 |
| [asc::execution_status::execution_status](execution_policies_and_status/asc_execution/execution_status_execution_status.md) | asc/execution | Constructor | C++17+ | Host | Ascend 950 |
| [asc::execution_status::native_code](execution_policies_and_status/asc_execution/execution_status_native_code.md) | asc/execution | Member function | C++17+ | Host | Ascend 950 |
| [asc::execution_status::success](execution_policies_and_status/asc_execution/execution_status_success.md) | asc/execution | Member function | C++17+ | Host | Ascend 950 |
| [asc::determinism](execution_policies_and_status/asc_execution_determinism_h/determinism.md) | asc/execution.determinism.h | Enum | C++17+ | Host | Ascend 950 |
| [asc::determinism::device_to_device](execution_policies_and_status/asc_execution_determinism_h/determinism_device_to_device.md) | asc/execution.determinism.h | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::determinism::not_guaranteed](execution_policies_and_status/asc_execution_determinism_h/determinism_not_guaranteed.md) | asc/execution.determinism.h | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::determinism::run_to_run](execution_policies_and_status/asc_execution_determinism_h/determinism_run_to_run.md) | asc/execution.determinism.h | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::output_ordering](execution_policies_and_status/asc_execution_output_ordering_h/output_ordering.md) | asc/execution.output_ordering.h | Enum | C++17+ | Host | Ascend 950 |
| [asc::output_ordering::sorted](execution_policies_and_status/asc_execution_output_ordering_h/output_ordering_sorted.md) | asc/execution.output_ordering.h | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::output_ordering::stable_sorted](execution_policies_and_status/asc_execution_output_ordering_h/output_ordering_stable_sorted.md) | asc/execution.output_ordering.h | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::output_ordering::unsorted](execution_policies_and_status/asc_execution_output_ordering_h/output_ordering_unsorted.md) | asc/execution.output_ordering.h | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::device_policy](execution_policies_and_status/asc_execution_policy_h/device_policy.md) | asc/execution.policy.h | Class | C++17+ | Host | Ascend 950 |
| [asc::device_policy::device_policy](execution_policies_and_status/asc_execution_policy_h/device_policy_device_policy.md) | asc/execution.policy.h | Constructor | C++17+ | Host | Ascend 950 |
| [asc::device_policy::on](execution_policies_and_status/asc_execution_policy_h/device_policy_on.md) | asc/execution.policy.h | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_policy::require](execution_policies_and_status/asc_execution_policy_h/device_policy_require.md) | asc/execution.policy.h | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_policy::requirements](execution_policies_and_status/asc_execution_policy_h/device_policy_requirements.md) | asc/execution.policy.h | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_policy::stream](execution_policies_and_status/asc_execution_policy_h/device_policy_stream.md) | asc/execution.policy.h | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_policy::temporary_storage](execution_policies_and_status/asc_execution_policy_h/device_policy_temporary_storage.md) | asc/execution.policy.h | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_policy::with_temporary_storage](execution_policies_and_status/asc_execution_policy_h/device_policy_with_temporary_storage.md) | asc/execution.policy.h | Member function | C++17+ | Host | Ascend 950 |
| [asc::execution::device](execution_policies_and_status/asc_execution_policy_h/execution_device.md) | asc/execution.policy.h | Variable | C++17+ | Host | Ascend 950 |
| [asc::execution_requirements](execution_policies_and_status/asc_execution_require_h/execution_requirements.md) | asc/execution.require.h | Class | C++17+ | Host | Ascend 950 |
| [asc::execution_requirements::determinism_value](execution_policies_and_status/asc_execution_require_h/execution_requirements_determinism_value.md) | asc/execution.require.h | Member function | C++17+ | Host | Ascend 950 |
| [asc::execution_requirements::execution_requirements](execution_policies_and_status/asc_execution_require_h/execution_requirements_execution_requirements.md) | asc/execution.require.h | Constructor | C++17+ | Host | Ascend 950 |
| [asc::execution_requirements::output_ordering_value](execution_policies_and_status/asc_execution_require_h/execution_requirements_output_ordering_value.md) | asc/execution.require.h | Member function | C++17+ | Host | Ascend 950 |
| [asc::execution_requirements::tie_break_value](execution_policies_and_status/asc_execution_require_h/execution_requirements_tie_break_value.md) | asc/execution.require.h | Member function | C++17+ | Host | Ascend 950 |
| [asc::require](execution_policies_and_status/asc_execution_require_h/require.md) | asc/execution.require.h | Function | C++17+ | Host | Ascend 950 |
| [asc::tie_break](execution_policies_and_status/asc_execution_tie_break_h/tie_break.md) | asc/execution.tie_break.h | Enum | C++17+ | Host | Ascend 950 |
| [asc::tie_break::prefer_larger_index](execution_policies_and_status/asc_execution_tie_break_h/tie_break_prefer_larger_index.md) | asc/execution.tie_break.h | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::tie_break::prefer_smaller_index](execution_policies_and_status/asc_execution_tie_break_h/tie_break_prefer_smaller_index.md) | asc/execution.tie_break.h | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::tie_break::unspecified](execution_policies_and_status/asc_execution_tie_break_h/tie_break_unspecified.md) | asc/execution.tie_break.h | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::aicore_launch_config](kernel_launch/asc_launch/aicore_launch_config.md) | asc/launch | Class | C++17+ | Host | Ascend 950 |
| [asc::aicore_launch_config::blocks](kernel_launch/asc_launch/aicore_launch_config_blocks.md) | asc/launch | Variable | C++17+ | Host | Ascend 950 |
| [asc::host_callback](kernel_launch/asc_launch/host_callback.md) | asc/launch | Function | C++17+ | Host | Ascend 950 |
| [asc::host_callback_t](kernel_launch/asc_launch/host_callback_t.md) | asc/launch | Type alias | C++17+ | Host | Ascend 950 |
| [asc::launch](kernel_launch/asc_launch/launch.md) | asc/launch | Function template | C++17+ | Host | Ascend 950 |
| [asc::simt_launch_config](kernel_launch/asc_launch/simt_launch_config.md) | asc/launch | Class | C++17+ | Host | Ascend 950 |
| [asc::simt_launch_config::block](kernel_launch/asc_launch/simt_launch_config_block.md) | asc/launch | Variable | C++17+ | Host | Ascend 950 |
| [asc::simt_launch_config::dynamic_ub_bytes](kernel_launch/asc_launch/simt_launch_config_dynamic_ub_bytes.md) | asc/launch | Variable | C++17+ | Host | Ascend 950 |
| [asc::simt_launch_config::grid](kernel_launch/asc_launch/simt_launch_config_grid.md) | asc/launch | Variable | C++17+ | Host | Ascend 950 |
| [asc::device_memory_pool](memory_resources_and_buffers/asc_memory_pool/device_memory_pool.md) | asc/memory_pool | Class | C++17+ | Host | Ascend 950 |
| [asc::device_memory_pool_ref](memory_resources_and_buffers/asc_memory_pool/device_memory_pool_ref.md) | asc/memory_pool | Class | C++17+ | Host | Ascend 950 |
| [asc::memory_pool_statistics](memory_resources_and_buffers/asc_memory_pool/memory_pool_statistics.md) | asc/memory_pool | Class | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_pool](memory_resources_and_buffers/asc_memory_pool/pinned_memory_pool.md) | asc/memory_pool | Class | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_pool_ref](memory_resources_and_buffers/asc_memory_pool/pinned_memory_pool_ref.md) | asc/memory_pool | Class | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource](memory_resources_and_buffers/asc_memory_resource/device_memory_resource.md) | asc/memory_resource | Class | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::allocate](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_allocate.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::deallocate](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_deallocate.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::device_memory_resource](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_device_memory_resource.md) | asc/memory_resource | Constructor | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::device_ordinal](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_device_ordinal.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::properties](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_properties.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_ref.md) | asc/memory_resource | Class | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::allocate](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_ref_allocate.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::deallocate](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_ref_deallocate.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::device_memory_resource_ref](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_ref_device_memory_resource_ref.md) | asc/memory_resource | Constructor | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::device_ordinal](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_ref_device_ordinal.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::`operator!=`](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_ref_operator_not_equal.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::`operator==`](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_ref_operator_equal.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::properties](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_ref_properties.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::valid](memory_resources_and_buffers/asc_memory_resource/device_memory_resource_ref_valid.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties](memory_resources_and_buffers/asc_memory_resource/memory_resource_properties.md) | asc/memory_resource | Class | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::device_accessible](memory_resources_and_buffers/asc_memory_resource/memory_resource_properties_device_accessible.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::host_accessible](memory_resources_and_buffers/asc_memory_resource/memory_resource_properties_host_accessible.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::maximum_alignment](memory_resources_and_buffers/asc_memory_resource/memory_resource_properties_maximum_alignment.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::memory_resource_properties](memory_resources_and_buffers/asc_memory_resource/memory_resource_properties_memory_resource_properties.md) | asc/memory_resource | Constructor | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource.md) | asc/memory_resource | Class | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::allocate](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_allocate.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::deallocate](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_deallocate.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::pinned_memory_resource](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_pinned_memory_resource.md) | asc/memory_resource | Constructor | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::properties](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_properties.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_ref.md) | asc/memory_resource | Class | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::allocate](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_ref_allocate.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::deallocate](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_ref_deallocate.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::`operator!=`](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_ref_operator_not_equal.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::`operator==`](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_ref_operator_equal.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::pinned_memory_resource_ref](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_ref_pinned_memory_resource_ref.md) | asc/memory_resource | Constructor | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::properties](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_ref_properties.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::valid](memory_resources_and_buffers/asc_memory_resource/pinned_memory_resource_ref_valid.md) | asc/memory_resource | Member function | C++17+ | Host | Ascend 950 |
| [asc::adopt_event](devices_streams_events/asc_stream/adopt_event.md) | asc/stream | Function | C++17+ | Host | Ascend 950 |
| [asc::adopt_stream](devices_streams_events/asc_stream/adopt_stream.md) | asc/stream | Function | C++17+ | Host | Ascend 950 |
| [asc::elapsed_time](devices_streams_events/asc_stream/elapsed_time.md) | asc/stream | Function | C++17+ | Host | Ascend 950 |
| [asc::event](devices_streams_events/asc_stream/event.md) | asc/stream | Class | C++17+ | Host | Ascend 950 |
| [asc::event::close](devices_streams_events/asc_stream/event_close.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::event::event](devices_streams_events/asc_stream/event_event.md) | asc/stream | Constructor | C++17+ | Host | Ascend 950 |
| [asc::event::`operator=`](devices_streams_events/asc_stream/event_operator_assign.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::event::release](devices_streams_events/asc_stream/event_release.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::event::~event](devices_streams_events/asc_stream/event_destructor_event.md) | asc/stream | Destructor | C++17+ | Host | Ascend 950 |
| [asc::event_ref](devices_streams_events/asc_stream/event_ref.md) | asc/stream | Class | C++17+ | Host | Ascend 950 |
| [asc::event_ref::event_ref](devices_streams_events/asc_stream/event_ref_event_ref.md) | asc/stream | Constructor | C++17+ | Host | Ascend 950 |
| [asc::event_ref::is_done](devices_streams_events/asc_stream/event_ref_is_done.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::event_ref::native_handle](devices_streams_events/asc_stream/event_ref_native_handle.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::event_ref::operator bool](devices_streams_events/asc_stream/event_ref_operator_bool.md) | asc/stream | Conversion function | C++17+ | Host | Ascend 950 |
| [asc::event_ref::record](devices_streams_events/asc_stream/event_ref_record.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::event_ref::synchronize](devices_streams_events/asc_stream/event_ref_synchronize.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::make_event](devices_streams_events/asc_stream/make_event.md) | asc/stream | Function | C++17+ | Host | Ascend 950 |
| [asc::make_stream](devices_streams_events/asc_stream/make_stream.md) | asc/stream | Function | C++17+ | Host | Ascend 950 |
| [asc::stream](devices_streams_events/asc_stream/stream.md) | asc/stream | Class | C++17+ | Host | Ascend 950 |
| [asc::stream::close](devices_streams_events/asc_stream/stream_close.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream::`operator=`](devices_streams_events/asc_stream/stream_operator_assign.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream::release](devices_streams_events/asc_stream/stream_release.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream::stream](devices_streams_events/asc_stream/stream_stream.md) | asc/stream | Constructor | C++17+ | Host | Ascend 950 |
| [asc::stream::~stream](devices_streams_events/asc_stream/stream_destructor_stream.md) | asc/stream | Destructor | C++17+ | Host | Ascend 950 |
| [asc::stream_ref](devices_streams_events/asc_stream/stream_ref.md) | asc/stream | Class | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::is_done](devices_streams_events/asc_stream/stream_ref_is_done.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::native_handle](devices_streams_events/asc_stream/stream_ref_native_handle.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::operator bool](devices_streams_events/asc_stream/stream_ref_operator_bool.md) | asc/stream | Conversion function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::priority](devices_streams_events/asc_stream/stream_ref_priority.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::stream_ref](devices_streams_events/asc_stream/stream_ref_stream_ref.md) | asc/stream | Constructor | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::synchronize](devices_streams_events/asc_stream/stream_ref_synchronize.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::wait](devices_streams_events/asc_stream/stream_ref_wait.md) | asc/stream | Member function | C++17+ | Host | Ascend 950 |
