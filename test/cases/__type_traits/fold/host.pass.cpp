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

#include <asc/std/__type_traits/fold.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][fold] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][fold] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // __fold_and_v tests
    // Empty pack: (_Preds && ...) = true (identity for AND)
    expect_true("asc::std::__fold_and_v<>", asc::std::__fold_and_v<>);

    // Single true
    expect_true("asc::std::__fold_and_v<true>", asc::std::__fold_and_v<true>);

    // Single false
    expect_false("asc::std::__fold_and_v<false>", asc::std::__fold_and_v<false>);

    // All true
    expect_true("asc::std::__fold_and_v<true, true, true>", asc::std::__fold_and_v<true, true, true>);

    // One false among true
    expect_false("asc::std::__fold_and_v<true, false, true>", asc::std::__fold_and_v<true, false, true>);

    // All false
    expect_false("asc::std::__fold_and_v<false, false, false>", asc::std::__fold_and_v<false, false, false>);

    // __fold_or_v tests
    // Empty pack: (_Preds || ...) = false (identity for OR)
    expect_false("asc::std::__fold_or_v<>", asc::std::__fold_or_v<>);

    // Single true
    expect_true("asc::std::__fold_or_v<true>", asc::std::__fold_or_v<true>);

    // Single false
    expect_false("asc::std::__fold_or_v<false>", asc::std::__fold_or_v<false>);

    // All false
    expect_false("asc::std::__fold_or_v<false, false, false>", asc::std::__fold_or_v<false, false, false>);

    // One true among false
    expect_true("asc::std::__fold_or_v<false, true, false>", asc::std::__fold_or_v<false, true, false>);

    // All true
    expect_true("asc::std::__fold_or_v<true, true, true>", asc::std::__fold_or_v<true, true, true>);

    // __fold_and type tests (bool_constant)
    // __fold_and<> should be true_type
    expect_true("asc::std::__fold_and<>::value", asc::std::__fold_and<>::value);
    expect_true("is_same<__fold_and<>, true_type>", std::is_same<asc::std::__fold_and<>, asc::std::true_type>::value);

    // __fold_and<true, true> should be true_type
    expect_true("asc::std::__fold_and<true, true>::value", asc::std::__fold_and<true, true>::value);
    expect_true("is_same<__fold_and<true, true>, true_type>",
        std::is_same<asc::std::__fold_and<true, true>, asc::std::true_type>::value);

    // __fold_and<true, false> should be false_type
    expect_false("asc::std::__fold_and<true, false>::value", asc::std::__fold_and<true, false>::value);
    expect_true("is_same<__fold_and<true, false>, false_type>",
        std::is_same<asc::std::__fold_and<true, false>, asc::std::false_type>::value);

    // __fold_or type tests (bool_constant)
    // __fold_or<> should be false_type
    expect_false("asc::std::__fold_or<>::value", asc::std::__fold_or<>::value);
    expect_true("is_same<__fold_or<>, false_type>", std::is_same<asc::std::__fold_or<>, asc::std::false_type>::value);

    // __fold_or<false, true> should be true_type
    expect_true("asc::std::__fold_or<false, true>::value", asc::std::__fold_or<false, true>::value);
    expect_true("is_same<__fold_or<false, true>, true_type>",
        std::is_same<asc::std::__fold_or<false, true>, asc::std::true_type>::value);

    // __fold_or<false, false> should be false_type
    expect_false("asc::std::__fold_or<false, false>::value", asc::std::__fold_or<false, false>::value);
    expect_true("is_same<__fold_or<false, false>, false_type>",
        std::is_same<asc::std::__fold_or<false, false>, asc::std::false_type>::value);

    return g_failures == 0 ? 0 : 1;
}
