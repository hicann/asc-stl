# asc::std::variant::valueless_by_exception

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

头文件路径为：`<asc/std/variant>`。

`asc::std::variant::valueless_by_exception`判断variant当前是否没有活动备选项。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

所属类型：[`asc::std::variant`](variant.md)。

```cpp
// asc::std::variant 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr bool valueless_by_exception() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 没有活动备选项时返回`true`，否则返回`false`。 |

## 约束说明

- Host切换备选项或`emplace`的新构造失败后返回`true`；此时`index()`为`variant_npos`，`get_if`返回空指针。
- 无活动备选项的对象可析构，并可通过成功构造或赋值恢复；读取值或调用`visit`前须先确认存在相应活动值。

- Device侧备选类型以及所选构造、赋值和交换操作必须不抛出异常。

## 调用示例

以下Host示例故意触发构造异常，检查无值状态并恢复为整数备选项。

```cpp
#include <asc/std/variant>

struct construction_failure {};

struct throwing_value {
    explicit throwing_value(int)
    {
        throw construction_failure{};
    }
};

bool example()
{
    asc::std::variant<int, throwing_value> value(7);
    try {
        value.emplace<1>(3);
        return false;
    } catch (const construction_failure&) {
        const bool empty = value.valueless_by_exception() &&
            value.index() == asc::std::variant_npos && asc::std::get_if<0>(&value) == nullptr;
        value.emplace<0>(11);
        return empty && !value.valueless_by_exception() && asc::std::get<0>(value) == 11;
    }
}
```

## 关联API

- [`asc::std::variant`](variant.md)
- [本头文件的接口列表](asc_std_variant.md)
