# asc::std::launder

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

头文件路径为：`<asc/std/memory>`、`<asc/std/new>`。

`asc::std::launder` 在对象生命周期转换后取得可用于访问新对象的指针。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

### 原型 1

```cpp
template<class T> constexpr T* asc::std::launder(T* pointer) noexcept;
```

此原型对应头文件：`<asc/std/new>`。

### 原型 2

```cpp
template<class T> [[nodiscard]] constexpr T* asc::std::launder(T* pointer) noexcept;
```

此原型对应头文件：`<asc/std/memory>`。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 被构造、销毁或管理的对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“在对象生命周期转换后取得可用于访问新对象的指针”所需的数据地址；可访问范围和生命周期须满足约束。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 被构造、销毁或管理的对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“在对象生命周期转换后取得可用于访问新对象的指针”所需的数据地址；可访问范围和生命周期须满足约束。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `T *` | 返回指向相同存储地址中当前活动对象的指针。 |
| 原型 2 | `T *` | 返回指向相同存储地址中当前活动对象的指针。 |

## 约束说明

- 提供 placement 对象生命周期和无动态分配的词汇接口
- 存储由调用方提供并满足对齐要求
- 当回滚会引发异常时，Device 侧相关操作必须不抛出异常

## 调用示例

以下 Host 片段使用有效对象或对齐存储；构造后的对象在示例末尾销毁。

```cpp
#include <asc/std/new>

decltype(auto) example()
{
    int value = 3;
    return asc::std::launder(&value);
}
```
