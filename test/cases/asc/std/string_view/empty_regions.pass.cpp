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

#include <asc/std/string_view>

template <class Char>
constexpr bool empty_regions()
{
    using traits = asc::std::char_traits<Char>;
    using view = asc::std::basic_string_view<Char>;
    const view empty{};
    Char marker = Char(3);
    const view full(&marker, 1);
    return empty.compare(empty) == 0 && empty.compare(full) < 0 && full.compare(empty) > 0 && full.ends_with(empty) &&
        full.starts_with(empty) && traits::compare(nullptr, &marker, 0) == 0 &&
        traits::compare(&marker, nullptr, 0) == 0 && traits::find(nullptr, 0, Char(3)) == nullptr &&
        traits::move(&marker, nullptr, 0) == &marker && traits::move(nullptr, &marker, 0) == nullptr &&
        traits::copy(&marker, nullptr, 0) == &marker && traits::copy(nullptr, &marker, 0) == nullptr &&
        traits::assign(nullptr, 0, Char(8)) == nullptr && marker == Char(3);
}

int main()
{
    static_assert(empty_regions<char>() && empty_regions<char16_t>());
    return empty_regions<char>() && empty_regions<char16_t>() && empty_regions<char32_t>() && empty_regions<wchar_t>() ?
        0 :
        1;
}
