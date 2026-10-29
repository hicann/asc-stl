# asc::tensor_copy_required_alignment

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

`asc::tensor_copy_required_alignment`将描述符最内维填充后的行长度按指定元素类型换算为字节数。

## 函数原型

```cpp
namespace asc {
template <class T, unsigned Rank>
[[nodiscard]] constexpr unsigned int tensor_copy_required_alignment(
    const asc::tensor_copy_descriptor<Rank>& descriptor) noexcept;
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 参与张量搬运的元素类型，决定元素大小及搬运对齐要求。 |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `descriptor` | 输入 | 描述张量形状、步长与搬运方向的对象；提交前须通过校验。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned int` | 返回最内维填充后行长度的字节数；换算乘积超出返回类型范围时返回0。 |

## 约束说明

- 可在Host、AI Core SIMD编程和AI Core SIMT编程中调用；本操作同步处理描述符，不启动数据搬运。
- `Rank`须为1至5的编译期无符号整数；各维度按从外到内的顺序编号，最内维为`Rank - 1`。
- `T`须为可以应用`sizeof(T)`的完整类型；`descriptor`须在调用期间有效。
- 返回[required_alignment](tensor_copy_descriptor_required_alignment.md)成员结果乘以`sizeof(T)`的字节数，乘积超出`unsigned int`范围时返回`0`。
- 本查询不校验描述符或实际端点地址；搬运两端的32字节边界要求不能由此返回值替代。

## 调用示例

以下片段以二维无填充描述符展示查询或校验；实际存储须满足描述符范围。

```cpp
#include <asc/tensor_copy>

bool example()
{
    const unsigned int extents[2] = {2, 2};
    const unsigned int strides[2] = {2, 1};
    const unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return asc::tensor_copy_required_alignment<int>(descriptor) == 8;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
