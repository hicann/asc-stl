# asc::make_stream

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

`asc::make_stream` 按指定优先级创建 Runtime Stream，并把所有权写入空的 `stream` 对象；输出对象已持有句柄或创建失败时返回 false。

该接口的可用位置为 Host。

## 函数原型

```cpp
bool asc::make_stream(asc::stream& output, asc::std::uint32_t priority = 0) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 待接收新建 Stream 的空 stream 对象引用：须尚未持有句柄，成功后获得新 Runtime Stream 的所有权；已持有句柄时直接返回失败。 |
| `priority` | 输入 | 新建 Stream 的优先级（uint32_t，传给底层 Runtime；0 为常规优先级）。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- `output` 非空（已持有句柄）时本接口拒绝执行，直接返回 `false`，不创建新的 Runtime Stream，也不修改 `output`
- output 失败时保持不变

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/stream>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

decltype(auto) example(asc::stream& output, asc::std::uint32_t priority = 0)
{
    return asc::make_stream(output, priority);
}
```

对应完整工程使用 `C++17`，并通过Ascend 950 真机编译与运行验证。

完整示例源码：[stream_event.cpp](../../../../examples/stream_event.cpp)。
