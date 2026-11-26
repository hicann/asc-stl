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

#ifndef ASC_STL_TEST_STANDARD_LOCK_SEMANTICS_H
#define ASC_STL_TEST_STANDARD_LOCK_SEMANTICS_H

#include <asc/std/mutex>
#include <asc/std/shared_mutex>
#include <asc/std/utility>

namespace asc_stl_standard_lock_test {

namespace ast = asc::std;

struct lock_state {
    int holders = 0;

    CANN_ASC_STL_API void lock()
    {
        holders = -1;
    }

    CANN_ASC_STL_API bool try_lock()
    {
        if (holders != 0)
            return false;
        lock();
        return true;
    }

    CANN_ASC_STL_API void unlock()
    {
        holders = 0;
    }

    CANN_ASC_STL_API void lock_shared()
    {
        ++holders;
    }

    CANN_ASC_STL_API bool try_lock_shared()
    {
        if (holders < 0)
            return false;
        lock_shared();
        return true;
    }

    CANN_ASC_STL_API void unlock_shared()
    {
        --holders;
    }
};

CANN_ASC_STL_API int evaluate_locks()
{
    lock_state left, right;
    right.lock();
    if (ast::try_lock(left, right) != 1 || left.holders != 0 || right.holders != -1)
        return 1;
    right.unlock();
    if (ast::try_lock(left, right) != -1 || left.holders != -1 || right.holders != -1)
        return 2;
    left.unlock();
    right.unlock();

    ast::unique_lock<lock_state> one(left, ast::defer_lock);
    ast::unique_lock<lock_state> two(right, ast::defer_lock);
    one.lock();
    ast::swap(one, two);
    if (two.mutex() != &left || !two.owns_lock() || one.owns_lock())
        return 3;
    one = ast::move(two);
    if (!one || two.mutex() != nullptr || one.release() != &left || one.mutex() != nullptr || left.holders != -1)
        return 4;
    left.unlock();

    ast::shared_lock<lock_state> shared(left, ast::defer_lock);
    ast::shared_lock<lock_state> other(right, ast::defer_lock);
    left.lock();
    if (shared.try_lock())
        return 5;
    left.unlock();
    shared.lock();
    if (!shared || left.holders != 1 || shared.mutex() != &left)
        return 6;
    shared.swap(other);
    shared = ast::move(other);
    if (!shared || other.mutex() != nullptr || shared.release() != &left || shared.mutex() != nullptr ||
        left.holders != 1)
        return 7;
    left.unlock_shared();
    return 0;
}

}  // namespace asc_stl_standard_lock_test

#endif  // ASC_STL_TEST_STANDARD_LOCK_SEMANTICS_H
