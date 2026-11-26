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

#include <asc/std/tuple>

#include <type_traits>

namespace {
using asc::std::allocator_arg;
using asc::std::get;
using asc::std::move;
using asc::std::tuple;
using asc::std::tuple_cat;
using asc::std::tuple_size_v;

struct explicit_int {
    int value;
    explicit explicit_int(int x) : value(x)
    {}
    explicit explicit_int(const explicit_int& other) : value(other.value)
    {}
    explicit_int(explicit_int&&) = default;
};

struct allocator {
    int tag;
};

struct explicit_default {
    int value;
    explicit constexpr explicit_default() noexcept : value(13)
    {}
};

template <class T>
void accept(T);
template <class T, class = void>
inline constexpr bool implicit_default = false;
template <class T>
inline constexpr bool implicit_default<T, std::void_t<decltype(accept<T>({}))>> = true;

static_assert(!std::is_default_constructible_v<tuple<int&>> && !std::is_default_constructible_v<tuple<explicit_int>>);
static_assert(implicit_default<tuple<int>> && !implicit_default<tuple<int, explicit_default>>);
static_assert(std::is_trivially_default_constructible_v<tuple<>>);
static_assert(get<0>(tuple<const int>{}) == 0 && get<1>(tuple<int, explicit_default>{}).value == 13);

struct allocated {
    using allocator_type = allocator;
    int value;
    int allocator_tag;
    allocated(asc::std::allocator_arg_t, const allocator& a) : value(0), allocator_tag(a.tag)
    {}
    allocated(int n) : value(n), allocator_tag(0)  // NOLINT(runtime/explicit)
    {}
    allocated(asc::std::allocator_arg_t, const allocator& a, int n) : value(n), allocator_tag(a.tag)
    {}
    allocated(asc::std::allocator_arg_t, const allocator& a, const allocated& other)
        : value(other.value), allocator_tag(a.tag)
    {}
    allocated(asc::std::allocator_arg_t, const allocator& a, allocated&& other)
        : value(other.value), allocator_tag(a.tag)
    {
        other.value = -1;
    }
};

struct empty_allocated {
    using allocator_type = allocator;
    static inline int tag = 0;
    explicit empty_allocated(const allocator& a)
    {
        tag = a.tag;
    }
    empty_allocated(const empty_allocated&, const allocator& a)
    {
        tag = -a.tag;
    }
};

int allocator_construction()
{
    const allocator a{41};
    tuple<int> zero(allocator_arg, a);
    if (get<0>(zero) != 0)
        return 1;
    tuple<allocated, empty_allocated> defaults(allocator_arg, a);
    if (get<0>(defaults).allocator_tag != a.tag || empty_allocated::tag != a.tag)
        return 3;
    const auto& fixed = defaults;
    tuple<allocated, empty_allocated> cloned(allocator_arg, a, fixed);
    if (get<0>(cloned).allocator_tag != a.tag || empty_allocated::tag != -a.tag)
        return 4;
    const allocated element(6);
    tuple<allocated> copied_element(allocator_arg, a, element);
    const auto& ref = copied_element;
    tuple<allocated> copied(allocator_arg, a, ref);
    tuple<allocated> moved(allocator_arg, a, move(copied));
    const tuple<int> number(8);
    tuple<allocated> converted(allocator_arg, a, number);
    return get<0>(copied_element).allocator_tag == 41 && get<0>(moved).value == 6 &&
            get<0>(moved).allocator_tag == 41 && get<0>(copied).value == -1 && get<0>(converted).value == 8 &&
            get<0>(converted).allocator_tag == 41 ?
        0 :
        2;
}
}  // namespace

int main()
{
    auto empty = tuple_cat();
    static_assert(tuple_size_v<decltype(empty)> == 0);
    const allocator a{5};
    tuple<> allocated_empty(allocator_arg, a);
    const tuple<> copied_empty(allocator_arg, a, allocated_empty);
    tuple<> moved_empty(allocator_arg, a, move(allocated_empty));
    moved_empty = copied_empty;
    moved_empty.swap(allocated_empty);
    const explicit_int x(4);
    tuple<explicit_int, int> value(x, 3);
    const int y = 7;
    tuple<explicit_int, int> explicit_copy(x, y);
    if (get<0>(value).value != 4 || get<0>(explicit_copy).value != 4)
        return 1;
    tuple<int, short> source(5, 2);
    const auto& ref = source;
    tuple<explicit_int, int> from_const(ref);
    tuple<explicit_int, int> from_rvalue(move(source));
    if (get<explicit_int>(from_const).value != 5 || get<0>(from_rvalue).value != 5)
        return 2;
    tuple<int, short> copied(ref);
    tuple<int, short> moved(move(copied));
    tuple<int, short> assigned;
    if (get<0>(assigned) != 0 || get<1>(assigned) != 0)
        return 5;
    assigned = ref;
    if (get<0>(assigned) != 5 || get<1>(assigned) != 2 || get<0>(moved) != 5 || get<1>(moved) != 2)
        return 4;
    get<0>(moved) = -7;
    assigned = move(moved);
    tuple<long, int> wide;  // NOLINT(build/include_what_you_use)
    wide = ref;
    if (get<long>(wide) != 5 || get<0>(assigned) != -7 || get<short>(move(assigned)) != 2 || get<0>(move(ref)) != 5 ||
        get<int>(ref) != 5 || get<short>(move(ref)) != 2)  // NOLINT(build/include_what_you_use)
        return 3;
    return allocator_construction();
}
