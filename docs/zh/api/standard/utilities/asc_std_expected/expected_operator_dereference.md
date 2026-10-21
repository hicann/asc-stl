# asc::std::expected::`operator*`

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

头文件路径为：`<asc/std/expected>`。

`asc::std::expected::operator*`解引用当前迭代器或有值对象。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

以下为`expected<Value, Error>`类内声明；Value和Error是所属类模板参数。

```cpp
constexpr Value& operator*() & noexcept;
```

```cpp
constexpr const Value& operator*() const& noexcept;
```

```cpp
constexpr Value&& operator*() && noexcept;
```

```cpp
constexpr const Value&& operator*() const&& noexcept;
```

## 参数说明

无函数参数。Value与Error是所属expected类模板的参数。

## 返回值说明

返回Value&、const Value&、Value&&或const Value&&。返回活动成功值的引用，cv/ref由本对象决定；访问要求has_value()。

## 约束说明

- 所属expected<Value, Error>要求有效的非void值类型和错误对象类型；当前操作还须满足本页原型、参数和状态要求。解引用要求has_value()；所得引用依赖对象及当前活动值的生存期。

## 调用示例

以下Host示例在被引用对象仍存活时检查结果。

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::expected<int, int> value(7);
    int* selected = &*value;
    *selected = 9;
    return value.has_value() && *value == 9;
}
```

## 关联API

- [`asc::std::expected`](expected.md)
- [本头文件的接口列表](asc_std_expected.md)
