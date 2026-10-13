# asc::block_dims（函数）

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

`asc::block_dims`创建Block层级的三维尺寸描述。

## 函数原型

```cpp
namespace asc {
constexpr asc::level_dimensions<asc::block_level> block_dims(asc::extent3d extents) noexcept;
} // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 各维的有效长度；维度数量和取值范围须满足本页约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::level_dimensions<asc::block_level>` | 返回由当前网格和线程块尺寸构成的执行层次或启动尺寸。 |

## 约束说明

- 提供C++17 constexpr Host/Device层次结构接口。
- 带extent的值要求每一维均非零。
- extent总数按无符号64位的x*y*z计算。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/hierarchy>

decltype(auto) example(asc::extent3d extents)
{
    return asc::block_dims(extents);
}
```

## 关联API

- [本头文件的接口列表](asc_hierarchy.md)
