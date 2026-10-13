# asc::std::mbstate_t

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

头文件路径为：`<asc/std/cuchar>`、`<asc/std/cwchar>`。

`asc::std::mbstate_t`标识当前ABI对应的时间、字符转换或宽字符类型。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cuchar`](https://en.cppreference.com/w/cpp/header/cuchar)。

## 声明

```cpp
namespace asc::std {
using mbstate_t = ::std::mbstate_t;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/cuchar>`、`<asc/std/cwchar>`。

## 约束说明

- Host使用系统多字节转换状态类型；首次转换前以`{}`初始化，并在同一字符序列的连续调用间保留对象。
- Device使用无状态单字节转换；`mbstate_t`保留用于兼容接口，不表示支持任意区域设置或多字节续接。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/cuchar>

bool example()
{
    asc::std::mbstate_t state{};
    char16_t result{};
    auto count = asc::std::mbrtoc16(&result, "A", 1, &state);
    return count == 1 && result == u'A';
}
```

## 关联API

- [本头文件的接口列表](asc_std_cuchar.md)
