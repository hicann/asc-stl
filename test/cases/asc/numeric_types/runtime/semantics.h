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

#ifndef ASC_STL_TEST_NUMERIC_TYPES_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_NUMERIC_TYPES_RUNTIME_SEMANTICS_H

#include "../../../../support/numeric_types_semantics.h"
#include "launch.h"

namespace numeric_types_runtime {

template <class T, numeric_types_test::R Round, numeric_types_test::S Sat>
CANN_ASC_STL_API unsigned conversion(unsigned direction, unsigned input)
{
    if (direction == 0) {
        return asc::to_bits(asc::numeric_convert<T, Round, Sat>(asc::std::bit_cast<float>(input)));
    }
    using Storage = typename asc::numeric_format_traits<T>::storage_type;
    return asc::std::bit_cast<unsigned>(
        asc::numeric_convert<float, Round, Sat>(asc::from_bits<T>(static_cast<Storage>(input))));
}

template <class T>
CANN_ASC_STL_API unsigned option(unsigned selected, unsigned direction, unsigned input)
{
    using R = numeric_types_test::R;
    using S = numeric_types_test::S;
    switch (selected) {
        case 0:
            return conversion<T, R::nearest_even, S::none>(direction, input);
        case 1:
            return conversion<T, R::nearest_even, S::finite>(direction, input);
        case 2:
            return conversion<T, R::toward_zero, S::none>(direction, input);
        case 3:
            return conversion<T, R::toward_zero, S::finite>(direction, input);
        case 4:
            return conversion<T, R::toward_positive, S::none>(direction, input);
        case 5:
            return conversion<T, R::toward_positive, S::finite>(direction, input);
        case 6:
            return conversion<T, R::toward_negative, S::none>(direction, input);
        case 7:
            return conversion<T, R::toward_negative, S::finite>(direction, input);
        default:
            return 0xdeadbeefU;
    }
}

CANN_ASC_STL_API unsigned evaluate(unsigned format, unsigned selected, unsigned direction, unsigned input)
{
    switch (format) {
        case 0:
            return option<asc::float16>(selected, direction, input);
        case 1:
            return option<asc::bfloat16>(selected, direction, input);
        case 2:
            return option<asc::float8_e4m3fn>(selected, direction, input);
        case 3:
            return option<asc::float8_e5m2>(selected, direction, input);
        default:
            return 0xdeadbeefU;
    }
}

CANN_ASC_STL_API unsigned parameters(numeric_parameters p)
{
    return (asc::to_bits(p.fp16) != 0x7e15) + (asc::to_bits(p.bf16) != 0xffc1) + (asc::to_bits(p.e4m3) != 0xff) +
        (asc::to_bits(p.e5m2) != 0x7d) + (asc::to_bits(p.scale) != 0) + (asc::to_bits(p.hif8) != 0xa5) +
        (asc::to_bits(p.e2m1) != 0x83) + (asc::to_bits(p.e1m2) != 0x7c) + (asc::to_bits(p.packed) != 0xf0) +
        (asc::to_bits(p.scalar) != 0x0e);
}

CANN_ASC_STL_API unsigned invariants(numeric_parameters p, unsigned lane)
{
    using R = numeric_types_test::R;
    unsigned failures = parameters(p) + numeric_types_test::representations(lane, numeric_lanes) +
        numeric_types_test::native_representations(lane, numeric_lanes);
    if (lane == 0) {
        failures += numeric_types_test::integers<R::nearest_even>() + numeric_types_test::integers<R::toward_zero>() +
            numeric_types_test::integers<R::toward_positive>() + numeric_types_test::integers<R::toward_negative>();
    }
    return failures;
}

}  // namespace numeric_types_runtime

#endif  // ASC_STL_TEST_NUMERIC_TYPES_RUNTIME_SEMANTICS_H
