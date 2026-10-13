# asc::adopt_stream

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

`asc::adopt_stream`把非空的Runtime Stream原生句柄所有权交给空的`stream`对象，不创建新的Runtime资源。

该接口的可用位置为Host。

## 函数原型

```cpp
namespace asc {
bool adopt_stream(asc::stream_ref::native_handle_type handle, asc::stream& output) noexcept;
} // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `handle` | 输入 | 提交或等待异步任务的Stream引用；任务完成前须保持有效。 |
| `output` | 输出 | 提供“把非空的Runtime Stream原生句柄所有权交给空的`stream`对象，不创建新的Runtime资源”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 句柄不得为空，输出对象在调用前必须为空。
- 失败时输出保持不变，成功时转移资源所有权。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/stream>

decltype(auto) example(asc::stream_ref::native_handle_type handle, asc::stream& output)
{
    return asc::adopt_stream(handle, output);
}
```

对应完整工程使用`C++17`；请在目标工具链及设备上编译和运行。

完整示例源码：[stream_event.cpp](../../../../examples/stream_event.cpp)。

## 关联API

- [本头文件的接口列表](asc_stream.md)
