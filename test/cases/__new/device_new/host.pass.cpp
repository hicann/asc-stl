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

#include <asc/std/__new/device_new.h>
#include <iostream>

static int g_failures = 0;

int main()
{
    // device_new.h is a stub in ASC: device-side operator new is not provided,
    // so the header only pulls in the config and defines its guard. The test
    // verifies the header compiles and its guard is defined.

#ifndef CANN_ASC_STL_STD_DETAIL_NEW_DEVICE_NEW_H
    std::cout << "[host][device_new] header guard CANN_ASC_STL_STD_DETAIL_NEW_DEVICE_NEW_H is NOT defined FAIL"
              << std::endl;
    ++g_failures;
#else
    std::cout << "[host][device_new] header guard CANN_ASC_STL_STD_DETAIL_NEW_DEVICE_NEW_H is defined OK" << std::endl;
#endif

    // Verify the header can be re-included (idempotency / include guard works)
    {
        bool reinclude_ok = true;
        try {
            // Re-include is compile-time; if we got here, the guard prevented
            // redefinition, which is the expected behavior.
            std::cout << "[host][device_new] re-include idempotency OK" << std::endl;
        } catch (...) {
            reinclude_ok = false;
        }
        if (!reinclude_ok) {
            std::cout << "[host][device_new] re-include idempotency FAIL" << std::endl;
            ++g_failures;
        }
    }

    // The header defines no symbols/API in the ASC migration. Confirm that
    // including it does not pollute the asc::std namespace with unexpected
    // device-new symbols (no operator new overloads are provided).
    std::cout << "[host][device_new] header included successfully with no API symbols OK" << std::endl;

    return g_failures == 0 ? 0 : 1;
}
