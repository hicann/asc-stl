#!/usr/bin/env bash

# Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ASC_STL_RESTORE_NOUNSET=0
case $- in
    *u*)
        ASC_STL_RESTORE_NOUNSET=1
        set +u
        ;;
esac

if [ -n "${ASC_STL_CANN_ENV_SCRIPT:-}" ]; then
    if [ ! -f "$ASC_STL_CANN_ENV_SCRIPT" ]; then
        echo "CANN environment script does not exist: $ASC_STL_CANN_ENV_SCRIPT" >&2
        return 2 2>/dev/null || exit 2
    fi
    # shellcheck disable=SC1090
    source "$ASC_STL_CANN_ENV_SCRIPT"
elif [ -z "${ASCEND_HOME_PATH:-}" ] && [ -f /usr/local/Ascend/ascend-toolkit/set_env.sh ]; then
    # shellcheck disable=SC1091
    source /usr/local/Ascend/ascend-toolkit/set_env.sh
elif [ -z "${ASCEND_HOME_PATH:-}" ]; then
    echo "CANN environment is unavailable; set ASC_STL_CANN_ENV_SCRIPT." >&2
    return 2 2>/dev/null || exit 2
fi

if [ "$ASC_STL_RESTORE_NOUNSET" -eq 1 ]; then
    set -u
fi

if [ -z "${ASCEND_HOME_PATH:-}" ] || [ ! -d "$ASCEND_HOME_PATH" ]; then
    echo "ASCEND_HOME_PATH does not name an installed CANN package." >&2
    return 2 2>/dev/null || exit 2
fi

if ! command -v bisheng >/dev/null 2>&1; then
    echo "The BiSheng compiler is unavailable in the loaded CANN environment." >&2
    return 2 2>/dev/null || exit 2
fi
