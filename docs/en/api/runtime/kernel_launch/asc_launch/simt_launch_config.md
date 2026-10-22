# asc::simt_launch_config

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Header: `<asc/launch>`.

`asc::simt_launch_config` describes the three-dimensional grid, three-dimensional block, and dynamic UB byte count of a SIMT kernel.

## Declaration

```cpp
namespace asc {
struct simt_launch_config;
}  // namespace asc
```

## Constraints

- This type or member only describes the Host-side launch configuration and does not submit a kernel function; see `launch` for the actual launch requirements.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/launch>

bool example()
{
    asc::simt_launch_config config{asc::extent3d{2, 1, 1}, asc::extent3d{32, 1, 1}, 0};
    return config.grid.count() == 2 && config.block.count() == 32 && config.dynamic_ub_bytes == 0;
}
```

## Related APIs

- [API list for this header](asc_launch.md)
