# asc::std::wctype_t

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

`asc::std::wctype_t`标识当前ABI对应的时间、字符转换或宽字符类型。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cwctype`](https://en.cppreference.com/w/cpp/header/cwctype)。

## 声明

Host保留系统类型身份：

```cpp
namespace asc::std {
using wctype_t = ::std::wctype_t;
}
```

Device使用无符号整数表示：

```cpp
namespace asc::std {
using wctype_t = unsigned int;
}
```

## 约束说明

- Host行为由系统`<cwctype>`实现，受当前C语言区域设置影响。
- Device的宽字符分类及大小写转换固定使用C locale。
- Host提供完整接口，设备端仅提供C语言区域设置相关接口。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/cwctype>

bool example()
{
    asc::std::wctype_t category = asc::std::wctype("digit");
    return asc::std::iswctype(L'7', category) != 0 && asc::std::iswctype(L'A', category) == 0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwctype.md)
