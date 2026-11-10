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

#include <asc/std/inplace_vector>

namespace {

struct element {
    explicit element(int input) noexcept : value(input)
    {}
    element(const element&) = delete;
    int value;
};

}  // namespace

int main()
{
    asc::std::inplace_vector<element, 1> values;
    const auto inserted = values.try_emplace_back(7);
    return inserted.has_value() && inserted->value == 7 ? 0 : 1;
}
