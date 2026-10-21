# asc::std::iswctype

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

头文件路径为：`<asc/std/cwctype>`。

`asc::std::iswctype`按当前支持的C区域设置规则分类输入字符。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cwctype`](https://en.cppreference.com/w/cpp/header/cwctype)。

## 函数原型

```cpp
namespace asc::std {
int iswctype(wint_t value, wctype_t descriptor) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待分类的宽字符（wint_t）；取值须可表示为宽字符或等于WEOF，等于WEOF时结果为0。 |
| `descriptor` | 输入 | 字符分类描述符（wctype_t），由wctype取得；指定参与判断的分类类别（如字母、数字、空白）。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `int` | 字符满足接口名称所指分类时返回非零值，否则返回零。 |

## 约束说明

- descriptor须来自同一区域设置下wctype成功返回的非零描述符；区域设置变更后重新取得描述符。不得把未知名称返回的0当作有效描述符。

- Host行为由系统`<cwctype>`实现，受当前C语言区域设置影响。
- Device的宽字符分类及大小写转换固定使用C locale。
- Host提供完整接口，设备端仅提供C语言区域设置相关接口。

## 调用示例

以下Host示例使用具体输入，并检查结果。

```cpp
#include <asc/std/cwctype>

bool example()
{
    const auto descriptor = asc::std::wctype("alpha");
    return descriptor != 0 && asc::std::iswctype(L'A', descriptor) != 0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwctype.md)
