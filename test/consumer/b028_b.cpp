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

#include <asc/std/map>
#include <asc/std/list>
#include <asc/std/__functional/mem_fn.h>
#include <asc/std/__functional/not_fn.h>
#include <asc/std/__system_error/lightweight_error.h>
#include <asc/std/__type_traits/is_aggregate.h>
#include <asc/std/__utility/rel_ops.h>

namespace {
struct aggregate {
    int value;
};
struct member {
    int value;
};
struct equals_zero {
    bool operator()(int value) const
    {
        return value == 0;
    }
};
}  // namespace

int asc_stl_b028_consumer_b()
{
    static_assert(asc::std::is_aggregate_v<aggregate>);
    member value{4};
    const bool traits = asc::std::is_error_condition_enum<asc::std::errc>::value;
    return asc::std::mem_fn(&member::value)(value) == 4 && asc::std::not_fn(equals_zero{})(4) && traits ? 0 : 1;
}
