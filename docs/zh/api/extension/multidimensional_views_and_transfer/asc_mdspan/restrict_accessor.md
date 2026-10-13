# asc::restrict_accessor

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

`asc::restrict_accessor`为满足不别名约束的数据句柄提供mdspan访问器。

## 声明

```cpp
namespace asc {
template<class Accessor> class restrict_accessor;
} // namespace asc
```

## 约束说明

- 提供Host和GM视图以及AI Core SIMD编程UB视图。
- 允许有符号步长。
- 可选的Host DLPack桥接不抛出异常。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/mdspan>

bool example()
{
    int values[] = {2, 4};
    asc::restrict_accessor<asc::std::default_accessor<int>> accessor;
    accessor.access(values, 1) = 7;
    return values[1] == 7 && accessor.offset(values, 1) == values + 1;
}
```

## 关联API

- [本头文件的接口列表](asc_mdspan.md)
