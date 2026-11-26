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

#include <asc/std/complex>
#include <asc/std/linalg>
#include <asc/std/mdspan>

#include <cmath>
#include <complex>
#include <type_traits>

namespace {

namespace ast = asc::std;
namespace la = ast::linalg;
using number = ast::complex<float>;
using plain = ast::default_accessor<number>;
using conjugate = la::conjugated_accessor<plain>;
using scalar = ast::default_accessor<float>;
using scale = la::scaled_accessor<float, scalar>;

static_assert(std::is_same_v<number::value_type, float>);
static_assert(std::is_same_v<conjugate::data_handle_type, number*>);
static_assert(std::is_same_v<std::remove_cv_t<conjugate::element_type>, number>);
static_assert(std::is_same_v<conjugate::reference, number>);
static_assert(std::is_same_v<conjugate::offset_policy, la::conjugated_accessor<plain::offset_policy>>);
static_assert(std::is_same_v<scale::data_handle_type, float*>);
static_assert(std::is_same_v<std::remove_cv_t<scale::element_type>, float>);
static_assert(std::is_same_v<scale::reference, float>);
static_assert(std::is_same_v<scale::offset_policy, la::scaled_accessor<float, scalar::offset_policy>>);
static_assert(std::is_same_v<la::layout_transpose<ast::layout_right>::nested_layout_type, ast::layout_right>);

bool close(float a, float b)
{
    return std::fabs(a - b) <= 0.00002F * (1 + std::fabs(b));
}
bool close(number a, std::complex<float> b)
{
    return close(a.real(), b.real()) && close(a.imag(), b.imag());
}

bool check_complex_arithmetic()
{
    const std::complex<float> values[] = {{-2, 3}, {0, -1}, {1, 0}, {2, -4}};
    for (auto left : values) {
        for (auto right : values) {
            const number a(left.real(), left.imag());
            const number b(right.real(), right.imag());
            if (!close(a + b, left + right) || !close(a - b, left - right) || !close(a * b, left * right) ||
                !close(a / b, left / right) || (a == b) != (left == right) || (a != b) != (left != right)) {
                return false;
            }
            number compound;
            compound = a;
            compound += b;
            if (!close(compound, left + right)) {
                return false;
            }
            compound -= b;
            compound *= b;
            if (!close(compound, left * right)) {
                return false;
            }
            compound /= b;
            if (!close(compound, left)) {
                return false;
            }
        }
        const number value(left.real(), left.imag());
        if (!close(ast::conj(value), std::conj(left)) || !close(ast::arg(value), std::arg(left)) ||
            !close(ast::proj(value), std::proj(left)) || !close(ast::polar(std::abs(left), std::arg(left)), left)) {
            return false;
        }
    }
    return true;
}

bool check_accessors()
{
    number complex_data[] = {{1, 2}, {3, -4}, {-5, 6}};
    const conjugate access{plain{}};
    for (unsigned i = 0; i < 3; ++i) {
        const auto value = access.access(complex_data, i);
        if (value.real() != complex_data[i].real() || value.imag() != -complex_data[i].imag() ||
            access.offset(complex_data, i) != complex_data + i ||
            &access.nested_accessor().access(complex_data, i) != complex_data + i) {
            return false;
        }
    }
    float real_data[] = {2, -3, 11};
    const float factors[] = {-2, 0, 3};
    for (float factor : factors) {
        const scale modifier(factor, scalar{});
        if (modifier.scaling_factor() != factor) {
            return false;
        }
        for (unsigned i = 0; i < 3; ++i) {
            if (modifier.access(real_data, i) != real_data[i] * factor ||
                modifier.offset(real_data, i) != real_data + i ||
                &modifier.nested_accessor().access(real_data, i) != real_data + i) {
                return false;
            }
        }
    }
    return true;
}

bool check_transpose()
{
    number data[] = {{1, 2}, {3, -4}, {-5, 6}, {-7, 8}, {9, 10}, {11, -12}};
    using shape = ast::extents<int, 2, 3>;
    using input = ast::mdspan<number, shape>;
    const input source(data, shape{});
    const auto transformed = la::conjugate_transposed(source);
    if (transformed.extent(0) != 3 || transformed.extent(1) != 2) {
        return false;
    }
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 2; ++col) {
            const auto offset = transformed.mapping()(row, col);
            const auto original = data[col * 3 + row];
            const auto value = transformed.accessor().access(transformed.data_handle(), offset);
            if (value.real() != original.real() || value.imag() != -original.imag()) {
                return false;
            }
        }
    }
    using nested = ast::layout_stride;
    using mapping = nested::mapping<shape>;
    const mapping stride{shape{}, ast::array<int, 2>{5, 1}};
    const la::layout_transpose<nested>::mapping<ast::extents<int, 3, 2>> transposed(stride);
    return transposed.extents().extent(0) == 3 && transposed.extents().extent(1) == 2 && transposed(2, 1) == 7 &&
        transposed.stride(0) == 1 && transposed.stride(1) == 5;
}

}  // namespace

int main()
{
    return check_complex_arithmetic() && check_accessors() && check_transpose() ? 0 : 1;
}
