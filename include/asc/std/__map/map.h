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

#ifndef CANN_ASC_STL_ASC_STD___MAP_MAP_H
#define CANN_ASC_STL_ASC_STD___MAP_MAP_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__tree/tree.h>
#include <asc/std/__utility/pair.h>

namespace asc::std {

// Members use CANN_ASC_STL_API like the set/unordered_* family: under the
// CCE SIMD branch CANN_ASC_STL_HOST_SIMT_API would degrade these to host-only
// calls, diverging from the sibling associative containers.
template <class Key, class T, class Compare, class Allocator>
class map {
public:
    using value_type = __arena_pair<const Key, T>;

private:
    using tree_type = __arena_associative_detail::basic_tree<Key, value_type,
        __arena_associative_detail::__arena_pair_key<Key, T>, Compare, Allocator>;

public:
    using size_type = __SIZE_TYPE__;
    using iterator = typename tree_type::iterator;
    CANN_ASC_STL_API explicit map(const Allocator& allocator) : tree_(Compare{}, allocator)
    {}
    CANN_ASC_STL_API map(const Compare& compare, const Allocator& allocator) : tree_(compare, allocator)
    {}
    map(const map&) = delete;
    map& operator=(const map&) = delete;
    CANN_ASC_STL_API map(map&&) noexcept = default;
    CANN_ASC_STL_API map& operator=(map&&) noexcept = default;
    CANN_ASC_STL_API bool empty() const noexcept
    {
        return tree_.empty();
    }
    CANN_ASC_STL_API size_type size() const noexcept
    {
        return tree_.size();
    }
    CANN_ASC_STL_API iterator begin() noexcept
    {
        return tree_.begin();
    }
    CANN_ASC_STL_API iterator end() noexcept
    {
        return tree_.end();
    }
    CANN_ASC_STL_API pair<iterator, bool> insert(const value_type& value)
    {
        __arena_pair<iterator, bool> result = tree_.insert(value);
        return pair<iterator, bool>(result.first, result.second);  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API pair<iterator, bool> insert(value_type&& value)
    {
        __arena_pair<iterator, bool> result = tree_.insert(static_cast<value_type&&>(value));
        return pair<iterator, bool>(result.first, result.second);  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API iterator find(const Key& key) noexcept
    {
        return tree_.find(key);
    }
    CANN_ASC_STL_API size_type count(const Key& key) noexcept
    {
        return tree_.count(key);
    }
    CANN_ASC_STL_API T& operator[](const Key& key)
    {
        iterator found = find(key);
        if (found != end())
            return found->second;
        // insert() reports arena exhaustion by failing fast instead of
        // returning an invalid iterator, so the returned node is always
        // dereferenceable and the extra find() round trip is unnecessary.
        return tree_.insert(value_type(key, T{})).first->second;
    }
    CANN_ASC_STL_API void clear() noexcept
    {
        tree_.clear();
    }

private:
    tree_type tree_;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___MAP_MAP_H
