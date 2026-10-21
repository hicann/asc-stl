# asc::std::expected::`operator-`>

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

`asc::std::expected::operator->`返回可用于访问所指对象成员的指针。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

以下为`expected<Value, Error>`类内声明；Value和Error是所属类模板参数。

```cpp
constexpr Value* operator->() noexcept;
```

```cpp
constexpr const Value* operator->() const noexcept;
```

## 参数说明

无函数参数。Value与Error是所属expected类模板的参数。

## 返回值说明

返回Value*或const Value*。返回活动成功值的地址；访问要求has_value()，所得指针依赖对象及当前值的生存期。

## 约束说明

- 支持所有cv/ref限定形式。
- Device侧可调用对象及结果构造必须不抛出异常。
- 返回的引用、指针或非拥有包装器不延长被引用对象的生命周期。使用时须保证该对象仍存活；对象销毁或其值存储生命周期结束后不得继续访问。

## 调用示例

以下Host示例在被引用对象仍存活时检查结果。

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::expected<int, int> value(7);
    int* selected = value.operator->();
    *selected = 9;
    return value.has_value() && *value == 9;
}
```

## 关联API

- [`asc::std::expected`](expected.md)
- [本头文件的接口列表](asc_std_expected.md)
