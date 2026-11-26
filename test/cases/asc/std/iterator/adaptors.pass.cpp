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
#include <deque>
#include <type_traits>

namespace {

namespace ast = asc::std;

struct element {
    int value;
};
struct sentinel {
    element* end;
    friend constexpr bool operator==(element* it, sentinel last) noexcept
    {
        return it == last.end;
    }
    friend constexpr bool operator==(sentinel last, element* it) noexcept
    {
        return it == last;
    }
    friend constexpr bool operator!=(element* it, sentinel last) noexcept
    {
        return !(it == last);
    }
    friend constexpr bool operator!=(sentinel last, element* it) noexcept
    {
        return !(last == it);
    }
};
struct project {
    long operator()(element& value) const
    {
        return value.value;
    }
};

using container = std::deque<int>;
using counted = ast::counted_iterator<element*>;
using moved = ast::move_iterator<element*>;
using reversed = ast::reverse_iterator<element*>;
using common = ast::common_iterator<element*, sentinel>;
using legacy = ast::iterator<ast::forward_iterator_tag, element>;

template <class Inserter>
constexpr bool check_insert_traits()
{
    using expected_difference = std::conditional_t<CANN_ASC_STL_DETAIL_HAS_CXX20(), std::ptrdiff_t, void>;
    return std::is_same_v<typename Inserter::container_type, container> &&
        std::is_same_v<typename Inserter::iterator_category, ast::output_iterator_tag> &&
        std::is_same_v<typename Inserter::difference_type, expected_difference> &&
        std::is_same_v<typename Inserter::pointer, void> && std::is_same_v<typename Inserter::reference, void> &&
        std::is_same_v<typename Inserter::value_type, void>;
}
static_assert(check_insert_traits<ast::back_insert_iterator<container>>());
static_assert(check_insert_traits<ast::front_insert_iterator<container>>());
static_assert(check_insert_traits<ast::insert_iterator<container>>());
static_assert(std::is_same_v<legacy::iterator_category, ast::forward_iterator_tag>);
static_assert(std::is_same_v<legacy::value_type, element> && std::is_same_v<legacy::pointer, element*>);
static_assert(std::is_same_v<legacy::reference, element&> && std::is_same_v<legacy::difference_type, std::ptrdiff_t>);
static_assert(std::is_same_v<ast::iterator_traits<element*>::iterator_concept, ast::contiguous_iterator_tag>);
static_assert(std::is_same_v<ast::indirect_result_t<project, element*>, long>);
static_assert(std::is_same_v<ast::iter_common_reference_t<element*>, element&>);
static_assert(std::is_same_v<ast::iter_reference_t<const element*>, const element&>);
static_assert(std::is_same_v<ast::iter_value_t<const element*>, element>);
static_assert(std::is_same_v<ast::iter_difference_t<element*>, std::ptrdiff_t>);
static_assert(
    std::is_same_v<counted::iterator_type, element*> && std::is_same_v<counted::difference_type, std::ptrdiff_t>);
static_assert(std::is_same_v<moved::iterator_type, element*> && std::is_same_v<moved::value_type, element>);
static_assert(std::is_same_v<moved::pointer, element*> && std::is_same_v<moved::reference, element&&>);
static_assert(std::is_same_v<moved::difference_type, std::ptrdiff_t>);
static_assert(std::is_same_v<moved::iterator_concept, ast::random_access_iterator_tag>);
static_assert(std::is_same_v<reversed::iterator_type, element*> && std::is_same_v<reversed::pointer, element*>);
static_assert(!ast::disable_sized_sentinel_for<element*, element*>);

bool check_insertion()
{
    container values;
    ast::back_insert_iterator<container> back(values);
    *back++ = 4;
    *++back = 7;
    ast::front_insert_iterator<container> front(values);
    *front++ = 1;
    *++front = -1;
    ast::insert_iterator<container> middle(values, values.begin() + 2);
    middle++;
    *middle = 2;
    *++middle = 3;
    const container expected{-1, 1, 2, 3, 4, 7};
    return values == expected && values.end() == ast::cend(values);
}

bool check_counted_and_common()
{
    element entries[] = {{3}, {5}, {7}, {9}};
    counted start(entries, 4);
    auto current = start + 2;
    if (current->value != 7 || current.count() != 2 || current[1].value != 9) {
        return false;
    }
    current -= 1;
    if (current++->value != 5 || (--current)->value != 5) {
        return false;
    }
    current += 2;
    auto prior = current - 1;
    if (current.base() != entries + 3 || prior.base() != entries + 2 || prior.count() != 2) {
        return false;
    }
    prior = current;
    ++prior;
    const ast::default_sentinel_t stop{};
    if (prior != stop || prior.count() != 0 || ast::cend(entries) != entries + 4) {
        return false;
    }
    common cursor(entries);
    const common end(sentinel{entries + 2});
    if (cursor->value != 3 || (cursor++)->value != 3 || cursor->value != 5 || ++cursor != end) {
        return false;
    }
    cursor = end;
    const ast::unreachable_sentinel_t infinite{};
    return cursor == end && entries != infinite && infinite != entries + 4;
}

bool check_move_and_reverse()
{
    element entries[] = {{1}, {2}, {3}, {4}};
    moved cursor(entries);
    auto pos = cursor + 2;
    if (pos[1].value != 4 || pos.operator->() != entries + 2 || (pos--).base() != entries + 2) {
        return false;
    }
    pos += 2;
    pos -= 1;
    if ((pos++).base() != entries + 2 || (--pos).base() != entries + 2 || (pos - 1).base() != entries + 1) {
        return false;
    }
    pos = cursor;
    if (pos.base() != entries || (++pos).base() != entries + 1) {
        return false;
    }
    ast::move_sentinel<const element*> end;
    end = ast::move_sentinel<element*>{entries + 4};
    if (end.base() != entries + 4) {
        return false;
    }

    reversed backward(entries + 4);
    auto second = backward + 1;
    if (second[1].value != 2 || (second++).base() != entries + 3 || (++second).base() != entries + 1) {
        return false;
    }
    second -= 1;
    if ((second--).base() != entries + 2 || (--second).base() != entries + 4) {
        return false;
    }
    second += 2;
    return second.base() == entries + 2 && (second - 1).base() == entries + 3 && (*second).value == 2;
}

}  // namespace

int main()
{
    if (!check_insertion()) {
        return 1;
    }
    if (!check_counted_and_common()) {
        return 2;
    }
    return check_move_and_reverse() ? 0 : 3;
}
