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

#include <asc/numeric_types>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc != 2)
        return 2;
    const unsigned choice = static_cast<unsigned>(std::strtoul(argv[1], nullptr, 10));
    volatile unsigned input = 16;
    if (choice == 0)
        (void)asc::from_bits<asc::int4>(static_cast<unsigned char>(input));
    if (choice == 1)
        (void)asc::pack_elements<asc::int4x2>(static_cast<unsigned char>(input), 0);
    if (choice == 2)
        (void)asc::pack_elements<asc::int4x2>(0, static_cast<unsigned char>(input));
    if (choice == 3)
        (void)asc::unpack_element(asc::int4x2{}, input);
    return 0;
}
