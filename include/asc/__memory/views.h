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

#ifndef CANN_ASC_STL_ASC___MEMORY_VIEWS_H
#define CANN_ASC_STL_ASC___MEMORY_VIEWS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__memory/buffers.h>

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
#define CANN_ASC_STL_DETAIL_MEMORY_GM __gm__
#define CANN_ASC_STL_DETAIL_MEMORY_UB __ubuf__
#else
#define CANN_ASC_STL_DETAIL_MEMORY_GM
#define CANN_ASC_STL_DETAIL_MEMORY_UB
#endif

namespace asc {

#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_DETAIL_TEMPORARY_STORAGE_API __host__ __aicore__ CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN inline
#else
#define CANN_ASC_STL_DETAIL_TEMPORARY_STORAGE_API CANN_ASC_STL_API
#endif

enum class memory_space { host, global, unified_buffer, local };

template <class T>
struct memory_space_of;

template <class T>
inline constexpr memory_space memory_space_of_v = memory_space_of<T>::value;

template <class T>
class gm_span {
public:
    using element_type = T;
    using pointer = CANN_ASC_STL_DETAIL_MEMORY_GM T*;
    using size_type = __SIZE_TYPE__;

    CANN_ASC_STL_API constexpr gm_span() noexcept = default;
    CANN_ASC_STL_API constexpr gm_span(pointer data, size_type size) noexcept : data_(data), size_(size)
    {}

    CANN_ASC_STL_API constexpr pointer data() const noexcept
    {
        return data_;
    }
    CANN_ASC_STL_API constexpr size_type size() const noexcept
    {
        return size_;
    }
    CANN_ASC_STL_API constexpr size_type size_bytes() const noexcept
    {
        // Precondition: size_ * sizeof(T) must not overflow size_type; the
        // span is a view over storage that exists, so realistic sizes cannot
        // wrap (only adversarial hand-constructed spans could).
        return size_ * sizeof(T);
    }
    CANN_ASC_STL_API constexpr bool empty() const noexcept
    {
        return size_ == 0;
    }
    CANN_ASC_STL_API constexpr CANN_ASC_STL_DETAIL_MEMORY_GM T& operator[](size_type index) const noexcept
    {
        return data_[index];
    }
    // Slicing is fail-closed like the rest of the memory layer: a count or
    // offset outside [0, size()] yields an empty span instead of a wrapped
    // pointer, both on host and device compilation.
    CANN_ASC_STL_API constexpr gm_span first(size_type count) const noexcept
    {
        return count > size_ ? gm_span{} : gm_span{data_, count};
    }
    CANN_ASC_STL_API constexpr gm_span last(size_type count) const noexcept
    {
        return count > size_ ? gm_span{} : gm_span{data_ + size_ - count, count};
    }
    CANN_ASC_STL_API constexpr gm_span subspan(size_type offset, size_type count) const noexcept
    {
        return offset > size_ || count > size_ - offset ? gm_span{} : gm_span{data_ + offset, count};
    }

private:
    pointer data_{};
    size_type size_{};
};

template <class T>
struct memory_space_of<gm_span<T>> {
    static constexpr memory_space value = memory_space::global;
};

#if !CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class T>
class ub_span {
public:
    using element_type = T;
    using pointer = CANN_ASC_STL_DETAIL_MEMORY_UB T*;
    using size_type = __SIZE_TYPE__;

    CANN_ASC_STL_API constexpr ub_span() noexcept = default;
    CANN_ASC_STL_API constexpr ub_span(pointer data, size_type size) noexcept : data_(data), size_(size)
    {}

