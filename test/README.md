# ASC-STL test gates

Tests are organized by stable product Header paths, never by implementation
wave, batch, delivery-unit, or progress identifiers. A target such as
`asc/std/source_location` maps directly to
`cases/asc/std/source_location/`; a target ending in `.h` drops only that
extension.

Each case may provide these metadata-controlled assets:

```text
host.pass.cpp
device.compile.asc
*.fail.cpp
*.fail.asc
runtime/cannsim/...
runtime/hardware/...
```

`metadata/headers.json` registers the product Header tree, direct product
dependencies, test applicability, and exceptional case-local assets. It must
not contain implementation scheduling or migration provenance. Generated
self-containment translation units, build products, CTest state, simulator
logs, and hardware reports belong only in out-of-source build directories.

The stable formal gate mirror entry points are:

```text
scripts/ci-quick-check.sh
scripts/ci-device-compile-check.sh
scripts/ci-cannsim-check.sh
```

`scripts/quick_check_code.sh` is the explicit local CodeCheck preflight, while
its pre-commit hooks also reject direct Python `print()` calls to mirror the
formal `G.LOG.02` logging rule. Style discovery is limited to ASC-STL-owned
source roots so unrelated infrastructure injected by formal CI is not audited.
`scripts/ci-hardware-check.sh` is the local Ascend950 enhancement. All product
and test compilation covers the mandatory C++17 baseline and supported C++20
mode.
