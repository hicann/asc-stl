# User acceptance and performance baselines

Release acceptance checks observable correctness, the documented user journey,
and timings in the selected environment. The scenarios below are representative;
they do not cover every API, input, device, or CANN version.

| User task | Executable entry | Independent result check |
| --- | --- | --- |
| Sort 32768 integer records | `scripts/run_user_acceptance.py` | Check every sorted value against the input distribution |
| Grow a sequence to 65536 elements | Same entry | Check every value, size and checksum; separately check self-reference during reallocation |
| Update a 256×256 matrix view | Same entry | Compare every element with the direct indexing formula |
| Build, launch and read back a kernel | [Complete Quick Start](../quick_start.md) | Compare with an independent Host golden and check cleanup |
| Submit device parallel algorithms | [Complete parallel example](../../../examples/extension/parallel_algorithms/README_en.md) | Check inputs, synchronization, outputs and cleanup for 57 cases |
| Manage Runtime resources | `scripts/check_api_docs.py --examples --mode runtime` | Distinguish execution from compilation, missing dependencies and cases not run |

## Host scenarios and baselines

Run from the product repository root. The report directory must not exist:

```bash
python3 scripts/run_user_acceptance.py \
  --compiler g++-13 --samples 7 --report-dir /path/to/new/host-acceptance
```

The runner builds ASC-STL and reference implementations with the same compiler,
`-O3`, and both C++17 and C++20. Sort and sequence references use the Host standard
library; the matrix reference uses direct row-major indexing. After one warmup,
seven samples provide medians and the ASC-STL/reference ratio. A ratio below one
means less elapsed time only for that measured workload. There is no arbitrary
performance pass threshold. Incorrect results, failed processes, missing samples
or source changes during execution fail acceptance.

Timings include allocation, initialization, operations and result checking for
the whole Host workload. They are not isolated API latency or Device kernel
timings. Reports retain samples, checksums, build commands, binary and source
hashes, commit and worktree status, and compiler and machine identities. A dirty
worktree identifies a development check; use a clean committed revision for
release evidence.

Stop other builds and heavy workloads before measuring, and keep scheduling and
the environment consistent. Temperature, frequency and background load affect
timings. Do not compare ratios across machines or toolchains directly, or infer
performance gains for other input sizes or device workloads.

## Device and Runtime scenarios

The supplemental `ci-release-check.sh` entry requires every selected stage to pass
and stops at the first non-`PASS` result. Exit 77 remains `NOT_APPLICABLE`, and an
environment failure retains `BLOCKED_ENVIRONMENT`; later stages become `NOT_RUN`.
The summary sets `passed=false` and the entry exits 1: selected release evidence is
incomplete, which does not necessarily mean a product defect. This differs from
CTest's optional-test skip policy. To check independent Host workloads, select
`--scope software --stage acceptance` with a new report directory. That result only
covers the selected stage. Hardware preflight must pass before Runtime execution.

Device compilation, cannsim and physical-device execution provide different
evidence. Hardware tasks need supported devices, CANN, drivers, healthy device
state, and bounded task and synchronization deadlines. Run the normal Quick Start
control first, then run parallel algorithms and Runtime examples serially. Stop
after an unexpected failure, preserve logs, and check device readiness again.
Process exit alone does not establish device recovery.

Execute Runtime documentation examples in the actual device environment:

```bash
python3 scripts/check_api_docs.py --examples --mode runtime --standard 17 \
  --compiler g++ --report /path/to/runtime17.json
python3 scripts/check_api_docs.py --examples --mode runtime --standard 20 \
  --compiler g++ --report /path/to/runtime20.json
```

Preserve the `run`, `compile_only`, `NOT_APPLICABLE` and `NOT_RUN` categories.
Compilation, missing dependencies and unexecuted cases are not hardware semantic
passes. Bind software gates, documentation examples, memory-safety checks and
user-scenario results to the same product revision. These scenarios supplement
the full Host, Device, cannsim and applicable hardware regression matrices.
