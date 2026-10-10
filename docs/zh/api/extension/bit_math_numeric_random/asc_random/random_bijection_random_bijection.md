# asc::random_bijection::random_bijection

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

`asc::random_bijection::random_bijection` 使用调用方提供的参数初始化 `asc::random_bijection` 对象。

## 函数原型

### 原型 1

```cpp
constexpr asc::random_bijection::random_bijection() noexcept;
```

### 原型 2

```cpp
template<class RNG> constexpr asc::random_bijection::random_bijection(Index size, RNG&& generator) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RNG` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `size` | 输入 | 对象或范围的大小。 |
| `generator` | 输入/输出 | 提供随机数的生成器；调用时其状态可能推进。 |

## 约束说明

- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式
- 不提供 SeedSequence、流式输入输出或共享全局状态

## 调用示例

以下 Host 片段使用具体类型演示本页接口；对象和指针的有效期须满足本页约束。

```cpp
#include <asc/random>

void example()
{
    asc::random_bijection<unsigned long long> mapping{};
    (void)mapping.size();
}
```
