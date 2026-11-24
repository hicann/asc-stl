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

set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
if ! source "$ROOT/scripts/cann-env.sh"; then
    echo "BLOCKED_ENVIRONMENT: CANN hardware environment is unavailable." >&2
    exit 2
fi
python3 "$ROOT/scripts/hardware_device.py"

SOURCE_CASE_ROOT="$ROOT/test/cases/asc/std/source_location/runtime/hardware"
FOUNDATION_CASE_ROOT="$ROOT/test/cases/asc/std/__cstring/memcpy/runtime/hardware"
B016_CASE_ROOT="$ROOT/test/cases/asc/hierarchy/runtime/hardware"
B019_CASE_ROOT="$ROOT/test/cases/asc/__algorithm/frontend/runtime/hardware"
B022_CASE_ROOT="$ROOT/test/cases/asc/std/atomic/runtime/hardware"
B017_WARP_CASE_ROOT="$ROOT/test/cases/asc/warp/runtime/hardware"
B018_COLLECTIVES_CASE_ROOT="$ROOT/test/cases/asc/__collectives/block/runtime/hardware"
B013_SCOPED_ATOMIC_CASE_ROOT="$ROOT/test/cases/asc/atomic/runtime/hardware"
B015_COMPLEX_CASE_ROOT="$ROOT/test/cases/asc/std/__complex/logarithms/runtime/hardware"
B014_CSTDLIB_CASE_ROOT="$ROOT/test/cases/asc/std/cstdlib/runtime/hardware"
B021_CTIME_CASE_ROOT="$ROOT/test/cases/asc/std/ctime/runtime/hardware"
B023_CASE_ROOT="$ROOT/test/cases/asc/algorithm/runtime/hardware"
B025_MEMORY_POOL_CASE_ROOT="$ROOT/scripts/hardware-cases/memory_pool"
B026_WORK_QUEUE_CASE_ROOT="$ROOT/test/cases/asc/work_queue/runtime/hardware"
NUMERIC_TYPES_CASE_ROOT="$ROOT/test/cases/asc/numeric_types/runtime"
ITERATOR_CASE_ROOT="$ROOT/test/cases/asc/iterator/runtime"
RANDOM_CASE_ROOT="$ROOT/test/cases/asc/random/runtime"
B026_CMATH_CASE_ROOT="$ROOT/test/cases/asc/cmath/runtime/hardware"
B026_TENSOR_COPY_CASE_ROOT="$ROOT/test/cases/asc/__tensor_copy/descriptor/runtime/hardware"
B024_ITERATOR_CASE_ROOT="$ROOT/test/cases/asc/std/iterator/runtime/hardware"
B027_BITSET_CASE_ROOT="$ROOT/test/cases/asc/std/bitset/runtime/hardware"
B028_LIST_CASE_ROOT="$ROOT/test/cases/asc/std/list/runtime/hardware"
W08_CASE_ROOT="$ROOT/test/cases/asc/tensor_copy/runtime/hardware"
W13_W14_CASE_ROOT="$ROOT/test/cases/asc/std/linalg/runtime/hardware"
BUILD_ROOT="${ASC_STL_HARDWARE_BUILD_DIR:-$ROOT/build/hardware}"
RUNS="${ASC_STL_HARDWARE_RUNS:-3}"
BUILD_JOBS="${CMAKE_BUILD_PARALLEL_LEVEL:-2}"
CASE_TIMEOUT="${ASC_STL_HARDWARE_CASE_TIMEOUT_SECONDS:-120}"
CLEANUP_GRACE="${ASC_STL_HARDWARE_CLEANUP_GRACE_SECONDS:-20}"
CASE_RESULTS="$BUILD_ROOT/hardware-case-results.csv"
HW1_RESULTS="$BUILD_ROOT/hw1-passed-cases.txt"
mkdir -p "$BUILD_ROOT"
: >"$CASE_RESULTS"
: >"$HW1_RESULTS"

run_bounded_hardware() {
    local label="$1"
    shift
    python3 "$ROOT/scripts/run_hardware_case.py" \
        --timeout "$CASE_TIMEOUT" --grace "$CLEANUP_GRACE" \
        --log "$BUILD_ROOT/logs/$label.log" "$@"
}

