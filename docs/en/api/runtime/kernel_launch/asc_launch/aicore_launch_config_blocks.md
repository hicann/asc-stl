# asc::aicore_launch_config::blocks

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

`asc::aicore_launch_config::blocks` specifies the number of AICore blocks to launch; the value must be greater than zero.

## Declaration

Member of: [`asc::aicore_launch_config`](aicore_launch_config.md).

```cpp
// Excerpt of the declaration inside asc::aicore_launch_config; template parameters and other members are provided by the enclosing class.
asc::std::uint32_t blocks;
```

## Constraints

- This type or member only describes the Host-side launch configuration and does not submit a kernel function; see `launch` for the actual launch requirements.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/launch>

bool example()
{
    asc::aicore_launch_config config{2};
    return config.blocks == 2;
}
```

## Related APIs

- [`asc::aicore_launch_config`](aicore_launch_config.md)
- [API list for this header](asc_launch.md)
