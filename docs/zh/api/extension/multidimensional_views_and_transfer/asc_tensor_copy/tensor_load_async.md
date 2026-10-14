# asc::tensor_load_async

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

头文件路径为：`<asc/tensor_copy>`。

`asc::tensor_load_async`按Descriptor和填充值从GM异步加载多维Tensor到UB。

## 函数原型

```cpp
namespace asc {
template<class T, unsigned Rank> asc::tensor_copy_status tensor_load_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<T> destination, asc::gm_span<const T> source, const asc::tensor_copy_descriptor<Rank>& descriptor, T fill_value) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 搬运的元素类型；须属于多维搬运后端支持的元素集合。 |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pipeline` | 输入 | 承载本次异步搬运的GM-UB流水线引用（自身不持有资源）；搬运完成前须保持有效。 |
| `stage` | 输入 | 本次加载提交到的流水线级索引（0起）；须小于该流水线的级数，否则返回invalid_stage且不发起搬运。 |
| `destination` | 输出 | 接收加载数据的UB目标存储视图（ub_span<T>）；元素容量须不小于按目标步长与两侧填充折算的需求元素数（否则返回insufficient_destination），搬运完成前存储须保持有效。 |
| `source` | 输入 | 被加载的GM源存储视图（gm_span<const T>）；元素容量须不小于按源步长折算的需求元素数、不含填充（否则返回insufficient_source），搬运完成前存储须保持有效。 |
| `descriptor` | 输入 | 描述各维度范围、源/目标步长与两侧填充的搬运描述符；须通过其validate校验（success），否则直接返回对应失败状态且不发起搬运。 |
| `fill_value` | 输入 | 写入目标两侧填充区域的元素值，类型同T。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::tensor_copy_status` | 返回异步加载任务的提交状态；提交成功不表示搬运已经完成。 |

## 约束说明

- 仅可在AI Core SIMD编程中调用。
- 源与目标两端地址须落在搬运引擎的 32 字节数据块边界上；任一端未对齐分别返回 insufficient_source/insufficient_destination（该硬件边界检查独立于 tensor_copy_required_alignment 的行距结果）。
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明。

## 调用示例

以下设备函数片段展示GM到UB的异步加载；流水级与源、目标存储须在完成前有效。

```cpp
#include <asc/tensor_copy>

__aicore__ decltype(auto) example(const asc::pipeline_ref& pipeline, asc::ub_span<int> destination,
    asc::gm_span<const int> source, const asc::tensor_copy_descriptor<2>& descriptor)
{
    return asc::tensor_load_async<int, 2>(pipeline, 0, destination, source, descriptor, 0);
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
