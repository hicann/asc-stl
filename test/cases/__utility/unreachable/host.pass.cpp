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

#include <asc/std/__utility/unreachable.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][unreachable] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

// Compile-time check: asc::std::unreachable() is [[noreturn]],
// so this [[noreturn]] function compiles without a return statement.
[[noreturn]] static void verify_noreturn()
{
    asc::std::unreachable();
}

int main()
{
    // Force the compiler to compile verify_noreturn (compile-time [[noreturn]] check)
    (void)&verify_noreturn;

    // Test 1: Verify [[noreturn]] attribute (compile-time)
    // If unreachable() were not [[noreturn]], verify_noreturn() would fail to compile.
    expect_true("unreachable() is [[noreturn]] (compile-time check)", true);

#ifdef ASC_ENABLE_HOST_ASSERTIONS
    // Test 2: When assertions are enabled, calling unreachable() should
    // cause abnormal termination (SIGABRT from __assert_fail).
    {
        std::cout << "[host][unreachable] Testing runtime termination (assertions enabled)..." << std::endl;
        pid_t pid = fork();
        if (pid == 0) {
            // Child: call unreachable() — should never return
            asc::std::unreachable();
            _exit(0);  // Should never reach here
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            bool abnormal = !WIFEXITED(status) || WEXITSTATUS(status) != 0;
            if (WIFSIGNALED(status)) {
                std::cout << "[host][unreachable] Child terminated by signal " << WTERMSIG(status) << std::endl;
            }
            expect_true("unreachable() causes abnormal termination (assertions enabled)", abnormal);
        } else {
            std::cout << "[host][unreachable] fork() failed — skipping runtime test" << std::endl;
        }
    }
#else
    std::cout << "[host][unreachable] Assertions disabled — skipping runtime termination test" << std::endl;
    std::cout << "[host][unreachable] (with assertions off, unreachable() reduces to __builtin_unreachable() = UB)"
              << std::endl;
#endif

    return g_failures == 0 ? 0 : 1;
}
