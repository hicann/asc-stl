# asc::std::stack::swap

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

头文件路径为：`<asc/std/stack>`。

`asc::std::stack::swap`交换两个对象保存的状态或元素。

标准语义参考：[cppreference `stack`](https://en.cppreference.com/w/cpp/header/stack)。

## 函数原型

所属类型：[`asc::std::stack`](stack.md)。

```cpp
// asc::std::stack 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr void swap(stack<T, Container>& other) noexcept(noexcept(this->c.swap(other.c)));
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 与当前对象交换状态的另一对象；交换后双方保存对方原有状态。 |

## 返回值说明

无返回值。

## 约束说明

- Container须支持swap；异常规格与所选Container的swap一致。
- Device使用的Container、元素操作及Compare须可在对应执行位置调用并满足其非抛出要求；Host的异常行为遵循所调用对象，未额外声明noexcept时不承诺不抛出。

## 调用示例

泛型代码可用`noexcept(a.swap(b))`检查异常规格而不执行交换；结果跟随底层容器，包括GCC 9的C++17模式。底层交换可能抛出时不能报告为不抛出；图遍历交换暂存工作栈时仍需遵守该容器的异常保证。

以下Host片段显式提供标准容器作为底层存储；设备端须提供可在目标位置调用的容器。

```cpp
#include <asc/std/stack>
#include <memory>
#include <deque>

bool example()
{
    using sequence = asc::std::stack<int, ::std::deque<int>>;
    sequence values;
    values.push(7);
    sequence other;
    other.push(9);
    values.swap(other);
    return values.top() == 9 && other.top() == 7;
}
```

## 关联API

- [`asc::std::stack`](stack.md)
- [本头文件的接口列表](asc_std_stack.md)
