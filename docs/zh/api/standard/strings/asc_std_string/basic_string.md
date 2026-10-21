# asc::std::basic_string

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

`asc::std::basic_string`拥有并管理连续字符序列。

标准语义参考：[cppreference `string`](https://en.cppreference.com/w/cpp/header/string)。

## 声明

```cpp
namespace asc::std {
template<class CharT, class Traits, class Allocator> class basic_string;
} // namespace asc::std
```

## 约束说明

- 以空字符结尾的输入可以来自本对象的字符存储，包括自身完整字符串或后缀。追加在需要扩容时保留源位置，字符指针赋值先读取源长度再修改内容；操作完成后重新取得因重分配失效的外部借用指针。
- 新长度加终止空字符所需空间必须可表示；无法表示时调用terminate，分配器操作仍须满足本类型的非抛出使用域。

- basic_string<char,Traits,A>显式allocator构造。
- 来自以空字符结尾 const CharT* 指针的赋值（operator=(const CharT*)，覆盖原内容后追加）；拷贝与移动赋值不交付。
- plain/local字符来源的append/push_back/clear。
- size/capacity/data/c_str/迭代/索引与析构。
- 仅容量充足和不抛出异常域。

## SIMT工具链验证边界

在CANN 9.2.0-beta.2、BiSheng 15.0.5（编译器指纹`c4866a4d…f84c6a`）的
纯SIMT `-O3`配置下，组合长字符串、局部arena和多次自身或后缀别名操作的单kernel
综合回归尚未通过。原C++17载荷已完成编译，但真机发生设备地址访问故障
（设备错误355；日志记录GM地址超过48位）；目前尚未唯一定位到某个成员函数，
也未证明所有局部arena均受影响。

当前分阶段回归将长字符串对象和arena放在GM中，并将无分配的局部短字符串优化
（SSO）场景作为独立阶段。支持表和局部SSO结果不表示任意局部arena组合已经通过；
这类组合须在目标工具链和运行域单独验证。具体通过范围以选定产品版本的完整验证
记录为准，分阶段结果不表示原单kernel形态已恢复。详见[B027运行期验证说明](../../../../../../test/support/README.md#b027完整语义的simt分阶段夹具)。

## 调用示例

以下Host示例使用显式分配器，并在字符串存活期间观察自身来源操作。

```cpp
#include <memory>
#include <asc/std/string>

bool example()
{
    ::std::allocator<char> allocator;
    using S = asc::std::basic_string<char, asc::std::char_traits<char>, ::std::allocator<char>>;
    S value("abcdefghijklmnopqrstuvwx", allocator);
    value.append(value.data());
    if (value.size() != 48) return false;
    value = value.c_str();
    if (value.size() != 48) return false;
    value = value.data() + 1;
    return value.size() == 47 && value.front() == 'b' && value.back() == 'x';
}
```

## 关联API

- [本头文件的接口列表](asc_std_string.md)
