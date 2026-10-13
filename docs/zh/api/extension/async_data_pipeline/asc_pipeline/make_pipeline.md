# asc::make_pipeline

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

`asc::make_pipeline`用一组或两组Load/Store Event创建pipeline_ref。

## 函数原型

### 原型1

```cpp
namespace asc {
asc::pipeline_ref make_pipeline(asc::pipeline_event_id load_event, asc::pipeline_event_id store_event) noexcept;
} // namespace asc
```

### 原型2

```cpp
namespace asc {
asc::pipeline_ref make_pipeline(asc::pipeline_event_id load_event0, asc::pipeline_event_id store_event0, asc::pipeline_event_id load_event1, asc::pipeline_event_id store_event1) noexcept;
} // namespace asc
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `load_event` | 输入 | 单级流水线的Load事件ID（pipeline_event_id）：MTE2 GM→UB搬入完成事件的编号；由调用方提供并在流水线有效期内独占。 |
| `store_event` | 输入 | 单级流水线的Store事件ID（pipeline_event_id）：MTE3 UB→GM搬出排空事件的编号；由调用方提供并在流水线有效期内独占。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `load_event0` | 输入 | 两级流水线第0级的Load事件ID（pipeline_event_id）：MTE2 GM→UB搬入完成事件的编号；与另一级不同且在流水线有效期内独占。 |
| `store_event0` | 输入 | 两级流水线第0级的Store事件ID（pipeline_event_id）：MTE3 UB→GM搬出排空事件的编号；与另一级不同且在流水线有效期内独占。 |
| `load_event1` | 输入 | 两级流水线第1级的Load事件ID（pipeline_event_id）：MTE2 GM→UB搬入完成事件的编号；与另一级不同且在流水线有效期内独占。 |
| `store_event1` | 输入 | 两级流水线第1级的Store事件ID（pipeline_event_id）：MTE3 UB→GM搬出排空事件的编号；与另一级不同且在流水线有效期内独占。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::pipeline_ref` | 返回绑定调用方提供事件的非拥有流水线引用。 |
| 原型2 | `asc::pipeline_ref` | 返回绑定调用方提供事件的非拥有流水线引用。 |

## 约束说明

- 仅可在AI Core SIMD编程中调用。
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/pipeline>

__aicore__ decltype(auto) example(asc::pipeline_event_id load_event, asc::pipeline_event_id store_event)
{
    return asc::make_pipeline(load_event, store_event);
}
```

## 关联API

- [本头文件的接口列表](asc_pipeline.md)
