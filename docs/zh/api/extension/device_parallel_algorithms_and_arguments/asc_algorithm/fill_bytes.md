# asc::fill_bytes

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

头文件路径为：`<asc/algorithm>`。

`asc::fill_bytes`使用给定的单字节值填充一段Device可访问内存。

## 函数原型

```cpp
namespace asc {
asc::execution_status fill_bytes(asc::stream_ref stream, void* destination, unsigned char value, asc::std::size_t bytes) noexcept;
} // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stream` | 输入 | 用于按序提交异步工作的Stream。相关资源须保持有效，直至工作完成。 |
| `destination` | 输出 | 待填充的目标内存起始地址：须可写且覆盖bytes字节，异步完成前保持有效。 |
| `value` | 输入 | 填充值（unsigned char，0~255）：以该字节逐字节重复写入目标区域。 |
| `bytes` | 输入 | 填充的字节数，单位为字节；为0时不提交任务并直接返回成功。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- 仅可在Host调用。
- Stream必须有效。
- 目标地址须可由Device访问，并在异步填充完成前保持有效。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/algorithm>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

decltype(auto) example(asc::stream_ref stream, void* destination, unsigned char value, asc::std::size_t bytes)
{
    return asc::fill_bytes(stream, destination, value, bytes);
}
```

## 关联API

- [`asc::execution_status`](../../../runtime/execution_policies_and_status/asc_execution/execution_status.md)：参数校验和任务提交状态；提交成功不表示异步工作已经完成。
