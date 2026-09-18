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

#include <asc/execution>

int main()
{
    static_assert(__is_trivially_copyable(asc::execution_status));
    constexpr asc::execution_status success{};
    static_assert(success.success());
    static_assert(success.code() == asc::execution_errc::success);
    static_assert(success.native_code() == 0);
    constexpr asc::execution_status backend{asc::execution_errc::backend_error, 17};
    static_assert(!backend.success());
    static_assert(backend.native_code() == 17);
    constexpr auto requirements = asc::require(asc::determinism::run_to_run);
    constexpr auto policy = asc::execution::device.require(requirements);
    static_assert(policy.requirements().determinism_value() == asc::determinism::run_to_run);
    return 0;
}
