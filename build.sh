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

set -e

CURRENT_DIR=$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")
BUILD_DIR=${CURRENT_DIR}/build
PKG_BUILD_DIR=${BUILD_DIR}/pkg
INSTALL_DIR=${BUILD_DIR}/install
CANN_PATH="${ASCEND_HOME_PATH:-/usr/local/Ascend/cann}"
CANN_PATH_SET="false"
THREAD_NUM=$(grep -c "^processor" /proc/cpuinfo)

RUN_HOST_TESTS="false"
RUN_DEVICE_COMPILE="false"
RUN_CANNSIM="false"
RUN_HARDWARE="false"
RUN_INSTALL="false"
MAKE_CLEAN="false"

dotted_line="----------------------------------------------------------------"

function log() {
    local current_time=$(date +"%Y-%m-%d %H:%M:%S")
    echo "[${current_time}] $1"
}

usage() {
    echo "build script for asc-stl repository (header-only C++ library)"
    echo "Usage: bash build.sh [OPTION]..."
    echo ""
    echo "    The following are all supported arguments:"
    echo ${dotted_line}
    echo "    -h, --help             Display help information"
    echo "    -j <N>                 Parallel jobs, default: CPU core count"
    echo "    -t, --test             Configure, build and run the Host gates:"
    echo "                           style check, header self-containment and Host"
    echo "                           semantic UT (requires C++17 compiler and Python 3)"
    echo "    --device-compile       Run the real CCE device compile gate"
    echo "                           (requires CANN package and BiSheng compiler)"
    echo "    --cannsim              Run the cannsim runtime gate"
    echo "                           (requires CANN package and cannsim executable)"
    echo "    --hardware             Run the Ascend 950 on-device gate"
    echo "                           (requires a real Ascend device)"
    echo "    -p, --cann_path <DIR>  CANN package installation root, applied to all device"
    echo "                           side gates (device compile / cannsim / hardware)."
    echo "                           The directory should contain set_env.sh (or"
    echo "                           ascend-toolkit/set_env.sh), which is sourced to load the"
    echo "                           matching compiler environment; ASCEND_HOME_PATH and"
    echo "                           ASC_STL_CANN_PACKAGE_PATH are set accordingly."
    echo "                           default: \$ASCEND_HOME_PATH or /usr/local/Ascend/cann"
    echo "    --prefix <DIR>         Install headers and CMake package config,"
    echo "                           default: build/install"
    echo "    --make_clean           Remove the build directory"
    echo ${dotted_line}
    echo "    With no option the script configures the project and installs the"
    echo "    headers together with the CMake package config into --prefix."
    echo ""
    echo "Examples:"
    echo "    bash build.sh"
    echo "    bash build.sh -t"
    echo "    bash build.sh --device-compile -p /usr/local/Ascend/cann"
    echo "    bash build.sh --cannsim -p /usr/local/Ascend/cann"
    echo "    bash build.sh --hardware"
    echo "    bash build.sh --prefix /usr/local/asc-stl -j 8"
}

function run_install() {
    # 安装流程使用独立的 build/pkg 目录（BUILD_TESTING=OFF），不占用测试与
    # IDE 使用的 build/ 目录，避免缓存中的开关影响后续 ctest 与 compile_commands。
    log "Configuring project (build directory: ${PKG_BUILD_DIR}, tests disabled for install)"
    cmake -S "${CURRENT_DIR}" -B "${PKG_BUILD_DIR}" -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=Release
    cmake --build "${PKG_BUILD_DIR}" --parallel "${THREAD_NUM}"
    log "Installing headers and CMake package config to ${INSTALL_DIR}"
    cmake --install "${PKG_BUILD_DIR}" --prefix "${INSTALL_DIR}"
    log "Install finished: ${INSTALL_DIR}"
}

