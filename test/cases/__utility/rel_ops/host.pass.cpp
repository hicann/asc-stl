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

#include <asc/std/__utility/rel_ops.h>
struct Value {
    int v;
    friend constexpr bool operator==(Value a, Value b)
    {
        return a.v == b.v;
    }
    friend constexpr bool operator<(Value a, Value b)
    {
        return a.v < b.v;
    }
};
bool test_rel_ops()
{
    Value a{2}, b{5}, c{2};
    return asc::std::rel_ops::operator!=(a, b) && asc::std::rel_ops::operator>(b, a) &&
        asc::std::rel_ops::operator<=(a, c) && asc::std::rel_ops::operator>=(b, a) &&
        !asc::std::rel_ops::operator!=(a, c);
}
int main()
{
    return test_rel_ops() ? 0 : 1;
}
