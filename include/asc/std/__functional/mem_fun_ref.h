/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_MEM_FUN_REF_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_MEM_FUN_REF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/binary_function.h>
#include <asc/std/__functional/unary_function.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS)

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH

template <class _Sp, class _Tp>
class ASC_DEPRECATED mem_fun_t : public __unary_function<_Tp*, _Sp> {
    _Sp (_Tp::*__p_)();

public:
    CANN_ASC_STL_API explicit mem_fun_t(_Sp (_Tp::*__p)()) : __p_(__p)
    {}
    CANN_ASC_STL_API _Sp operator()(_Tp* __p) const
    {
        return (__p->*__p_)();
    }
};

template <class _Sp, class _Tp, class _Ap>
class ASC_DEPRECATED mem_fun1_t : public __binary_function<_Tp*, _Ap, _Sp> {
    _Sp (_Tp::*__p_)(_Ap);

public:
    CANN_ASC_STL_API explicit mem_fun1_t(_Sp (_Tp::*__p)(_Ap)) : __p_(__p)
    {}
    CANN_ASC_STL_API _Sp operator()(_Tp* __p, _Ap __x) const
    {
        return (__p->*__p_)(__x);
    }
};

template <class _Sp, class _Tp>
ASC_DEPRECATED CANN_ASC_STL_API mem_fun_t<_Sp, _Tp> mem_fun(_Sp (_Tp::*__f)())
{
    return mem_fun_t<_Sp, _Tp>(__f);
}

template <class _Sp, class _Tp, class _Ap>
ASC_DEPRECATED CANN_ASC_STL_API mem_fun1_t<_Sp, _Tp, _Ap> mem_fun(_Sp (_Tp::*__f)(_Ap))
{
    return mem_fun1_t<_Sp, _Tp, _Ap>(__f);
}

template <class _Sp, class _Tp>
class ASC_DEPRECATED mem_fun_ref_t : public __unary_function<_Tp, _Sp> {
    _Sp (_Tp::*__p_)();

public:
    CANN_ASC_STL_API explicit mem_fun_ref_t(_Sp (_Tp::*__p)()) : __p_(__p)
    {}
    CANN_ASC_STL_API _Sp operator()(_Tp& __p) const
    {
        return (__p.*__p_)();
    }
};

template <class _Sp, class _Tp, class _Ap>
class ASC_DEPRECATED mem_fun1_ref_t : public __binary_function<_Tp, _Ap, _Sp> {
    _Sp (_Tp::*__p_)(_Ap);

public:
    CANN_ASC_STL_API explicit mem_fun1_ref_t(_Sp (_Tp::*__p)(_Ap)) : __p_(__p)
    {}
    CANN_ASC_STL_API _Sp operator()(_Tp& __p, _Ap __x) const
    {
        return (__p.*__p_)(__x);
    }
};

template <class _Sp, class _Tp>
ASC_DEPRECATED CANN_ASC_STL_API mem_fun_ref_t<_Sp, _Tp> mem_fun_ref(_Sp (_Tp::*__f)())
{
    return mem_fun_ref_t<_Sp, _Tp>(__f);
}

template <class _Sp, class _Tp, class _Ap>
ASC_DEPRECATED CANN_ASC_STL_API mem_fun1_ref_t<_Sp, _Tp, _Ap> mem_fun_ref(_Sp (_Tp::*__f)(_Ap))
{
    return mem_fun1_ref_t<_Sp, _Tp, _Ap>(__f);
}

template <class _Sp, class _Tp>
class ASC_DEPRECATED const_mem_fun_t : public __unary_function<const _Tp*, _Sp> {
    _Sp (_Tp::*__p_)() const;

public:
    CANN_ASC_STL_API explicit const_mem_fun_t(_Sp (_Tp::*__p)() const) : __p_(__p)
    {}
    CANN_ASC_STL_API _Sp operator()(const _Tp* __p) const
    {
        return (__p->*__p_)();
    }
};

template <class _Sp, class _Tp, class _Ap>
class ASC_DEPRECATED const_mem_fun1_t : public __binary_function<const _Tp*, _Ap, _Sp> {
    _Sp (_Tp::*__p_)(_Ap) const;

public:
    CANN_ASC_STL_API explicit const_mem_fun1_t(_Sp (_Tp::*__p)(_Ap) const) : __p_(__p)
    {}
    CANN_ASC_STL_API _Sp operator()(const _Tp* __p, _Ap __x) const
    {
        return (__p->*__p_)(__x);
    }
};

template <class _Sp, class _Tp>
ASC_DEPRECATED CANN_ASC_STL_API const_mem_fun_t<_Sp, _Tp> mem_fun(_Sp (_Tp::*__f)() const)
{
    return const_mem_fun_t<_Sp, _Tp>(__f);
}

template <class _Sp, class _Tp, class _Ap>
ASC_DEPRECATED CANN_ASC_STL_API const_mem_fun1_t<_Sp, _Tp, _Ap> mem_fun(_Sp (_Tp::*__f)(_Ap) const)
{
    return const_mem_fun1_t<_Sp, _Tp, _Ap>(__f);
}

template <class _Sp, class _Tp>
class ASC_DEPRECATED const_mem_fun_ref_t : public __unary_function<_Tp, _Sp> {
    _Sp (_Tp::*__p_)() const;

public:
    CANN_ASC_STL_API explicit const_mem_fun_ref_t(_Sp (_Tp::*__p)() const) : __p_(__p)
    {}
    CANN_ASC_STL_API _Sp operator()(const _Tp& __p) const
    {
        return (__p.*__p_)();
    }
};

template <class _Sp, class _Tp, class _Ap>
class ASC_DEPRECATED const_mem_fun1_ref_t : public __binary_function<_Tp, _Ap, _Sp> {
    _Sp (_Tp::*__p_)(_Ap) const;

public:
    CANN_ASC_STL_API explicit const_mem_fun1_ref_t(_Sp (_Tp::*__p)(_Ap) const) : __p_(__p)
    {}
    CANN_ASC_STL_API _Sp operator()(const _Tp& __p, _Ap __x) const
    {
        return (__p.*__p_)(__x);
    }
};

template <class _Sp, class _Tp>
ASC_DEPRECATED CANN_ASC_STL_API const_mem_fun_ref_t<_Sp, _Tp> mem_fun_ref(_Sp (_Tp::*__f)() const)
{
    return const_mem_fun_ref_t<_Sp, _Tp>(__f);
}

template <class _Sp, class _Tp, class _Ap>
ASC_DEPRECATED CANN_ASC_STL_API const_mem_fun1_ref_t<_Sp, _Tp, _Ap> mem_fun_ref(_Sp (_Tp::*__f)(_Ap) const)
{
    return const_mem_fun1_ref_t<_Sp, _Tp, _Ap>(__f);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

#endif  // defined(CANN_ASC_STL_DETAIL_ACCL_ENABLE_CXX17_REMOVED_BINDERS)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_MEM_FUN_REF_H
