# asc::elapsed_time

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

头文件路径为：`<asc/stream>`。

`asc::elapsed_time`查询两个已记录Event之间的Runtime时间间隔，并在成功时以毫秒为单位写入输出参数。

该接口的可用位置为Host。

## 函数原型

```cpp
namespace asc {
bool elapsed_time(asc::event_ref start, asc::event_ref end, float& milliseconds) noexcept;
}  // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 用于记录或等待执行进度的Event引用。 |
| `end` | 输入 | 用于记录或等待执行进度的Event引用。 |
| `milliseconds` | 输出 | 接收两个Event之间的运行时间，单位为毫秒。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- `start`或`end`为空（未持有句柄的Event引用）时本接口拒绝执行，直接返回`false`，且不修改`milliseconds`。
- milliseconds失败时保持不变。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/stream>

decltype(auto) example(asc::event_ref start, asc::event_ref end, float& milliseconds)
{
    return asc::elapsed_time(start, end, milliseconds);
}
```

对应完整工程使用`C++17`；请在目标工具链及设备上编译和运行。

完整示例源码：[stream_event.cpp](../../../../examples/stream_event.cpp)。

## 关联API

- [本头文件的接口列表](asc_stream.md)
