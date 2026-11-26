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

#include <asc/std/barrier>
#include <asc/std/latch>
#include <asc/std/mutex>
#include <asc/std/semaphore>
#include <asc/std/shared_mutex>

#include <mutex>
#include <shared_mutex>
#include <type_traits>
#include <utility>

namespace {

namespace ast = asc::std;

static_assert(std::is_same_v<std::remove_cv_t<decltype(ast::adopt_lock)>, ast::adopt_lock_t>);
static_assert(std::is_same_v<std::remove_cv_t<decltype(ast::defer_lock)>, ast::defer_lock_t>);
static_assert(std::is_same_v<std::remove_cv_t<decltype(ast::try_to_lock)>, ast::try_to_lock_t>);
static_assert(std::is_same_v<ast::unique_lock<std::mutex>::mutex_type, std::mutex>);
static_assert(std::is_same_v<ast::shared_lock<std::shared_mutex>::mutex_type, std::shared_mutex>);
static_assert(std::is_same_v<ast::binary_semaphore, ast::counting_semaphore<1>>);

bool check_phase_primitives()
{
    using barrier = ast::barrier<>;
    static_assert(barrier::max() >= 2);
    barrier phased(2);
    barrier::arrival_token token = phased.arrive();
    phased.arrive_and_drop();
    phased.wait(std::move(token));
    for (int phase = 0; phase < 3; ++phase) {
        phased.wait(phased.arrive());
    }
    ast::latch pending(2);
    if (pending.try_wait()) {
        return false;
    }
    pending.count_down();
    if (pending.try_wait()) {
        return false;
    }
    pending.count_down();
    pending.wait();
    if (!pending.try_wait()) {
        return false;
    }
    ast::binary_semaphore binary(0);
    if (binary.try_acquire()) {
        return false;
    }
    binary.release();
    return binary.try_acquire() && !binary.try_acquire();
}

bool check_unique_locks()
{
    std::mutex first;
    std::mutex second;
    ast::unique_lock<std::mutex> left(first, ast::defer_lock);
    ast::unique_lock<std::mutex> right(second, ast::try_to_lock);
    if (left.owns_lock() || !right.owns_lock() || left.mutex() != &first || right.mutex() != &second) {
        return false;
    }
    left.lock();
    left.swap(right);
    if (!left.owns_lock() || !right.owns_lock() || left.mutex() != &second || right.mutex() != &first) {
        return false;
    }
    left.unlock();
    right.unlock();
    first.lock();
    const ast::unique_lock<std::mutex> adopted(first, ast::adopt_lock);
    return adopted.owns_lock() && adopted.mutex() == &first;
}

bool check_shared_locks()
{
    std::shared_mutex first;
    std::shared_mutex second;
    ast::shared_lock<std::shared_mutex> left(first, ast::defer_lock);
    ast::shared_lock<std::shared_mutex> right(second, ast::defer_lock);
    if (left.mutex() != &first || right.mutex() != &second || left.owns_lock() || right.owns_lock()) {
        return false;
    }
    left.lock();
    if (!right.try_lock()) {
        return false;
    }
    left.swap(right);
    if (left.mutex() != &second || right.mutex() != &first || !left.owns_lock() || !right.owns_lock()) {
        return false;
    }
    auto* released = left.release();
    if (released != &second || left.mutex() != nullptr || left.owns_lock()) {
        return false;
    }
    released->unlock_shared();
    return left.release() == nullptr && right.owns_lock();
}

}  // namespace

int main()
{
    return check_phase_primitives() && check_unique_locks() && check_shared_locks() ? 0 : 1;
}
