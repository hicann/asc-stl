/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include <asc/std/__utility/exception_guard.h>
struct Rollback {
    int* count;
    constexpr void operator()() const
    {
        ++*count;
    }
};
int main()
{
    int count = 0;
    {
        auto guard = asc::std::__make_exception_guard(Rollback{&count});
    }
    if (count != 1)
        return 1;
    {
        auto guard = asc::std::__make_exception_guard(Rollback{&count});
        guard.__complete();
    }
    if (count != 1)
        return 2;
    {
        auto first = asc::std::__make_exception_guard(Rollback{&count});
        auto moved = asc::std::move(first);  // NOLINT(build/include_what_you_use)
        moved.__complete();
    }
    return count == 1 ? 0 : 3;
}
