# asc::copy_async

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

`asc::copy_async`在指定流水级提交全局内存（GM）与片上缓冲区（UB）之间的连续数据搬运。提交后须按流水线同步规则等待完成，再读取目标视图或复用源存储。

## 函数原型

### 原型1

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int16_t> destination,
    asc::ub_span<const asc::std::int16_t> source) noexcept;
}  // namespace asc
```

### 原型2

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int32_t> destination,
    asc::ub_span<const asc::std::int32_t> source) noexcept;
}  // namespace asc
```

### 原型3

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::int8_t> destination,
    asc::ub_span<const asc::std::int8_t> source) noexcept;
}  // namespace asc
```

### 原型4

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::uint16_t> destination,
    asc::ub_span<const asc::std::uint16_t> source) noexcept;
}  // namespace asc
```

### 原型5

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::uint32_t> destination,
    asc::ub_span<const asc::std::uint32_t> source) noexcept;
}  // namespace asc
```

### 原型6

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<asc::std::uint8_t> destination,
    asc::ub_span<const asc::std::uint8_t> source) noexcept;
}  // namespace asc
```

### 原型7

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<float> destination,
    asc::ub_span<const float> source) noexcept;
}  // namespace asc
```

### 原型8

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::int16_t> destination,
    asc::gm_span<const asc::std::int16_t> source) noexcept;
}  // namespace asc
```

### 原型9

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::int32_t> destination,
    asc::gm_span<const asc::std::int32_t> source) noexcept;
}  // namespace asc
```

### 原型10

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::int8_t> destination,
    asc::gm_span<const asc::std::int8_t> source) noexcept;
}  // namespace asc
```

### 原型11

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::uint16_t> destination,
    asc::gm_span<const asc::std::uint16_t> source) noexcept;
}  // namespace asc
```

### 原型12

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::uint32_t> destination,
    asc::gm_span<const asc::std::uint32_t> source) noexcept;
}  // namespace asc
```

### 原型13

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<asc::std::uint8_t> destination,
    asc::gm_span<const asc::std::uint8_t> source) noexcept;
}  // namespace asc
```

### 原型14

```cpp
namespace asc {
void copy_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<float> destination,
    asc::gm_span<const float> source) noexcept;
}  // namespace asc
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pipeline` | 输入 | 管理本次异步搬运的流水线引用；流水线须在搬运完成前有效。 |
| `stage` | 输入 | 流水级索引，须小于该流水线的级数。 |
| `destination` | 输出 | 接收搬运结果的非拥有视图；由所选原型决定其存储位于GM或UB，长度须足以容纳源数据。 |
| `source` | 输入 | 提供待搬运数据的非拥有视图；由所选原型决定其存储位于UB或GM，完成前底层存储须有效。 |

## 数据类型

支持两个方向：GM → UB、UB → GM。两个视图的元素类型必须相同，可选`int8_t`、`uint8_t`、`int16_t`、`uint16_t`、`int32_t`、`uint32_t`或`float`；每种类型和方向各有独立原型。

## 返回值说明

无返回值。

## 约束说明

- 两端存储须32字节对齐，目标容量至少等于源容量，源字节数须能由unsigned int表示；本接口不负责分配或容量校验。
- 每轮按producer_acquire、GM→UB copy、producer_commit、consumer_wait、计算、consumer_release、UB→GM copy排序，末轮调用wait。返回不表示数据完成；在相应等待前不得读目标或复用源。

- 仅可在AI Core SIMD编程中调用。
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明。

## 调用示例

以1个AI Core启动。input和output各含至少8个unsigned int，GM起始地址32字节对齐；Host同步后output[i]应等于input[i]+1。完整的阶段配对如下，UB→GM必须先consumer_release再copy_async。

完整工程见[流水线搬运示例](../../../../examples/pipeline_copy/README.md)。

```cpp
#include <asc/pipeline>
__global__ __vector__ void example(__gm__ unsigned int* output, __gm__ const unsigned int* input)
{
    alignas(32) __ubuf__ unsigned int buffer[8];
    const auto pipeline = asc::make_pipeline(0, 1);
    pipeline.producer_acquire(0);
    asc::copy_async(pipeline, 0, asc::ub_span<unsigned int>(buffer, 8), asc::gm_span<const unsigned int>(input, 8));
    pipeline.producer_commit(0);
    pipeline.consumer_wait(0);
    for (unsigned index = 0; index < 8; ++index)
        buffer[index] += 1;
    pipeline.consumer_release(0);
    asc::copy_async(pipeline, 0, asc::gm_span<unsigned int>(output, 8), asc::ub_span<const unsigned int>(buffer, 8));
    pipeline.wait();
}
```

## 关联API

- [asc::make_pipeline](make_pipeline.md)
- [asc::pipeline_ref::producer_commit](pipeline_ref_producer_commit.md)
- [asc::pipeline_ref::consumer_wait](pipeline_ref_consumer_wait.md)
