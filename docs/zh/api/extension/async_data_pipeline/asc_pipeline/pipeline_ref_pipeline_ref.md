# asc::pipeline_ref::pipeline_ref

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

`asc::pipeline_ref::pipeline_ref` 使用调用方提供的参数初始化 `asc::pipeline_ref` 对象。

## 函数原型

### 原型 1

```cpp
asc::pipeline_ref::pipeline_ref(asc::pipeline_event_id load_event0, asc::pipeline_event_id store_event0, asc::pipeline_event_id load_event1, asc::pipeline_event_id store_event1) noexcept;
```

### 原型 2

```cpp
asc::pipeline_ref::pipeline_ref(const asc::pipeline_ref&) noexcept;
```

### 原型 3

```cpp
explicit asc::pipeline_ref::pipeline_ref(asc::pipeline_event_id load_event, asc::pipeline_event_id store_event) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `load_event0` | 输入 | 两级流水线第 0 级的 Load 事件 ID（pipeline_event_id）：MTE2 GM→UB 搬入完成事件的编号；由调用方提供并在流水线有效期内独占。 |
| `store_event0` | 输入 | 两级流水线第 0 级的 Store 事件 ID（pipeline_event_id）：MTE3 UB→GM 搬出排空事件的编号；由调用方提供并在流水线有效期内独占。 |
| `load_event1` | 输入 | 两级流水线第 1 级的 Load 事件 ID（pipeline_event_id）：MTE2 GM→UB 搬入完成事件的编号；由调用方提供并在流水线有效期内独占。 |
| `store_event1` | 输入 | 两级流水线第 1 级的 Store 事件 ID（pipeline_event_id）：MTE3 UB→GM 搬出排空事件的编号；由调用方提供并在流水线有效期内独占。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `参数1` | 输入 | 待复制的另一 `pipeline_ref`：复制构造复制其阶段与事件 ID 借用状态，两对象共享同一组事件。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `load_event` | 输入 | 单级流水线的 Load 事件 ID（pipeline_event_id）：MTE2 GM→UB 搬入完成事件的编号；由调用方提供并在流水线有效期内独占。 |
| `store_event` | 输入 | 单级流水线的 Store 事件 ID（pipeline_event_id）：MTE3 UB→GM 搬出排空事件的编号；由调用方提供并在流水线有效期内独占。 |

## 约束说明

- 仅可在 AI Core SIMD 编程中调用
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明

## 调用示例

以下 AI Core SIMD 片段演示阶段操作；事件 ID 和调用顺序须满足本页约束。

```cpp
#include <asc/pipeline>

__aicore__ void example(asc::pipeline_event_id load_event, asc::pipeline_event_id store_event)
{
    // 两个事件 ID 在流水线有效期内须由调用方独占。
    asc::pipeline_ref pipeline(load_event, store_event);
    (void)pipeline.stages();
}
```
