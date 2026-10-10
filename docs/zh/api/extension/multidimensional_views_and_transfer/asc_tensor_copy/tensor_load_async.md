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

`asc::tensor_load_async` 按 Descriptor 和填充值从 GM 异步加载多维 Tensor 到 UB。

## 函数原型

```cpp
template<class T, unsigned Rank> asc::tensor_copy_status asc::tensor_load_async(const asc::pipeline_ref& pipeline, unsigned int stage, asc::ub_span<T> destination, asc::gm_span<const T> source, const asc::tensor_copy_descriptor<Rank>& descriptor, T fill_value) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Rank` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pipeline` | 输入 | 管理当前异步搬运阶段的流水线引用；等待完成前须保持有效。 |
| `stage` | 输入 | 指定“按 Descriptor 和填充值从 GM 异步加载多维 Tensor 到 UB”使用的标量值；取值须满足声明和约束。 |
| `destination` | 输出 | 用于接收结果的目标存储。异步操作完成前，其存储须保持有效。 |
| `source` | 输入 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |
| `descriptor` | 输入 | 描述张量形状、步长与搬运方向的对象；提交前须通过校验。 |
| `fill_value` | 输入 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::tensor_copy_status` | 返回异步加载任务的提交状态；提交成功不表示搬运已经完成。 |

## 约束说明

- 仅可在 AI Core SIMD 编程中调用
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明

## 调用示例

以下设备函数片段展示 GM 到 UB 的异步加载；流水级与源、目标存储须在完成前有效。

```cpp
#include <asc/tensor_copy>

__aicore__ decltype(auto) example(const asc::pipeline_ref& pipeline, asc::ub_span<int> destination,
    asc::gm_span<const int> source, const asc::tensor_copy_descriptor<2>& descriptor)
{
    return asc::tensor_load_async<int, 2>(pipeline, 0, destination, source, descriptor, 0);
}
```
