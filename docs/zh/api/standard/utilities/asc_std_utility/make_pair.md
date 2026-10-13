# asc::std::make_pair

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

头文件路径为：`<asc/std/utility>`。

`asc::std::make_pair`根据两个值构造pair，并应用规定的类型退化规则。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
namespace asc::std {
template<class T1, class T2> constexpr pair<unwrap_ref_decay_t<T1>, unwrap_ref_decay_t<T2>> make_pair(T1&& left, T2&& right);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 首元素实参的类型；经decay及引用解包后决定结果pair的first类型。 |
| `T2` | 次元素实参的类型；经decay及引用解包后决定结果pair的second类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入/输出 | 构造first成员的来源值；左值被复制、右值被移动，右值移动后处于有效但未指定状态。 |
| `right` | 输入/输出 | 构造second成员的来源值；左值被复制、右值被移动，右值移动后处于有效但未指定状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `pair<unwrap_ref_decay_t<T1>, unwrap_ref_decay_t<T2>>` | 返回保存两个输入值的新`pair`对象。 |

## 约束说明

- 异常规格以对应声明为准；Device侧使用的元素操作须不抛出异常。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下片段用具体数值展示本页调用。

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    return asc::std::make_pair(1, 2);
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