run_hardware_case() {
    local runtime_case="$1"
    local standard="$2"
    local mode="$3"
    local run_index="$4"
    shift 4
    local label="cxx$standard-${runtime_case//\//_}-$mode-$run_index"
    local status=0
    if run_bounded_hardware "$label" -- "$@"; then
        printf '%s,%s,%s,%s,PASS\n' "$runtime_case" "$standard" "$mode" "$run_index" >>"$CASE_RESULTS"
    else
        status=$?
        printf '%s,%s,%s,%s,FAIL\n' "$runtime_case" "$standard" "$mode" "$run_index" >>"$CASE_RESULTS"
        echo "FAIL: hardware suite stopped after $label (exit=$status); verify device health before retrying." >&2
        return "$status"
    fi
}
for standard in 17 20; do
    SOURCE_BUILD_DIR="$BUILD_ROOT/cxx$standard/source-location"
    FOUNDATION_BUILD_DIR="$BUILD_ROOT/cxx$standard/foundation"
    B016_BUILD_DIR="$BUILD_ROOT/cxx$standard/b016"
    B019_BUILD_DIR="$BUILD_ROOT/cxx$standard/b019"
    B022_BUILD_DIR="$BUILD_ROOT/cxx$standard/b022"
    B017_WARP_BUILD_DIR="$BUILD_ROOT/cxx$standard/b017-warp"
    B018_COLLECTIVES_BUILD_DIR="$BUILD_ROOT/cxx$standard/b018-collectives"
    B013_SCOPED_ATOMIC_BUILD_DIR="$BUILD_ROOT/cxx$standard/b013-scoped-atomic"
    B015_COMPLEX_BUILD_DIR="$BUILD_ROOT/cxx$standard/b015-complex"
    B014_CSTDLIB_BUILD_DIR="$BUILD_ROOT/cxx$standard/b014-cstdlib"
    B021_CTIME_BUILD_DIR="$BUILD_ROOT/cxx$standard/b021-ctime"
    B023_BUILD_DIR="$BUILD_ROOT/cxx$standard/b023"
    BOUNDS_BUILD_DIR="$BUILD_ROOT/cxx$standard/pointer-bounds"
    RANGES_BUILD_DIR="$BUILD_ROOT/cxx$standard/range-algorithms"
    B025_MEMORY_POOL_BUILD_DIR="$BUILD_ROOT/cxx$standard/b025-memory-pool"
    B026_WORK_QUEUE_BUILD_DIR="$BUILD_ROOT/cxx$standard/b026-work-queue"
    NUMERIC_TYPES_BUILD_DIR="$BUILD_ROOT/cxx$standard/numeric-types"
    ITERATOR_BUILD_DIR="$BUILD_ROOT/cxx$standard/iterator"
    RANDOM_BUILD_DIR="$BUILD_ROOT/cxx$standard-random"
    B026_CMATH_BUILD_DIR="$BUILD_ROOT/cxx$standard/b026-cmath"
    B026_TENSOR_COPY_BUILD_DIR="$BUILD_ROOT/cxx$standard/b026-tensor-copy"
    B024_ITERATOR_BUILD_DIR="$BUILD_ROOT/cxx$standard/b024-iterator"
    B027_BITSET_BUILD_DIR="$BUILD_ROOT/cxx$standard/b027-bitset"
    B028_LIST_BUILD_DIR="$BUILD_ROOT/cxx$standard/b028-list-map"
    W08_BUILD_DIR="$BUILD_ROOT/cxx$standard/w08"
    W13_W14_BUILD_DIR="$BUILD_ROOT/cxx$standard/w13-w14"
    cmake -S "$SOURCE_CASE_ROOT" -B "$SOURCE_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$SOURCE_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$FOUNDATION_CASE_ROOT" -B "$FOUNDATION_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$FOUNDATION_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B016_CASE_ROOT" -B "$B016_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B016_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B019_CASE_ROOT" -B "$B019_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B019_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B022_CASE_ROOT" -B "$B022_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B022_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B017_WARP_CASE_ROOT" -B "$B017_WARP_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B017_WARP_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B018_COLLECTIVES_CASE_ROOT" -B "$B018_COLLECTIVES_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B018_COLLECTIVES_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B013_SCOPED_ATOMIC_CASE_ROOT" -B "$B013_SCOPED_ATOMIC_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B013_SCOPED_ATOMIC_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B015_COMPLEX_CASE_ROOT" -B "$B015_COMPLEX_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B015_COMPLEX_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B014_CSTDLIB_CASE_ROOT" -B "$B014_CSTDLIB_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B014_CSTDLIB_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B021_CTIME_CASE_ROOT" -B "$B021_CTIME_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B021_CTIME_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B023_CASE_ROOT" -B "$B023_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B023_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$ROOT/test/cases/asc/std/__algorithm/lower_bound/runtime/hardware" -B "$BOUNDS_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$BOUNDS_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$ROOT/test/cases/asc/std/__algorithm/ranges_copy/runtime/hardware" -B "$RANGES_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$RANGES_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B025_MEMORY_POOL_CASE_ROOT" -B "$B025_MEMORY_POOL_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B025_MEMORY_POOL_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B026_WORK_QUEUE_CASE_ROOT" -B "$B026_WORK_QUEUE_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B026_WORK_QUEUE_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$NUMERIC_TYPES_CASE_ROOT" -B "$NUMERIC_TYPES_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$NUMERIC_TYPES_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$ITERATOR_CASE_ROOT" -B "$ITERATOR_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$ITERATOR_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B026_CMATH_CASE_ROOT" -B "$B026_CMATH_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B026_CMATH_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B026_TENSOR_COPY_CASE_ROOT" -B "$B026_TENSOR_COPY_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B026_TENSOR_COPY_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B024_ITERATOR_CASE_ROOT" -B "$B024_ITERATOR_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B024_ITERATOR_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B027_BITSET_CASE_ROOT" -B "$B027_BITSET_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B027_BITSET_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$B028_LIST_CASE_ROOT" -B "$B028_LIST_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$B028_LIST_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$W08_CASE_ROOT" -B "$W08_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$W08_BUILD_DIR" -j"$BUILD_JOBS"
    cmake -S "$W13_W14_CASE_ROOT" -B "$W13_W14_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$W13_W14_BUILD_DIR" -j"$BUILD_JOBS"

    cmake -S "$RANDOM_CASE_ROOT" -B "$RANDOM_BUILD_DIR" \
        -DASC_STL_INCLUDE_DIR="$ROOT/include" -DASC_STL_CXX_STANDARD="$standard" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$RANDOM_BUILD_DIR" -j "$BUILD_JOBS"

    for run_index in $(seq 1 "$RUNS"); do
        echo "C++$standard source_location hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/std/source_location" "$standard" simd "$run_index" "$SOURCE_BUILD_DIR/asc_stl_source_location_simd"
        echo "C++$standard source_location hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/source_location" "$standard" simt "$run_index" "$SOURCE_BUILD_DIR/asc_stl_source_location_simt"
        echo "C++$standard foundation runtime hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/std/__cstring/memcpy.h" "$standard" simd "$run_index" "$FOUNDATION_BUILD_DIR/asc_stl_foundation_simd"
        echo "C++$standard foundation runtime hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/__cstring/memcpy.h" "$standard" simt "$run_index" "$FOUNDATION_BUILD_DIR/asc_stl_foundation_simt"
        echo "C++$standard hierarchy hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/hierarchy" "$standard" simd "$run_index" "$B016_BUILD_DIR/asc_stl_b016_simd"
        echo "C++$standard hierarchy hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/hierarchy" "$standard" simt "$run_index" "$B016_BUILD_DIR/asc_stl_b016_simt"
        echo "C++$standard algorithm runtime hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/__algorithm/frontend.h" "$standard" simd "$run_index" "$B019_BUILD_DIR/asc_stl_b019_simd"
        echo "C++$standard algorithm runtime hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/__algorithm/frontend.h" "$standard" simt "$run_index" "$B019_BUILD_DIR/asc_stl_b019_simt"
        echo "C++$standard batch 22 atomic and rotate hardware run $run_index/$RUNS: D-SIMD"
        run_bounded_hardware "cxx$standard-b022-simd-$run_index" -- "$B022_BUILD_DIR/asc_stl_b022_simd"
        echo "C++$standard batch 22 atomic and rotate hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/atomic" "$standard" simt "$run_index" "$B022_BUILD_DIR/asc_stl_b022_simt"
        echo "C++$standard warp hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/warp" "$standard" simt "$run_index" "$B017_WARP_BUILD_DIR/asc_stl_b017_simt"
        echo "C++$standard warp failure-injection run $run_index/$RUNS: D-SIMT"
        ASC_STL_WARP_INJECT_FAILURE=1 run_bounded_hardware "cxx$standard-warp-injection-$run_index" \
            --expected-exit 42 --expected-marker ASC_STL_EXPECTED_WARP_FAILURE_VERIFIED \
            -- "$B017_WARP_BUILD_DIR/asc_stl_b017_simt"
        echo "C++$standard collectives hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/__collectives/block.h" "$standard" simd "$run_index" "$B018_COLLECTIVES_BUILD_DIR/asc_stl_b018_simd"
        echo "C++$standard collectives hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/__collectives/block.h" "$standard" simt "$run_index" "$B018_COLLECTIVES_BUILD_DIR/asc_stl_b018_simt"
        echo "C++$standard scoped atomic hardware run $run_index/$RUNS: D-SIMD"
        run_bounded_hardware "cxx$standard-atomic-simd-$run_index" -- "$B013_SCOPED_ATOMIC_BUILD_DIR/asc_stl_atomic_simd"
        echo "C++$standard scoped atomic hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/atomic" "$standard" simt "$run_index" "$B013_SCOPED_ATOMIC_BUILD_DIR/asc_stl_atomic_simt"
        echo "C++$standard complex logarithms hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/std/__complex/logarithms.h" "$standard" simd "$run_index" "$B015_COMPLEX_BUILD_DIR/asc_stl_b015_simd"
        echo "C++$standard complex logarithms hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/__complex/logarithms.h" "$standard" simt "$run_index" "$B015_COMPLEX_BUILD_DIR/asc_stl_b015_simt"
        echo "C++$standard cstdlib hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/std/cstdlib" "$standard" simd "$run_index" "$B014_CSTDLIB_BUILD_DIR/asc_stl_b014_simd"
        echo "C++$standard cstdlib hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/cstdlib" "$standard" simt "$run_index" "$B014_CSTDLIB_BUILD_DIR/asc_stl_b014_simt"
        echo "C++$standard ctime hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/std/ctime" "$standard" simd "$run_index" "$B021_CTIME_BUILD_DIR/asc_stl_b021_simd"
        echo "C++$standard ctime hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/ctime" "$standard" simt "$run_index" "$B021_CTIME_BUILD_DIR/asc_stl_b021_simt"
        echo "C++$standard batch 23 string-view comparison hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/algorithm" "$standard" simd "$run_index" "$B023_BUILD_DIR/asc_stl_b023_simd"
        echo "C++$standard batch 23 string-view comparison hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/algorithm" "$standard" simt "$run_index" "$B023_BUILD_DIR/asc_stl_b023_simt"
        run_hardware_case "asc/std/__algorithm/lower_bound.h" "$standard" simt "$run_index" "$BOUNDS_BUILD_DIR/asc_stl_bounds_simt"
        run_hardware_case "asc/std/__algorithm/ranges_copy.h" "$standard" simt "$run_index" "$RANGES_BUILD_DIR/asc_stl_ranges_simt"
        echo "C++$standard batch 25 memory-pool lifecycle hardware run $run_index/$RUNS: Host+CANN"
        run_bounded_hardware "cxx$standard-memory-pool-$run_index" -- "$B025_MEMORY_POOL_BUILD_DIR/asc_stl_b025_memory_pool"
        echo "C++$standard work queue hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/work_queue" "$standard" simd "$run_index" "$B026_WORK_QUEUE_BUILD_DIR/asc_stl_b026_work_queue_simd"
        echo "C++$standard work queue hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/work_queue" "$standard" simt "$run_index" "$B026_WORK_QUEUE_BUILD_DIR/asc_stl_b026_work_queue_simt"
        run_hardware_case "asc/numeric_types" "$standard" simd "$run_index" "$NUMERIC_TYPES_BUILD_DIR/asc_stl_numeric_types_simd"
        run_hardware_case "asc/numeric_types" "$standard" simt "$run_index" "$NUMERIC_TYPES_BUILD_DIR/asc_stl_numeric_types_simt"
        run_hardware_case "asc/iterator" "$standard" simd "$run_index" "$ITERATOR_BUILD_DIR/asc_stl_iterator_simd"
        run_hardware_case "asc/iterator" "$standard" simt "$run_index" "$ITERATOR_BUILD_DIR/asc_stl_iterator_simt"
        run_hardware_case "asc/random" "$standard" simd "$run_index" "$RANDOM_BUILD_DIR/asc_stl_random_simd"
        run_hardware_case "asc/random" "$standard" simt "$run_index" "$RANDOM_BUILD_DIR/asc_stl_random_simt"
        echo "C++$standard cmath hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/cmath" "$standard" simd "$run_index" "$B026_CMATH_BUILD_DIR/asc_stl_b026_cmath_simd"
        echo "C++$standard cmath hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/cmath" "$standard" simt "$run_index" "$B026_CMATH_BUILD_DIR/asc_stl_b026_cmath_simt"
        echo "C++$standard tensor copy hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/__tensor_copy/descriptor.h" "$standard" simd "$run_index" "$B026_TENSOR_COPY_BUILD_DIR/asc_stl_b026_tensor_copy_simd"
        echo "C++$standard tensor copy hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/__tensor_copy/descriptor.h" "$standard" simt "$run_index" "$B026_TENSOR_COPY_BUILD_DIR/asc_stl_b026_tensor_copy_simt"
        echo "C++$standard iterator cursor revalidation run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/iterator" "$standard" simt "$run_index" "$B024_ITERATOR_BUILD_DIR/asc_stl_b024_simt"
        echo "C++$standard batch 27 bitset/fixed-storage hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/std/bitset" "$standard" simd "$run_index" "$B027_BITSET_BUILD_DIR/asc_stl_b027_simd"
        echo "C++$standard batch 27 bitset/fixed-storage hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/bitset" "$standard" simt "$run_index" "$B027_BITSET_BUILD_DIR/asc_stl_b027_simt"
        echo "C++$standard batch 28 list/map hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/list" "$standard" simt "$run_index" "$B028_LIST_BUILD_DIR/asc_stl_b028_simt"
        echo "C++$standard batch 28 foundation hardware run $run_index/$RUNS: D-SIMD"
        run_bounded_hardware "cxx$standard-b028-simd-$run_index" -- "$B028_LIST_BUILD_DIR/asc_stl_b028_simd"
        echo "C++$standard W08/W09/W10/W11/W12 hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/tensor_copy" "$standard" simd "$run_index" "$W08_BUILD_DIR/asc_stl_w08_simd"
        echo "C++$standard W08/W09/W10/W11/W12 hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/tensor_copy" "$standard" simt "$run_index" "$W08_BUILD_DIR/asc_stl_w08_simt"
        echo "C++$standard W13/W14 hardware run $run_index/$RUNS: D-SIMD"
        run_hardware_case "asc/std/linalg" "$standard" simd "$run_index" "$W13_W14_BUILD_DIR/asc_stl_w13_w14_simd"
        echo "C++$standard W13/W14 hardware run $run_index/$RUNS: D-SIMT"
        run_hardware_case "asc/std/linalg" "$standard" simt "$run_index" "$W13_W14_BUILD_DIR/asc_stl_w13_w14_simt"
    done
