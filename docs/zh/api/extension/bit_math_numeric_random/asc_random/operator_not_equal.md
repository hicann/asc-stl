# asc::operator!=（函数模板）

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

头文件路径为：`<asc/random>`。

`asc::operator!=` 比较两个相同参数的 PCG64 引擎当前状态是否不同。

## 函数原型

```cpp
template<asc::std::uint64_t AHigh, asc::std::uint64_t ALow, asc::std::uint64_t CHigh, asc::std::uint64_t CLow> constexpr bool asc::operator!=(const asc::pcg64_engine<AHigh, ALow, CHigh, CLow>& left, const asc::pcg64_engine<AHigh, ALow, CHigh, CLow>& right) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `AHigh` | PCG64 状态递推乘数 A 的高 64 位，编译期无符号整数常量。 |
| `ALow` | PCG64 状态递推乘数 A 的低 64 位，编译期无符号整数常量。 |
| `CHigh` | PCG64 状态递推增量 C 的高 64 位，编译期无符号整数常量。 |
| `CLow` | PCG64 状态递推增量 C 的低 64 位，编译期无符号整数常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与不相等比较的左侧 PCG64 引擎；比较其当前状态。 |
| `right` | 输入 | 参与不相等比较的右侧 PCG64 引擎；比较其当前状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式
- 不提供 SeedSequence、流式输入输出或共享全局状态

## 调用示例

以下片段给出具体模板实参和调用对象。

```cpp
#include <asc/random>

decltype(auto) example()
{
    asc::pcg64 left;
    asc::pcg64 right;
    return asc::operator!=(left, right);
}
```
