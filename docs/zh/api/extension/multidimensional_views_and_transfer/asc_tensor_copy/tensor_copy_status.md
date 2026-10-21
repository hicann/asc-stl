# asc::tensor_copy_status

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

`asc::tensor_copy_status`定义Tensor Copy校验和执行状态。

## 声明

```cpp
namespace asc {
enum class tensor_copy_status : int;
} // namespace asc
```

## 约束说明

- 该枚举及其常量可在Host、AI Core SIMD编程和AI Core SIMT编程中保存和比较；读取状态值本身不进行校验或搬运。
- 须按返回该值的接口解释状态：描述符校验只涉及数值条件，异步搬运还涉及视图容量、地址与流水级，`success`不表示异步数据已可读取。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/tensor_copy>

bool example()
{
    const asc::tensor_copy_status status = asc::tensor_copy_status::insufficient_destination;
    return status != asc::tensor_copy_status::success;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
