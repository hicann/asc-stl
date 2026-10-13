# asc::operator!=（函数）

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

`asc::operator!=` 判断两个 Device 引用的序号，或两个 Stream/Event 引用保存的原生句柄是否不同。

## 函数原型

### 原型 1

```cpp
constexpr bool asc::operator!=(asc::device_ref lhs, asc::device_ref rhs) noexcept;
```

此原型对应头文件：`<asc/devices>`。

### 原型 2

```cpp
constexpr bool asc::operator!=(asc::event_ref lhs, asc::event_ref rhs) noexcept;
```

此原型对应头文件：`<asc/stream>`。

### 原型 3

```cpp
constexpr bool asc::operator!=(asc::stream_ref lhs, asc::stream_ref rhs) noexcept;
```

此原型对应头文件：`<asc/stream>`。

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与比较的左侧 Device 引用：按两个引用的设备序号判定是否不同。 |
| `rhs` | 输入 | 参与比较的右侧 Device 引用：按两个引用的设备序号判定是否不同。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与比较的左侧 Event 引用：按各自保存的原生事件句柄判定是否不同。 |
| `rhs` | 输入 | 参与比较的右侧 Event 引用：按各自保存的原生事件句柄判定是否不同。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与比较的左侧 Stream 引用：按各自保存的原生流句柄判定是否不同。 |
| `rhs` | 输入 | 参与比较的右侧 Stream 引用：按各自保存的原生流句柄判定是否不同。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 2 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 3 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- 仅可在 Host 查询或选择 Device
- 引用只保存设备序号且不拥有 Runtime 状态
- 查询失败时输出参数保持原值，属性仅限当前接口列出的 AI Core、Vector Core、Warp、UB、GM、L2 与架构字段
- 提供可为空的非拥有 Host 引用
- 原生句柄为不透明 void 指针
- 仅当 CANN Runtime 调用成功时才更新查询结果和输出参数

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/devices>

decltype(auto) example(asc::device_ref lhs, asc::device_ref rhs)
{
    return asc::operator!=(lhs, rhs);
}
```

对应完整工程使用 `C++17`，并通过Ascend 950 真机编译与运行验证。

完整示例源码：[stream_event.cpp](../../../../examples/stream_event.cpp)。
