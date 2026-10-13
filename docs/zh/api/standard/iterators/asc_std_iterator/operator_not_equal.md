# asc::std::operator!=（move_iterator 重载）（函数模板）

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

头文件路径为：`<asc/std/iterator>`。

`asc::std::operator!=(const move_sentinel<Sentinel>&, const move_iterator<Iter>&)` 由 `<asc/std/iterator>` 提供，移动哨位与移动迭代器的反向不等比较。接口遵循对应 C++ 标准设施的语义；ASC-STL 的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
template<class Iter, class Sentinel, asc::std::enable_if_t<__move_iter_comparable<Iter, Sentinel>, int> = 0> constexpr bool asc::std::operator!=(const move_sentinel<Sentinel>& sentinel, const move_iterator<Iter>& iterator)
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Iter` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |
| `Sentinel` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |
| `int` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `sentinel` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |
| `iterator` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `, int> = 0> constexpr bool` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 显式提供的不等重载：底层迭代器与哨位可比较时取相等判定的反值

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/iterator>

template <class Iter, class Sentinel>
decltype(auto) example(const asc::std::move_sentinel<Sentinel>& sentinel, const asc::std::move_iterator<Iter>& iterator)
{
    return asc::std::operator!=(sentinel, iterator);
}
```
