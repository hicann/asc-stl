# asc::block

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

头文件路径为：`<asc/hierarchy>`。

`asc::block`提供Block层级的全局常量标签。

## 声明

```cpp
namespace asc {
inline constexpr block_level block{};
}  // namespace asc
```

## 约束说明

- 提供C++17 constexpr Host/Device层次结构接口。
- 带extent的值要求每一维均非零。
- extent总数按无符号64位的x*y*z计算。

## 调用示例

以下Host示例使用具体类型或维度，检查独立的预期值；不查询正在运行的Device执行上下文。

```cpp
#include <asc/hierarchy>
#include <asc/std/type_traits>

static_assert(asc::std::is_same_v<decltype(asc::block), const asc::block_level>);
```

## 关联API

- [本头文件的接口列表](asc_hierarchy.md)