    CANN_ASC_STL_API constexpr pointer data() const noexcept
    {
        return data_;
    }
    CANN_ASC_STL_API constexpr size_type size() const noexcept
    {
        return size_;
    }
    CANN_ASC_STL_API constexpr size_type size_bytes() const noexcept
    {
        // Same no-overflow precondition as gm_span::size_bytes.
        return size_ * sizeof(T);
    }
    CANN_ASC_STL_API constexpr bool empty() const noexcept
    {
        return size_ == 0;
    }
    CANN_ASC_STL_API constexpr CANN_ASC_STL_DETAIL_MEMORY_UB T& operator[](size_type index) const noexcept
    {
        return data_[index];
    }
    // Slicing is fail-closed exactly as gm_span.
    CANN_ASC_STL_API constexpr ub_span first(size_type count) const noexcept
    {
        return count > size_ ? ub_span{} : ub_span{data_, count};
    }
    CANN_ASC_STL_API constexpr ub_span last(size_type count) const noexcept
    {
        return count > size_ ? ub_span{} : ub_span{data_ + size_ - count, count};
    }
    CANN_ASC_STL_API constexpr ub_span subspan(size_type offset, size_type count) const noexcept
    {
        return offset > size_ || count > size_ - offset ? ub_span{} : ub_span{data_ + offset, count};
    }

private:
    pointer data_{};
    size_type size_{};
};

template <class T>
struct memory_space_of<ub_span<T>> {
    static constexpr memory_space value = memory_space::unified_buffer;
};
#endif

class monotonic_arena {
public:
    CANN_ASC_STL_API constexpr monotonic_arena() noexcept = default;
    CANN_ASC_STL_API constexpr monotonic_arena(void* storage, __SIZE_TYPE__ size) noexcept
        : storage_(static_cast<unsigned char*>(storage)), size_(size)
    {}

