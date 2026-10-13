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

`asc::pipeline_ref::pipeline_ref`使用调用方提供的参数初始化`asc::pipeline_ref`对象。

## 函数原型

所属类型：[`asc::pipeline_ref`](pipeline_ref.md)。

### 原型1

```cpp
// asc::pipeline_ref 类内的声明节选；模板形参和其他成员由所属类提供。
pipeline_ref(asc::pipeline_event_id load_event0, asc::pipeline_event_id store_event0, asc::pipeline_event_id load_event1, asc::pipeline_event_id store_event1) noexcept;
```

### 原型2

```cpp
// asc::pipeline_ref 类内的声明节选；模板形参和其他成员由所属类提供。
pipeline_ref(const asc::pipeline_ref&) noexcept;
```

### 原型3

```cpp
// asc::pipeline_ref 类内的声明节选；模板形参和其他成员由所属类提供。
explicit pipeline_ref(asc::pipeline_event_id load_event, asc::pipeline_event_id store_event) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `load_event0` | 输入 | 两级流水线第0级的Load事件ID（pipeline_event_id）：MTE2 GM→UB搬入完成事件的编号；由调用方提供并在流水线有效期内独占。 |
| `store_event0` | 输入 | 两级流水线第0级的Store事件ID（pipeline_event_id）：MTE3 UB→GM搬出排空事件的编号；由调用方提供并在流水线有效期内独占。 |
| `load_event1` | 输入 | 两级流水线第1级的Load事件ID（pipeline_event_id）：MTE2 GM→UB搬入完成事件的编号；由调用方提供并在流水线有效期内独占。 |
| `store_event1` | 输入 | 两级流水线第1级的Store事件ID（pipeline_event_id）：MTE3 UB→GM搬出排空事件的编号；由调用方提供并在流水线有效期内独占。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `参数1` | 输入 | 待复制的另一`pipeline_ref`：复制构造复制其阶段与事件ID借用状态，两对象共享同一组事件。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `load_event` | 输入 | 单级流水线的Load事件ID（pipeline_event_id）：MTE2 GM→UB搬入完成事件的编号；由调用方提供并在流水线有效期内独占。 |
| `store_event` | 输入 | 单级流水线的Store事件ID（pipeline_event_id）：MTE3 UB→GM搬出排空事件的编号；由调用方提供并在流水线有效期内独占。 |

## 返回值说明

无返回值。

## 约束说明

- 仅可在AI Core SIMD编程中调用。
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明。

## 调用示例

以1个AI Core启动。input与output均为至少1024字节、32字节对齐的GM缓冲区；输入第i项为i时，完成后输出第i项应为i+1。

```cpp
#include <asc/pipeline>

__global__ __vector__ void example(__gm__ unsigned int* output, __gm__ const unsigned int* input)
{
    __ubuf__ unsigned int buffer[256];
    // 事件2和3由本核函数独占，不能同时交给其他TPipe或TQue。
    const asc::pipeline_event_id load_event = 2;
    const asc::pipeline_event_id store_event = 3;
    asc::pipeline_ref pipeline(load_event, store_event);
    pipeline.producer_acquire(0);
    asc::copy_async(pipeline, 0, asc::ub_span<unsigned int>(buffer, 256),
        asc::gm_span<const unsigned int>(input, 256));
    pipeline.producer_commit(0);
    pipeline.consumer_wait(0);
    for (unsigned int index = 0; index < 256; ++index) buffer[index] += pipeline.stages();
    pipeline.consumer_release(0);
    asc::copy_async(pipeline, 0, asc::gm_span<unsigned int>(output, 256),
        asc::ub_span<const unsigned int>(buffer, 256));
    pipeline.wait();
}
```

完整工程及运行步骤见[《pipeline_copy示例》](../../../../examples/pipeline_copy/README.md)。

## 关联API

- [`asc::pipeline_ref`](pipeline_ref.md)
- [本头文件的接口列表](asc_pipeline.md)
