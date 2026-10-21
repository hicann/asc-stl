# `asc::operator==`（函数）

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

头文件路径为：`<asc/devices>`、`<asc/stream>`。

`asc::operator==`比较两个Device引用的序号，或比较两个Stream/Event引用保存的原生句柄是否相同。

## 函数原型

### 原型1

```cpp
constexpr bool asc::operator==(asc::device_ref lhs, asc::device_ref rhs) noexcept;
```

此原型对应头文件：`<asc/devices>`。

### 原型2

```cpp
constexpr bool asc::operator==(asc::event_ref lhs, asc::event_ref rhs) noexcept;
```

此原型对应头文件：`<asc/stream>`。

### 原型3

```cpp
constexpr bool asc::operator==(asc::stream_ref lhs, asc::stream_ref rhs) noexcept;
```

此原型对应头文件：`<asc/stream>`。

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与比较的左侧Device引用：按两个引用的设备序号判定是否相等。 |
| `rhs` | 输入 | 参与比较的右侧Device引用：按两个引用的设备序号判定是否相等。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与比较的左侧Event引用：按各自保存的原生事件句柄判定是否相同。 |
| `rhs` | 输入 | 参与比较的右侧Event引用：按各自保存的原生事件句柄判定是否相同。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与比较的左侧Stream引用：按各自保存的原生流句柄判定是否相同。 |
| `rhs` | 输入 | 参与比较的右侧Stream引用：按各自保存的原生流句柄判定是否相同。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `bool` | 条件成立时返回`true`，否则返回`false`。 |
| 原型2 | `bool` | 条件成立时返回`true`，否则返回`false`。 |
| 原型3 | `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 本页描述已保存的设备属性值、架构枚举或ordinal比较；观察这些值不查询Runtime。
- 获取实际设备属性时的初始化和设备可用要求见`device_ref::properties`；比较ordinal不证明对应设备实际存在。

## 调用示例

以下Host示例按保存的ordinal比较引用；使用运算符语法使隐藏友元通过实参相关查找参与解析。

```cpp
#include <asc/devices>
bool example()
{
    asc::device_ref left(0);
    asc::device_ref same(0);
    asc::device_ref other(1);
    return left == same && left != other;
}
```

## 关联API

- [本头文件的接口列表](asc_devices.md)
