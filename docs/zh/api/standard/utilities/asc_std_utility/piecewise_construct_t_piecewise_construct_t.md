# asc::std::piecewise_construct_t::piecewise_construct_t

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

`asc::std::piecewise_construct_t::piecewise_construct_t`按本页所列构造形态初始化`piecewise_construct_t`对象。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

### 原型1

```cpp
constexpr piecewise_construct_t() noexcept;
```

### 原型2

```cpp
constexpr piecewise_construct_t(const piecewise_construct_t& other);
```

### 原型3

```cpp
constexpr piecewise_construct_t(piecewise_construct_t&& other);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

## 返回值说明

无返回值。

## 约束说明

- 异常规格以对应声明为准；Device侧使用的元素操作须不抛出异常。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/utility>
#include <asc/std/tuple>

bool example()
{
    asc::std::piecewise_construct_t tag{};
    asc::std::pair<int, int> value(tag, asc::std::make_tuple(2), asc::std::make_tuple(3));
    return value.first == 2 && value.second == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
