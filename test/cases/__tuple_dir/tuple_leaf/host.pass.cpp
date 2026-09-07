/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include <asc/std/__tuple_dir/tuple_leaf.h>

// 引用 leaf 的拷贝构造回归探针: 声明 move assignment 不得删除隐式拷贝构造。
static_assert(std::is_copy_constructible_v<
    asc::std::__tuple_leaf<0, int&, asc::std::__tuple_leaf_specialization::__synthesize_assignment>>);
static_assert(std::is_copy_constructible_v<
    asc::std::__tuple_leaf<0, const int, asc::std::__tuple_leaf_specialization::__synthesize_assignment>>);

int main()
{
    asc::std::__tuple_leaf<0, int> leaf(42);
    if (leaf.__get() != 42)
        return 1;
    asc::std::__tuple_leaf<0, int> other(7);
    leaf.swap(other);
    if (leaf.__get() != 7 || other.__get() != 42)
        return 1;
    return 0;
}
