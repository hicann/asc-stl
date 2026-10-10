# asc::execution_requirements::execution_requirements

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

头文件路径为：`<asc/execution.require.h>`。

`asc::execution_requirements` 默认构造函数创建不保证确定性、不要求输出有序且不指定相同键值处理规则的要求组合。

该接口的可用位置为 Host。

## 函数原型

```cpp
constexpr asc::execution_requirements::execution_requirements() noexcept;
```

## 参数说明

无参数。

## 约束说明

- 对象为不可变值
- 默认采用 determinism::not_guaranteed、output_ordering::unsorted 和 tie_break::unspecified

## 调用示例

以下 Host 片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/execution.require.h>

void example()
{
    asc::execution_requirements requirements{};
    (void)requirements.determinism_value();
}
```
