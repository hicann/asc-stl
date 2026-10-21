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

`asc::launch`在指定Stream上异步启动编译期确定的SIMT或AICore Kernel。成功状态表示启动已提交；所有按值传递的Kernel参数必须可平凡复制。

## 函数原型

### 原型1

```cpp
namespace asc {
template <auto Kernel, class... Args>
asc::execution_status launch(asc::stream_ref stream, asc::aicore_launch_config config, Args... args) noexcept;
}  // namespace asc
```

### 原型2

```cpp
namespace asc {
template <auto Kernel, class... Args>
asc::execution_status launch(asc::stream_ref stream, asc::simt_launch_config config, Args... args) noexcept;
}  // namespace asc
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Kernel` | 编译期确定的设备核函数入口。 |
| `Args` | 按值传递给核函数的实参类型列表；每个类型必须可平凡复制。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stream` | 输入 | 接收本次启动任务的Stream；提交后任务按该Stream的顺序执行，完成前Stream必须有效。 |
| `config` | 输入 | AI Core SIMD编程核函数的启动配置，指定所需的执行块。 |
| `args` | 输入 | 传递给核函数的按值实参；提交后执行期间不得引用已失效的外部资源。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Kernel` | 编译期确定的设备核函数入口。 |
| `Args` | 按值传递给核函数的实参类型列表；每个类型必须可平凡复制。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stream` | 输入 | 接收本次启动任务的Stream；提交后任务按该Stream的顺序执行，完成前Stream必须有效。 |
| `config` | 输入 | AI Core SIMT编程核函数的启动配置，指定网格、线程块和动态共享内存。 |
| `args` | 输入 | 传递给核函数的按值实参；提交后执行期间不得引用已失效的外部资源。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |
| 原型2 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- 这些核函数提交重载要求Clang兼容的毕昇ASC翻译单元，并显式定义`CANN_ASC_STL_USE_SIMT_LAUNCH`。
- 宏值为非零时只提供`simt_launch_config`重载；为零时只提供`aicore_launch_config`重载；未定义时两者均不提供。按实际编译模式选择对应配置。

- 仅可在毕昇ASC翻译单元的Host提交阶段调用。
- 调用时必须显式指定编译期Kernel模板实参，Stream和启动维度必须有效，按值传递的参数必须可平凡复制。
- 成功仅表示任务已经提交。
- 仅可在Host调用。
- Kernel必须是编译期确定的目标，参数按值传递且可平凡复制。
- Stream、启动维度及参数生命周期必须有效。
- 成功仅表示任务已按Stream顺序提交。

## 调用示例

以下片段用于毕昇ASC翻译单元：Host使用有效Stream提交普通AI Core Kernel，output指向有效全局内存。

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

## 关联API

- [asc::stream_ref](../../devices_streams_events/asc_stream/stream_ref.md)
- [asc::aicore_launch_config](aicore_launch_config.md)
- [asc::simt_launch_config](simt_launch_config.md)
- [asc::execution_status](../../execution_policies_and_status/asc_execution/execution_status.md)
