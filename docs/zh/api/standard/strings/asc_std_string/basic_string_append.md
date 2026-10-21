# asc::std::basic_string::append

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

`asc::std::basic_string::append`把字符或字符串内容追加到当前字符串末尾。

标准语义参考：[cppreference `string`](https://en.cppreference.com/w/cpp/header/string)。

## 函数原型

所属类型：[`asc::std::basic_string`](basic_string.md)。

```cpp
// asc::std::basic_string 类内的声明节选；模板形参和其他成员由所属类提供。
basic_string<CharT, Traits, Allocator>& append(const CharT* text);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `text` | 输入 | 待复制的源字符序列；无长度实参时须以零字符终止，有长度实参时至少包含指定数量的可读字符。调用复制字符，不取得源存储所有权。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `basic_string<CharT, Traits, Allocator> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |

## 约束说明

- 纯SIMT使用还须遵循所属类型的[工具链验证边界](basic_string.md#simt工具链验证边界)。

- 以空字符结尾的输入可以来自本对象的字符存储，包括自身完整字符串或后缀。追加在需要扩容时保留源位置，字符指针赋值先读取源长度再修改内容；操作完成后重新取得因重分配失效的外部借用指针。
- 新长度加终止空字符所需空间必须可表示；无法表示时调用terminate，分配器操作仍须满足本类型的非抛出使用域。

- basic_string<char,Traits,A>显式allocator构造。
- plain/local字符来源的append/push_back/clear。
- size/capacity/data/c_str/迭代/索引与析构。
- 仅容量充足和不抛出异常域。

## 调用示例

以下Host示例使用显式分配器，并在字符串存活期间观察自身来源操作。

```cpp
#include <memory>
#include <asc/std/string>

bool example()
{
    ::std::allocator<char> allocator;
    using S = asc::std::basic_string<char, asc::std::char_traits<char>, ::std::allocator<char>>;
    S value("abc", allocator);
    S& result = value.append(value.data());
    return &result == &value && value.size() == 6 && value[0] == 'a' && value[3] == 'a' && value.back() == 'c';
}
```

## 关联API

- [`asc::std::basic_string`](basic_string.md)
- [本头文件的接口列表](asc_std_string.md)
