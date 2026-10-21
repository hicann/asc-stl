# asc::std::inplace_vector::try_emplace_back

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

头文件路径为：`<asc/std/inplace_vector>`。

`asc::std::inplace_vector::try_emplace_back`尝试在固定容量容器尾部原位构造元素，成功时返回其引用。

该接口支持Host和Device，均限于本页列出的非抛出操作。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

所属类型：[`inplace_vector<T, Capacity>`](inplace_vector.md)。以下为类内声明，类型别名及模板形参由所属类提供。

### 原型1

```cpp
template<class... Args>
constexpr optional<reference> try_emplace_back(Args&&... args);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args` | 新元素构造实参类型包；须能以对应值类别构造T。 |

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `args` | 输入 | 转发给T构造函数的实参；构造期间须有效，T保存的借用关系另须满足其生存期。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `optional<reference>` | 有容量时借用新元素；容量已满时为空，不构造或消耗来源。 |

## 约束说明

- 容量不足时返回空optional，不构造新元素；有容量时返回借用新元素的optional<T&>。
- 非空结果借用的元素必须继续存活；元素构造要求仍须满足。
- 元素的对应构造、赋值和析构须满足非抛出使用域；constexpr声明不保证任意T和语言模式都能常量求值。

## 调用示例

以下Host片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/inplace_vector>

decltype(auto) example(asc::std::inplace_vector<int, 8>& values)
{
    return values.try_emplace_back(7);
}
```

## 关联API

- [`asc::std::inplace_vector`](inplace_vector.md)
- [本头文件的接口列表](asc_std_inplace_vector.md)
