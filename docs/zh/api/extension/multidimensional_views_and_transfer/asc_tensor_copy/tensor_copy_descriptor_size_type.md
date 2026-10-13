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

`asc::tensor_copy_descriptor::size_type` 表示 Tensor Copy Descriptor 的维度和步长数值类型。

## 声明

`size_type` 为类模板 `asc::tensor_copy_descriptor<Rank>` 的成员类型别名，在类模板上下文中声明如下：

```cpp
template<unsigned Rank>
class asc::tensor_copy_descriptor {
public:
    using size_type = unsigned int;
};
```

## 约束说明

- 描述符及状态类型可在 Host、AI Core SIMD 编程 和 AI Core SIMT 编程中使用
- Rank 为 1 至 5
- 维度和步长采用 uint32_t，校验零维、零步长、大小溢出与对齐要求，校验本身不启动异步搬运

## 调用示例

以下片段选用具体模板实参读取嵌套类型。

```cpp
#include <asc/tensor_copy>

void use_type()
{
    using selected = typename asc::tensor_copy_descriptor<2>::size_type;
    (void)sizeof(selected);
}
```
