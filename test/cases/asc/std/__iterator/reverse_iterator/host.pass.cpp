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

#include <asc/std/__iterator/reverse_iterator.h>

#include <cstddef>
#include <cstdio>
#include <type_traits>

// Semantics ported from the ASC-STL reverse_iterator host suite: construction
// and conversion, base roundtrip, traversal direction reversal (++ is a
// decrement of the underlying iterator), the random-access family (+/+=/-/-=
// and operator[]), cross-type difference, reversed comparison ordering,
// iter_move/iter_swap through the customization points (acting on base-1),
// double reversal restoring the original order, disable_sized_sentinel_for,
// and a custom bidirectional iterator path (non-pointer operator-> and the
// bidirectional iterator_concept downgrade).

static int g_failures = 0;

static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::fprintf(stderr, "[host][reverse_iterator] FAIL: %s\n", label);
        ++g_failures;
    }
}

// Minimal custom bidirectional iterator: non-pointer, covering the
// non-pointer branch of operator-> and the iterator_concept downgrade
// (non random-access underlying iterator -> bidirectional_iterator_tag).
struct IntBox {
    int value;
};

class BoxIter {
    IntBox* pointer_;

public:
    using iterator_category = asc::std::bidirectional_iterator_tag;
    using value_type = IntBox;
    using difference_type = std::ptrdiff_t;
    using pointer = IntBox*;
    using reference = IntBox&;

    CANN_ASC_STL_API BoxIter() : pointer_(nullptr)
    {}
    CANN_ASC_STL_API explicit BoxIter(IntBox* pointer) : pointer_(pointer)
    {}

    CANN_ASC_STL_API reference operator*() const
    {
        return *pointer_;
    }
    CANN_ASC_STL_API pointer operator->() const
    {
        return pointer_;
    }
    CANN_ASC_STL_API BoxIter& operator++()
    {
        ++pointer_;
        return *this;
    }
    CANN_ASC_STL_API BoxIter operator++(int)
    {
        BoxIter temporary(*this);
        ++pointer_;
        return temporary;
    }
    CANN_ASC_STL_API BoxIter& operator--()
    {
        --pointer_;
        return *this;
    }
    CANN_ASC_STL_API BoxIter operator--(int)
    {
        BoxIter temporary(*this);
        --pointer_;
        return temporary;
    }
    CANN_ASC_STL_API friend bool operator==(const BoxIter& left, const BoxIter& right)
    {
        return left.pointer_ == right.pointer_;
    }
    CANN_ASC_STL_API friend bool operator!=(const BoxIter& left, const BoxIter& right)
    {
        return left.pointer_ != right.pointer_;
    }
};

