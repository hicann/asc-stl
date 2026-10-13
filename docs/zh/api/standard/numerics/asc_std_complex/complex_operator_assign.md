# asc::std::complex::operator=

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

头文件路径为：`<asc/std/complex>`。

`asc::std::complex::operator=` 按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型 1

```cpp
constexpr complex<T>& asc::std::complex::operator=(complex<T>&& other) noexcept;
```

### 原型 2

```cpp
constexpr complex<T>& asc::std::complex::operator=(const complex<T>& other) noexcept;
```

### 原型 3

```cpp
constexpr complex<T>& asc::std::complex::operator=(const T& other) noexcept;
```

### 原型 4

```cpp
template<class U> complex<T>& asc::std::complex::operator=(const ::std::complex<U>& other) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `complex<T> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 2 | `complex<T> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 3 | `complex<T> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 4 | `complex<T> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 仅提供页面声明的 float 或 complex<float> 运算
- 接口可用性取决于相应的 float 数学能力

## 调用示例

以下 Host 片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/complex>

void example(asc::std::complex<float>& target, asc::std::complex<float>& source)
{
    target = static_cast<asc::std::complex<float>&&>(source);
}
```
