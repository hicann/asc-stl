# asc::minimum::`operator()`

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

`asc::minimum::operator()`比较两个输入并返回较小值。

## 函数原型

主模板`asc::minimum<T>`的类内声明：

```cpp
constexpr T operator()(const T& left, const T& right) const noexcept(noexcept(right < left));
```

透明特化`asc::minimum<void>`的类内声明：

```cpp
template <class Left, class Right>
constexpr auto operator()(Left&& left, Right&& right) const
    noexcept(noexcept(right < left)) -> decltype(right < left ? right : left);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Left` | 左侧比较操作数的类型。 |
| `Right` | 右侧比较操作数的类型。 |

## 返回值说明

- 主模板返回T值副本。
- void特化返回条件表达式的实际类型，可能为引用；被选操作数必须在返回引用使用期间存活。

## 约束说明

- 本页对象只执行所述谓词、比较或编译期属性查询，不进行Runtime提交。
- 比较操作数须支持相应运算；透明min/max可能返回引用，选中对象须在使用期间有效。
- 复制参数声明只表明调用方的复制承诺，不延长捕获引用的生命周期，也不代替可调用性检查。

## 调用示例

以下Host示例使用具体输入，在对象存活期内检查结果。

```cpp
#include <asc/functional>
bool example()
{
    int left = 1;
    int right = 2;
    const int& result = asc::minimum<>{}(left, right);
    return &result == &left && result == 1;
}
```

## 关联API

- [`asc::minimum`](minimum.md)
- [本头文件的接口列表](asc_functional.md)
