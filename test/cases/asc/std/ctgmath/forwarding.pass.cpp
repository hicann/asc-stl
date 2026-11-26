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

#include <asc/std/ctgmath>

int main()
{
    using complex = asc::std::complex<float>;
    const complex z(0, 0);
    return asc::std::cos(0.0F) == 1.0F && asc::std::cos(z) == complex(1, 0) && asc::std::sqrt(4.0) == 2.0 &&
            asc::std::sqrt(complex(-4, 0)) == complex(0, 2) && asc::std::pow(2.0F, 3.0F) == 8 &&
            asc::std::abs(complex(3, -4)) == 5 ?
        0 :
        1;
}
