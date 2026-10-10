# asc::dlpack_tensor

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

头文件路径为：`<asc/mdspan>`。

`asc::dlpack_tensor` 保存 DLPack 张量元数据及其关联的数据指针。

## 声明

```cpp
template<asc::std::size_t Rank> class asc::dlpack_tensor
```

## 约束说明

- 提供 Host 和 GM 视图以及 AI Core SIMD 编程 UB 视图
- 允许有符号步长
- 可选的 Host DLPack 桥接不抛出异常

## 调用示例

此接口仅在提供 DLPack 头文件时可用；以下片段按头文件是否存在选择编译。

```cpp
#include <asc/mdspan>

#if __has_include(<dlpack/dlpack.h>)
void use_type()
{
    using selected = asc::dlpack_tensor<2>;
    (void)sizeof(selected);
}
#endif
```
