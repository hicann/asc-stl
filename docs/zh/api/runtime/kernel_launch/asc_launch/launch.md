# asc::launch

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

`asc::launch` 在指定 Stream 上异步启动编译期确定的 SIMT 或 AICore Kernel。成功状态表示启动已提交；所有按值传递的 Kernel 参数必须可平凡复制。

## 函数原型

### 原型 1

```cpp
template<auto Kernel, class... Args> asc::execution_status asc::launch(asc::stream_ref stream, asc::aicore_launch_config config, Args... args) noexcept;
```

### 原型 2

```cpp
template<auto Kernel, class... Args> asc::execution_status asc::launch(asc::stream_ref stream, asc::simt_launch_config config, Args... args) noexcept;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Kernel` | 编译期确定的设备核函数入口。 |
| `Args` | 按值传递给核函数的实参类型列表；每个类型必须可平凡复制。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stream` | 输入 | 接收本次启动任务的 Stream；提交后任务按该 Stream 的顺序执行，完成前 Stream 必须有效。 |
| `config` | 输入 | AI Core SIMD 编程核函数的启动配置，指定所需的执行块。 |
| `args` | 输入 | 传递给核函数的按值实参；提交后执行期间不得引用已失效的外部资源。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Kernel` | 编译期确定的设备核函数入口。 |
| `Args` | 按值传递给核函数的实参类型列表；每个类型必须可平凡复制。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stream` | 输入 | 接收本次启动任务的 Stream；提交后任务按该 Stream 的顺序执行，完成前 Stream 必须有效。 |
| `config` | 输入 | AI Core SIMT 编程核函数的启动配置，指定网格、线程块和动态共享内存。 |
| `args` | 输入 | 传递给核函数的按值实参；提交后执行期间不得引用已失效的外部资源。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |
| 原型 2 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- 仅可在毕昇 ASC 翻译单元的 Host 提交阶段调用
- 调用时必须显式指定编译期 Kernel 模板实参，Stream 和启动维度必须有效，按值传递的参数必须可平凡复制
- 成功仅表示任务已经提交。
- 仅可在 Host 调用
- Kernel 必须是编译期确定的目标，参数按值传递且可平凡复制
- Stream、启动维度及参数生命周期必须有效
- 成功仅表示任务已按 Stream 顺序提交

## 调用示例

以下片段用于毕昇 ASC 翻译单元：Host 使用有效 Stream 提交普通 AI Core Kernel，output 指向有效全局内存。

```cpp
#include <asc/launch>

extern "C" __global__ __vector__ void example_kernel(__gm__ int* output)
{
    output[0] = 7;
}
decltype(auto) example(asc::stream_ref stream, int* output)
{
    return asc::launch<example_kernel>(stream, asc::aicore_launch_config{1}, output);
}
```

## 关联 API

- [asc::stream_ref](../../devices_streams_events/asc_stream/stream_ref.md)
- [asc::aicore_launch_config](aicore_launch_config.md)
- [asc::simt_launch_config](simt_launch_config.md)
- [asc::execution_status](../../execution_policies_and_status/asc_execution/execution_status.md)
