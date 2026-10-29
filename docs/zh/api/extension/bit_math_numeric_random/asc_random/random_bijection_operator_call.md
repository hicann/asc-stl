# asc::random_bijection::`operator()`

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

`asc::random_bijection::operator()`把输入索引映射为有限域内唯一的置换索引。

## 函数原型

所属类型：[`asc::random_bijection`](random_bijection.md)。

```cpp
// asc::random_bijection 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr Index operator()(Index index) const noexcept;
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 被映射的索引，须属于[0, size)；结果在同一有限域内。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `Index` | 返回该索引对应的置换索引；同一对象对相同索引返回相同值，不推进随机引擎。 |

## 约束说明

- 本页类型、别名或字段只描述所保存的随机状态或置换信息；观察它不调用Runtime、不访问共享全局状态。
- 映射调用须使用非空有限域和域内索引；生成器调用的种子、计数器要求见其成员页。

## 调用示例

以下Host片段以具体值演示调用；输入须满足本页约束。

```cpp
#include <asc/random>
#include <asc/std/type_traits>

bool example()
{
    asc::pcg64 generator(9);
    asc::random_bijection<unsigned long long> mapping(17, generator);
    bool seen[17] = {};
    for (asc::random_bijection<unsigned long long>::index_type index = 0; index < 17; ++index) {
        const auto output = mapping(index);
        if (output >= 17 || seen[output]) return false;
        seen[output] = true;
    }
    for (bool present : seen) { if (!present) return false; }
    return mapping.size() == 17;
}
```

## 关联API

- [`asc::random_bijection`](random_bijection.md)
- [本头文件的接口列表](asc_random.md)
