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

#ifndef ASC_STL_TEST_ASSOCIATIVE_ITERATOR_CHECKS_H
#define ASC_STL_TEST_ASSOCIATIVE_ITERATOR_CHECKS_H

#include <asc/__config>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/declval.h>

namespace asc_stl_associative_iterator_test {

template <class Iterator, class Element>
inline constexpr bool exposes_element = asc::std::is_same_v<decltype(*asc::std::declval<Iterator&>()), Element&> &&
    asc::std::is_same_v<decltype(asc::std::declval<Iterator&>().operator->()), Element*>;

template <class Set, class Key>
CANN_ASC_STL_HOST_SIMT_API bool check_key(Set& values, const Key& key)
{
    auto inserted = values.insert(key);
    auto found = values.find(key);
    static_assert(asc::std::is_same_v<decltype(values.begin()), decltype(found)>);
    static_assert(asc::std::is_same_v<decltype(inserted.first), decltype(found)>);
    static_assert(exposes_element<decltype(found), const Key>);
    if (!inserted.second || found == values.end() || found != inserted.first) {
        return false;
    }
    auto duplicate = values.insert(key);
    return !duplicate.second && duplicate.first == found && found.operator->() == asc::std::addressof(*found);
}

template <class Map, class Key, class Mapped>
CANN_ASC_STL_HOST_SIMT_API bool update_mapped(Map& values, const Key& key, const Mapped& replacement)
{
    auto found = values.find(key);
    static_assert(asc::std::is_same_v<decltype((found->first)), const Key&>);
    static_assert(asc::std::is_same_v<decltype(((*found).second)), Mapped&>);
    if (found == values.end()) {
        return false;
    }
    found->second = replacement;
    return values[key] == replacement;
}

}  // namespace asc_stl_associative_iterator_test

#endif  // ASC_STL_TEST_ASSOCIATIVE_ITERATOR_CHECKS_H