int main()
{
    int array[5] = {10, 20, 30, 40, 50};

    // --- construction / base roundtrip / make_reverse_iterator ---
    auto rb = asc::std::make_reverse_iterator(array + 5);
    auto re = asc::std::make_reverse_iterator(array);
    static_assert(std::is_same<decltype(rb), asc::std::reverse_iterator<int*>>::value, "deduced type");
    expect(rb.base() == array + 5, "make_reverse_iterator base roundtrip");
    asc::std::reverse_iterator<int*> explicit_ri(array + 3);
    expect(explicit_ri.base() == array + 3, "explicit ctor base");

    // --- dereference and subscript: reversed view ---
    expect(*rb == 50, "*rbegin == last");
    expect(rb[0] == 50 && rb[1] == 40 && rb[4] == 10, "operator[] reversed indexing");

    // --- traversal direction reversal: ++ decrements the underlying iterator;
    //     weighted reversed sum golden = 50*1+40*2+30*3+20*4+10*5 = 350 ---
    {
        int sum = 0;
        int k = 1;
        for (auto it = rb; it != re; ++it, ++k) {
            sum += *it * k;
        }
        expect(sum == 350, "weighted reversed traversal sum");
    }

    // --- pre/post increment and decrement ---
    {
        auto it = rb;
        auto old = it++;
        expect(*old == 50 && *it == 40, "post-increment returns old");
        auto old2 = it--;
        expect(*old2 == 40 && *it == 50, "post-decrement returns old");
        expect(*++it == 40 && *--it == 50, "pre inc/dec");
    }

    // --- random-access family ---
    expect(*(rb + 2) == 30, "operator+(n)");
    expect(*(2 + rb) == 30, "friend operator+(n, iter)");
    expect(*((rb + 2) - 1) == 40, "operator-(n)");
    {
        auto it = rb;
        it += 3;
        expect(*it == 20, "operator+=");
        it -= 2;
        expect(*it == 40, "operator-=");
    }

    // --- difference: friend operator- subtracts underlying in reverse ---
    expect(re - rb == 5, "rend - rbegin == size");
    expect(rb - re == -5, "rbegin - rend == -size");
    expect((rb + 2) - rb == 2, "sliced difference");

    // --- reversed comparison ordering: exposed < is underlying > ---
    expect(rb == rb, "self equality");
    expect(rb != re, "rbegin != rend");
    expect(rb < re, "rbegin < rend (reversed ordering)");
    expect(!(rb > re), "not (rbegin > rend)");
    expect(rb <= re && re >= rb, "mixed direction <=");
    auto mid = rb + 2;
    expect(mid > rb, "mid > rbegin after +2 (reversed ordering)");

    // --- converting construction and assignment (int* -> const int*) ---
    {
        asc::std::reverse_iterator<const int*> const_ri(rb);
        expect(const_ri.base() == array + 5, "converting ctor base");
        asc::std::reverse_iterator<const int*> assigned;
        assigned = rb;
        expect(assigned.base() == array + 5, "converting assignment base");
        expect(*assigned == 50, "converting deref");
    }

    // --- iter_move / iter_swap through the customization points (base-1) ---
    {
        int x = 42;
        int* pointer = &x;
        auto rpointer = asc::std::make_reverse_iterator(pointer + 1);
        static_assert(
            std::is_same<decltype(asc::std::iter_move(rpointer)), int&&>::value, "iter_move yields the base-1 rvalue");
        int&& rv = asc::std::iter_move(rpointer);
        expect(rv == 42, "iter_move yields base-1 element");
    }
    {
        int a[2] = {1, 2};
        int b[2] = {7, 8};
        auto ra = asc::std::make_reverse_iterator(a + 2);
        auto rb2 = asc::std::make_reverse_iterator(b + 2);
        asc::std::iter_swap(ra, rb2);
        expect(a[1] == 8 && b[1] == 2, "iter_swap swaps base-1 elements");
        // the unqualified call also resolves through ADL to asc::std::iter_swap
        int c[2] = {3, 4};
        int d[2] = {5, 6};
        iter_swap(asc::std::make_reverse_iterator(c + 2), asc::std::make_reverse_iterator(d + 2));
        expect(c[1] == 6 && d[1] == 4, "unqualified iter_swap via ADL");
    }

    // --- double reversal restores the original order ---
    {
        auto rr = asc::std::make_reverse_iterator(asc::std::make_reverse_iterator(array + 1));
        expect(*rr == 20, "double reverse deref == *p");
        expect(*++rr == 30, "double reverse advance follows original order");
        expect(*(rr + 1) == 40, "double reverse random access");
    }

    // --- type aliases (pointer base) ---
    static_assert(
        std::is_same<asc::std::reverse_iterator<int*>::iterator_concept, asc::std::random_access_iterator_tag>::value,
        "iterator_concept");
    static_assert(
        std::is_same<asc::std::reverse_iterator<int*>::iterator_category, asc::std::random_access_iterator_tag>::value,
        "iterator_category");
    static_assert(std::is_same<asc::std::reverse_iterator<int*>::value_type, int>::value, "value_type");
    static_assert(
        std::is_same<asc::std::reverse_iterator<int*>::difference_type, std::ptrdiff_t>::value, "difference_type");
    static_assert(std::is_same<asc::std::reverse_iterator<int*>::reference, int&>::value, "reference");

    // --- disable_sized_sentinel_for: a reversed sized pair stays sized ---
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    static_assert(asc::std::sized_sentinel_for<asc::std::reverse_iterator<int*>, asc::std::reverse_iterator<int*>>,
        "reversed pointer pair is a sized sentinel pair");
#endif

    // --- custom bidirectional iterator (non-pointer) ---
    {
        IntBox boxes[3] = {{1}, {2}, {3}};
        asc::std::reverse_iterator<BoxIter> brb{BoxIter(boxes + 3)};
        asc::std::reverse_iterator<BoxIter> bre{BoxIter(boxes)};
        static_assert(std::is_same<asc::std::reverse_iterator<BoxIter>::iterator_concept,
                          asc::std::bidirectional_iterator_tag>::value,
            "bidirectional downgrade");
        expect(brb->value == 3, "custom iter operator-> (non-pointer branch)");
        int sum = 0;
        for (auto it = brb; it != bre; ++it) {
            sum += it->value;
        }
        expect(sum == 6, "custom bidirectional reversed traversal");
        expect(brb.base() == BoxIter(boxes + 3), "custom iter base");
    }

    // --- runtime volatile spot checks (prevent constant folding) ---
    {
        volatile int vseed = 3;
        int index = vseed;
        expect(*(rb + index) == 20, "runtime offset deref");
        volatile int volatile_array[5] = {3, 1, 4, 1, 5};
        int* volatile_pointer = const_cast<int*>(volatile_array);
        auto volatile_rb = asc::std::make_reverse_iterator(volatile_pointer + 5);
        auto volatile_re = asc::std::make_reverse_iterator(volatile_pointer);
        int sum = 0;
        for (auto it = volatile_rb; it != volatile_re; ++it) {
            sum += *it;
        }
        expect(sum == 14, "runtime volatile traversal sum");
    }

    if (g_failures == 0) {
        std::printf("[host][reverse_iterator] all semantic checks passed\n");
    }
    return g_failures == 0 ? 0 : 1;
}
