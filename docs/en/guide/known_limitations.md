# Known compatibility and execution limits

ASC-STL provides the interfaces documented in the [API reference](../api/README.md),
with per-interface language, execution-location, type and allocation constraints.
It is not a complete drop-in replacement for the Host standard library. For
example, `vector` requires an explicit allocator and excludes copy operations;
other containers have their own documented subset.

## CANN package identity

The currently exercised device configuration is CANN 9.2.0-beta.2 with BiSheng/CCE
15.0.5. Packages carrying the same version label can have different SDK layouts
and component builds. Match the package build and compiler identity to validation
results; a version number alone does not establish compatibility with all later
packages. SDK selection must preserve the required driver and supported 950 SoC.

Layer queries accept `c_api/utils/sys_var.h` or the older
`c_api/sys_var/sys_var.h`; compilation fails if neither exists. Tensor descriptor
64-bit multiply-overflow checks use segmented 32-bit arithmetic to avoid an
unavailable device `__multi3` symbol in affected older BiSheng builds.

## Pure-SIMT code-shape limits

The [detailed regression record](../../../test/support/README.md) retains original
observations and their identities. Three separate boundaries remain:

- **Confirmed compiler miscompile:** with BiSheng/CCE 15 fingerprint
  `c4866a4d…f84c6a`, constant-initialized local arrays followed by continuing reverse
  pointer traversals under `--enable-simt` can return incorrect values or cause
  an out-of-bounds device fault. Matching device binaries reproduced the failure
  in simulation and on Ascend 950. This also occurs without ASC-STL. The affected
  test constructs the same values at runtime while retaining the operation and
  expected results. That adaptation does not prove the compiler is fixed.
- **Combined constant-array algorithm regression (B022):** its original complete
  code shape remains unresolved. The SIMT test loads the same values from Host
  input in GM, while Host/SIMD retain the constant-input path. This is a separate
  observation, not proof that every constant local array is affected.
- **Long-string/local-arena combined regression (B027):** the original single
  kernel with a long local arena has not been shown to recover. The current SIMT
  test uses staged kernels with long-string objects and their arena in GM; local
  short-string checks are retained. Host/SIMD retain the complete original path.
  Passing the staged test does not establish the original shape or SDK is fixed.

Use the documented supported domains. Do not generalize these observations into
all arrays or strings being unavailable, or treat an adapted fixture's success as
evidence for an untested code shape. Revalidate applicable C++17/C++20 compilation,
simulation and hardware paths after toolchain changes.

## Hardware execution

Compilation and simulation do not establish physical-device correctness. Hardware
tests require a healthy supported device and bounded execution. The repository's
hardware gate currently expects exactly one readable/writable compute node; its
physical `/dev/davinciN` suffix is not the ACL logical device ID. The introductory
example uses logical device 0 and checks every Runtime return code and cleanup.
After a device error or timeout, inspect the environment before more submissions.
