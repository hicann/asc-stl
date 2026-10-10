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

#include <asc/std/type_traits>
#include <asc/std/vector>

#include <new>

struct arena_state {
    unsigned char* storage;
    asc::std::size_t capacity;
    asc::std::size_t offset;
};

template <class T>
struct arena_allocator {
    using value_type = T;
    arena_state* state;

    template <class U>
    struct rebind {
        using other = arena_allocator<U>;
    };

    explicit arena_allocator(arena_state* input) : state(input)
    {}

    T* allocate(asc::std::size_t count)
    {
        const asc::std::size_t alignment = alignof(T);
        const asc::std::size_t begin = (state->offset + alignment - 1) / alignment * alignment;
        if (begin + count * sizeof(T) > state->capacity)
            return nullptr;
        T* result = reinterpret_cast<T*>(state->storage + begin);
        state->offset = begin + count * sizeof(T);
        return result;
    }

    void deallocate(T*, asc::std::size_t) noexcept
    {}
};

int main()
{
    alignas(int) unsigned char storage[256]{};
    arena_state state{storage, sizeof(storage), 0};
    using allocator = arena_allocator<int>;
    using vector_type = asc::std::vector<int, allocator>;

    static_assert(asc::std::is_same_v<vector_type::value_type, int>);
    static_assert(asc::std::is_same_v<vector_type::allocator_type, allocator>);
    static_assert(asc::std::is_same_v<vector_type::size_type, asc::std::size_t>);
    static_assert(asc::std::is_same_v<vector_type::difference_type, asc::std::ptrdiff_t>);
    static_assert(asc::std::is_same_v<vector_type::reference, int&>);
    static_assert(asc::std::is_same_v<vector_type::const_reference, const int&>);
    static_assert(asc::std::is_same_v<vector_type::pointer, int*>);
    static_assert(asc::std::is_same_v<vector_type::const_pointer, const int*>);
    static_assert(asc::std::is_same_v<vector_type::iterator, int*>);
    static_assert(asc::std::is_same_v<vector_type::const_iterator, const int*>);

    vector_type values{allocator(&state)};
    if (!values.empty() || values.size() != 0 || values.capacity() != 0)
        return 1;
    values.reserve(4);
    values.push_back(1);
    values.emplace_back(2);
    values.push_back(3);
    if (values.data() != values.begin() || values.end() - values.begin() != 3)
        return 2;
    if (values.front() != 1 || values[1] != 2 || values.back() != 3)
        return 3;
    if (values.get_allocator().state != &state)
        return 4;
    values.pop_back();
    if (values.size() != 2)
        return 5;
    values.clear();
    if (!values.empty())
        return 6;

    vector_type source{allocator(&state)};
    source.push_back(9);
    vector_type target{allocator(&state)};
    target = static_cast<vector_type&&>(source);
    if (!source.empty() || target.front() != 9)
        return 7;

    alignas(vector_type) unsigned char object_storage[sizeof(vector_type)];
    vector_type* manual = ::new (static_cast<void*>(object_storage)) vector_type(allocator(&state));
    manual->~vector_type();
    return 0;
}
