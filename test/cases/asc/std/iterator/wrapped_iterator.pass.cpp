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
#include <asc/std/memory>
#include <type_traits>

namespace {
int storage[] = {9, 2, 4};
// The container implementations use raw-pointer iterators. This fixture gives the
// internal wrapper a valid nonempty sequence through its default constructor.
template <class T>
struct cursor {
    using value_type = int;
    using difference_type = __PTRDIFF_TYPE__;
    using pointer = T*;
    using reference = T&;
    using iterator_category = asc::std::random_access_iterator_tag;
    T* p = storage;
    cursor() = default;
    template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>, int> = 0>
    cursor(const cursor<U>& other) : p(other.p)
    {}
    operator T*() const
    {
        return p;
    }
    T* operator->() const
    {
        return p;
    }
    cursor& operator++()
    {
        ++p;
        return *this;
    }
    cursor& operator--()
    {
        --p;
        return *this;
    }
    cursor& operator+=(difference_type n)
    {
        p += n;
        return *this;
    }
};
template <class A, class B>
bool ordered(const A& a, const B& b)
{
    return !(a == b) && a != b && a < b && a <= b && b > a && b >= a && b - a == 2;
}

template <class I>
bool sequence(I begin)
{
    auto i = begin;
    if (*i++ != 9 || *++i != 4 || *i-- != 4 || *--i != 9)
        return false;
    if ((i += 2).operator->() != storage + 2 || (i -= 1).operator->() != storage + 1)
        return false;
    return (i + 1)[0] == 4 && (i - 1)[0] == 9 && i[-1] == 9 && i[1] == 4;
}
template <class I>
constexpr bool iterator_types()
{
    return std::is_same_v<typename I::value_type, int> &&
        std::is_same_v<typename I::difference_type, __PTRDIFF_TYPE__> && std::is_same_v<typename I::pointer, int*> &&
        std::is_same_v<typename I::reference, int&> &&
        std::is_same_v<typename I::iterator_category, asc::std::random_access_iterator_tag> &&
        std::is_same_v<typename I::iterator_concept, asc::std::contiguous_iterator_tag>;
}
}  // namespace

int main()
{
    using iter = asc::std::__wrap_iter<cursor<int>>;
    using read = asc::std::__wrap_iter<cursor<const int>>;
    static_assert(std::is_same_v<iter::iterator_type, cursor<int>>);
    static_assert(iterator_types<iter>() && iterator_types<asc::std::__bounded_iter<int*>>());
    auto bounded = asc::std::__make_bounded_iter(storage, storage, storage + 3);
    asc::std::__bounded_iter<const int*> constant(bounded);
    decltype(bounded) singular{};
    if (singular != decltype(bounded){})
        return 4;
    singular = bounded;
    decltype(bounded) moved(static_cast<decltype(bounded)&&>(singular));
    singular = static_cast<decltype(bounded)&&>(moved);
    iter begin{};
    if (constant.operator->() != storage || !sequence(singular) || !sequence(begin))
        return 3;
    auto tail = 2 + begin;
    read cb(begin), ct(tail);
    if (!ordered(begin, tail) || !ordered(begin, ct) || !ordered(cb, tail) || !(begin == cb) || !(begin == begin))
        return 1;
    return asc::std::pointer_traits<iter>::to_address(tail) == storage + 2 && asc::std::to_address(cb) == storage &&
            *tail == 4 ?
        0 :
        2;
}
