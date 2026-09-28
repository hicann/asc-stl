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

#include <asc/buffer>
#include <asc/memory_pool>
#include <asc/std/__functional/bind.h>
#include <asc/std/__cwchar/algorithms.h>

int asc_stl_b025_consumer_a()
{
    // The two new public entries parse and expose their exact vocabulary on
    // the installed tree. Like the memory-resource consumer before it, only
    // the metadata surface is exercised here: constructing a pool or buffer
    // would instantiate the ACL-bound event and resource members, whose
    // runtime behavior is covered by the target-derived ACL-stub semantic
    // cases instead.
    constexpr asc::memory_pool_statistics statistics{300, 100, 200};
    static_assert(statistics.reserved_bytes() == 300 && statistics.used_bytes() == 100);
    static_assert(statistics.cached_bytes() == 200);
    constexpr asc::device_memory_pool_config pool_config{0, 1u << 20, 1u << 18};
    constexpr asc::pinned_memory_pool_config pinned_config{1u << 18, 1u << 16};
    static_assert(pool_config.device_ordinal == 0 && pool_config.release_threshold == 1u << 18);
    static_assert(pinned_config.maximum_cached_bytes == 1u << 18);
    using asc::std::placeholders::_1;
    auto bound = asc::std::bind([](int left, int right) { return left + right; }, _1, 31);
    const wchar_t text[4] = {L'h', L'i', L'!', L'\0'};
    return bound(11) == 42 && asc::std::wcslen(text) == 3 ? 0 : 1;
}
