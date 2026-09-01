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

#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/is_same.h>

template <class _Tp>
using CvRef = _Tp const&;

struct Left {};

struct Right {};

struct Common {};

namespace asc::std {
template <template <class> class _TQual, template <class> class _UQual>
struct basic_common_reference<Left, Right, _TQual, _UQual> {
    using type = Common;
};
}  // namespace asc::std

static_assert(asc::std::is_same_v<asc::std::common_reference_t<int>, int>);
static_assert(asc::std::is_same_v<asc::std::common_reference_t<int&, int&>, int&>);
static_assert(asc::std::is_same_v<asc::std::common_reference_t<const int&, int&>, const int&>);
static_assert(asc::std::is_same_v<asc::std::common_reference_t<int&&, int&&>, int&&>);
static_assert(asc::std::is_same_v<asc::std::common_reference_t<int&&, const int&>, const int&>);
static_assert(asc::std::is_same_v<asc::std::common_reference_t<int, double>, double>);
static_assert(asc::std::is_same_v<asc::std::common_reference_t<Left, Right>, Common>);
static_assert(asc::std::is_same_v<asc::std::common_reference_t<short, int, long>, long>);
static_assert(asc::std::__has_common_reference<int&, const int&>);

int main()
{
    return 0;
}
