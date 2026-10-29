# asc::simt_hierarchy::count

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

`asc::simt_hierarchy::count`返回指定SIMT层级包含的线性元素数量。

## 函数原型

所属类型：[`asc::simt_hierarchy`](simt_hierarchy.md)。

### 原型1

```cpp
// asc::simt_hierarchy 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr unsigned long long count(asc::block_level) const noexcept;
```

### 原型2

```cpp
// asc::simt_hierarchy 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr unsigned long long count(asc::grid_level) const noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| 级别标签（未命名参数） | 输入 | 级别标签：传入asc::block（block_level值）选择Block级，返回该级三维尺寸的元素总数x*y*z。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| 级别标签（未命名参数） | 输入 | 级别标签：传入asc::grid（grid_level值）选择Grid级，返回该级三维尺寸的元素总数x*y*z。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `unsigned long long` | 返回所选三维范围x*y*z的无符号64位数量，不返回尺寸对象。 |
| 原型2 | `unsigned long long` | 返回所选三维范围x*y*z的无符号64位数量，不返回尺寸对象。 |

## 约束说明

- 逐轴尺寸须满足当前设备的合法启动上限，x*y*z必须在unsigned long long中可表示；仅非零不足以保证这一条件。这里的值操作不校验实际硬件限制。

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
    return hierarchy.count(asc::grid) == 24 && hierarchy.count(asc::block) == 64;
}
```

## 关联API

- [`asc::simt_hierarchy`](simt_hierarchy.md)
- [本头文件的接口列表](asc_hierarchy.md)
