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

#ifndef CANN_ASC_STL_ASC_STD___SET_SET_H
#define CANN_ASC_STL_ASC_STD___SET_SET_H

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

template <class Key, class Compare, class Allocator>
class set {
    using tree_type = __arena_associative_detail::basic_tree<Key, Key, __arena_associative_detail::identity_key<Key>,
        Compare, Allocator>;

public:
    using value_type = Key;
    using size_type = __SIZE_TYPE__;
    using iterator = typename tree_type::iterator;
    CANN_ASC_STL_API explicit set(const Allocator& allocator) : tree_(Compare{}, allocator)
    {}
    CANN_ASC_STL_API set(const Compare& compare, const Allocator& allocator) : tree_(compare, allocator)
    {}
    set(const set&) = delete;
    set& operator=(const set&) = delete;
    CANN_ASC_STL_API set(set&&) noexcept = default;
    CANN_ASC_STL_API set& operator=(set&&) noexcept = default;
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
    CANN_ASC_STL_API pair<iterator, bool> insert(const Key& key)
    {
        __arena_pair<iterator, bool> result = tree_.insert(key);
        return pair<iterator, bool>(result.first, result.second);  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API pair<iterator, bool> insert(Key&& key)
    {
        __arena_pair<iterator, bool> result = tree_.insert(static_cast<Key&&>(key));
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
    CANN_ASC_STL_API void clear() noexcept
    {
        tree_.clear();
    }

private:
    tree_type tree_;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___SET_SET_H
