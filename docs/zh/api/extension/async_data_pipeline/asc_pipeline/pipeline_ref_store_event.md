# asc::pipeline_ref::store_event

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

头文件路径为：`<asc/pipeline>`。

`asc::pipeline_ref::store_event` 返回指定流水级使用的 Store Event 编号。

## 函数原型

```cpp
asc::pipeline_event_id asc::pipeline_ref::store_event(unsigned int stage) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stage` | 输入 | 指定“查询指定流水级使用的 Store Event 编号”使用的标量值；取值须满足声明和约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::pipeline_event_id` | 返回指定流水级使用的 Store Event 编号。 |

## 约束说明

- 仅可在 AI Core SIMD 编程中调用
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明

## 调用示例

以下 AI Core SIMD 片段演示阶段操作；事件 ID 和调用顺序须满足本页约束。

```cpp
#include <asc/pipeline>

__aicore__ decltype(auto) example(const asc::pipeline_ref& pipeline, unsigned int stage)
{
    // stage 必须属于当前流水线，调用方负责完整的阶段配对协议。
    return pipeline.store_event(stage);
}
```
