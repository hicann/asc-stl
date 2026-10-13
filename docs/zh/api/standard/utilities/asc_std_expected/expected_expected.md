# asc::std::expected::expected

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

`asc::std::expected::expected`按本页所列构造形态初始化`expected`对象。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

### 原型1

```cpp
constexpr expected(const Value& value);
```

### 原型2

```cpp
constexpr expected(const expected<Value, Error>& value);
```

### 原型3

```cpp
constexpr expected(const unexpected<Error>& value);
```

### 原型4

```cpp
constexpr expected(unexpect_t tag, const Error& error);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 构造期望值所用的源值；被复制为新对象的期望值。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 复制来源expected；其期望值或错误值连同状态被复制到新对象。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 错误值来源（unexpected包装）；新对象以意外状态保存其错误值的副本。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | unexpect_t消歧标记；本身不携带数据，表示按意外状态构造对象。 |
| `error` | 输入 | 构造错误值所用的源错误值；被复制为新对象意外状态中的错误值。 |

## 返回值说明

无返回值。

## 约束说明

- T必须为非void类型，E必须为对象类型。
- 适用操作必须不抛出异常。
- 提供构造、赋值、emplace和swap。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::expected<int, int> value(7);
    return value.has_value() && *value == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_expected.md)
