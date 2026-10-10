# asc::std::as_bytes

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

头文件路径为：`<asc/std/span>`。

`asc::std::as_bytes` 把 span 转换为只读字节视图而不拥有存储。

标准语义参考：[cppreference `span`](https://en.cppreference.com/w/cpp/header/span)。

## 函数原型

```cpp
template<class T, size_t Extent> auto asc::std::as_bytes(span<T, Extent> value) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Extent` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `auto` | 返回观察同一存储的非拥有字节视图；原 span 不转移所有权。 |

## 约束说明

- 支持固定或动态 extent，以及指针、数组和兼容的连续范围
- AI Core SIMD 编程 中仅当元素指针或范围可表示为标准普通指针时才可使用，不提供非标准 GM/UB 指针重载

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/span>

decltype(auto) example()
{
    int values[2] = {1, 2};
    asc::std::span<int> view(values, 2);
    return asc::std::as_bytes(view);
}
```
