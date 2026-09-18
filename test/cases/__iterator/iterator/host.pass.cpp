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

#define ASC_IGNORE_DEPRECATED_API
#include <asc/std/__iterator/iterator.h>
#include <iostream>
#include <type_traits>
#include <iterator>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][iterator] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Test default template parameters: iterator<forward_iterator_tag, int>
    using It1 = asc::std::iterator<std::forward_iterator_tag, int>;
    expect_true("is_same<It1::value_type, int>", (std::is_same<It1::value_type, int>::value));
    expect_true(
        "is_same<It1::difference_type, ptrdiff_t>", (std::is_same<It1::difference_type, std::ptrdiff_t>::value));
    expect_true("is_same<It1::pointer, int*>", (std::is_same<It1::pointer, int*>::value));
    expect_true("is_same<It1::reference, int&>", (std::is_same<It1::reference, int&>::value));
    expect_true("is_same<It1::iterator_category, forward_iterator_tag>",
        (std::is_same<It1::iterator_category, std::forward_iterator_tag>::value));

    // Test custom template parameters: iterator<input_iterator_tag, double, long, double*, const double&>
    using It2 = asc::std::iterator<std::input_iterator_tag, double, long, double*, const double&>;
    expect_true("is_same<It2::value_type, double>", (std::is_same<It2::value_type, double>::value));
    expect_true("is_same<It2::difference_type, long>", (std::is_same<It2::difference_type, long>::value));
    expect_true("is_same<It2::pointer, double*>", (std::is_same<It2::pointer, double*>::value));
    expect_true("is_same<It2::reference, const double&>", (std::is_same<It2::reference, const double&>::value));
    expect_true("is_same<It2::iterator_category, input_iterator_tag>",
        (std::is_same<It2::iterator_category, std::input_iterator_tag>::value));

    // Test with random_access_iterator_tag and default params
    using It3 = asc::std::iterator<std::random_access_iterator_tag, char>;
    expect_true("is_same<It3::value_type, char>", (std::is_same<It3::value_type, char>::value));
    expect_true(
        "is_same<It3::difference_type, ptrdiff_t>", (std::is_same<It3::difference_type, std::ptrdiff_t>::value));
    expect_true("is_same<It3::pointer, char*>", (std::is_same<It3::pointer, char*>::value));
    expect_true("is_same<It3::reference, char&>", (std::is_same<It3::reference, char&>::value));
    expect_true("is_same<It3::iterator_category, random_access_iterator_tag>",
        (std::is_same<It3::iterator_category, std::random_access_iterator_tag>::value));

    // Test bidirectional_iterator_tag
    using It4 = asc::std::iterator<std::bidirectional_iterator_tag, float>;
    expect_true("is_same<It4::value_type, float>", (std::is_same<It4::value_type, float>::value));
    expect_true("is_same<It4::pointer, float*>", (std::is_same<It4::pointer, float*>::value));
    expect_true("is_same<It4::reference, float&>", (std::is_same<It4::reference, float&>::value));
    expect_true("is_same<It4::iterator_category, bidirectional_iterator_tag>",
        (std::is_same<It4::iterator_category, std::bidirectional_iterator_tag>::value));

    // Test default-constructibility (empty struct)
    It1 it1{};
    (void)it1;
    expect_true("iterator default-constructible", true);

    return g_failures == 0 ? 0 : 1;
}
