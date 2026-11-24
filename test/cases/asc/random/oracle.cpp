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

#include <asc/random>
#include <iostream>
#include <string>

bool evaluate(const std::string& operation, const unsigned long long* input)
{
    using wide = asc::detail::random_uint128;
    wide result;
    if (operation == "sequence") {
        asc::pcg64 engine(input[0]);
        engine.discard(input[1]);
        const auto first = engine();
        const auto second = engine();
        std::cout << first << ' ' << second << '\n';
        return true;
    }
    if (operation == "add") {
        result = asc::detail::add(wide(input[0], input[1]), wide(input[2], input[3]));
    } else if (operation == "multiply") {
        result = asc::detail::multiply(wide(input[0], input[1]), wide(input[2], input[3]));
    } else if (operation == "rotate") {
        result = wide(asc::detail::rotate_right(input[0], static_cast<unsigned>(input[1])));
    } else {
        return false;
    }
    std::cout << result.high << ' ' << result.low << '\n';
    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::string operation;
    unsigned long long input[4]{};
    unsigned records = 0;
    while (std::cin >> operation) {
        if (!(std::cin >> input[0] >> input[1] >> input[2] >> input[3]) || !evaluate(operation, input))
            return 1;
        ++records;
    }
    return records != 0 && std::cin.eof() ? 0 : 2;
}
