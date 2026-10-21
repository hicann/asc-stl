# asc::validate_tensor_copy_descriptor

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

`asc::validate_tensor_copy_descriptor`检查Tensor Copy Descriptor的范围、步长和大小计算是否合法。

## 函数原型

```cpp
namespace asc {
template <unsigned Rank>
[[nodiscard]] constexpr asc::tensor_copy_status validate_tensor_copy_descriptor(
    const asc::tensor_copy_descriptor<Rank>& descriptor) noexcept;
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `descriptor` | 输入 | 待检查的描述符；调用期间须有效，可包含尚未通过校验的数值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::tensor_copy_status` | 返回描述符数值校验状态；本调用不修改描述符，也不提交搬运。 |

## 约束说明

- 可在Host、AI Core SIMD编程和AI Core SIMT编程中调用；本操作同步处理描述符，不启动数据搬运。
- `Rank`须为1至5的编译期无符号整数；各维度按从外到内的顺序编号，最内维为`Rank - 1`。
- `descriptor`须在调用期间有效；本函数返回其[validate](tensor_copy_descriptor_validate.md)成员的校验结果。
- 按维度检查非零有效长度和非零源/目标步长；发现问题分别返回`zero_extent`或`zero_stride`。
- 任一侧填充超过255、填充后元素总量溢出或源/目标步长跨度累计溢出时，返回`size_overflow`；其余情况返回`success`。
- 校验不访问源/目标存储，不检查实际视图容量、流水级或端点地址；搬运接口还会执行各自检查。

## 调用示例

以下片段以二维无填充描述符展示查询或校验；实际存储须满足描述符范围。

```cpp
#include <asc/tensor_copy>

decltype(auto) example()
{
    unsigned int extents[2] = {2, 2};
    unsigned int strides[2] = {2, 1};
    unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return asc::validate_tensor_copy_descriptor(descriptor);
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
