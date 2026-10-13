# asc::is_aligned

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

头文件路径为：`<asc/memory>`。

`asc::is_aligned`检查整数地址值或指针是否满足给定字节对齐要求。

## 函数原型

### 原型1

```cpp
namespace asc {
template<class Integer> constexpr bool is_aligned(Integer value, Integer alignment) noexcept;
} // namespace asc
```

### 原型2

```cpp
namespace asc {
template<class T> constexpr bool is_aligned(T* pointer, asc::std::size_t alignment) noexcept;
} // namespace asc
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Integer` | 待检查地址值与对齐值共用的整数类型；须支持取模运算。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待检查的整数地址值；当value对alignment取模为0（且alignment非零）时视为对齐。 |
| `alignment` | 输入 | 待检查的倍数；0返回false。指针形式以字节为单位，整数形式与value同单位。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 指针指向的对象类型；仅用于推导指针形参，本接口不解引用指针。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 待检查的指针；仅取其地址数值按alignment做字节对齐判断，不访问所指向的对象。 |
| `alignment` | 输入 | 待检查的倍数；0返回false。指针形式以字节为单位，整数形式与value同单位。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `bool` | alignment非零且数值／地址能被alignment整除时为`true`。 |
| 原型2 | `bool` | alignment非零且数值／地址能被alignment整除时为`true`。 |

## 约束说明

- `alignment == 0`明确返回`false`；正alignment不要求是2的幂。
- 整数重载要求value和alignment支持取模运算。
- 指针重载按地址值检查字节对齐。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/memory>

bool example()
{
    return asc::is_aligned(14, 7) && !asc::is_aligned(15, 7) && !asc::is_aligned(14, 0);
}
```

## 关联API

- [本头文件的接口列表](asc_memory.md)
