# asc::host_callback

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

头文件路径为：`<asc/launch>`。

`asc::host_callback` 按指定 Stream 的任务顺序提交 Host 回调。Stream 或回调函数为空时返回参数无效，底层 Runtime 失败时保留原生状态码。

## 函数原型

```cpp
asc::execution_status asc::host_callback(asc::stream_ref stream, asc::host_callback_t callback, void* data) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stream` | 输入 | 用于按序提交异步工作的 Stream。相关资源须保持有效，直至工作完成。 |
| `callback` | 输入 | 提供“按指定 Stream 的任务顺序提交 Host 回调”所需的输入对象；类型须满足所选原型约束。 |
| `data` | 输入 | 提供“按指定 Stream 的任务顺序提交 Host 回调”所需的数据地址；可访问范围和生命周期须满足约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- 仅可在 Host 调用
- Stream 和回调函数必须有效
- 回调及用户数据须保持有效直至执行，回调不得跨越 C 接口边界抛出异常

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/launch>

decltype(auto) example(asc::stream_ref stream, asc::host_callback_t callback, void* data)
{
    return asc::host_callback(stream, callback, data);
}
```
