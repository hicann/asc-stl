# asc::tensor_copy_descriptor

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

`asc::tensor_copy_descriptor`描述多维Tensor搬运的范围、源/目标步长和两侧填充。

## 声明

```cpp
namespace asc {
template<unsigned Rank> class tensor_copy_descriptor;
} // namespace asc
```

## 约束说明

- `Rank`须为1至5的编译期无符号整数；各维度按从外到内的顺序编号，最内维为`Rank - 1`。
- 范围、源/目标步长及左右填充以32位无符号元素数保存；描述符拥有这些数值，不拥有或引用源/目标数据存储。
- 构造和查询可在Host、AI Core SIMD编程和AI Core SIMT编程中进行，不启动数据搬运；实际搬运前须调用[validate](tensor_copy_descriptor_validate.md)并满足搬运接口的存储、地址空间与同步要求。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/tensor_copy>
#include <asc/std/type_traits>

bool example()
{
    using Descriptor = asc::tensor_copy_descriptor<2>;
    static_assert(asc::std::is_same_v<Descriptor::size_type, unsigned int>);
    Descriptor descriptor;
    return descriptor.rank() == 2 && descriptor.validate() == asc::tensor_copy_status::zero_extent;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
