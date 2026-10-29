# asc::grid_dims（函数模板）

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

`asc::grid_dims`创建Grid层级的三维尺寸描述。

## 函数原型

```cpp
namespace asc {
template<unsigned int X, unsigned int Y = 1, unsigned int Z = 1> constexpr asc::level_dimensions<asc::grid_level> grid_dims() noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `X` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `Y` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `Z` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::level_dimensions<asc::grid_level>` | 返回由当前网格和线程块尺寸构成的执行层次或启动尺寸。 |

## 约束说明

- 提供C++17 constexpr Host/Device层次结构接口。
- 带extent的值要求每一维均非零。
- extent总数按无符号64位的x*y*z计算。

## 调用示例

以下Host示例使用具体类型或维度，检查独立的预期值；不查询正在运行的Device执行上下文。

```cpp
#include <asc/hierarchy>
#include <asc/std/type_traits>

bool example()
{
    const auto dimensions = asc::grid_dims<2, 3, 4>();
    static_assert(asc::std::is_same_v<decltype(dimensions), const asc::level_dimensions<asc::grid_level>>);
    const auto extents = dimensions.extents;
    return extents.x == 2 && extents.y == 3 && extents.z == 4 && extents.count() == 24;
}
```

## 关联API

- [本头文件的接口列表](asc_hierarchy.md)
