# asc::args::immediate::immediate

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

头文件路径为：`<asc/argument>`。

`asc::args::immediate::immediate`使用调用方提供的参数初始化`asc::args::immediate`对象。

## 函数原型

所属类型：[`asc::args::immediate`](args_immediate.md)。

### 原型1

```cpp
// asc::args::immediate 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr immediate(T value, Bounds bounds) noexcept;
```

### 原型2

```cpp
// asc::args::immediate 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr explicit immediate(T value) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 提交时对Host可用的立即参数值：保存于包装对象并经value()读取。 |
| `bounds` | 输入 | 该立即参数取值的边界对象（no_bounds/static_bounds/runtime_bounds）。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 提交时对Host可用的立即参数值：保存于包装对象并经value()读取。 |

## 返回值说明

无返回值。

## 约束说明

- 使用C++17，可在Host、AI Core SIMD编程 和AI Core SIMT编程中使用。
- Bounds必须为asc::args::no_bounds或asc::args::static_bounds。
- 延迟指针在使用时不得为空，调用方存储必须覆盖整个使用周期。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/argument>

bool example()
{
    asc::args::immediate<int> argument(7, asc::args::no_bounds{});
    return argument.value() == 7;
}
```

## 关联API

- [`asc::args::immediate`](args_immediate.md)
- [本头文件的接口列表](asc_argument.md)
