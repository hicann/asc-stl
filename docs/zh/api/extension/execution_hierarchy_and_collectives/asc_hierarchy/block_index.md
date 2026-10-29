# asc::block_index

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

`asc::block_index`在SIMT返回blockIdx.x，在SIMD返回block_idx；SIMT三维Grid中不是完整展平索引。

## 函数原型

```cpp
namespace asc {
unsigned long long block_index() noexcept;
}  // namespace asc
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned long long` | 返回当前执行单元在所属层级中的索引。 |

## 约束说明

- 可在AI Core SIMD编程、AI Core SIMT编程中使用。
- 所选重载的类型、地址空间、取值范围和对象生命周期必须满足其公开声明。

## 调用示例

以下SIMT核函数按Grid=(2,3,4)、Block=(8,4,2)启动时，将每个线程的查询结果写入独立位置。调用方须分配至少1536个unsigned long long的有效GM输出，并在核函数完成后回读。每项为对应blockIdx.x，取值0或1；本接口不是三维Block的展平索引。文档门禁验证真实SIMT编译，不代表NPU执行通过。

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
    output[offset] = asc::block_index();
}
```

## 关联API

- [本头文件的接口列表](asc_hierarchy.md)
