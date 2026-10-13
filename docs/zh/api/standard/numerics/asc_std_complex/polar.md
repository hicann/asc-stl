# asc::std::polar

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

`asc::std::polar` 由模长与幅角构造复数。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

```cpp
template<class T> complex<T> asc::std::polar(const T& radius, const T& angle = T()) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 模长、幅角与返回复数的成分值类型，须为浮点类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `radius` | 输入 | 复数的模长（非负实数，无量纲）。 |
| `angle` | 输入 | 复数的幅角（角度量，单位为弧度）；省略时取 0。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `complex<T>` | 返回由给定模长和幅角构造的复数。 |

## 约束说明

- 仅提供页面声明的 float 或 `complex<float>` 运算
- 接口可用性取决于相应的 float 数学能力

## 调用示例

以下 Host 片段使用具体对象展示接口调用。

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    return asc::std::polar(1.0f, 0.5f);
}
```
