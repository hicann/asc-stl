# asc::std::hash

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

头文件路径为：`<asc/std/optional>`。

`asc::std::hash<asc::std::optional<T>>` 由 `<asc/std/optional>` 提供，optional 的哈希特化：空值哈希 0，有值时 hash<remove_const_t<T>>{}(*value)；使 unordered 容器可直接容纳 optional。CSV hash 行 target_headers 不含 optional，故记新增。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

```cpp
template <class T> struct hash<optional<T>> { size_t operator()(const optional<T>& value) const; }
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `按声明确定` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- T 须使 hash<remove_const_t<T>> 可调用，即 remove_const_t<T> 为可哈希类型
- 空 optional 的哈希值为 0；含值时返回 hash<remove_const_t<T>>{}(*value)
- operator() 接受 const optional<T>& 并返回 size_t，使 unordered 容器可直接容纳 optional<T>

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/optional>

template <class T>
decltype(auto) example(const asc::std::optional<T>& value)
{
    return asc::std::hash(value);
}
```