function apply_cann_path() {
    # 仅在显式传入 -p/--cann_path 时生效：统一 CANN 安装选择、环境加载与
    # 工具链校验——优先加载该安装自带的 set_env.sh（含编译器路径），并同步
    # ASCEND_HOME_PATH 与 ASC_STL_CANN_PACKAGE_PATH；用户已显式设置的
    # ASC_STL_CANN_ENV_SCRIPT 不被覆盖。
    [ "${CANN_PATH_SET}" = "true" ] || return 0
    if [ -z "${ASC_STL_CANN_ENV_SCRIPT:-}" ]; then
        if [ -f "${CANN_PATH}/set_env.sh" ]; then
            export ASC_STL_CANN_ENV_SCRIPT="${CANN_PATH}/set_env.sh"
        elif [ -f "${CANN_PATH}/ascend-toolkit/set_env.sh" ]; then
            export ASC_STL_CANN_ENV_SCRIPT="${CANN_PATH}/ascend-toolkit/set_env.sh"
        else
            log "Warning: set_env.sh not found under ${CANN_PATH}; only ASCEND_HOME_PATH is set, make sure the toolchain is already in PATH"
        fi
    fi
    export ASCEND_HOME_PATH="${CANN_PATH}"
    export ASC_STL_CANN_PACKAGE_PATH="${CANN_PATH}"
}

ARGS=$(getopt -o hj:tp: -l help,test,device-compile,cannsim,hardware,make_clean,prefix:,cann_path: -- "$@")
if [ $? -ne 0 ]; then
    usage
    exit 1
fi
eval set -- "${ARGS}"

while true; do
    case "$1" in
        -h|--help)
            usage
            exit 0
            ;;
        -j)
            THREAD_NUM="$2"
            shift 2
            ;;
        -t|--test)
            RUN_HOST_TESTS="true"
            shift
            ;;
        --device-compile)
            RUN_DEVICE_COMPILE="true"
            shift
            ;;
        --cannsim)
            RUN_CANNSIM="true"
            shift
            ;;
        --hardware)
            RUN_HARDWARE="true"
            shift
            ;;
        --make_clean)
            MAKE_CLEAN="true"
            shift
            ;;
        --prefix)
            INSTALL_DIR="$2"
            RUN_INSTALL="true"
            shift 2
            ;;
        -p|--cann_path)
            CANN_PATH="$2"
            CANN_PATH_SET="true"
            shift 2
            ;;
        --)
            shift
            break
            ;;
        *)
            usage
            exit 1
            ;;
    esac
done

if [ "$#" -gt 0 ]; then
    log "Unexpected positional argument: $1"
    usage
    exit 1
fi

if [ "${MAKE_CLEAN}" = "true" ]; then
    log "Removing build directory: ${BUILD_DIR}"
    rm -rf "${BUILD_DIR}"
fi

if [ "${RUN_HOST_TESTS}" = "true" ]; then
    log "Running Host gates (ci-quick-check.sh)"
    bash "${CURRENT_DIR}/scripts/ci-quick-check.sh"
fi

if [ "${RUN_DEVICE_COMPILE}" = "true" ]; then
    apply_cann_path
    log "Running device compile gate (CANN package: ${CANN_PATH})"
    bash "${CURRENT_DIR}/scripts/ci-device-compile-check.sh"
fi

if [ "${RUN_CANNSIM}" = "true" ]; then
    apply_cann_path
    log "Running cannsim gate (CANN package: ${CANN_PATH})"
    bash "${CURRENT_DIR}/scripts/ci-cannsim-check.sh"
fi

if [ "${RUN_HARDWARE}" = "true" ]; then
    apply_cann_path
    log "Running Ascend 950 on-device gate (CANN package: ${CANN_PATH})"
    bash "${CURRENT_DIR}/scripts/ci-hardware-check.sh"
fi

if [ "${RUN_INSTALL}" = "true" ] || {
    [ "${RUN_HOST_TESTS}" = "false" ] && [ "${RUN_DEVICE_COMPILE}" = "false" ] &&
    [ "${RUN_CANNSIM}" = "false" ] && [ "${RUN_HARDWARE}" = "false" ] &&
    [ "${MAKE_CLEAN}" = "false" ]
}; then
    run_install
fi
