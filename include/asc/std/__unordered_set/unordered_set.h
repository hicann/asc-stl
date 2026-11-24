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

#ifndef CANN_ASC_STL_ASC_STD___UNORDERED_SET_UNORDERED_SET_H
#define CANN_ASC_STL_ASC_STD___UNORDERED_SET_UNORDERED_SET_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__hash_table/hash_table.h>

namespace asc::std {

template <class Key, class Hash, class Equal, class Allocator>
class unordered_set {
    using table_type = __arena_associative_detail::basic_hash_table<Key, Key,
        __arena_associative_detail::identity_key<Key>, Hash, Equal, Allocator>;

public:
    using size_type = __SIZE_TYPE__;
    using iterator = typename table_type::iterator;
    CANN_ASC_STL_API explicit unordered_set(const Allocator& allocator) : table_(Hash{}, Equal{}, allocator)
    {}
    unordered_set(const unordered_set&) = delete;
    unordered_set& operator=(const unordered_set&) = delete;
    CANN_ASC_STL_API unordered_set(unordered_set&&) noexcept = default;
    CANN_ASC_STL_API unordered_set& operator=(unordered_set&&) noexcept = default;
    CANN_ASC_STL_API bool empty() const noexcept
    {
        return table_.empty();
    }
    CANN_ASC_STL_API size_type size() const noexcept
    {
        return table_.size();
    }
    CANN_ASC_STL_API size_type bucket_count() const noexcept
    {
        return table_.bucket_count();
    }
    CANN_ASC_STL_API iterator begin() noexcept
    {
        return table_.begin();
    }
    CANN_ASC_STL_API iterator end() noexcept
    {
        return table_.end();
    }
    CANN_ASC_STL_API __arena_pair<iterator, bool> insert(const Key& key)
    {
        return table_.insert(key);
    }
    CANN_ASC_STL_API __arena_pair<iterator, bool> insert(Key&& key)
    {
        return table_.insert(static_cast<Key&&>(key));
    }
    CANN_ASC_STL_API iterator find(const Key& key) noexcept
    {
        return table_.find(key);
    }
    CANN_ASC_STL_API size_type count(const Key& key) noexcept
    {
        return table_.count(key);
    }
    CANN_ASC_STL_API void clear() noexcept
    {
        table_.clear();
    }

private:
    table_type table_;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___UNORDERED_SET_UNORDERED_SET_H
