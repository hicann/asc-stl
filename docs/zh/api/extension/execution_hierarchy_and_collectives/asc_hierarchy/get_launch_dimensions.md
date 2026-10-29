# asc::get_launch_dimensions

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：支持
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3系列产品：不支持
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2系列产品：不支持
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2推理产品：不支持
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas推理系列产品AI Core：不支持
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas推理系列产品Vector Core：不支持
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas训练系列产品：不支持
<!-- end id7 -->

## 功能说明

头文件路径为：`<asc/hierarchy>`。

`asc::get_launch_dimensions`从simt_hierarchy提取Grid和Block启动尺寸。

## 函数原型

```cpp
namespace asc {
constexpr asc::launch_dimensions get_launch_dimensions(asc::simt_hierarchy hierarchy) noexcept;
} // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `hierarchy` | 输入 | 待提取启动尺寸的simt_hierarchy对象：其Grid与Block三维尺寸被复制进返回的launch_dimensions。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::launch_dimensions` | 返回由当前网格和线程块尺寸构成的执行层次或启动尺寸。 |

## 约束说明

- 提供C++17 constexpr Host/Device层次结构接口。
- 带extent的值要求每一维均非零。
- extent总数按无符号64位的x*y*z计算。

## 调用示例

以下Host示例使用具体类型或维度，检查独立的预期值；不查询正在运行的Device执行上下文。

```cpp
#include <asc/hierarchy>

bool example()
{
    const auto hierarchy = asc::make_hierarchy(asc::grid_dims<2, 3, 4>(), asc::block_dims<8, 4, 2>());
    const auto dimensions = asc::get_launch_dimensions(hierarchy);
    return dimensions.grid.x == 2 && dimensions.grid.y == 3 && dimensions.grid.z == 4 &&
        dimensions.block.x == 8 && dimensions.block.y == 4 && dimensions.block.z == 2 &&
        dimensions.grid.count() == 24 && dimensions.block.count() == 64;
}
```

## 关联API

- [本头文件的接口列表](asc_hierarchy.md)
