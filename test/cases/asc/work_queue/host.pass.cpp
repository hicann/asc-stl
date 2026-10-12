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

#include <asc/work_queue>

#include <cassert>
#include <cstdint>

int main()
{
    // work_chunk is a plain half-open interval value type.
    constexpr asc::work_chunk<std::uint32_t> empty_chunk{};
    static_assert(empty_chunk.empty());
    static_assert(empty_chunk.size() == 0);

    constexpr asc::work_chunk<std::uint32_t> chunk{3, 9};
    static_assert(!chunk.empty());
    static_assert(chunk.size() == 6);
    static_assert(chunk.begin == 3);
    static_assert(chunk.end == 9);

    constexpr asc::work_chunk<std::uint64_t> wide{1, 1ull << 40};
    static_assert(wide.size() == (1ull << 40) - 1);

    // The queue borrows a caller-owned cursor and carries the end bound and
    // grain size as values: only the cursor cell is touched while claiming.
    asc::detail::work_cursor cursor{0, 20, 7};
    auto queue = asc::make_work_queue<std::uint32_t>(cursor, 20u, 7u);
    assert(queue.cursor() == &cursor);
    assert(queue.end_value() == 20);
    assert(queue.grain_size() == 7);

    const asc::work_queue_ref<std::uint32_t> default_queue{};
    assert(default_queue.cursor() == nullptr);
    assert(default_queue.end_value() == 0);
    asc::work_chunk<std::uint32_t> claimed{};
    assert(!asc::acquire_work(default_queue, claimed));
    assert(claimed.empty());

    // Host claiming walks disjoint clipped chunks that exactly cover the
    // initial cursor value up to end: 20 items with grain 7 produce
    // [0,7), [7,14), [14,20) and then exhaustion.
    asc::work_chunk<std::uint32_t> piece{};
    assert(asc::acquire_work(queue, piece));
    assert(piece.begin == 0 && piece.end == 7);
    assert(asc::acquire_work(queue, piece));
    assert(piece.begin == 7 && piece.end == 14);
    assert(asc::acquire_work(queue, piece));
    assert(piece.begin == 14 && piece.end == 20);
    assert(!asc::acquire_work(queue, piece));
    assert(piece.empty());

    // A 64-bit index queue follows the same contract.
    asc::detail::work_cursor wide_cursor{0, 257, 11};
    auto wide_queue = asc::make_work_queue<std::uint64_t>(wide_cursor, 257ull, 11ull);
    asc::work_chunk<std::uint64_t> wide_piece{};
    std::uint64_t covered = 0;
    std::uint64_t expected_begin = 0;
    while (asc::acquire_work(wide_queue, wide_piece)) {
        assert(wide_piece.begin == expected_begin);
        assert(wide_piece.end <= 257);
        covered += wide_piece.size();
        expected_begin = wide_piece.end;
    }
    assert(covered == 257);
    assert(expected_begin >= 257 - 11);

    // Exercise the frozen uint64_t index domain across the sign bit without
    // traversing the enormous prefix of the range.
    constexpr std::uint64_t high_bit = std::uint64_t{1} << 63;
    asc::detail::work_cursor crossing_cursor{high_bit - 2, high_bit + 3, 2};
    auto crossing_queue = asc::make_work_queue<std::uint64_t>(crossing_cursor, high_bit + 3, std::uint64_t{2});
    assert(asc::acquire_work(crossing_queue, wide_piece));
    assert(wide_piece.begin == high_bit - 2 && wide_piece.end == high_bit);
    assert(asc::acquire_work(crossing_queue, wide_piece));
    assert(wide_piece.begin == high_bit && wide_piece.end == high_bit + 2);
    assert(asc::acquire_work(crossing_queue, wide_piece));
    assert(wide_piece.begin == high_bit + 2 && wide_piece.end == high_bit + 3);
    assert(!asc::acquire_work(crossing_queue, wide_piece));

    asc::detail::work_cursor zero_cursor{0, 1, 1};
    auto high_end_queue = asc::make_work_queue<std::uint64_t>(zero_cursor, high_bit, std::uint64_t{3});
    assert(asc::acquire_work(high_end_queue, wide_piece));
    assert(wide_piece.begin == 0 && wide_piece.end == 3);

    // A non-positive grain size is clamped to one by the cursor constructor.
    asc::detail::work_cursor unit_cursor{0, 5, 0};
    assert(unit_cursor.grain_size == 1);
    return 0;
}
