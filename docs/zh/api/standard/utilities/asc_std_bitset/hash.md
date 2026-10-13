# asc::std::hash

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

头文件路径为：`<asc/std/bitset>`、`<asc/std/functional>`、`<asc/std/variant>`。

`asc::std::hash<T>` 为已交付的算术、指针、位集合和其他明确支持的值类型提供哈希函数对象；是否存在相应特化以所选 `T` 的声明为准。

标准语义参考：[cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset)。

## 声明

### 原型 1

```cpp
template<class T> struct asc::std::hash
```

此原型对应头文件：`<asc/std/functional>`。

### 原型 2

```cpp
template<class... Types> struct asc::std::hash<asc::std::variant<Types...>>
```

此原型对应头文件：`<asc/std/variant>`。

### 原型 3

```cpp
template<size_t Size> struct asc::std::hash<asc::std::bitset<Size>>
```

此原型对应头文件：`<asc/std/bitset>`。

## 约束说明

- 主模板对枚举类型按底层整型取哈希，其余类型按对象字节序列取哈希；对所选 `T` 是否存在可用特化以实际声明为准
- 提供算术类型、枚举类型、指针类型和 nullptr_t 的 hash 特化，各 operator() 均为非抛出并返回 size_t
- variant<Types...> 特化要求各备选类型可哈希，将活跃备选值的哈希与其索引的哈希合成，valueless_by_exception 时取固定哨兵值
- bitset<Size> 特化按位序列取哈希，operator() 为 constexpr、非抛出并返回 size_t

## 调用示例

以下片段用具体模板实参实例化类型；实际对象仍须满足本页构造与生命周期约束。

```cpp
#include <asc/std/bitset>

void use_type()
{
    using selected = asc::std::hash<asc::std::bitset<8>>;
    (void)sizeof(selected);
}
```
