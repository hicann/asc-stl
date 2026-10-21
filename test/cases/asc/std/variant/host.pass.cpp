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

#include <initializer_list>

#include "../../../../support/w09_w10_semantics.h"

namespace {

struct construction_failure {};

struct lifetime_token {
    inline static int alive = 0;
    inline static int constructed = 0;
    inline static int destroyed = 0;

    explicit lifetime_token(int = 0)
    {
        ++alive;
        ++constructed;
    }
    lifetime_token(const lifetime_token&) : lifetime_token()
    {}
    lifetime_token(lifetime_token&&) : lifetime_token()
    {}
    lifetime_token& operator=(const lifetime_token&) = default;
    lifetime_token& operator=(lifetime_token&&) = default;
    ~lifetime_token()
    {
        --alive;
        ++destroyed;
    }
};

struct throwing_value {
    inline static int alive = 0;
    inline static int constructed = 0;
    inline static int destroyed = 0;
    inline static bool fail_construction = false;
    inline static bool fail_copy = false;
    inline static bool fail_move = false;
    inline static bool fail_assignment = false;
    int value;

    explicit throwing_value(int input) : value(input)
    {
        finish_construction(fail_construction);
    }
    throwing_value(std::initializer_list<int> values, int input) : value(input + static_cast<int>(values.size()))
    {
        finish_construction(fail_construction);
    }
    throwing_value(const throwing_value& other) : value(other.value)
    {
        finish_construction(fail_copy);
    }
    throwing_value(throwing_value&& other) : value(other.value)
    {
        finish_construction(fail_move);
    }
    throwing_value& operator=(const throwing_value& other)
    {
        value = other.value;
        if (fail_assignment)
            throw construction_failure{};
        return *this;
    }
    throwing_value& operator=(throwing_value&& other)
    {
        value = other.value;
        if (fail_assignment)
            throw construction_failure{};
        return *this;
    }
    ~throwing_value()
    {
        --alive;
        ++destroyed;
    }

private:
    static void finish_construction(bool fail)
    {
        if (fail)
            throw construction_failure{};
        ++alive;
        ++constructed;
    }
};

using variant_type = asc::std::variant<lifetime_token, throwing_value>;
using nested_variant_type = asc::std::variant<int, lifetime_token, throwing_value>;

template <asc::std::size_t Index = 1, class Variant>
bool has_no_active_value(Variant& value)
{
    return value.valueless_by_exception() && value.index() == asc::std::variant_npos &&
        asc::std::get_if<0>(&value) == nullptr && asc::std::get_if<Index>(&value) == nullptr;
}

bool lifetimes_balanced()
{
    return lifetime_token::alive == 0 && lifetime_token::constructed == lifetime_token::destroyed &&
        throwing_value::alive == 0 && throwing_value::constructed == throwing_value::destroyed;
}

template <class Variant = variant_type, asc::std::size_t Index = 1>
bool assignment_changes_alternative(bool move)
{
    bool observed = false;
    {
        Variant target(asc::std::in_place_type<lifetime_token>);
        Variant source(asc::std::in_place_index<Index>, 23);
        throwing_value::fail_copy = !move;
        throwing_value::fail_move = move;
        try {
            if (move)
                target = asc::std::move(source);
            else
                target = source;
        } catch (const construction_failure&) {
            observed = has_no_active_value<Index>(target) && source.index() == Index && lifetime_token::alive == 0 &&
                throwing_value::alive == 1;
        }
        throwing_value::fail_copy = false;
        throwing_value::fail_move = false;
        auto& recovered = target.template emplace<Index>(31);
        observed = observed && !target.valueless_by_exception() && target.index() == Index && recovered.value == 31;
    }
    return observed && lifetimes_balanced();
}

template <class Variant = variant_type, asc::std::size_t Index = 1>
bool emplace_changes_alternative(int form)
{
    bool observed = false;
    {
        Variant target(asc::std::in_place_type<lifetime_token>);
        throwing_value::fail_construction = true;
        try {
            if (form == 0)
                target.template emplace<Index>(23);
            else if (form == 1)
                target.template emplace<throwing_value>(23);
            else if (form == 2)
                target.template emplace<Index>({1, 2}, 23);
            else
                target.template emplace<throwing_value>({1, 2}, 23);
        } catch (const construction_failure&) {
            observed = has_no_active_value<Index>(target) && lifetime_token::alive == 0 && throwing_value::alive == 0;
        }
        throwing_value::fail_construction = false;
        auto& recovered = target.template emplace<Index>(31);
        observed = observed && target.index() == Index && !target.valueless_by_exception() && recovered.value == 31;
    }
    return observed && lifetimes_balanced();
}

bool assignment_keeps_alternative(bool move)
{
    bool observed = false;
    {
        variant_type target(asc::std::in_place_index<1>, 7);
        variant_type source(asc::std::in_place_index<1>, 23);
        const int destroyed_before = throwing_value::destroyed;
        throwing_value::fail_assignment = true;
        try {
            if (move)
                target = asc::std::move(source);
            else
                target = source;
        } catch (const construction_failure&) {
            // The contained assignment may change its value before throwing; its lifetime continues.
            observed = target.index() == 1 && !target.valueless_by_exception() &&
                asc::std::get<1>(target).value == 23 && throwing_value::alive == 2 &&
                throwing_value::destroyed == destroyed_before;
        }
        throwing_value::fail_assignment = false;
    }
    return observed && lifetimes_balanced();
}

template <class Variant = variant_type, asc::std::size_t Index = 1>
bool assignment_from_valueless()
{
    bool observed = false;
    {
        Variant source(asc::std::in_place_type<lifetime_token>);
        throwing_value::fail_construction = true;
        try {
            source.template emplace<Index>(3);
        } catch (const construction_failure&) {
            observed = has_no_active_value<Index>(source);
        }
        throwing_value::fail_construction = false;
        Variant copied(asc::std::in_place_type<lifetime_token>);
        copied = source;
        Variant moved(asc::std::in_place_type<lifetime_token>);
        moved = asc::std::move(source);
        Variant copy_constructed(source);
        Variant move_constructed(asc::std::move(source));
        copied = copy_constructed;
        moved = asc::std::move(move_constructed);  // NOLINT(build/include_what_you_use)
        observed = observed && has_no_active_value<Index>(copied) && has_no_active_value<Index>(moved) &&
            has_no_active_value<Index>(copy_constructed) && has_no_active_value<Index>(move_constructed);
    }
    return observed && lifetimes_balanced();
}

int evaluate_exception_state()
{
    if (!assignment_changes_alternative(false))
        return 101;
    if (!assignment_changes_alternative(true))
        return 102;
    for (int form = 0; form != 4; ++form) {
        if (!emplace_changes_alternative(form))
            return 103 + form;
    }
    if (!assignment_keeps_alternative(false))
        return 107;
    if (!assignment_keeps_alternative(true))
        return 108;
    if (!assignment_from_valueless())
        return 109;
    if (!assignment_changes_alternative<nested_variant_type, 2>(false))
        return 110;
    if (!assignment_changes_alternative<nested_variant_type, 2>(true))
        return 111;
    for (int form = 0; form != 4; ++form) {
        if (!emplace_changes_alternative<nested_variant_type, 2>(form))
            return 112 + form;
    }
    if (!assignment_from_valueless<nested_variant_type, 2>())
        return 116;
    return 0;
}

}  // namespace

int main()
{
    const int shared = asc_stl_w09_w10_test::evaluate_memory_variant();
    return shared != 0 ? shared : evaluate_exception_state();
}
