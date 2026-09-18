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

#include <asc/std/__functional/weak_result_type.h>
#include <asc/std/__type_traits/is_same.h>

struct WithResult {
    using result_type = long;
};

struct UnaryDerived : asc::std::__unary_function<int, long> {};

struct BinaryDerived : asc::std::__binary_function<int, short, long> {};

struct MemberOwner {
    long nullary() const;
    long unary(short) volatile;
};

static_assert(asc::std::__has_member_result_type<WithResult>);
static_assert(!asc::std::__has_member_result_type<int>);
static_assert(asc::std::__derives_from_unary_function<UnaryDerived>::value);
static_assert(!asc::std::__derives_from_unary_function<BinaryDerived>::value);
static_assert(asc::std::__derives_from_binary_function<BinaryDerived>::value);

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
static_assert(asc::std::is_same_v<typename asc::std::__weak_result_type<WithResult>::result_type, long>);
static_assert(asc::std::is_same_v<typename asc::std::__weak_result_type<int()>::result_type, int>);
static_assert(asc::std::is_same_v<typename asc::std::__weak_result_type<int(int)>::argument_type, int>);
static_assert(asc::std::is_same_v<typename asc::std::__weak_result_type<int(int)>::result_type, int>);
static_assert(asc::std::is_same_v<typename asc::std::__weak_result_type<long(int, short)>::first_argument_type, int>);
static_assert(
    asc::std::is_same_v<typename asc::std::__weak_result_type<long(int, short)>::second_argument_type, short>);
static_assert(asc::std::is_same_v<typename asc::std::__weak_result_type<long(int, short)>::result_type, long>);
static_assert(asc::std::is_same_v<typename asc::std::__weak_result_type<long (MemberOwner::*)() const>::argument_type,
    const MemberOwner*>);
static_assert(asc::std::is_same_v<
    typename asc::std::__weak_result_type<long (MemberOwner::*)(short) volatile>::first_argument_type,
    volatile MemberOwner*>);
static_assert(asc::std::is_same_v<typename asc::std::__weak_result_type<int(int, int, int)>::result_type, int>);
#endif
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

int main()
{
    return 0;
}
