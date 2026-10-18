# asc::std::variant::swap

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

`asc::std::variant::swap`交换两个对象保存的状态或元素。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

所属类型：[`asc::std::variant<Types...>`](variant.md)。以下为类内声明；未命名约束形参和默认索引用于选择重载，调用方无需指定。

### 交换内容

```cpp
constexpr void swap(variant& other) noexcept(
    __fold_and_v<(is_nothrow_move_constructible_v<Types> && is_nothrow_move_assignable_v<Types>)...>);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Types` | 所属`variant`的备选类型列表，不得包含数组、引用或`void`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入；交换时为输入/输出 | 同类型来源对象；右值形式允许移动其活动备选值，交换会改变两个对象。 |

## 返回值说明

无返回值。

## 约束说明

- 对象一次保存一个活动备选值，读取前须通过`index()`确认所选备选项。
- Device使用的备选类型及构造、赋值、析构和交换操作须在对应编程模式可用且不抛出异常。
- 交换通过移动构造和移动赋值完成；所有备选类型须支持相应操作，全部操作不抛出异常时本成员为`noexcept`。

## 调用示例

以下Host示例使用具体对象，并检查调用结果。

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> left(7);
    asc::std::variant<int, float> right(2.5F);
    left.swap(right);
    return left.index() == 1 && right.index() == 0 &&
        asc::std::get<1>(left) == 2.5F && asc::std::get<0>(right) == 7;
}
```

## 关联API

- [`asc::std::variant`](variant.md)
- [本头文件的接口列表](asc_std_variant.md)
