# asc::std::common_type

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

头文件路径为：`<asc/std/type_traits>`。

`asc::std::common_type` 计算一组类型的公共值类型。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

### 原型 1

```cpp
template<class ...T> class asc::std::common_type
```

### 原型 2

```cpp
template<class T, class U, class V, class ...Rest> struct asc::std::common_type
```

### 原型 3

```cpp
template<class T, class U> struct asc::std::common_type
```

### 原型 4

```cpp
template<class T> struct asc::std::common_type
```

## 约束说明

- 提供特征类以及标准的 _t、_v 辅助形式

## 调用示例

以下 Host 片段用具体类型实参和 `static_assert` 验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // ::type 与 _t 都得到条件表达式的公共类型
    static_assert(asc::std::is_same_v<asc::std::common_type<int, long>::type, long>);
    static_assert(asc::std::is_same_v<asc::std::common_type_t<int, double>, double>);
    // 反例：公共类型不取第一个实参
    static_assert(!asc::std::is_same_v<asc::std::common_type_t<int, long>, int>);
}
```
