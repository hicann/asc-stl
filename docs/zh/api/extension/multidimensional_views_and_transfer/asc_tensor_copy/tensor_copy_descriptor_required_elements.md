# asc::tensor_copy_descriptor::required_elements

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

`asc::tensor_copy_descriptor::required_elements`返回描述符各维填充后长度的乘积，不计入步长空隙。

## 函数原型

以下为`asc::tensor_copy_descriptor<Rank>`类内声明，Rank由所属类模板提供。

```cpp
constexpr unsigned long long required_elements() const noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned long long` | 返回描述符各维填充后长度的乘积，不计入步长空隙。 |

## 约束说明

- 可在Host、AI Core SIMD编程和AI Core SIMT编程中调用；本操作同步处理描述符，不启动数据搬运。
- 返回各维`extent + left_padding + right_padding`的乘积；任一填充后长度为零或乘积超出`unsigned long long`范围时返回`0`。
- 本查询不计入步长造成的存储空隙，也不检查零步长、填充上限或实际源/目标容量；调用前需要的参数检查见[validate](tensor_copy_descriptor_validate.md)。
- 实际搬运的视图容量按各方向的步长跨度检查；不能将此乘积当作任意步长布局的存储跨度。

## 调用示例

以下Host片段以二维描述符演示调用。

```cpp
#include <asc/tensor_copy>

decltype(auto) example(const asc::tensor_copy_descriptor<2>& descriptor)
{
    auto value = descriptor.required_elements();
    return value;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
