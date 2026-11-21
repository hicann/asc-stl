# asc::std::variant::`operator=`

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

`asc::std::variant::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

所属类型：[`asc::std::variant<Types...>`](variant.md)。以下为类内声明；未命名约束形参和默认索引用于选择重载，调用方无需指定。

### 复制赋值

```cpp
constexpr variant& operator=(const variant& other);
```

### 移动赋值

```cpp
constexpr variant& operator=(variant&& other);
```

### 值转换赋值

```cpp
template <class T, size_t Index = __variant_best_match<remove_cvref_t<T>, void, Types...>::value,
    enable_if_t<Index != variant_npos &&
            (is_assignable_v<variant_alternative_t<Index, variant>&, T> ||
                is_constructible_v<variant_alternative_t<Index, variant>, T>),
        int> = 0>
constexpr variant& operator=(T&& value);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Types` | 所属`variant`的备选类型列表，不得包含数组、引用或`void`。 |
| `T` | 值转换赋值的输入类型；由实参推导，并据此选择可接收该值的备选类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入；交换时为输入/输出 | 同类型来源对象；右值形式允许移动其活动备选值，交换会改变两个对象。 |
| `value` | 输入（可能被移动） | 用于选择并构造或赋值活动备选项的值。 |

## 返回值说明

返回当前`variant`对象的引用，即`*this`。

## 约束说明

- Host 上，复制赋值切换备选项时，如果新类型的复制构造可能抛出异常且移动构造不会抛出异常，会先复制到临时对象。复制失败时保留原值。直接在目标位置构造新值的路径若抛出异常，对象将没有活动备选项。
- 切换备选项的构造失败不保留旧值；本实现不承诺通过额外临时副本保留旧备选项。
- 同一活动备选项的赋值失败不结束该对象的寿命；索引保持不变，值的状态由备选类型的赋值操作决定。
- 从没有活动备选项的来源复制或移动赋值后，目标同样没有活动备选项。

- 对象一次保存一个活动备选值，读取前须通过`index()`确认所选备选项。
- Device使用的备选类型及构造、赋值、析构和交换操作须在对应编程模式可用且不抛出异常。
- 同一活动类型的赋值要求对应赋值表达式可用；切换活动类型时要求目标类型可由来源值构造。

## 调用示例

以下Host示例使用具体对象，并检查调用结果。

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> value(7);
    value = 2.5F;
    return value.index() == 1 && asc::std::get<1>(value) == 2.5F;
}
```

## 关联API

- [`asc::std::variant`](variant.md)
- [本头文件的接口列表](asc_std_variant.md)
