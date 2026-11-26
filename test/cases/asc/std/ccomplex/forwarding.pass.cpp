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

#include <asc/std/ccomplex>

int main()
{
    using complex = asc::std::complex<float>;
    constexpr complex z(3, -4);
    static_assert(asc::std::real(z) == 3 && asc::std::imag(z) == -4);
    static_assert(asc::std::norm(z) == 25);
    return asc::std::abs(z) == 5 && asc::std::sqrt(complex(-4, -0.0F)) == complex(0, -2) ? 0 : 1;
}
