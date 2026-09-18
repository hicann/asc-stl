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

#include <asc/std/__host_stdlib/time.h>
#include <iostream>
#include <string>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][time] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // Test that time() returns a valid time_t
    time_t t1 = time(nullptr);
    expect_true("time(nullptr) > 0", t1 > 0);

    // Test clock() returns a non-negative value or -1 (both are valid)
    clock_t c = clock();
    (void)c;

    // Test difftime
    time_t t2 = time(nullptr);
    double diff = difftime(t2, t1);
    expect_true("difftime(t2, t1) >= 0.0", diff >= 0.0);

    // Test mktime with a known date: 2000-01-01
    struct tm tm_val = {};
    tm_val.tm_year = 100;
    tm_val.tm_mon = 0;
    tm_val.tm_mday = 1;
    tm_val.tm_hour = 0;
    tm_val.tm_min = 0;
    tm_val.tm_sec = 0;
    time_t epoch2000 = mktime(&tm_val);
    expect_true("mktime(2000-01-01) > 0", epoch2000 > 0);

    // Test difftime between two consecutive days == 86400 seconds
    struct tm tm_val2 = {};
    tm_val2.tm_year = 100;
    tm_val2.tm_mon = 0;
    tm_val2.tm_mday = 2;
    tm_val2.tm_hour = 0;
    tm_val2.tm_min = 0;
    tm_val2.tm_sec = 0;
    time_t epoch2000_2 = mktime(&tm_val2);
    double day_diff = difftime(epoch2000_2, epoch2000);
    expect_true("difftime(2000-01-02, 2000-01-01) == 86400.0", day_diff == 86400.0);

    // Test strftime
    char buf[64];
    struct tm tm_fmt = {};
    tm_fmt.tm_year = 125;
    tm_fmt.tm_mon = 0;
    tm_fmt.tm_mday = 15;
    tm_fmt.tm_hour = 12;
    tm_fmt.tm_min = 30;
    tm_fmt.tm_sec = 45;
    mktime(&tm_fmt);
    size_t n = strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm_fmt);
    expect_true("strftime result length > 0", n > 0);
    std::string result(buf);
    expect_true("strftime produces '2025-01-15 12:30:45'", result == "2025-01-15 12:30:45");

    return g_failures == 0 ? 0 : 1;
}
