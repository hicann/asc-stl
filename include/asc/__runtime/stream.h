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

#ifndef CANN_ASC_STL_ASC___RUNTIME_STREAM_H
#define CANN_ASC_STL_ASC___RUNTIME_STREAM_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if defined(INC_EXTERNAL_ACL_ACL_RT_H_)
#define CANN_ASC_STL_DETAIL_HAS_ACL_STREAM_RUNTIME 1
#elif defined(__has_include)
#if __has_include(<acl/acl_rt.h>)
#include <acl/acl_rt.h>
#define CANN_ASC_STL_DETAIL_HAS_ACL_STREAM_RUNTIME 1
#endif
#endif

#if !defined(CANN_ASC_STL_DETAIL_HAS_ACL_STREAM_RUNTIME)
extern "C" int aclrtSynchronizeStream(void* stream);
extern "C" int aclrtStreamQuery(void* stream, int* status);
extern "C" int aclrtStreamGetPriority(void* stream, unsigned int* priority);
extern "C" int aclrtStreamWaitEvent(void* stream, void* event);
extern "C" int aclrtRecordEvent(void* event, void* stream);
extern "C" int aclrtSynchronizeEvent(void* event);
extern "C" int aclrtQueryEventStatus(void* event, int* status);
extern "C" int aclrtCreateStreamWithConfig(void** stream, unsigned int priority, unsigned int flag);
extern "C" int aclrtDestroyStream(void* stream);
extern "C" int aclrtCreateEvent(void** event);
extern "C" int aclrtDestroyEvent(void* event);
extern "C" int aclrtEventElapsedTime(float* milliseconds, void* start, void* end);
#endif

namespace asc::std {

using uint32_t = __UINT32_TYPE__;

}  // namespace asc::std

namespace asc {

class event_ref;
class stream;
class event;

class stream_ref {
public:
    using native_handle_type = void*;

    constexpr stream_ref() noexcept = default;
    constexpr explicit stream_ref(native_handle_type handle) noexcept : handle_(handle)
    {}
    constexpr native_handle_type native_handle() const noexcept
    {
        return handle_;
    }
    constexpr explicit operator bool() const noexcept
    {
        return handle_ != nullptr;
    }
    bool synchronize() const noexcept
    {
        return handle_ != nullptr && ::aclrtSynchronizeStream(handle_) == 0;
    }
    bool is_done(bool& output) const noexcept
    {
#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_STREAM_RUNTIME)
        aclrtStreamStatus status = ACL_STREAM_STATUS_COMPLETE;
#else
        int status = 0;
#endif
        if (handle_ == nullptr || ::aclrtStreamQuery(handle_, &status) != 0) {
            return false;
        }
#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_STREAM_RUNTIME)
        output = status == ACL_STREAM_STATUS_COMPLETE;
#else
        output = status == 0;
#endif
        return true;
    }
    bool priority(::asc::std::uint32_t& output) const noexcept
    {
        unsigned int value = 0;
        if (handle_ == nullptr || ::aclrtStreamGetPriority(handle_, &value) != 0) {
            return false;
        }
        output = static_cast<::asc::std::uint32_t>(value);
        return true;
    }
    bool wait(event_ref event) const noexcept;

protected:
    constexpr native_handle_type release_handle() noexcept
    {
        native_handle_type result = handle_;
        handle_ = nullptr;
        return result;
    }
    constexpr void exchange_handle(stream_ref& other) noexcept
    {
        native_handle_type value = handle_;
        handle_ = other.handle_;
        other.handle_ = value;
    }

    native_handle_type handle_ = nullptr;
};

class event_ref {
public:
    using native_handle_type = void*;

    constexpr event_ref() noexcept = default;
    constexpr explicit event_ref(native_handle_type handle) noexcept : handle_(handle)
    {}
    constexpr native_handle_type native_handle() const noexcept
    {
        return handle_;
    }
    constexpr explicit operator bool() const noexcept
    {
        return handle_ != nullptr;
    }
    bool record(stream_ref stream) const noexcept
    {
        return handle_ != nullptr && stream && ::aclrtRecordEvent(handle_, stream.native_handle()) == 0;
    }
    bool synchronize() const noexcept
    {
        return handle_ != nullptr && ::aclrtSynchronizeEvent(handle_) == 0;
    }
    bool is_done(bool& output) const noexcept
    {
#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_STREAM_RUNTIME)
        aclrtEventRecordedStatus status = ACL_EVENT_RECORDED_STATUS_NOT_READY;
#else
        int status = 0;
#endif
        if (handle_ == nullptr || ::aclrtQueryEventStatus(handle_, &status) != 0) {
            return false;
        }
#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_STREAM_RUNTIME)
        output = status == ACL_EVENT_RECORDED_STATUS_COMPLETE;
#else
        output = status == 1;
#endif
        return true;
    }

protected:
    constexpr native_handle_type release_handle() noexcept
    {
        native_handle_type result = handle_;
        handle_ = nullptr;
        return result;
    }
    constexpr void exchange_handle(event_ref& other) noexcept
    {
        native_handle_type value = handle_;
        handle_ = other.handle_;
        other.handle_ = value;
    }

