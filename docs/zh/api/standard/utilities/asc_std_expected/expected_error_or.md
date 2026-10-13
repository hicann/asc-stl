# asc::std::expected::error_or

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

`asc::std::expected::error_or` 有错误时返回错误值，否则返回调用方给出的替代值。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

### 原型 1

```cpp
template<class G> E asc::std::expected::error_or(G&& default_value)&&;
```

### 原型 2

```cpp
template<class G> E asc::std::expected::error_or(G&& default_value) const&;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `G` | 替代错误值的类型；须能转换为 E。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `default_value` | 输入/输出 | 替代错误值；本对象不含错误时返回由它转换得到的 E，含错误时返回所存错误值。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `G` | 替代错误值的类型；须能转换为 E。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `default_value` | 输入/输出 | 替代错误值；本对象不含错误时返回由它转换得到的 E，含错误时返回所存错误值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `E` | 返回错误值，否则返回调用方给出的替代值。 |
| 原型 2 | `E` | 返回错误值，否则返回调用方给出的替代值。 |

## 约束说明

- 支持所有 cv/ref 限定形式
- Device 侧可调用对象及结果构造必须不抛出异常

## 调用示例

以下 Host 片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/expected>

decltype(auto) example()
{
    asc::std::expected<int, int> value(asc::std::unexpect, 3);
    return static_cast<asc::std::expected<int, int>&&>(value).error_or(0);
}
```
