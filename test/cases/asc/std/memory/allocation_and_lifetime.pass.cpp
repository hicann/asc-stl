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

#include <asc/std/memory>
#include <asc/std/new>
#include <asc/std/scoped_allocator>
#include <asc/std/span>

#include <cstddef>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace {

namespace ast = asc::std;

struct state {
    unsigned allocations = 0;
    unsigned deallocations = 0;
    unsigned constructions = 0;
    unsigned destructions = 0;
};

template <class T>
struct allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using is_always_equal = std::false_type;
    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_swap = std::true_type;

    template <class U>
    struct rebind {
        using other = allocator<U>;
    };

    state* calls;
    int identity;

    T* allocate(size_type count)
    {
        ++calls->allocations;
        return std::allocator<T>{}.allocate(count);
    }

    auto allocate_at_least(size_type count)
    {
        return ast::allocation_result<T*, size_type>{allocate(count + 1), count + 1};
    }

    void deallocate(T* ptr, size_type count)
    {
        ++calls->deallocations;
        std::allocator<T>{}.deallocate(ptr, count);
    }

    template <class U, class... Args>
    void construct(U* ptr, Args&&... args)
    {
        ++calls->constructions;
        ::new (static_cast<void*>(ptr)) U(std::forward<Args>(args)...);
    }

    template <class U>
    void destroy(U* ptr)
    {
        ++calls->destructions;
        ptr->~U();
    }

    size_type max_size() const noexcept
    {
        return 127;
    }

    allocator select_on_container_copy_construction() const noexcept
    {
        return {calls, identity + 100};
    }

    template <class U>
    bool operator==(const allocator<U>& other) const
    {
        return calls == other.calls && identity == other.identity;
    }
    template <class U>
    bool operator!=(const allocator<U>& other) const
    {
        return !(*this == other);
    }
};

using traits = ast::allocator_traits<allocator<int>>;
using scoped = ast::scoped_allocator_adaptor<allocator<int>, allocator<char>>;
using inner = ast::scoped_allocator_adaptor<allocator<char>>;

template <class Policy>
constexpr bool check_types()
{
    return std::is_same_v<typename Policy::value_type, int> && std::is_same_v<typename Policy::pointer, int*> &&
        std::is_same_v<typename Policy::const_pointer, const int*> &&
        std::is_same_v<typename Policy::void_pointer, void*> &&
        std::is_same_v<typename Policy::const_void_pointer, const void*> &&
        std::is_same_v<typename Policy::size_type, std::size_t> &&
        std::is_same_v<typename Policy::difference_type, std::ptrdiff_t> && !Policy::is_always_equal::value &&
        Policy::propagate_on_container_copy_assignment::value &&
        !Policy::propagate_on_container_move_assignment::value && Policy::propagate_on_container_swap::value;
}
static_assert(check_types<traits>());
static_assert(std::is_same_v<scoped::pointer, int*> && std::is_same_v<scoped::value_type, int>);
static_assert(
    std::is_same_v<scoped::size_type, std::size_t> && std::is_same_v<scoped::difference_type, std::ptrdiff_t>);
static_assert(std::is_same_v<traits::allocator_type, allocator<int>>);
static_assert(std::is_same_v<traits::rebind_alloc<char>, allocator<char>>);
static_assert(std::is_same_v<traits::rebind_traits<char>, ast::allocator_traits<allocator<char>>>);
static_assert(std::is_same_v<scoped::outer_allocator_type, allocator<int>>);
static_assert(std::is_same_v<scoped::inner_allocator_type, inner>);
static_assert(
    std::is_same_v<scoped::rebind<float>::other, ast::scoped_allocator_adaptor<allocator<float>, allocator<char>>>);
static_assert(std::is_same_v<ast::pointer_traits<int*>::pointer, int*>);
static_assert(std::is_same_v<ast::pointer_traits<int*>::difference_type, std::ptrdiff_t>);
static_assert(std::is_trivially_destructible_v<ast::allocator_arg_t>);

template <class T>
struct bare_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    T* allocate(std::size_t);
    void deallocate(T*, std::size_t);
};
using bare_scoped = ast::scoped_allocator_adaptor<bare_allocator<int>>;

