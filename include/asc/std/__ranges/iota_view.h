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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_IOTA_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_IOTA_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__concepts/semiregular.h>
#include <asc/std/__concepts/totally_ordered.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/unreachable_sentinel.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

namespace asc::std::ranges {

// 计数迭代器的迭代器概念层级：整型值具备完整随机访问运算，其余弱递增类型保守降级为输入迭代器。
template <class Value>
using __iota_iterator_concept = conditional_t<is_integral_v<Value>, random_access_iterator_tag, input_iterator_tag>;

template <class Value, class Bound = unreachable_sentinel_t>
class iota_view : public view_interface<iota_view<Value, Bound>> {
public:
    // 保持基座公开成员名 iterator；实现改为本文件内嵌计数迭代器（不再依赖 __iota_iterator）。
    class iterator {
    public:
        using iterator_concept = __iota_iterator_concept<Value>;
        using iterator_category = __iota_iterator_concept<Value>;
        using value_type = Value;
        using difference_type = __PTRDIFF_TYPE__;
        using reference = Value;
        using pointer = void;

        CANN_ASC_STL_API constexpr iterator() noexcept : value_{}
        {}
        CANN_ASC_STL_API constexpr explicit iterator(Value value) noexcept : value_(value)
        {}
        CANN_ASC_STL_API constexpr Value operator*() const noexcept
        {
            return value_;
        }
        CANN_ASC_STL_API constexpr Value operator[](difference_type offset) const noexcept
        {
            return static_cast<Value>(value_ + offset);
        }
        CANN_ASC_STL_API constexpr iterator& operator++() noexcept
        {
            ++value_;
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator operator++(int) noexcept
        {
            auto copy = *this;
            ++*this;
            return copy;
        }
        CANN_ASC_STL_API constexpr iterator& operator--() noexcept
        {
            --value_;
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator operator--(int) noexcept
        {
            auto copy = *this;
            --*this;
            return copy;
        }
        CANN_ASC_STL_API constexpr iterator& operator+=(difference_type value) noexcept
        {
            value_ = static_cast<Value>(value_ + value);
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator& operator-=(difference_type value) noexcept
        {
            return *this += -value;
        }
        friend CANN_ASC_STL_API constexpr iterator operator+(iterator value, difference_type offset) noexcept
        {
            value += offset;
            return value;
        }
        friend CANN_ASC_STL_API constexpr iterator operator+(difference_type offset, iterator value) noexcept
        {
            value += offset;
            return value;
        }
        friend CANN_ASC_STL_API constexpr iterator operator-(iterator value, difference_type offset) noexcept
        {
            value -= offset;
            return value;
        }
        friend CANN_ASC_STL_API constexpr difference_type operator-(iterator left, iterator right) noexcept
        {
            return static_cast<difference_type>(left.value_ - right.value_);
        }
        friend CANN_ASC_STL_API constexpr bool operator==(iterator left, iterator right) noexcept
        {
            return left.value_ == right.value_;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(iterator left, iterator right) noexcept
        {
            return !(left == right);
        }
        friend CANN_ASC_STL_API constexpr bool operator<(iterator left, iterator right) noexcept
        {
            return left.value_ < right.value_;
        }
        friend CANN_ASC_STL_API constexpr bool operator<=(iterator left, iterator right) noexcept
        {
            return !(right < left);
        }
        friend CANN_ASC_STL_API constexpr bool operator>(iterator left, iterator right) noexcept
        {
            return right < left;
        }
        friend CANN_ASC_STL_API constexpr bool operator>=(iterator left, iterator right) noexcept
        {
            return !(left < right);
        }

    private:
        Value value_;
    };
    using __iterator = iterator;

    // 异构有界哨兵：保存原始 Bound，避免窄化回 Value 造成的截断。
    struct __sentinel {
        friend class iota_view;

    private:
        Bound bound_sentinel_ = Bound();

    public:
        __sentinel() = default;
        CANN_ASC_STL_API constexpr explicit __sentinel(Bound bound_sentinel) noexcept(
            is_nothrow_move_constructible_v<Bound>)
            : bound_sentinel_(::asc::std::move(bound_sentinel))
        {}

        [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
            const __iterator& x, const __sentinel& y) noexcept
        {
            return *x == y.bound_sentinel_;
        }
#if !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
        [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
            const __sentinel& x, const __iterator& y) noexcept
        {
            return x.bound_sentinel_ == *y;
        }

        [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
            const __iterator& x, const __sentinel& y) noexcept
        {
            return !(*x == y.bound_sentinel_);
        }

        [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
            const __sentinel& x, const __iterator& y) noexcept
        {
            return !(x.bound_sentinel_ == *y);
        }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
        template <class Bound2 = Bound>
            requires sized_sentinel_for<Bound2, Value>
        [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_difference_t<Value> operator-(
            const __iterator& x, const __sentinel& y) noexcept
        {
            return static_cast<iter_difference_t<Value>>(*x - y.bound_sentinel_);
        }

        template <class Bound2 = Bound>
            requires sized_sentinel_for<Bound2, Value>
        [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_difference_t<Value> operator-(
            const __sentinel& x, const __iterator& y) noexcept
        {
            return -(y - x);
        }
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    };

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr iota_view()
        requires default_initializable<Value>
    = default;
#else
    CANN_ASC_STL_API constexpr iota_view() noexcept : value_{}, bound_sentinel_{}
    {}
#endif
    CANN_ASC_STL_API constexpr explicit iota_view(Value value) noexcept
        : value_(::asc::std::move(value)), bound_sentinel_{}
    {}
    CANN_ASC_STL_API constexpr iota_view(type_identity_t<Value> value, type_identity_t<Bound> bound_sentinel) noexcept
        : value_(::asc::std::move(value)), bound_sentinel_(::asc::std::move(bound_sentinel))
    {}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class Bound2 = Bound>
        requires same_as<Value, Bound2>
    CANN_ASC_STL_API constexpr iota_view(__iterator first, __iterator last) noexcept : iota_view(*first, *last)
    {}

    template <class Bound2 = Bound>
        requires same_as<Bound2, unreachable_sentinel_t>
    CANN_ASC_STL_API constexpr iota_view(__iterator first, Bound2 last) noexcept
        : iota_view(*first, ::asc::std::move(last))
    {}

    template <class Bound2 = Bound>
        requires(!same_as<Value, Bound2> && !same_as<Value, unreachable_sentinel_t>)
    CANN_ASC_STL_API constexpr iota_view(__iterator first, __sentinel last) noexcept
        : iota_view(*first, ::asc::std::move(last.bound_sentinel_))
    {}
#else
    template <class Bound2 = Bound, enable_if_t<is_same_v<Value, Bound2>, int> = 0>
    CANN_ASC_STL_API constexpr iota_view(__iterator first, __iterator last) noexcept : iota_view(*first, *last)
    {}
#endif

    [[nodiscard]] CANN_ASC_STL_API constexpr __iterator begin() const noexcept
    {
        return __iterator(value_);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr auto end() const noexcept
    {
        if constexpr (is_same_v<Value, Bound>) {
            return __iterator(bound_sentinel_);
        } else if constexpr (is_same_v<Bound, unreachable_sentinel_t>) {
            return unreachable_sentinel;
        } else {
            return __sentinel(bound_sentinel_);
        }
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class Bound2 = Bound>
        requires(same_as<Value, Bound2> || (is_integral_v<Value> && is_integral_v<Bound2>) ||
            sized_sentinel_for<Bound2, Value>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto size() const noexcept
#else
    template <class Bound2 = Bound,
        enable_if_t<is_same_v<Value, Bound2> || (is_integral_v<Value> && is_integral_v<Bound2>), int> = 0>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto size() const noexcept
#endif
    {
        if constexpr (is_integral_v<Value> && is_integral_v<Bound>) {
            // 按无符号模运算求跨度，避免有符号相减的未定义行为。
            if (value_ < 0) {
                if (bound_sentinel_ < 0) {
                    return ::asc::std::__to_unsigned_like(-value_) - ::asc::std::__to_unsigned_like(-bound_sentinel_);
                }
                return ::asc::std::__to_unsigned_like(bound_sentinel_) + ::asc::std::__to_unsigned_like(-value_);
            }
            return ::asc::std::__to_unsigned_like(bound_sentinel_) - ::asc::std::__to_unsigned_like(value_);
        } else {
            return bound_sentinel_ - value_;
        }
    }

private:
    Value value_ = Value();
    Bound bound_sentinel_ = Bound();
};

// 混用有符号/无符号端点的推导不参与标准 C++20 形状，予以排除。
template <class Value, class Bound,
    enable_if_t<!is_integral_v<Value> || !is_integral_v<Bound> || (is_signed_v<Value> == is_signed_v<Bound>), int> = 0>
iota_view(Value, Bound) -> iota_view<Value, Bound>;

template <class V, class B>
inline constexpr bool enable_borrowed_range<iota_view<V, B>> = true;
namespace views {
struct __iota_fn {
    // 单参形态生成无界计数区间（终哨兵为 unreachable）。
    template <class Value>
    CANN_ASC_STL_API constexpr iota_view<Value> operator()(Value value) const noexcept
    {
        return iota_view<Value>(::asc::std::move(value));
    }
    template <class Value, class Bound>
    CANN_ASC_STL_API constexpr iota_view<Value, Bound> operator()(Value value, Bound bound) const noexcept
    {
        return {::asc::std::move(value), ::asc::std::move(bound)};  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __iota_fn iota{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_IOTA_VIEW_H
