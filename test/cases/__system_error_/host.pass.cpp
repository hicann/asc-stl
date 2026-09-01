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

#include <asc/std/__system_error_>
#include <iostream>
#include <cerrno>

static int g_failures = 0;

static void expect_eq(const char* expr, int got, int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][__system_error_] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

static void check_part1()
{
    // In hosted mode asc::std::errc is an alias for std::errc.
    // Verify each enumerator matches the corresponding POSIX errno macro.
    expect_eq("errc::address_family_not_supported", static_cast<int>(asc::std::errc::address_family_not_supported),
        EAFNOSUPPORT);
    expect_eq("errc::address_in_use", static_cast<int>(asc::std::errc::address_in_use), EADDRINUSE);
    expect_eq("errc::address_not_available", static_cast<int>(asc::std::errc::address_not_available), EADDRNOTAVAIL);
    expect_eq("errc::already_connected", static_cast<int>(asc::std::errc::already_connected), EISCONN);
    expect_eq("errc::argument_list_too_long", static_cast<int>(asc::std::errc::argument_list_too_long), E2BIG);
    expect_eq("errc::argument_out_of_domain", static_cast<int>(asc::std::errc::argument_out_of_domain), EDOM);
    expect_eq("errc::bad_address", static_cast<int>(asc::std::errc::bad_address), EFAULT);
    expect_eq("errc::bad_file_descriptor", static_cast<int>(asc::std::errc::bad_file_descriptor), EBADF);
    expect_eq("errc::bad_message", static_cast<int>(asc::std::errc::bad_message), EBADMSG);
    expect_eq("errc::broken_pipe", static_cast<int>(asc::std::errc::broken_pipe), EPIPE);
    expect_eq("errc::connection_aborted", static_cast<int>(asc::std::errc::connection_aborted), ECONNABORTED);
    expect_eq("errc::connection_already_in_progress", static_cast<int>(asc::std::errc::connection_already_in_progress),
        EALREADY);
    expect_eq("errc::connection_refused", static_cast<int>(asc::std::errc::connection_refused), ECONNREFUSED);
    expect_eq("errc::connection_reset", static_cast<int>(asc::std::errc::connection_reset), ECONNRESET);
    expect_eq("errc::cross_device_link", static_cast<int>(asc::std::errc::cross_device_link), EXDEV);
    expect_eq("errc::destination_address_required", static_cast<int>(asc::std::errc::destination_address_required),
        EDESTADDRREQ);
    expect_eq("errc::device_or_resource_busy", static_cast<int>(asc::std::errc::device_or_resource_busy), EBUSY);
    expect_eq("errc::directory_not_empty", static_cast<int>(asc::std::errc::directory_not_empty), ENOTEMPTY);
    expect_eq("errc::executable_format_error", static_cast<int>(asc::std::errc::executable_format_error), ENOEXEC);
    expect_eq("errc::file_exists", static_cast<int>(asc::std::errc::file_exists), EEXIST);
    expect_eq("errc::file_too_large", static_cast<int>(asc::std::errc::file_too_large), EFBIG);
    expect_eq("errc::filename_too_long", static_cast<int>(asc::std::errc::filename_too_long), ENAMETOOLONG);
    expect_eq("errc::function_not_supported", static_cast<int>(asc::std::errc::function_not_supported), ENOSYS);
    expect_eq("errc::host_unreachable", static_cast<int>(asc::std::errc::host_unreachable), EHOSTUNREACH);
}

static void check_part2()
{
    expect_eq("errc::identifier_removed", static_cast<int>(asc::std::errc::identifier_removed), EIDRM);
    expect_eq("errc::illegal_byte_sequence", static_cast<int>(asc::std::errc::illegal_byte_sequence), EILSEQ);
    expect_eq("errc::inappropriate_io_control_operation",
        static_cast<int>(asc::std::errc::inappropriate_io_control_operation), ENOTTY);
    expect_eq("errc::interrupted", static_cast<int>(asc::std::errc::interrupted), EINTR);
    expect_eq("errc::invalid_argument", static_cast<int>(asc::std::errc::invalid_argument), EINVAL);
    expect_eq("errc::invalid_seek", static_cast<int>(asc::std::errc::invalid_seek), ESPIPE);
    expect_eq("errc::io_error", static_cast<int>(asc::std::errc::io_error), EIO);
    expect_eq("errc::is_a_directory", static_cast<int>(asc::std::errc::is_a_directory), EISDIR);
    expect_eq("errc::message_size", static_cast<int>(asc::std::errc::message_size), EMSGSIZE);
    expect_eq("errc::network_down", static_cast<int>(asc::std::errc::network_down), ENETDOWN);
    expect_eq("errc::network_reset", static_cast<int>(asc::std::errc::network_reset), ENETRESET);
    expect_eq("errc::network_unreachable", static_cast<int>(asc::std::errc::network_unreachable), ENETUNREACH);
    expect_eq("errc::no_buffer_space", static_cast<int>(asc::std::errc::no_buffer_space), ENOBUFS);
    expect_eq("errc::no_child_process", static_cast<int>(asc::std::errc::no_child_process), ECHILD);
    expect_eq("errc::no_link", static_cast<int>(asc::std::errc::no_link), ENOLINK);
    expect_eq("errc::no_lock_available", static_cast<int>(asc::std::errc::no_lock_available), ENOLCK);
    expect_eq("errc::no_message_available", static_cast<int>(asc::std::errc::no_message_available), ENODATA);
    expect_eq("errc::no_message", static_cast<int>(asc::std::errc::no_message), ENOMSG);
    expect_eq("errc::no_protocol_option", static_cast<int>(asc::std::errc::no_protocol_option), ENOPROTOOPT);
    expect_eq("errc::no_space_on_device", static_cast<int>(asc::std::errc::no_space_on_device), ENOSPC);
    expect_eq("errc::no_stream_resources", static_cast<int>(asc::std::errc::no_stream_resources), ENOSR);
    expect_eq("errc::no_such_device_or_address", static_cast<int>(asc::std::errc::no_such_device_or_address), ENXIO);
    expect_eq("errc::no_such_device", static_cast<int>(asc::std::errc::no_such_device), ENODEV);
    expect_eq("errc::no_such_file_or_directory", static_cast<int>(asc::std::errc::no_such_file_or_directory), ENOENT);
    expect_eq("errc::no_such_process", static_cast<int>(asc::std::errc::no_such_process), ESRCH);
    expect_eq("errc::not_a_directory", static_cast<int>(asc::std::errc::not_a_directory), ENOTDIR);
    expect_eq("errc::not_a_socket", static_cast<int>(asc::std::errc::not_a_socket), ENOTSOCK);
    expect_eq("errc::not_a_stream", static_cast<int>(asc::std::errc::not_a_stream), ENOSTR);
}

