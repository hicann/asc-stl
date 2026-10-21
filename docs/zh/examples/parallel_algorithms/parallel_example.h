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

#ifndef CANN_ASC_STL_DOCS_PARALLEL_EXAMPLE_H
#define CANN_ASC_STL_DOCS_PARALLEL_EXAMPLE_H

#include <acl/acl.h>
#include <asc/execution>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <cstdio>

// Host-owned fixture: all pointers below denote separately allocated GM.
class parallel_example_context {
public:
    explicit parallel_example_context(const char* name) : name_(name)
    {}
    int* input{};
    int* other{};
    int* output{};
    asc::std::size_t* size_sink{};
    asc::std::uint32_t* flag_sink{};

    bool open()
    {
        if (!check("create_stream", aclrtCreateStream(&stream_)))
            return false;
        if (!allocate(reinterpret_cast<void**>(&input), 4 * sizeof(int)))
            return false;
        if (!allocate(reinterpret_cast<void**>(&other), 4 * sizeof(int)))
            return false;
        if (!allocate(reinterpret_cast<void**>(&output), 16 * sizeof(int)))
            return false;
        if (!allocate(reinterpret_cast<void**>(&size_sink), sizeof(*size_sink)))
            return false;
        if (!allocate(reinterpret_cast<void**>(&flag_sink), sizeof(*flag_sink)))
            return false;
        return allocate(&scratch_, scratch_bytes);
    }

    asc::device_policy policy() const
    {
        return asc::execution::device.on(asc::stream_ref(stream_))
            .with_temporary_storage(asc::temporary_storage_ref(scratch_, scratch_bytes, asc::memory_space::global));
    }

    bool prepare(const int (&values)[4], const int (&second)[4])
    {
        return check("upload_input",
                   aclrtMemcpy(input, sizeof(values), values, sizeof(values), ACL_MEMCPY_HOST_TO_DEVICE)) &&
            check("upload_other",
                aclrtMemcpy(other, sizeof(second), second, sizeof(second), ACL_MEMCPY_HOST_TO_DEVICE)) &&
            check("initialize_output", aclrtMemset(output, 16 * sizeof(int), 0xa5, 16 * sizeof(int))) &&
            check("initialize_size", aclrtMemset(size_sink, sizeof(*size_sink), 0xff, sizeof(*size_sink))) &&
            check("initialize_flag", aclrtMemset(flag_sink, sizeof(*flag_sink), 0xa5, sizeof(*flag_sink)));
    }

    bool complete(asc::execution_status status)
    {
        std::printf("{\"case\":\"%s\",\"phase\":\"submit\",\"code\":%d,\"native\":%d}\n", name_,
            static_cast<int>(status.code()), status.native_code());
        const aclError synchronized = aclrtSynchronizeStreamWithTimeout(stream_, 10000);
        safe_to_release_ = synchronized == ACL_SUCCESS;
        const bool completed = check("stream_sync", synchronized);
        return status.success() && completed;
    }

    template <class T, asc::std::size_t Count>
    bool read(const T* source, T (&destination)[Count])
    {
        if (!check("readback",
                aclrtMemcpy(destination, sizeof(destination), source, sizeof(destination), ACL_MEMCPY_DEVICE_TO_HOST)))
            return false;
        for (asc::std::size_t index = 0; index < Count; ++index)
            std::printf("{\"case\":\"%s\",\"phase\":\"readback_value\",\"index\":%u,\"bits\":%llu}\n", name_,
                static_cast<unsigned>(index), static_cast<unsigned long long>(destination[index]));
        return true;
    }

    bool close()
    {
        if (safe_to_release_ && stream_ != nullptr) {
            safe_to_release_ = check("cleanup_sync", aclrtSynchronizeStreamWithTimeout(stream_, 10000));
        }
        if (!safe_to_release_) {
            std::printf("{\"case\":\"%s\",\"phase\":\"cleanup\",\"state\":\"retained_after_sync_failure\"}\n", name_);
            return false;
        }
        bool passed = release(reinterpret_cast<void**>(&input));
        passed = release(reinterpret_cast<void**>(&other)) && passed;
        passed = release(reinterpret_cast<void**>(&output)) && passed;
        passed = release(reinterpret_cast<void**>(&size_sink)) && passed;
        passed = release(reinterpret_cast<void**>(&flag_sink)) && passed;
        passed = release(&scratch_) && passed;
        if (stream_ != nullptr) {
            const aclError status = aclrtDestroyStream(stream_);
            if (check("destroy_stream", status))
                stream_ = nullptr;
            else
                passed = false;
        }
        return passed;
    }

