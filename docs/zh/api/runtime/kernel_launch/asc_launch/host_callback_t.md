# asc::host_callback_t

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

`asc::host_callback_t`是Host回调函数指针类型；回调接收调用方提供的`void*`用户数据且不返回值。

## 声明

```cpp
namespace asc {
using host_callback_t = void (*)(void*);
} // namespace asc
```

## 约束说明

- 仅可在Host调用。
- Kernel必须是编译期确定的目标，参数按值传递且可平凡复制。
- Stream、启动维度及参数生命周期必须有效。
- 成功仅表示任务已按Stream顺序提交。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/launch>

bool example()
{
    int result = 0;
    asc::host_callback_t callback = [](void* data) { *static_cast<int*>(data) = 7; };
    // 此处直接演示回调签名；异步提交参见host_callback。
    callback(&result);
    return result == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_launch.md)