static void check_part3()
{
    expect_eq("errc::not_connected", static_cast<int>(asc::std::errc::not_connected), ENOTCONN);
    expect_eq("errc::not_enough_memory", static_cast<int>(asc::std::errc::not_enough_memory), ENOMEM);
    expect_eq("errc::not_supported", static_cast<int>(asc::std::errc::not_supported), ENOTSUP);
    expect_eq("errc::operation_canceled", static_cast<int>(asc::std::errc::operation_canceled), ECANCELED);
    expect_eq("errc::operation_in_progress", static_cast<int>(asc::std::errc::operation_in_progress), EINPROGRESS);
    expect_eq("errc::operation_not_permitted", static_cast<int>(asc::std::errc::operation_not_permitted), EPERM);
    expect_eq("errc::operation_not_supported", static_cast<int>(asc::std::errc::operation_not_supported), EOPNOTSUPP);
    expect_eq("errc::operation_would_block", static_cast<int>(asc::std::errc::operation_would_block), EWOULDBLOCK);
    expect_eq("errc::owner_dead", static_cast<int>(asc::std::errc::owner_dead), EOWNERDEAD);
    expect_eq("errc::permission_denied", static_cast<int>(asc::std::errc::permission_denied), EACCES);
    expect_eq("errc::protocol_error", static_cast<int>(asc::std::errc::protocol_error), EPROTO);
    expect_eq(
        "errc::protocol_not_supported", static_cast<int>(asc::std::errc::protocol_not_supported), EPROTONOSUPPORT);
    expect_eq("errc::read_only_file_system", static_cast<int>(asc::std::errc::read_only_file_system), EROFS);
    expect_eq("errc::resource_deadlock_would_occur", static_cast<int>(asc::std::errc::resource_deadlock_would_occur),
        EDEADLK);
    expect_eq("errc::resource_unavailable_try_again", static_cast<int>(asc::std::errc::resource_unavailable_try_again),
        EAGAIN);
    expect_eq("errc::result_out_of_range", static_cast<int>(asc::std::errc::result_out_of_range), ERANGE);
    expect_eq("errc::state_not_recoverable", static_cast<int>(asc::std::errc::state_not_recoverable), ENOTRECOVERABLE);
    expect_eq("errc::stream_timeout", static_cast<int>(asc::std::errc::stream_timeout), ETIME);
    expect_eq("errc::text_file_busy", static_cast<int>(asc::std::errc::text_file_busy), ETXTBSY);
    expect_eq("errc::timed_out", static_cast<int>(asc::std::errc::timed_out), ETIMEDOUT);
    expect_eq(
        "errc::too_many_files_open_in_system", static_cast<int>(asc::std::errc::too_many_files_open_in_system), ENFILE);
    expect_eq("errc::too_many_files_open", static_cast<int>(asc::std::errc::too_many_files_open), EMFILE);
    expect_eq("errc::too_many_links", static_cast<int>(asc::std::errc::too_many_links), EMLINK);
    expect_eq(
        "errc::too_many_symbolic_link_levels", static_cast<int>(asc::std::errc::too_many_symbolic_link_levels), ELOOP);
}

static void check_part4()
{
    expect_eq("errc::value_too_large", static_cast<int>(asc::std::errc::value_too_large), EOVERFLOW);
    expect_eq("errc::wrong_protocol_type", static_cast<int>(asc::std::errc::wrong_protocol_type), EPROTOTYPE);
}

int main()
{
    check_part1();
    check_part2();
    check_part3();
    check_part4();

    return g_failures == 0 ? 0 : 1;
}
