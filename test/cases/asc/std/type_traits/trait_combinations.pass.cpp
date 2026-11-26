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

#include <type_traits>

namespace {

namespace ast = asc::std;

struct empty {};
struct final_type final {};
struct base {
    virtual ~base() = default;
};
struct derived : base {};
struct abstract_type {
    virtual void call() = 0;
};
struct throwing_constructor {
    throwing_constructor() noexcept(false);
};
struct deleted_constructor {
    deleted_constructor() = delete;
};
struct callable {
    int operator()(int) const noexcept;
};
struct throwing_callable {
    explicit throwing_callable(int argument) noexcept(false);
    int operator()(int argument) const;
};
struct noncopyable {
    noncopyable() = default;
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
};
union alternative {
    char left;
    int right;
};
enum class scoped : unsigned {};
using unknown_bound = int[];
using multi_rank = int[2][3];

#define CHECK_UNARY_TRAIT(Name, ...) \
    static_assert(((ast::Name<__VA_ARGS__>::value == std::Name<__VA_ARGS__>::value)), #Name)
CHECK_UNARY_TRAIT(has_unique_object_representations, unsigned char);
CHECK_UNARY_TRAIT(has_unique_object_representations, empty);
CHECK_UNARY_TRAIT(has_virtual_destructor, base);
CHECK_UNARY_TRAIT(has_virtual_destructor, empty);
CHECK_UNARY_TRAIT(is_abstract, abstract_type);
CHECK_UNARY_TRAIT(is_abstract, derived);
CHECK_UNARY_TRAIT(is_class, const empty);
CHECK_UNARY_TRAIT(is_class, alternative);
CHECK_UNARY_TRAIT(is_const, const int);
CHECK_UNARY_TRAIT(is_const, const int&);
CHECK_UNARY_TRAIT(is_default_constructible, empty);
CHECK_UNARY_TRAIT(is_default_constructible, deleted_constructor);
CHECK_UNARY_TRAIT(is_empty, empty);
CHECK_UNARY_TRAIT(is_empty, base);
CHECK_UNARY_TRAIT(is_enum, scoped);
CHECK_UNARY_TRAIT(is_enum, unsigned);
CHECK_UNARY_TRAIT(is_final, final_type);
CHECK_UNARY_TRAIT(is_final, empty);
CHECK_UNARY_TRAIT(is_fundamental, void);
CHECK_UNARY_TRAIT(is_fundamental, int*);
CHECK_UNARY_TRAIT(is_lvalue_reference, int&);
CHECK_UNARY_TRAIT(is_lvalue_reference, int&&);
CHECK_UNARY_TRAIT(is_nothrow_default_constructible, empty);
CHECK_UNARY_TRAIT(is_nothrow_default_constructible, throwing_constructor);
CHECK_UNARY_TRAIT(is_nothrow_swappable, int);
CHECK_UNARY_TRAIT(is_nothrow_swappable, noncopyable);
CHECK_UNARY_TRAIT(is_object, multi_rank);
CHECK_UNARY_TRAIT(is_object, const int&);
CHECK_UNARY_TRAIT(is_polymorphic, derived);
CHECK_UNARY_TRAIT(is_polymorphic, final_type);
CHECK_UNARY_TRAIT(is_reference, int&&);
CHECK_UNARY_TRAIT(is_reference, const int);
CHECK_UNARY_TRAIT(is_rvalue_reference, int&);
CHECK_UNARY_TRAIT(is_rvalue_reference, int&&);
CHECK_UNARY_TRAIT(is_standard_layout, empty);
CHECK_UNARY_TRAIT(is_standard_layout, base);
CHECK_UNARY_TRAIT(is_swappable, int);
CHECK_UNARY_TRAIT(is_swappable, noncopyable);
CHECK_UNARY_TRAIT(is_trivial, int);
CHECK_UNARY_TRAIT(is_trivial, throwing_constructor);
CHECK_UNARY_TRAIT(is_trivially_copyable, multi_rank);
CHECK_UNARY_TRAIT(is_trivially_copyable, derived);
CHECK_UNARY_TRAIT(is_union, alternative);
CHECK_UNARY_TRAIT(is_union, empty);
CHECK_UNARY_TRAIT(is_volatile, volatile long);
CHECK_UNARY_TRAIT(is_volatile, volatile long*);
CHECK_UNARY_TRAIT(rank, multi_rank);
CHECK_UNARY_TRAIT(rank, unknown_bound);
CHECK_UNARY_TRAIT(rank, int*);
#undef CHECK_UNARY_TRAIT

#define CHECK_TRAIT(Name, ...) static_assert(ast::Name<__VA_ARGS__>::value == std::Name<__VA_ARGS__>::value, #Name)
CHECK_TRAIT(is_base_of, base, derived);
CHECK_TRAIT(is_base_of, derived, base);
CHECK_TRAIT(is_same, int, int);
CHECK_TRAIT(is_same, int, const int);
CHECK_TRAIT(is_nothrow_constructible, throwing_callable, int);
CHECK_TRAIT(is_nothrow_constructible, int, int);
CHECK_TRAIT(is_trivially_assignable, int&, int);
CHECK_TRAIT(is_trivially_assignable, const int&, int);
CHECK_TRAIT(is_trivially_constructible, int, int);
CHECK_TRAIT(is_trivially_constructible, throwing_callable, int);
CHECK_TRAIT(is_invocable, callable, int);
CHECK_TRAIT(is_invocable, callable, int*);
CHECK_TRAIT(is_invocable_r, void, callable, int);
CHECK_TRAIT(is_invocable_r, int*, callable, int);
CHECK_TRAIT(is_nothrow_invocable, callable, int);
CHECK_TRAIT(is_nothrow_invocable, throwing_callable, int);
CHECK_TRAIT(is_nothrow_invocable_r, int, callable, int);
CHECK_TRAIT(is_nothrow_invocable_r, int, throwing_callable, int);
CHECK_TRAIT(is_swappable_with, int&, int&);
CHECK_TRAIT(is_swappable_with, int&, const int&);
CHECK_TRAIT(is_nothrow_swappable_with, int&, int&);
CHECK_TRAIT(is_nothrow_swappable_with, noncopyable&, noncopyable&);
#undef CHECK_TRAIT

static_assert(ast::is_swappable_with_v<int&, int&> && !ast::is_swappable_with_v<int&, const int&>);
static_assert(ast::is_nothrow_swappable_with_v<int&, int&> && !ast::is_nothrow_swappable_with_v<int&, int>);
static_assert(ast::is_unbounded_array<unknown_bound>::value && !ast::is_unbounded_array<multi_rank>::value);
static_assert(std::is_same_v<typename ast::invoke_result<callable, int>::type, int>);
static_assert(std::is_same_v<typename ast::add_const<int>::type, const int>);
static_assert(std::is_same_v<typename ast::add_const<int&>::type, int&>);
static_assert(std::is_same_v<typename ast::add_volatile<const int>::type, const volatile int>);
static_assert(std::is_same_v<typename ast::add_volatile<int&>::type, int&>);
static_assert(std::is_same_v<typename ast::add_cv<int*>::type, int* const volatile>);
static_assert(std::is_same_v<typename ast::add_cv<int&>::type, int&>);

using metadata = ast::integral_constant<int, -7>;
static_assert(metadata{}() == -7);
static_assert(std::is_same_v<metadata::type, metadata> && std::is_same_v<metadata::value_type, int>);
static_assert(ast::aligned_union<1, int, double>::alignment_value == alignof(double));
static_assert(ast::aligned_union<128, char, int>::alignment_value == alignof(int));

struct no_value {};
static_assert(ast::disjunction<ast::false_type, ast::true_type, no_value>::value);
static_assert(!ast::disjunction<ast::false_type, ast::false_type>::value);
static_assert(ast::negation<ast::false_type>::value && !ast::negation<ast::true_type>::value);

template <class T>
using identity = T;

template <class T, class = void>
struct has_type : std::false_type {};
template <class T>
struct has_type<T, std::void_t<typename T::type>> : std::true_type {};
static_assert(!has_type<ast::basic_common_reference<int, double, identity, identity>>::value);
static_assert(!has_type<ast::invoke_result<callable, int*>>::value);
}  // namespace

int main()
{
    return 0;
}
