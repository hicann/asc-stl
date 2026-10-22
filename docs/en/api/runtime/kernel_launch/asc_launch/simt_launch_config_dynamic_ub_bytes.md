# asc::simt_launch_config::dynamic_ub_bytes

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

`asc::simt_launch_config::dynamic_ub_bytes` specifies the size of the dynamic UB space requested for each SIMT block, in bytes.

## Declaration

Member of: [`asc::simt_launch_config`](simt_launch_config.md).

```cpp
// Excerpt of the declaration inside asc::simt_launch_config; template parameters and other members are provided by the enclosing class.
asc::std::size_t dynamic_ub_bytes;
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

- [`asc::simt_launch_config`](simt_launch_config.md)
- [API list for this header](asc_launch.md)
