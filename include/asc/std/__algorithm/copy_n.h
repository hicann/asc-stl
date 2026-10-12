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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_COPY_N_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_COPY_N_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/copy.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/convert_to_integral.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// 内部探测：iterator_traits<_Iterator>::iterator_category 是否存在且派生自
// random_access_iterator_tag。探测保持 SFINAE 友好，无 traits 特化的迭代
// 器按输入遍历处理（与朴素逐元素路径一致，不收窄基座可用性）。
template <class _Iterator, class = void>
inline constexpr bool __copy_n_random_access_v = false;
template <class _Iterator>
inline constexpr bool
    __copy_n_random_access_v<_Iterator, void_t<typename iterator_traits<_Iterator>::iterator_category>> =
        is_base_of_v<random_access_iterator_tag, typename iterator_traits<_Iterator>::iterator_category>;

template <class InputIterator, class Size, class OutputIterator>
CANN_ASC_STL_API constexpr OutputIterator copy_n(InputIterator first, Size count, OutputIterator result)
{
    using _IntegralSize = decltype(::asc::std::__convert_to_integral(count));
    _IntegralSize __n = static_cast<_IntegralSize>(count);
    if (__n <= 0) {
        return result;
    }
    if constexpr (__copy_n_random_access_v<InputIterator>) {
        // 随机访问遍历：补出尾迭代器后转调 copy，继承其平凡可拷贝 memmove 快径。
        return ::asc::std::copy(first, first + __n, result);  // NOLINT(build/include_what_you_use)
    } else {
        // 输入遍历：先写首元素，再按"步进-读取"交替推进，比朴素循环少一次迭代器步进。
        *result = *first;
        ++result;
        for (--__n; __n > 0; --__n) {
            ++first;
            *result = *first;
            ++result;
        }
        return result;
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_COPY_N_H