    native_handle_type handle_ = nullptr;
};

inline bool stream_ref::wait(event_ref event) const noexcept
{
    return handle_ != nullptr && event && ::aclrtStreamWaitEvent(handle_, event.native_handle()) == 0;
}

constexpr bool operator==(stream_ref lhs, stream_ref rhs) noexcept
{
    return lhs.native_handle() == rhs.native_handle();
}
constexpr bool operator!=(stream_ref lhs, stream_ref rhs) noexcept
{
    return !(lhs == rhs);
}
constexpr bool operator==(event_ref lhs, event_ref rhs) noexcept
{
    return lhs.native_handle() == rhs.native_handle();
}
constexpr bool operator!=(event_ref lhs, event_ref rhs) noexcept
{
    return !(lhs == rhs);
}

class stream : public stream_ref {
public:
    stream() noexcept = default;
    stream(const stream&) = delete;
    stream& operator=(const stream&) = delete;
    stream(stream&& other) noexcept : stream_ref(other.release_handle())
    {}
    stream& operator=(stream&& other) noexcept
    {
        if (this != &other) {
            exchange_handle(other);
        }
        return *this;
    }
    ~stream()
    {
        native_handle_type handle = release_handle();
        if (handle != nullptr) {
            (void)::aclrtSynchronizeStream(handle);
            (void)::aclrtDestroyStream(handle);
        }
    }
    native_handle_type release() noexcept
    {
        return release_handle();
    }
    bool close() noexcept
    {
        if (handle_ == nullptr) {
            return true;
        }
        if (::aclrtSynchronizeStream(handle_) != 0 || ::aclrtDestroyStream(handle_) != 0) {
            return false;
        }
        handle_ = nullptr;
        return true;
    }

private:
    friend bool make_stream(stream&, ::asc::std::uint32_t) noexcept;
    friend bool adopt_stream(native_handle_type, stream&) noexcept;
};

class event : public event_ref {
public:
    event() noexcept = default;
    event(const event&) = delete;
    event& operator=(const event&) = delete;
    event(event&& other) noexcept : event_ref(other.release_handle())
    {}
    event& operator=(event&& other) noexcept
    {
        if (this != &other) {
            exchange_handle(other);
        }
        return *this;
    }
    ~event()
    {
        native_handle_type handle = release_handle();
        if (handle != nullptr) {
            (void)::aclrtSynchronizeEvent(handle);
            (void)::aclrtDestroyEvent(handle);
        }
    }
    native_handle_type release() noexcept
    {
        return release_handle();
    }
    bool close() noexcept
    {
        if (handle_ == nullptr) {
            return true;
        }
        if (::aclrtSynchronizeEvent(handle_) != 0 || ::aclrtDestroyEvent(handle_) != 0) {
            return false;
        }
        handle_ = nullptr;
        return true;
    }

private:
    friend bool make_event(event&) noexcept;
    friend bool adopt_event(native_handle_type, event&) noexcept;
};

inline bool make_stream(stream& output, ::asc::std::uint32_t priority = 0) noexcept
{
    if (output) {
        return false;
    }
    void* handle = nullptr;
    if (::aclrtCreateStreamWithConfig(&handle, static_cast<unsigned int>(priority), 0) != 0) {
        return false;
    }
    output.handle_ = handle;
    return true;
}

inline bool make_event(event& output) noexcept
{
    if (output) {
        return false;
    }
    void* handle = nullptr;
    if (::aclrtCreateEvent(&handle) != 0) {
        return false;
    }
    output.handle_ = handle;
    return true;
}

inline bool adopt_stream(stream_ref::native_handle_type handle, stream& output) noexcept
{
    if (handle == nullptr || output) {
        return false;
    }
    output.handle_ = handle;
    return true;
}

inline bool adopt_event(event_ref::native_handle_type handle, event& output) noexcept
{
    if (handle == nullptr || output) {
        return false;
    }
    output.handle_ = handle;
    return true;
}

inline bool elapsed_time(event_ref start, event_ref end, float& milliseconds) noexcept
{
    float value = 0.0F;
    if (!start || !end || ::aclrtEventElapsedTime(&value, start.native_handle(), end.native_handle()) != 0) {
        return false;
    }
    milliseconds = value;
    return true;
}

}  // namespace asc

#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_STREAM_RUNTIME)
#undef CANN_ASC_STL_DETAIL_HAS_ACL_STREAM_RUNTIME
#endif

#endif  // CANN_ASC_STL_ASC___RUNTIME_STREAM_H
