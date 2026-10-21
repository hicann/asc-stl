# asc::random_bijection::size

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

`asc::random_bijection::size`返回一一映射覆盖的有限索引域大小。

## 函数原型

所属类型：[`asc::random_bijection`](random_bijection.md)。

```cpp
// asc::random_bijection 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr Index size() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `Index` | 返回一一映射覆盖的有限索引域大小。 |

## 约束说明

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