#define CHECK_ABSENT_ALIAS(Name)                                             \
    template <class T, class = void>                                         \
    struct has_##Name : std::false_type {};                                  \
    template <class T>                                                       \
    struct has_##Name<T, std::void_t<typename T::Name>> : std::true_type {}; \
    static_assert(!has_##Name<bare_scoped>::value)
CHECK_ABSENT_ALIAS(const_pointer);
CHECK_ABSENT_ALIAS(const_void_pointer);
CHECK_ABSENT_ALIAS(void_pointer);
CHECK_ABSENT_ALIAS(outer_traits);
CHECK_ABSENT_ALIAS(is_always_equal);
CHECK_ABSENT_ALIAS(propagate_on_container_copy_assignment);
CHECK_ABSENT_ALIAS(propagate_on_container_move_assignment);
CHECK_ABSENT_ALIAS(propagate_on_container_swap);
#undef CHECK_ABSENT_ALIAS

template <class Policy, class = void>
struct has_member_allocate_at_least : std::false_type {};
template <class Policy>
struct has_member_allocate_at_least<Policy,
    std::void_t<decltype(Policy::allocate_at_least(std::declval<typename Policy::allocator_type&>(), 1))>>
    : std::true_type {};
static_assert(!has_member_allocate_at_least<traits>::value);
static_assert(
    std::is_same_v<decltype(std::declval<const scoped&>().select_on_container_copy_construction()), allocator<int>>);

struct absent {};
template <class T>
absent make_obj_using_allocator(...);
template <class T>
absent uses_allocator_construction_args(...);
[[maybe_unused]] absent uninitialized_construct_using_allocator(...)
{
    return {};
}
static_assert(std::is_same_v<decltype(make_obj_using_allocator<int>(std::declval<scoped const&>(), 5)), absent>);
static_assert(
    std::is_same_v<decltype(uses_allocator_construction_args<int>(std::declval<scoped const&>(), 5)), absent>);
static_assert(std::is_same_v<
    decltype(uninitialized_construct_using_allocator(std::declval<int*>(), std::declval<scoped const&>(), 5)), absent>);

struct allocator_aware {
    using allocator_type = allocator<int>;
    int identity;
    int value;

    allocator_aware(ast::allocator_arg_t, const allocator_type& alloc, int number)
        : identity(alloc.identity), value(number)
    {}
};

static_assert(ast::uses_allocator<allocator_aware, allocator<int>>::value);
static_assert(!ast::uses_allocator<int, allocator<int>>::value);

bool check_allocator_dispatch()
{
    state calls;
    allocator<int> alloc{&calls, 13};
    auto* plain = traits::allocate(alloc, 2);
    traits::construct(alloc, plain, 33);
    traits::construct(alloc, plain + 1, -7);
    const bool constructed = plain[0] == 33 && plain[1] == -7 && calls.constructions == 2;
    traits::destroy(alloc, plain + 1);
    traits::destroy(alloc, plain);
    traits::deallocate(alloc, plain, 2);

    const auto block = ast::allocate_at_least(alloc, 3);
    const bool expanded = block.count == 4;
    traits::deallocate(alloc, block.ptr, block.count);
    std::allocator<int> standard;
    auto fallback = ast::allocate_at_least(standard, 3);
    const bool exact = fallback.count == 3;
    standard.deallocate(fallback.ptr, fallback.count);
    const auto copied = traits::select_on_container_copy_construction(alloc);
    const ast::allocator_arg_t tag{};
    const allocator_aware explicit_object(tag, alloc, 5);
    const allocator_aware global_tag(ast::allocator_arg, copied, 6);

    return constructed && expanded && exact && alloc.identity == 13 && copied.identity == 113 &&
        explicit_object.identity == 13 && explicit_object.value == 5 && global_tag.identity == 113 &&
        global_tag.value == 6 && traits::max_size(alloc) == 127 && calls.allocations == 2 && calls.deallocations == 2 &&
        calls.destructions == 2;
}

bool check_scoped_allocators()
{
    state calls;
    scoped first(allocator<int>{&calls, 7}, allocator<char>{&calls, 11});
    scoped same(allocator<int>{&calls, 7}, allocator<char>{&calls, 11});
    scoped different(allocator<int>{&calls, 7}, allocator<char>{&calls, 19});
    if (!(first == same) || first != same || first == different || !(first != different)) {
        return false;
    }
    const auto inner_copy = first.inner_allocator().outer_allocator().select_on_container_copy_construction();
    if (inner_copy.identity != 111 || first.outer_allocator().identity != 7 ||
        first.inner_allocator().outer_allocator().identity != 11) {
        return false;
    }
    same = different;
    const scoped& const_view = same;
    return same == different && const_view.outer_allocator().identity == 7 &&
        const_view.inner_allocator().outer_allocator().identity == 19 && same.max_size() == 127;
}

struct observed {
    inline static int live = 0;
    int value;

    observed() : value(-9)
    {
        ++live;
    }
    explicit observed(int input) : value(input)
    {
        ++live;
    }
    observed(const observed& other) : value(other.value)
    {
        ++live;
    }
    observed(observed&& other) noexcept : value(other.value)
    {
        other.value = -77;
        ++live;
    }
    ~observed()
    {
        --live;
    }
};

bool check_uninitialized_algorithms()
{
    constexpr int count = 3;
    std::allocator<observed> alloc;
    auto* storage = alloc.allocate(count);
    bool correct = observed::live == 0;

    ast::uninitialized_default_construct(storage, storage + count);
    correct = correct && observed::live == count && storage[0].value == -9 && storage[2].value == -9;
    const auto destroyed_end = ast::destroy_n(storage, count);
    correct = correct && destroyed_end == storage + count && observed::live == 0;
    ast::uninitialized_default_construct_n(storage, count);
    correct = correct && observed::live == count;
    ast::destroy_n(storage, count);

    const observed pattern(19);
    ast::uninitialized_fill(storage, storage + count, pattern);
    correct = correct && observed::live == count + 1 && storage[0].value == 19 && storage[2].value == 19;
    ast::destroy_n(storage, count);
    ast::uninitialized_fill_n(storage, count, pattern);
    correct = correct && observed::live == count + 1 && storage[1].value == 19;
    ast::destroy_n(storage, count);

    observed input[] = {observed{3}, observed{4}, observed{5}};
    auto* copy_end = ast::uninitialized_copy_n(input, count, storage);
    correct = correct && copy_end == storage + count && observed::live == 2 * count + 1 && storage[0].value == 3 &&
        storage[2].value == 5 && input[0].value == 3;
    ast::destroy_n(storage, count);
    const auto move_end = ast::uninitialized_move_n(input, count, storage);
    correct = correct && move_end.first == input + count && move_end.second == storage + count &&
        storage[0].value == 3 && storage[2].value == 5 && input[0].value == -77;
    ast::destroy_n(storage, count);
    const auto moved = ast::uninitialized_move(input, input + count, storage);
    correct = correct && moved == storage + count && observed::live == 2 * count + 1;
    ast::destroy_n(storage, count);
    alloc.deallocate(storage, count);

    std::allocator<int> integers;
    auto* values = integers.allocate(count);
    ast::uninitialized_value_construct(values, values + count);
    correct = correct && values[0] == 0 && values[1] == 0 && values[2] == 0;
    ast::destroy_n(values, count);
    ast::uninitialized_value_construct_n(values, count);
    correct = correct && values[0] == 0 && values[2] == 0;
    ast::destroy_n(values, count);
    integers.deallocate(values, count);
    return correct;
}

bool check_storage_views_and_placement()
{
    static_assert(std::is_enum_v<ast::align_val_t>);
    static_assert(std::is_same_v<std::remove_cv_t<decltype(ast::nothrow)>, ast::nothrow_t>);
    alignas(32) unsigned char bytes[32]{2, 4, 8, 16};
    const ast::span<unsigned char> view(bytes);
    const auto writable = ast::as_writable_bytes(view);
    writable[2] = static_cast<ast::byte>(17);
    if (writable.size() != sizeof(bytes) || bytes[2] != 17 || ast::assume_aligned<32>(bytes) != bytes) {
        return false;
    }
    void* one = ::operator new(sizeof(int), static_cast<void*>(bytes));
    void* array = ::operator new[](sizeof(int), static_cast<void*>(bytes));
    return one == bytes && array == bytes;
}

}  // namespace

int main()
{
    if (!check_allocator_dispatch()) {
        return 1;
    }
    if (!check_scoped_allocators()) {
        return 2;
    }
    if (!check_uninitialized_algorithms() || observed::live != 0) {
        return 3;
    }
    return check_storage_views_and_placement() ? 0 : 4;
}
