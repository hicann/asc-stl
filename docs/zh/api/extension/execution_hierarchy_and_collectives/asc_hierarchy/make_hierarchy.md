# asc::make_hierarchy

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

`asc::make_hierarchy` 由 Grid 和 Block 尺寸构造 SIMT 层级描述。

## 函数原型

```cpp
constexpr asc::simt_hierarchy asc::make_hierarchy(asc::level_dimensions<asc::grid_level> grid, asc::level_dimensions<asc::block_level> block) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `grid` | 输入 | 提供“由 Grid 和 Block 尺寸构造 SIMT 层级描述”所需的输入对象；类型须满足所选原型约束。 |
| `block` | 输入 | 提供“由 Grid 和 Block 尺寸构造 SIMT 层级描述”所需的输入对象；类型须满足所选原型约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::simt_hierarchy` | 返回由当前网格和线程块尺寸构成的执行层次或启动尺寸。 |

## 约束说明

- 提供 C++17 constexpr Host/Device 层次结构接口
- 带 extent 的值要求每一维均非零
- extent 总数按无符号 64 位的 x*y*z 计算

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/hierarchy>

decltype(auto) example(asc::level_dimensions<asc::grid_level> grid, asc::level_dimensions<asc::block_level> block)
{
    return asc::make_hierarchy(grid, block);
}
```
