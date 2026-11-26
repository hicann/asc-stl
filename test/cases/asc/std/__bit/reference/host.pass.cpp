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

#include <asc/std/__bit/reference.h>

#include <cassert>
#include <cstddef>

namespace {

// A minimal bit-container satisfying the __bit_iterator container contract.
struct BoolVector {
    using __storage_type = unsigned long;
    using __storage_pointer = __storage_type*;
    using __const_storage_pointer = const __storage_type*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = asc::std::__bit_iterator<BoolVector, false>;
    using __self = BoolVector;
    static const unsigned __bits_per_word = sizeof(__storage_type) * 8;

    static constexpr std::size_t words_for(std::size_t bits)
    {
        return (bits + __bits_per_word - 1) / __bits_per_word;
    }

    explicit BoolVector(std::size_t bits) : size_(bits), storage_(new __storage_type[words_for(bits)]{})
    {}
    ~BoolVector()
    {
        delete[] storage_;
    }
    BoolVector(const BoolVector&) = delete;
    BoolVector& operator=(const BoolVector&) = delete;

    iterator begin()
    {
        return iterator(storage_, 0);
    }
    iterator end()
    {
        return iterator(storage_ + size_ / __bits_per_word, static_cast<unsigned>(size_ % __bits_per_word));
    }

    bool at(std::size_t index) const
    {
        return (storage_[index / __bits_per_word] & (__storage_type(1) << (index % __bits_per_word))) != 0;
    }

    std::size_t size_;
    __storage_pointer storage_;
};

}  // namespace

int main()
{
    BoolVector bits(130);
    assert(BoolVector::words_for(130) == 3);

    // The iterator walks every bit with pointer-like arithmetic.
    auto it = bits.begin();
    *it = true;
    assert(bits.at(0));
    *it = false;
    assert(!bits.at(0));
    ++it;
    *it = true;
    assert(bits.at(1) && !bits.at(0));
    auto last = bits.begin() + 129;
    *last = true;
    assert(bits.at(129));
    assert(bits.end() - bits.begin() == 130);
    assert(*(bits.begin() + 64) == false);

    // flip and the bool conversion carry through the reference proxy.
    auto reference = *bits.begin();
    reference = true;
    assert(reference);
    assert(~reference == false);
    reference.flip();
    assert(!reference);
    bool read = reference;
    assert(!read);

    // fill and fill_n cover whole and partial words in both values.
    asc::std::fill(bits.begin(), bits.end(), true);
    for (std::size_t index = 0; index < 130; ++index) {
        assert(bits.at(index));
    }
    asc::std::fill_n(bits.begin(), 67, false);
    for (std::size_t index = 0; index < 67; ++index) {
        assert(!bits.at(index));
    }
    for (std::size_t index = 67; index < 130; ++index) {
        assert(bits.at(index));
    }

    // copy keeps aligned and unaligned source offsets correct.
    BoolVector source(130);
    for (std::size_t index = 0; index < 130; index += 3) {
        *(source.begin() + static_cast<std::ptrdiff_t>(index)) = true;
    }
    BoolVector aligned(130);
    asc::std::copy(source.begin(), source.end(), aligned.begin());
    for (std::size_t index = 0; index < 130; ++index) {
        assert(aligned.at(index) == (index % 3 == 0));
    }
    BoolVector unaligned(130);
    asc::std::copy(source.begin() + 5, source.end() - 2, unaligned.begin() + 7);
    for (std::size_t index = 5; index < 128; ++index) {
        assert(unaligned.at(index - 5 + 7) == (index % 3 == 0));
    }

    // copy_backward and swap_ranges exercise the reverse and pairwise forms.
    BoolVector backward(130);
    asc::std::copy_backward(source.begin() + 3, source.end(), backward.end());  // NOLINT(build/include_what_you_use)
    for (std::size_t index = 3; index < 130; ++index) {
        assert(backward.at(index) == (index % 3 == 0));
    }
    BoolVector swapped(130);
    asc::std::fill(swapped.begin(), swapped.end(), true);
    asc::std::swap_ranges(source.begin(), source.begin() + 20, swapped.begin());
    for (std::size_t index = 0; index < 20; ++index) {
        assert(swapped.at(index) == (index % 3 == 0));
        assert(source.at(index) == true);
    }

    // move aliases copy for trivial bool elements (restore the pattern the
    // swap mutated first).
    asc::std::fill(source.begin(), source.begin() + 20, false);
    for (std::size_t index = 0; index < 20; index += 3) {
        *(source.begin() + static_cast<std::ptrdiff_t>(index)) = true;
    }
    BoolVector moved(130);
    asc::std::move(source.begin(), source.end(), moved.begin());
    for (std::size_t index = 0; index < 130; ++index) {
        assert(moved.at(index) == (index % 3 == 0));
    }

    // Overlapping backward movement spans three storage words and preserves both sentinels.
    const auto destination = asc::std::move_backward(moved.begin() + 1, moved.end() - 3, moved.end() - 1);
    if (destination != moved.begin() + 3 ||
        asc::std::move_backward(moved.begin(), moved.begin(), moved.end()) != moved.end())
        return 1;
    for (std::size_t index = 0; index < 130; ++index) {
        const auto original = index >= 3 && index < 129 ? index - 2 : index;
        if (moved.at(index) != (original % 3 == 0))
            return 2;
    }

    // rotate moves a prefix to the back.
    BoolVector rotated(130);
    asc::std::fill(rotated.begin(), rotated.begin() + 40, true);
    asc::std::rotate(rotated.begin(), rotated.begin() + 40, rotated.end());
    for (std::size_t index = 0; index < 90; ++index) {
        assert(!rotated.at(index));
    }
    for (std::size_t index = 90; index < 130; ++index) {
        assert(rotated.at(index));
    }

    // equal compares aligned and unaligned bit sequences.
    BoolVector mirror(130);
    asc::std::copy(source.begin(), source.end(), mirror.begin());
    assert(asc::std::equal(source.begin(), source.end(), mirror.begin()));
    *(mirror.begin() + 77) = !mirror.at(77);
    assert(!asc::std::equal(source.begin(), source.end(), mirror.begin()));
    BoolVector shifted(130);
    asc::std::copy(source.begin() + 9, source.end(), shifted.begin() + 4);  // NOLINT(build/include_what_you_use)
    assert(!asc::std::equal(source.begin() + 9, source.end(), shifted.begin()));
    assert(asc::std::equal(source.begin() + 9, source.end(), shifted.begin() + 4));

    // swap overloads exchange through the proxy.
    BoolVector left(4);
    BoolVector right(4);
    *(left.begin() + 1) = true;
    swap(*(left.begin() + 1), *(right.begin() + 2));  // NOLINT(build/include_what_you_use)
    assert(!left.at(1) && right.at(2));
    *(left.begin() + 2) = true;
    bool plain = false;
    swap(plain, *(left.begin() + 2));  // NOLINT(build/include_what_you_use)
    assert(plain && !left.at(2));
    return 0;
}
