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

#include <asc/std/__type_traits/num_bits.h>

#include <iostream>

int main()
{
    int failures = 0;
    failures +=
        asc::std::__num_bits_v<unsigned int> == int(sizeof(unsigned int) * CHAR_BIT) ?  // NOLINT(readability/casting)
        0 :
        1;                                                                             // NOLINT(readability/casting)
    failures += asc::std::__num_bits_v<int*> == int(sizeof(int*) * CHAR_BIT) ? 0 : 1;  // NOLINT(readability/casting)
    failures += asc::std::__num_bits_v<asc::std::complex<float>> ==
            int(2 * sizeof(float) * CHAR_BIT) ?  // NOLINT(readability/casting)
        0 :
        1;  // NOLINT(readability/casting)
    std::cout << "[host][num_bits] failures=" << failures << '\n';
    return failures == 0 ? 0 : 1;
}
