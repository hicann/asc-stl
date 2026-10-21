# asc::std::ranges::zip_view::zip_view

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::zip_view::zip_view`按本页所列构造形态初始化`zip_view`对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`zip_view`](ranges_zip_view.md)。以下按当前实现列声明摘要；省略仅供SFINAE的选择参数，保留供调用使用的类型默认值。默认构造形式均有逐项参与条件，不能据此假定所有特化都可默认构造。

### 原型1

```cpp
constexpr zip_view() = default;
```

默认构造是否可用取决于两个底层视图的默认构造。

### 原型2

```cpp
constexpr zip_view(FirstView first, SecondView second);
```

按值接收并移动保存两个底层视图，不是变参构造。

## 参数说明

### 原型1的参数

无函数参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 第一路随机访问且有大小的视图。 |
| `second` | 输入 | 第二路随机访问且有大小的视图。 |

## 返回值说明

无返回值。

## 约束说明

- 每种形式须满足其原型所列参与条件；实际保存的范围或值还须满足所属视图的类型要求。
- 构造视图不会复制它所借用的元素；底层存储和被借用对象须覆盖相应迭代器与元素访问期。
- 以noexcept标注的形式须遵守实际成员操作不抛出异常的要求；具体异常规格见各原型。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/tuple>

bool example()
{
    int first[3] = {1, 2, 3};
    int second[2] = {4, 5};
    auto view = asc::std::ranges::views::zip(first, second);
    auto item = *view.begin();
    asc::std::get<0>(item) = 7;
    return view.size() == 2 && first[0] == 7 && asc::std::get<1>(item) == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
