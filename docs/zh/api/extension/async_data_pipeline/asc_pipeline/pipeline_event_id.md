# asc::pipeline_event_id

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

`asc::pipeline_event_id`表示Pipeline Load/Store Event编号的无符号整数类型。

## 声明

```cpp
namespace asc {
using pipeline_event_id = unsigned int;
} // namespace asc
```

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

- [本头文件的接口列表](asc_pipeline.md)
