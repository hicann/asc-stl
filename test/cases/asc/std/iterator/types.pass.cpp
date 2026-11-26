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

#include <asc/std/iterator>
#include <cstddef>
#include <type_traits>

namespace s = asc::std;

using wrapped = s::__wrap_iter<const int*>;
using bounded = s::__bounded_iter<const int*>;
using counted = s::counted_iterator<int*>;
using common = s::common_iterator<counted, s::default_sentinel_t>;
using ct = s::iterator_traits<common>;
static_assert(std::is_same_v<ct::iterator_concept, s::forward_iterator_tag>);
static_assert(std::is_same_v<ct::iterator_category, s::forward_iterator_tag>);
static_assert(std::is_same_v<ct::pointer, counted>);
static_assert(std::is_same_v<ct::value_type, int>);
static_assert(std::is_same_v<ct::difference_type, std::ptrdiff_t>);
static_assert(std::is_same_v<ct::reference, int&>);
template <class I>
constexpr bool ptr_types()
{
    using t = s::pointer_traits<I>;
    return std::is_same_v<typename t::pointer, I> && std::is_same_v<typename t::difference_type, std::ptrdiff_t> &&
        std::is_same_v<typename t::element_type, const int>;
}
static_assert(ptr_types<wrapped>() && ptr_types<bounded>());
static_assert(std::is_same_v<s::iterator_traits<int*>::iterator_category, s::random_access_iterator_tag>);
static_assert(std::is_same_v<s::iterator_traits<counted>::pointer, int*>);
static_assert(std::is_same_v<s::incrementable_traits<common>::difference_type, std::ptrdiff_t>);
struct projection {
    short operator()(int) const;
};
using projected = s::projected<int*, projection>;
static_assert(std::is_same_v<decltype(*s::declval<const projected&>()), short>);
static_assert(std::is_same_v<projected::value_type, short> &&
    std::is_same_v<s::incrementable_traits<projected>::difference_type, std::ptrdiff_t>);

int main()
{}