    bool safe_to_release() const
    {
        return safe_to_release_;
    }

private:
    static constexpr asc::std::size_t scratch_bytes = 8192;
    const char* name_;
    aclrtStream stream_{};
    void* scratch_{};
    bool safe_to_release_{true};

    bool check(const char* phase, aclError code) const
    {
        std::printf("{\"case\":\"%s\",\"phase\":\"%s\",\"code\":%d}\n", name_, phase, static_cast<int>(code));
        return code == ACL_SUCCESS;
    }
    bool allocate(void** slot, asc::std::size_t bytes)
    {
        return check("allocate_gm", aclrtMalloc(slot, bytes, ACL_MEM_MALLOC_HUGE_FIRST));
    }
    bool release(void** slot)
    {
        if (*slot == nullptr)
            return true;
        const aclError status = aclrtFree(*slot);
        if (!check("free_gm", status))
            return false;
        *slot = nullptr;
        return true;
    }
};

bool run_parallel_adjacent_difference(parallel_example_context&);
bool run_parallel_adjacent_find(parallel_example_context&);
bool run_parallel_all_of(parallel_example_context&);
bool run_parallel_any_of(parallel_example_context&);
bool run_parallel_copy(parallel_example_context&);
bool run_parallel_copy_if(parallel_example_context&);
bool run_parallel_copy_n(parallel_example_context&);
bool run_parallel_count(parallel_example_context&);
bool run_parallel_count_if(parallel_example_context&);
bool run_parallel_equal(parallel_example_context&);
bool run_parallel_exclusive_scan(parallel_example_context&);
bool run_parallel_fill(parallel_example_context&);
bool run_parallel_fill_n(parallel_example_context&);
bool run_parallel_find(parallel_example_context&);
bool run_parallel_find_if(parallel_example_context&);
bool run_parallel_find_if_not(parallel_example_context&);
bool run_parallel_for_each(parallel_example_context&);
bool run_parallel_for_each_n(parallel_example_context&);
bool run_parallel_generate(parallel_example_context&);
bool run_parallel_generate_n(parallel_example_context&);
bool run_parallel_inclusive_scan(parallel_example_context&);
bool run_parallel_is_heap(parallel_example_context&);
bool run_parallel_is_heap_until(parallel_example_context&);
bool run_parallel_is_partitioned(parallel_example_context&);
bool run_parallel_is_sorted(parallel_example_context&);
bool run_parallel_is_sorted_until(parallel_example_context&);
bool run_parallel_max_element(parallel_example_context&);
bool run_parallel_merge(parallel_example_context&);
bool run_parallel_min_element(parallel_example_context&);
bool run_parallel_mismatch(parallel_example_context&);
bool run_parallel_none_of(parallel_example_context&);
bool run_parallel_partition(parallel_example_context&);
bool run_parallel_partition_copy(parallel_example_context&);
bool run_parallel_reduce(parallel_example_context&);
bool run_parallel_remove(parallel_example_context&);
bool run_parallel_remove_copy(parallel_example_context&);
bool run_parallel_remove_copy_if(parallel_example_context&);
bool run_parallel_remove_if(parallel_example_context&);
bool run_parallel_replace(parallel_example_context&);
bool run_parallel_replace_copy(parallel_example_context&);
bool run_parallel_replace_copy_if(parallel_example_context&);
bool run_parallel_replace_if(parallel_example_context&);
bool run_parallel_reverse(parallel_example_context&);
bool run_parallel_reverse_copy(parallel_example_context&);
bool run_parallel_rotate(parallel_example_context&);
bool run_parallel_rotate_copy(parallel_example_context&);
bool run_parallel_shift_left(parallel_example_context&);
bool run_parallel_shift_right(parallel_example_context&);
bool run_parallel_sort(parallel_example_context&);
bool run_parallel_stable_partition(parallel_example_context&);
bool run_parallel_swap_ranges(parallel_example_context&);
bool run_parallel_transform(parallel_example_context&);
bool run_parallel_transform_exclusive_scan(parallel_example_context&);
bool run_parallel_transform_inclusive_scan(parallel_example_context&);
bool run_parallel_transform_reduce(parallel_example_context&);
bool run_parallel_unique(parallel_example_context&);
bool run_parallel_unique_copy(parallel_example_context&);

struct parallel_example_case {
    const char* name;
    bool (*run)(parallel_example_context&);
};
const parallel_example_case* parallel_example_cases(asc::std::size_t& count);

#endif  // CANN_ASC_STL_DOCS_PARALLEL_EXAMPLE_H
