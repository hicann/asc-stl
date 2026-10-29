# asc::tensor_copy_descriptor::validate

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

`asc::tensor_copy_descriptor::validate`检查当前Tensor Copy Descriptor是否满足范围和步长要求。

## 函数原型

以下为`asc::tensor_copy_descriptor<Rank>`类内声明，Rank由所属类模板提供。

```cpp
constexpr asc::tensor_copy_status validate() const noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::tensor_copy_status` | 返回描述符数值校验状态；本调用不修改描述符，也不提交搬运。 |

## 约束说明

- 可在Host、AI Core SIMD编程和AI Core SIMT编程中调用；本操作同步处理描述符，不启动数据搬运。
- `Rank`须为1至5的编译期无符号整数；各维度按从外到内的顺序编号，最内维为`Rank - 1`。
- 按维度检查非零有效长度和非零源/目标步长；发现问题分别返回`zero_extent`或`zero_stride`。
- 任一侧填充超过255、填充后元素总量溢出或源/目标步长跨度累计溢出时，返回`size_overflow`；其余情况返回`success`。
- 校验不访问源/目标存储，不检查实际视图容量、流水级或端点地址；搬运接口还会执行各自检查。

## 调用示例

以下Host片段以二维描述符演示调用。

```cpp
#include <asc/tensor_copy>

bool example()
{
    const unsigned int extents[2] = {2, 2};
    const unsigned int strides[2] = {2, 1};
    const unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return descriptor.validate() == asc::tensor_copy_status::success;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