done
python3 "$ROOT/test/scripts/validate_hardware_results.py" \
    --manifest "$ROOT/test/metadata/headers.json" --results "$CASE_RESULTS" --runs "$RUNS"
printf '%s\n' \
    "asc/__algorithm/frontend.h" \
    "asc/__collectives/block.h" \
    "asc/__tensor_copy/descriptor.h" \
    "asc/atomic" \
    "asc/cmath" \
    "asc/numeric_types" \
    "asc/iterator" \
    "asc/random" \
    "asc/hierarchy" \
    "asc/std/__algorithm/lower_bound.h" \
    "asc/std/__algorithm/ranges_copy.h" \
    "asc/std/__complex/logarithms.h" \
    "asc/std/__cstring/memcpy.h" \
    "asc/std/atomic" \
    "asc/std/ctime" \
    "asc/std/iterator" \
    "asc/std/linalg" \
    "asc/std/list" \
    "asc/tensor_copy" \
    "asc/warp" \
    "asc/work_queue" >>"$HW1_RESULTS"
echo "PASS: C++17/C++20 source_location, foundation, hierarchy, algorithm, B022 atomic/rotate, B023 string-view, B025 memory-pool, work-queue, cmath, tensor-copy, iterator, B027 bitset/fixed-storage, B028 list/map, W08/W09/W10/W11/W12, and W13/W14 hardware semantics ($RUNS runs each)"