    // Fail-closed bump allocation. Zero-byte requests are rejected (return
    // nullptr) so two zero-size allocations can never alias one address, and
    // the request is checked against the remaining bytes before any offset
    // arithmetic, which makes the offset+size addition below non-wrapping.
    CANN_ASC_STL_API constexpr void* allocate(__SIZE_TYPE__ size, __SIZE_TYPE__ alignment) noexcept
    {
        if (storage_ == nullptr || size == 0 || size > remaining()) {
            return nullptr;
        }
        if (alignment == 0 || (alignment & (alignment - 1U)) != 0) {
            return nullptr;
        }
        const auto base = reinterpret_cast<__UINTPTR_TYPE__>(storage_ + used_);
        const auto aligned = (base + alignment - 1U) & ~(alignment - 1U);
        const auto next = static_cast<__SIZE_TYPE__>(aligned - reinterpret_cast<__UINTPTR_TYPE__>(storage_)) + size;
        if (next > size_) {
            // The alignment padding pushed the offset past the end; `next`
            // cannot have wrapped here because both the offset and the size
            // are individually bounded by size_.
            return nullptr;
        }
        used_ = next;
        return reinterpret_cast<void*>(aligned);
    }
    CANN_ASC_STL_API constexpr void reset() noexcept
    {
        used_ = 0;
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ capacity() const noexcept
    {
        return size_;
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ used() const noexcept
    {
        return used_;
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ remaining() const noexcept
    {
        return size_ - used_;
    }

private:
    unsigned char* storage_{};
    __SIZE_TYPE__ size_{};
    __SIZE_TYPE__ used_{};
};

// Non-standard allocator over a monotonic_arena. Contract (deliberate
// deviation from the C++ named allocator requirements): it exists for
// non-standard containers and hand-written allocation paths, never for
// std-compatible containers; a count whose byte size overflows, a zero
// count, and arena exhaustion all return nullptr instead of raising, so
// callers must null-check the result.
template <class T>
class arena_allocator {
public:
    using value_type = T;
    template <class U>
    struct rebind {
        using other = arena_allocator<U>;
    };

    arena_allocator() = delete;
    CANN_ASC_STL_API explicit constexpr arena_allocator(monotonic_arena& arena) noexcept : arena_(&arena)
    {}
    template <class U>
    CANN_ASC_STL_API constexpr arena_allocator(const arena_allocator<U>& other) noexcept : arena_(other.arena())
    {}

    CANN_ASC_STL_API constexpr T* allocate(__SIZE_TYPE__ count) noexcept
    {
        if (arena_ == nullptr || count == 0) {
            return nullptr;
        }
        // Overflow-checked byte size: a wrapped count*sizeof(T) reports zero
        // and turns into a nullptr instead of a silently tiny allocation.
        const __SIZE_TYPE__ bytes = detail::buffer_element_bytes(sizeof(T), count);
        return bytes == 0 ? nullptr : static_cast<T*>(arena_->allocate(bytes, alignof(T)));
    }
    CANN_ASC_STL_API constexpr void deallocate(T*, __SIZE_TYPE__) noexcept
    {}
    CANN_ASC_STL_API constexpr monotonic_arena* arena() const noexcept
    {
        return arena_;
    }

    template <class U>
    CANN_ASC_STL_API constexpr bool operator==(const arena_allocator<U>& other) const noexcept
    {
        return arena_ == other.arena();
    }
    template <class U>
    CANN_ASC_STL_API constexpr bool operator!=(const arena_allocator<U>& other) const noexcept
    {
        return !(*this == other);
    }

private:
    template <class>
    friend class arena_allocator;
    monotonic_arena* arena_{};
};

class temporary_storage_ref {
public:
    CANN_ASC_STL_DETAIL_TEMPORARY_STORAGE_API constexpr temporary_storage_ref() noexcept = default;
    CANN_ASC_STL_DETAIL_TEMPORARY_STORAGE_API constexpr temporary_storage_ref(
        void* data, __SIZE_TYPE__ size, memory_space space) noexcept
        : data_(data), size_(size), space_(space)
    {}
    CANN_ASC_STL_DETAIL_TEMPORARY_STORAGE_API constexpr void* data() const noexcept
    {
        return data_;
    }
    CANN_ASC_STL_DETAIL_TEMPORARY_STORAGE_API constexpr __SIZE_TYPE__ size_bytes() const noexcept
    {
        return size_;
    }
    CANN_ASC_STL_DETAIL_TEMPORARY_STORAGE_API constexpr memory_space space() const noexcept
    {
        return space_;
    }
    CANN_ASC_STL_DETAIL_TEMPORARY_STORAGE_API constexpr bool empty() const noexcept
    {
        return size_ == 0;
    }

private:
    void* data_{};
    __SIZE_TYPE__ size_{};
    memory_space space_{memory_space::local};
};

class pointer_attributes {
public:
    memory_space space{memory_space::local};
    bool host_accessible{false};
    bool device_accessible{false};
    __SIZE_TYPE__ allocation_bytes{0};
};

template <class Integer>
CANN_ASC_STL_API constexpr Integer aligned_size(Integer size, Integer alignment) noexcept
{
    // Precondition: size + alignment - 1 must not overflow Integer; callers
    // round real buffer sizes, for which the slack cannot wrap.
    return alignment == 0 ? size : static_cast<Integer>((size + alignment - 1) / alignment * alignment);
}

template <class Integer>
CANN_ASC_STL_API constexpr bool is_aligned(Integer value, Integer alignment) noexcept
{
    return alignment != 0 && value % alignment == 0;
}

template <class T>
CANN_ASC_STL_API constexpr bool is_aligned(T* pointer, __SIZE_TYPE__ alignment) noexcept
{
    return alignment != 0 && reinterpret_cast<__UINTPTR_TYPE__>(pointer) % alignment == 0;
}

}  // namespace asc

#undef CANN_ASC_STL_DETAIL_TEMPORARY_STORAGE_API
#undef CANN_ASC_STL_DETAIL_MEMORY_GM
#undef CANN_ASC_STL_DETAIL_MEMORY_UB

#endif  // CANN_ASC_STL_ASC___MEMORY_VIEWS_H
