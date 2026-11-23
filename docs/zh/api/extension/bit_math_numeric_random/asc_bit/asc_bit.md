# 头文件asc/bit

提供无符号32位和64位整数的位反转、掩码生成、位域提取与插入操作

## 使用方式

```cpp
#include <asc/bit>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::bit_reverse](bit_reverse.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::bitfield_extract](bitfield_extract.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::bitfield_insert](bitfield_insert.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::bitmask](bitmask.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |

## 公共规则

仅支持 `asc::std::uint32_t`、`asc::std::uint64_t` 及同型别名，不支持的模板类型不参与重载。位编号从最低有效位 0 开始，与内存字节序无关。插入的两个值参数共同推导同一类型；显式指定类型时遵循普通值参数转换规则。

三个位域函数使用相同的合法区间判定。非法区间与零宽时，提取和掩码返回零，插入返回原目标值；合法全宽分别返回原值、源值和全一掩码。Host、SIMT 线程和 SIMD 核的标量代码在 C++17/20 下遵守相同规则，所有函数均为 `constexpr`、`noexcept`。

全位反转镜像每个位的位置，字节交换以字节为单位，循环移位保持位的循环次序。

[边界行为与迁移说明](../../../../../release/bit_changes.md)
