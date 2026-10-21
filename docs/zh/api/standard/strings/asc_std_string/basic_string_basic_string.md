# asc::std::basic_string::basic_string

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

`asc::std::basic_string::basic_string`按本页所列构造形态初始化`basic_string`对象。

标准语义参考：[cppreference `string`](https://en.cppreference.com/w/cpp/header/string)。

## 函数原型

### 原型1

```cpp
explicit basic_string(const Allocator& allocator) noexcept;
```

### 原型2

```cpp
basic_string(const CharT* pointer, const Allocator& allocator);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 待复制的源字符序列；无长度实参时须以零字符终止，有长度实参时至少包含指定数量的可读字符。调用复制字符，不取得源存储所有权。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

## 返回值说明

无返回值。

## 约束说明

- 纯SIMT使用还须遵循所属类型的[工具链验证边界](basic_string.md#simt工具链验证边界)。

- basic_string<char,Traits,A>显式allocator构造。
- plain/local字符来源的append/push_back/clear。
- size/capacity/data/c_str/迭代/索引与析构。
- 仅容量充足和不抛出异常域。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <memory>
#include <string>
#include <asc/std/string>

bool example()
{
    using string_type = asc::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>>;
    string_type text(::std::allocator<char>{});
    text += "hi";
    return text.size() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_string.md)
