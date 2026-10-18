# asc::tensor_copy_descriptor::size_type

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

`asc::tensor_copy_descriptor::size_type`表示Tensor Copy Descriptor的维度和步长数值类型。

## 声明

`size_type`为类模板`asc::tensor_copy_descriptor<Rank>`的成员类型别名，在类模板上下文中声明如下：

```cpp
template<unsigned Rank>
class asc::tensor_copy_descriptor {
public:
    using size_type = unsigned int;
};
```

## 约束说明

在泛型代码中可通过所属类型的`size_type`声明大小变量，无需硬编码底层整数类型；该别名与其他成员类型的关系见所属类型页面。

- 此别名表示所属类型用于元素数量或大小的无符号整数类型；读取类型本身不分配内存，也不访问元素。
- 构造、分配和访问的运行条件见所属类型[asc::tensor_copy_descriptor](tensor_copy_descriptor.md)。

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
