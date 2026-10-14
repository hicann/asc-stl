# asc::tensor_store_async

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

`asc::tensor_store_async` 按 Descriptor 从 UB 异步存储多维 Tensor 到 GM，是 `asc::tensor_load_async` 的 UB→GM 方向镜像。

描述符按往返方式复用：`source_stride` 仍描述 GM 布局，`destination_stride` 描述 load 写入的带填充 UB 布局；store 逐行读取越过左填充的有效数据，填充区被跳过而不搬运。GM 侧不存在填充，因此本接口无填充值参数。

提交成功后内嵌执行该流水轮次的消费者侧 retire 步（`consumer_release`），本接口等价于 plain pipeline 词汇中 `copy_async(..., gm, ub)` 加 `consumer_release` 的组合；调用前须已完成对该级缓冲的全部标量读取。

## 函数原型

```cpp
template<class T, unsigned Rank> asc::tensor_copy_status asc::tensor_store_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::gm_span<T> destination, asc::ub_span<const T> source, const asc::tensor_copy_descriptor<Rank>& descriptor) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 搬运的元素类型；须属于多维搬运后端支持的元素集合。 |
| `Rank` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pipeline` | 输入 | 管理当前异步搬运阶段的流水线引用；等待完成前须保持有效。 |
| `stage` | 输入 | 流水线阶段编号；须小于 pipeline.stages()。 |
| `destination` | 输出 | 用于接收结果的 GM 目标存储。异步操作完成前，其存储须保持有效。 |
| `source` | 输入 | 源数据所在的 UB 存储视图。异步操作完成前，其存储须保持有效。 |
| `descriptor` | 输入 | 描述张量形状、步长与搬运方向的对象；提交前须通过校验。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::tensor_copy_status` | 返回异步存储任务的提交状态；提交成功不表示搬运已经完成。 |

## 约束说明

- 仅可在 AI Core SIMD 编程中调用
- 提交前依次校验描述符合法性、stage 范围（越界返回 `invalid_stage`）、最内维运行字节长度与两端所需元素数（溢出返回 `size_overflow`、视图不足分别返回 `insufficient_destination`/`insufficient_source`）
- 对齐搬运路径的两端地址对齐为调用方前置条件，与 `asc::tensor_copy_required_alignment` 对 load 方向的说明一致
- 调用前须完成对该流水级 UB 缓冲的全部标量读取（接口内嵌消费者侧 retire 步）
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明

## 调用示例

以下设备函数片段展示 UB 到 GM 的异步存储；流水级与源、目标存储须在完成前有效，且调用前已完成对该级缓冲的读取。

```cpp
#include <asc/tensor_copy>

__aicore__ decltype(auto) example(const asc::pipeline_ref& pipeline, asc::gm_span<int> destination,
    asc::ub_span<const int> source, const asc::tensor_copy_descriptor<2>& descriptor)
{
    return asc::tensor_store_async<int, 2>(pipeline, 0, destination, source, descriptor);
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
