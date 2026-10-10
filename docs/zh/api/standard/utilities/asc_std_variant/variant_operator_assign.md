# asc::std::variant::operator=

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

`asc::std::variant::operator=` 按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

### 原型 1

```cpp
constexpr variant<Types...>& asc::std::variant::operator=(const variant<Types...>& other);
```

### 原型 2

```cpp
constexpr variant<Types...>& asc::std::variant::operator=(variant<Types...>&& other);
```

### 原型 3

```cpp
template<class Arg, class Constraints, class> variant<Types...>& asc::std::variant::operator=(Arg&& other) noexcept(Constraints::Nothrowassignable);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Arg` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Constraints` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `未命名参数3` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `variant<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 2 | `variant<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 3 | `variant<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- Device 侧备选类型以及所选构造、赋值和交换操作必须不抛出异常
- index、operator*、emplace、swap 和 visit 仅提供非抛出路径

## 调用示例

以下 Host 片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/variant>

void example()
{
    asc::std::variant<int, float> left(7), right(8);
    left = right;
}
```
