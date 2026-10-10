# asc::std::pair::swap

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

`asc::std::pair::swap` 交换两个对象保存的状态或元素。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
constexpr void asc::std::pair::swap(pair<T1, T2>& other) noexcept(is_nothrow_swappable_v<T1>&& is_nothrow_swappable_v<T2>);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 返回值说明

无返回值。

## 约束说明

- pair 操作不抛出异常
- 关系运算符均为显式提供

## 调用示例

以下 Host 片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/utility>

void example()
{
    asc::std::pair<int, int> left(1, 2), right(3, 4);
    left.swap(right);
}
```
