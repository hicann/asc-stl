# asc::std::basic_string::reserve

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

头文件路径为：`<asc/std/string>`。

`asc::std::basic_string::reserve`请求至少可容纳指定数量元素的存储容量。

标准语义参考：[cppreference `string`](https://en.cppreference.com/w/cpp/header/string)。

## 函数原型

所属类型：[`asc::std::basic_string`](basic_string.md)。

```cpp
// asc::std::basic_string 类内的声明节选；模板形参和其他成员由所属类提供。
void reserve(size_type requested);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `requested` | 输入 | 请求的最低字符容量；requested + 1须能由size_type表示，并能由分配器分配。成功返回后capacity()不小于requested。 |

## 返回值说明

无返回值。

## 约束说明

- 纯SIMT使用还须遵循所属类型的[工具链验证边界](basic_string.md#simt工具链验证边界)。

- 分配器须提供至少requested + 1个字符的存储，额外1个位置用于终止空字符；分配返回空指针时调用terminate，不保证以异常返回。requested + 1无法表示时也调用terminate。

- basic_string<char,Traits,A>显式allocator构造。
- plain/local字符来源的append/push_back/clear。
- size/capacity/data/c_str/迭代/索引与析构。
- 仅容量充足和不抛出异常域。

## 调用示例

以下Host示例给出具体输入并检查结果；底层对象与存储在检查期间仍有效。

```cpp
#include <memory>
#include <asc/std/string>

bool example()
{
    ::std::allocator<char> allocator;
    asc::std::basic_string<char, asc::std::char_traits<char>, ::std::allocator<char>> value("abc", allocator);
    value.reserve(32);
    return value.capacity() >= 32 && value.size() == 3 && value[0] == 'a' && value.c_str()[3] == '\0';
}
```

## 关联API

- [`asc::std::basic_string`](basic_string.md)
- [本头文件的接口列表](asc_std_string.md)
