# asc::sub_block_count

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

`asc::sub_block_count`返回当前AICore内可用的Sub Block数量。

## 函数原型

```cpp
namespace asc {
unsigned int sub_block_count() noexcept;
} // namespace asc
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned int` | 返回所属执行层级中的单元数量。 |

## 约束说明

- 仅可在AI Core SIMD编程中调用。
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明。

## 调用示例

以下SIMD核函数为每个AI Core Block中的每个Sub Block写入一项。调用方须提供至少AI Core Block数量乘以实际Sub Block数量个unsigned int的有效GM输出，并在核函数完成后回读。每项应为当前启动环境的Sub Block数量；该数量由实际硬件和启动方式决定。该查询仅在SIMD提供；文档门禁验证真实SIMD编译，不代表NPU执行通过。

```cpp
#include <asc/hierarchy>

__global__ __vector__ void example(__gm__ unsigned int* output)
{
    const auto block = asc::block_index();
    const auto sub_blocks = asc::sub_block_count();
    const auto sub_block = asc::sub_block_index();
    output[block * sub_blocks + sub_block] = asc::sub_block_count();
}
```

## 关联API

- [本头文件的接口列表](asc_hierarchy.md)
