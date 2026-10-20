# asc::std::inplace_vector::`operator=`

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

`asc::std::inplace_vector::operator=`按所选赋值重载更新对象，并返回规定的结果。

该接口支持Host和Device，均限于本页列出的非抛出操作。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

所属类型：[`asc::std::inplace_vector`](inplace_vector.md)。

### 原型1

```cpp
// asc::std::inplace_vector 类内的声明节选；模板形参和其他成员由所属类提供。
inplace_vector<T, Capacity>& operator=(const inplace_vector<T, Capacity>& other);
```

### 原型2

```cpp
// asc::std::inplace_vector 类内的声明节选；模板形参和其他成员由所属类提供。
inplace_vector<T, Capacity>& operator=(inplace_vector<T, Capacity>&& other);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `inplace_vector<T, Capacity> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型2 | `inplace_vector<T, Capacity> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 元素保存在固定容量的对象内存中，不进行动态分配。
- `try_`插入在容量不足时返回空结果；`unchecked_`插入要求调用前仍有容量。
- Host提供完整接口，设备端仅提供不抛出异常的接口。

## 调用示例

以下Host片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/inplace_vector>

void example(asc::std::inplace_vector<int, 8>& target, const asc::std::inplace_vector<int, 8>& source)
{
    target = source;
}
```

## 关联API

- [`asc::std::inplace_vector`](inplace_vector.md)
- [本头文件的接口列表](asc_std_inplace_vector.md)
