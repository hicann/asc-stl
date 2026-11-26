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

#include <asc/std/mutex>
#include <type_traits>

namespace s = asc::std;

struct mutex {
    void lock();
    bool try_lock();
    void unlock();
};
static_assert(std::is_same_v<s::lock_guard<mutex>::mutex_type, mutex> &&
    std::is_same_v<s::scoped_lock<mutex>::mutex_type, mutex>);
static_assert(std::is_constructible_v<s::scoped_lock<>> &&
    std::is_constructible_v<s::scoped_lock<mutex>, s::adopt_lock_t, mutex&> &&
    std::is_constructible_v<s::scoped_lock<mutex, mutex>, s::adopt_lock_t, mutex&, mutex&>);
static_assert(std::is_same_v<decltype(s::defer_lock), const s::defer_lock_t> &&
    std::is_same_v<decltype(s::adopt_lock), const s::adopt_lock_t> &&
    std::is_same_v<decltype(s::try_to_lock), const s::try_to_lock_t>);

static_assert(
    !std::is_copy_constructible_v<s::unique_lock<mutex>> && !std::is_copy_assignable_v<s::unique_lock<mutex>>);
static_assert(!std::is_copy_constructible_v<s::lock_guard<mutex>> && !std::is_copy_assignable_v<s::lock_guard<mutex>>);
static_assert(
    !std::is_copy_constructible_v<s::scoped_lock<mutex>> && !std::is_copy_assignable_v<s::scoped_lock<mutex>>);
static_assert(!std::is_copy_constructible_v<s::scoped_lock<mutex, mutex>> &&
    !std::is_copy_assignable_v<s::scoped_lock<mutex, mutex>>);

int main()
{}
