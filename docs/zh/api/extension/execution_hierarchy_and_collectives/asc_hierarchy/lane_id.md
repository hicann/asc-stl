# asc::lane_id

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

头文件路径为：`<asc/hierarchy>`。

`asc::lane_id`返回当前线程在Warp内的Lane编号。

## 函数原型

```cpp
namespace asc {
unsigned int lane_id() noexcept;
} // namespace asc
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned int` | 返回当前执行单元在所属层级中的索引。 |

## 约束说明

- 仅可在AI Core SIMT编程中调用。
- 必须在正在执行的AI Core SIMT核函数内查询；结果取自当前启动配置，本函数不执行线程同步。

## 调用示例

以下SIMT核函数按Grid=(2,3,4)、Block=(8,4,2)启动时，将每个线程的查询结果写入独立位置。调用方须分配至少1536个unsigned long long的有效GM输出，并在核函数完成后回读。每个Block的64项中，Lane编号0至31重复两次。文档门禁验证真实SIMT编译，不代表NPU执行通过。

```cpp
#include <asc/hierarchy>

__global__ void example(unsigned long long* output)
{
    const unsigned long long local = threadIdx.x +
        static_cast<unsigned long long>(blockDim.x) * (threadIdx.y + blockDim.y * threadIdx.z);
    const unsigned long long block = blockIdx.x +
        static_cast<unsigned long long>(gridDim.x) * (blockIdx.y + gridDim.y * blockIdx.z);
    const unsigned long long threads = static_cast<unsigned long long>(blockDim.x) * blockDim.y * blockDim.z;
    const unsigned long long offset = block * threads + local;
    output[offset] = asc::lane_id();
}
```

## 关联API

- [本头文件的接口列表](asc_hierarchy.md)
