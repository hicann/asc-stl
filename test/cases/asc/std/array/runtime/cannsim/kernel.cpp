/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <acl/acl.h>

#include "../semantics.h"

#if defined(ASC_STL_STANDARD_RUNTIME_PROFILES)
#include "support/standard_container_semantics.h"
#include "support/standard_synchronization_semantics.h"

using asc_stl_standard_runtime::test_data;
using asc_stl_standard_runtime::test_group;

template <test_group Group>
__global__ void asc_stl_standard_profile_kernel(test_data* io)
{
    namespace ct = asc_stl_standard_container_test;
    namespace sync = asc_stl_standard_synchronization_test;
    if constexpr (Group == test_group::synchronization) {
        static_assert(sizeof(sync::atomic_storage) <= sizeof(io->synchronization_storage));
        auto& storage = *::new (static_cast<void*>(io->synchronization_storage)) sync::atomic_storage{};
        const int rmw = sync::evaluate_rmw(storage, static_cast<unsigned>(io->seed));
        io->failures[0] = rmw != 0 ? rmw : sync::evaluate_phases(storage) << 4;
    } else {
        ct::arena_state state{io->container_storage, sizeof(io->container_storage), 0, 0, 0};
        int outcome = 0;
        if constexpr (Group == test_group::sequences)
            outcome = ct::evaluate_sequences(state, io->seed);
        if constexpr (Group == test_group::ordered_set)
            outcome = ct::evaluate_ordered_set(state, io->seed);
        if constexpr (Group == test_group::unordered_set)
            outcome = ct::evaluate_unordered_set(state, io->seed);
        if constexpr (Group == test_group::unordered_map)
            outcome = ct::evaluate_unordered_map(state, io->seed);
        if constexpr (Group == test_group::scoped_allocator)
            outcome = ct::evaluate_scoped_allocator(state);
        if constexpr (Group == test_group::adaptors)
            outcome = ct::evaluate_adaptors(io->seed);
        io->failures[0] = outcome;
    }
}

void launch_asc_stl_standard(test_data* io, aclrtStream stream, int selected)
{
    switch (static_cast<test_group>(selected)) {
        case test_group::sequences:
            asc_stl_standard_profile_kernel<test_group::sequences><<<1, 1, 0, stream>>>(io);
            return;
        case test_group::ordered_set:
            asc_stl_standard_profile_kernel<test_group::ordered_set><<<1, 1, 0, stream>>>(io);
            return;
        case test_group::unordered_set:
            asc_stl_standard_profile_kernel<test_group::unordered_set><<<1, 1, 0, stream>>>(io);
            return;
        case test_group::unordered_map:
            asc_stl_standard_profile_kernel<test_group::unordered_map><<<1, 1, 0, stream>>>(io);
            return;
        case test_group::scoped_allocator:
            asc_stl_standard_profile_kernel<test_group::scoped_allocator><<<1, 1, 0, stream>>>(io);
            return;
        case test_group::adaptors:
            asc_stl_standard_profile_kernel<test_group::adaptors><<<1, 1, 0, stream>>>(io);
            return;
        case test_group::synchronization:
            asc_stl_standard_profile_kernel<test_group::synchronization><<<1, 1, 0, stream>>>(io);
            return;
        default:
            return;  // The Host validates the name before launch.
    }
}
#else
#include "support/b013_semantics.h"
#include "support/b020_semantics.h"
#include "cases/asc/std/chrono/support/calendar_semantics.h"
#include "support/cxx17_container_semantics.h"
#include "cases/asc/std/ranges/support/cxx17_views_semantics.h"
#include "cases/asc/std/iterator/support/insert_iterator_semantics.h"
#include "cases/asc/std/algorithm/support/standard_algorithm_semantics.h"
#include "support/standard_lock_semantics.h"
#include "support/standard_numeric_semantics.h"
#include "support/standard_value_semantics.h"
#include "support/standard_view_semantics.h"
#include "support/w09_w10_semantics.h"

namespace {

using asc_stl_standard_runtime::test_data;
using asc_stl_standard_runtime::test_group;

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int evaluate_algorithms(int seed)
{
    return (asc_stl_b013_test::evaluate_algorithms() != 0 ? 1 : 0) |
        (asc_stl_b020_test::evaluate_query_algorithms() != 0 ? 2 : 0) |
        (asc_stl_b020_test::evaluate_selection_algorithms() != 0 ? 4 : 0) |
        (asc_stl_standard_algorithm_test::evaluate_mutations(seed) << 3) |
        (asc_stl_standard_algorithm_test::evaluate_reordering(seed) << 7);
}

CANN_ASC_STL_API int evaluate(test_group group, int seed)
{
    switch (group) {
        case test_group::calendar:
            return asc_stl_calendar_test::evaluate(seed) + asc_stl_w09_w10_test::evaluate_calendar_boundaries();
        case test_group::algorithms:
            return evaluate_algorithms(seed);
        case test_group::function_objects:
            return asc_stl_standard_value_test::evaluate_function_objects(seed);
        case test_group::value_types:
            return asc_stl_standard_value_test::evaluate_value_types(seed) + asc_stl_b020_test::evaluate_optional() +
                asc_stl_w09_w10_test::evaluate_memory_variant();
        case test_group::ranges:
            return asc_stl_standard_view_test::evaluate_ranges(seed) + asc_stl_cxx17_views_test::evaluate() +
                asc_stl_insert_iterator_test::evaluate_adaptors(seed);
        case test_group::layouts:
            return asc_stl_standard_view_test::evaluate_layouts(seed) + asc_stl_w09_w10_test::evaluate_mdspan();
        case test_group::bytes_and_complex:
            return asc_stl_standard_value_test::evaluate_bytes_and_complex(seed);
        case test_group::text:
            return asc_stl_standard_value_test::evaluate_text(seed) + asc_stl_b013_test::evaluate_cstring();
        case test_group::memory:
            return asc_stl_cxx17_container_test::evaluate_allocation_facilities() +
                asc_stl_w09_w10_test::evaluate_alignment_chrono() + asc_stl_w09_w10_test::evaluate_mutex() +
                asc_stl_standard_lock_test::evaluate_locks();
        case test_group::numeric:
            return asc_stl_standard_numeric_test::evaluate_numeric(seed);
        case test_group::random:
            return asc_stl_standard_numeric_test::evaluate_random(seed);
        default:
            return 1;
    }
}

}  // namespace

#if defined(ASC_STL_STANDARD_RUNTIME_SIMT)
__global__ void asc_stl_standard_kernel(test_data* io)
{
    const unsigned int index = blockIdx.x;
    io->failures[index] = evaluate(static_cast<test_group>(index), io->seed);
}

#else
__global__ __vector__ void asc_stl_standard_kernel(__gm__ test_data* io)
{
    for (int group = 0; group < asc_stl_standard_runtime::kCoreGroupCount; ++group)
        io->failures[group] = evaluate(static_cast<test_group>(group), io->seed);
}
#endif

void launch_asc_stl_standard(test_data* io, aclrtStream stream, int)
{
#if defined(ASC_STL_STANDARD_RUNTIME_SIMT)
    asc_stl_standard_kernel<<<asc_stl_standard_runtime::kCoreGroupCount, 1, 0, stream>>>(io);
#else
    asc_stl_standard_kernel<<<1, nullptr, stream>>>(io);
#endif
}
#endif
