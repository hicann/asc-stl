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

`asc::random_bijection::random_bijection`使用调用方提供的参数初始化`asc::random_bijection`对象。

## 函数原型

所属类型：[`asc::random_bijection`](random_bijection.md)。

### 原型1

```cpp
// asc::random_bijection 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr random_bijection() noexcept;
```

### 原型2

```cpp
// asc::random_bijection 类内的声明节选；模板形参和其他成员由所属类提供。
template <class RNG>
constexpr random_bijection(Index size, RNG&& generator) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RNG` | 用于生成双射参数的随机数引擎类型；须能提供所需的无符号随机值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `size` | 输入 | 对象或范围的大小。 |
| `generator` | 输入/输出 | 提供随机数的生成器；调用时其状态可能推进。 |

## 返回值说明

无返回值。

## 约束说明

- 构造置换时从生成器每次结果的高32位提取轮密钥；只有低32位提供熵的发生器会得到全零轮密钥。需要随机轮密钥时应提供高位也具有熵的64位发生器。

- 本页类型、别名或字段只描述所保存的随机状态或置换信息；观察它不调用Runtime、不访问共享全局状态。
- 映射调用须使用非空有限域和域内索引；生成器调用的种子、计数器要求见其成员页。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 engine(7);
    asc::random_bijection<unsigned long long> permutation(8, engine);
    return permutation.size() == 8 && permutation(0) < 8;
}
```

## 关联API

- [`asc::random_bijection`](random_bijection.md)
- [本头文件的接口列表](asc_random.md)
