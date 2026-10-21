# asc::std::reference_wrapper::reference_wrapper

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

头文件路径为：`<asc/std/functional>`。

`asc::std::reference_wrapper::reference_wrapper`按本页所列构造形态初始化`reference_wrapper`对象。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

以下为类内的**等价调用形态摘要**，以公开类型特征表达引用绑定的异常条件，并省略实现的选择参数。

```cpp
template<class U>
constexpr reference_wrapper(U&& value) noexcept(is_nothrow_convertible_v<U, T&>);
```

## 参数说明

声明中的未命名模板约束参数用于选择可用重载，调用方无需提供；接口的适用类型和调用条件见约束说明。

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 被包装对象的来源类型；须能以左值引用绑定（U& 有效），且不能是reference_wrapper自身。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 被包装对象的来源；构造后的reference_wrapper保存指向该对象的引用，不拥有其所有权，对象生命周期须覆盖包装器使用期。 |

## 返回值说明

无返回值。

## 约束说明

- U须能隐式绑定或转换为T&；构造模板排除同类型reference_wrapper，普通复制使用其隐式特殊成员。异常说明由该引用转换是否抛出决定，而非复制被引用对象。

- 来源值须能绑定为有效的`T&`；不能用临时对象建立随后悬空的引用。
- 构造的包装器不拥有对象；被引用对象须在包装器访问期间保持有效。
- 构造模板排除同类型包装器，普通复制仍可复制已有包装器的引用关系。

## 调用示例

以下Host示例使用具体对象，并检查调用结果。

```cpp
#include <asc/std/functional>

bool example()
{
    int value = 3;
    asc::std::reference_wrapper<int> reference(value);
    reference.get() = 7;
    return value == 7 && &reference.get() == &value;
}
```

## 关联API

- [本头文件的接口列表](asc_std_functional.md)
