# asc::tensor_copy_descriptor::tensor_copy_descriptor

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

`asc::tensor_copy_descriptor::tensor_copy_descriptor`默认构造`asc::tensor_copy_descriptor`对象，将描述各维的数值初始化为零。

## 函数原型

以下为`asc::tensor_copy_descriptor<Rank>`类内声明，Rank由所属类模板提供。

```cpp
constexpr tensor_copy_descriptor() noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

## 返回值说明

无返回值。

## 约束说明

- `Rank`须为1至5的编译期无符号整数；各维度按从外到内的顺序编号，最内维为`Rank - 1`。
- 默认构造把所有维度的有效长度、源/目标步长及两侧填充初始化为零；此时[validate](tensor_copy_descriptor_validate.md)返回`zero_extent`。
- 可在Host、AI Core SIMD编程和AI Core SIMT编程中构造；构造不启动数据搬运。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/tensor_copy>

bool example()
{
    asc::tensor_copy_descriptor<2> descriptor;
    return descriptor.rank() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
