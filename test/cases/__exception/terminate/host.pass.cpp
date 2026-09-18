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

#include <asc/std/__exception/terminate.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][terminate] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Verify terminate() is noexcept
    expect_true("noexcept(asc::std::terminate())", noexcept(asc::std::terminate()));

    // Verify that terminate() actually terminates the process with non-zero exit code.
    // We test this in a child process so the test harness itself is not killed.
    {
        pid_t pid = fork();
        if (pid == 0) {
            // Child: call terminate() which should call exit(-1)
            asc::std::terminate();
            // Should never reach here
            _exit(0);
        } else if (pid > 0) {
            int status = 0;
            waitpid(pid, &status, 0);
            bool exited_nonzero = WIFEXITED(status) && (WEXITSTATUS(status) != 0);
            expect_true("child process exits non-zero after terminate()", exited_nonzero);
        } else {
            expect_true("fork() succeeded", false);
        }
    }

    // set_terminate, get_terminate, and terminate_handler are not exposed
    // by the header yet, so they are not tested here.
    std::cout << "[host][terminate] set_terminate/get_terminate/terminate_handler are disabled (#if 0) - skipped"
              << std::endl;

    return g_failures == 0 ? 0 : 1;
}
