# asc::std::variant::emplace

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

`asc::std::variant::emplace` 在指定位置直接构造元素。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

### 原型 1

```cpp
template<class T, class ...Args, size_t Index, enable_if_t<is_constructible_v<T, Args...>, int>> T& asc::std::variant::emplace(Args&&... args);
```

### 原型 2

```cpp
template<size_t Index, class ...Args, class Constraints, class> typename Constraints::T& asc::std::variant::emplace(Args&&... args);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Index` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Constraints` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `未命名参数4` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `T &` | 返回原位构造的元素引用或所选原型规定的插入结果。 |
| 原型 2 | `typename Constraints::T &` | 返回原位构造的元素引用或所选原型规定的插入结果。 |

## 约束说明

- Device 侧备选类型以及所选构造、赋值和交换操作必须不抛出异常
- index、operator*、emplace、swap 和 visit 仅提供非抛出路径

## 调用示例

以下 Host 片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/variant>

decltype(auto) example()
{
    asc::std::variant<int, float> value(7);
    return value.emplace<int>(8);
}
```
