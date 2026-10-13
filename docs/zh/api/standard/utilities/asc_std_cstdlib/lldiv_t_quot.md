# asc::std::lldiv_t::quot

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

头文件路径为：`<asc/std/cstdlib>`。

`asc::std::lldiv_t::quot`保存整数除法结果的商。

标准语义参考：[cppreference `cstdlib`](https://en.cppreference.com/w/cpp/header/cstdlib)。

## 声明

所属类型：[`asc::std::lldiv_t`](lldiv_t.md)。

```cpp
// asc::std::lldiv_t 类内的声明节选；模板形参和其他成员由所属类提供。
long long quot;
```

## 约束说明

- 提供整数重载及相应结果类型。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/cstdlib>

bool example()
{
    asc::std::lldiv_t result = asc::std::lldiv(17, 5);
    return result.quot == 3 && result.rem == 2;
}
```

## 关联API

- [`asc::std::lldiv_t`](lldiv_t.md)
- [本头文件的接口列表](asc_std_cstdlib.md)
