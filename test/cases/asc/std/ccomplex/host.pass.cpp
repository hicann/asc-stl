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
    asc::std::complex<float> value(3.0f, 4.0f);
    if (value.real() != 3.0f || value.imag() != 4.0f) {
        return 1;
    }
    value += asc::std::complex<float>(1.0f, 1.0f);
    if (value.real() != 4.0f || value.imag() != 5.0f) {
        return 2;
    }
    const asc::std::complex<float> summed = value + asc::std::complex<float>(1.0f, -1.0f);
    if (summed.real() != 5.0f || summed.imag() != 4.0f) {
        return 3;
    }
    if (value != asc::std::complex<float>(4.0f, 5.0f)) {
        return 4;
    }
    if (asc::std::abs(asc::std::complex<float>(3.0f, 4.0f)) != 5.0f) {
        return 5;
    }
    return 0;
}
