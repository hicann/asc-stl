# asc::identity_element

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

头文件路径为：`<asc/functional>`。

`asc::identity_element`返回已登记运算及值类型的单位元；未登记组合不能调用。

## 函数原型

```cpp
namespace asc {
template<class Operator, class T> constexpr T identity_element() noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Operator` | 已登记的`asc::std`标准函数对象类型。 |
| `T` | 与该运算匹配的值类型。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回已登记运算及值类型的单位元。 |

## 约束说明

- 仅接受已登记的整数算术、布尔逻辑或无符号整数位运算组合。
- 浮点加法未登记。

## 调用示例

以下片段使用已登记的标准函数对象与具体整数类型。

```cpp
#include <asc/functional>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

void example()
{
    static_assert(asc::identity_element<asc::std::plus<int>, int>() == 0);
}
```

## 关联API

- [asc::has_identity_element_v](has_identity_element_v.md)
