# asc::std::hash

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

头文件路径为：`<asc/std/bitset>`、`<asc/std/functional>`、`<asc/std/variant>`。

`asc::std::hash<T>`提供返回`size_t`的哈希函数对象。已有算术、指针、枚举及其它值类型特化按各自的专用规则处理；主模板还保留了非枚举类型的对象字节回退。使用回退为容器键计算哈希时，须满足下述对象表示与相等关系条件；“可调用”本身不保证满足键的哈希要求。

标准语义参考：[cppreference `hash`](https://en.cppreference.com/w/cpp/utility/hash)。

## 声明

### 原型1

```cpp
namespace asc::std {
template<class T> struct hash;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/functional>`。

### 原型2

```cpp
namespace asc::std {
template<class... Types> struct hash<asc::std::variant<Types...>>;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/variant>`。

### 原型3

```cpp
namespace asc::std {
template<size_t Size> struct hash<asc::std::bitset<Size>>;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/bitset>`。

## 约束说明

- 对容器所用的键相等关系，若`Equal(a, b)`为`true`，必须有`Hash(a) == Hash(b)`；不相等的键允许哈希碰撞。选用自定义相等关系时，哈希也必须与它一致。
- 没有对应特化的非枚举主模板按全部对象字节取哈希。这是保留的产品扩展，不表示任意用户类型都自动满足标准Hash要求。只有全部被读取字节均确定、且每对等价键的对象表示相同的域，才可将此回退作为键哈希使用；仅可平凡复制并不足够。
- 键含可能变化的填充字节、相等判断忽略的字段，或具有非平凡对象状态时，须提供按值语义计算的自定义哈希。可为无序容器显式指定`Hash`，或为用户类型提供与其相等关系一致的哈希特化；调用方不能期待回退自动识别这些字段。
- 枚举主模板按底层整型取哈希；已提供的算术、指针及`nullptr_t`特化按对应声明调用，不应把上述回退规则套用到已有特化的处理路径。
- `variant<Types...>`特化合成活跃备选值的哈希及索引；`valueless_by_exception`状态下使用固定的空备选哨兵值参与合成。每个备选值的哈希也须与其相等判断一致。备选类型的哈希可调用，不等于已经满足这一语义要求。
- `bitset<Size>`特化按位序列取哈希，调用为`constexpr`且不抛出异常。

## 调用示例

以下Host示例使用两个`id`相同、`cache`不同的相等键；自定义哈希只处理参与相等判断的`id`。

```cpp
#include <asc/std/bitset>
#include <asc/std/functional>
#include <asc/std/type_traits>

struct example_key {
    int id;
    int cache;
    friend bool operator==(const example_key& left, const example_key& right) noexcept
    {
        return left.id == right.id;
    }
};

struct example_hash {
    asc::std::size_t operator()(const example_key& value) const noexcept
    {
        return asc::std::hash<int>{}(value.id);
    }
};

struct example_equal {
    bool operator()(const example_key& left, const example_key& right) const noexcept
    {
        return left == right;
    }
};

static_assert(asc::std::is_trivially_copyable_v<example_key>);

bool example_key_hash()
{
    const example_key first{7, 1};
    const example_key second{7, 99};
    const example_hash key_hash;
    return first == second && first.cache != second.cache
        && key_hash(first) == key_hash(second);
}

bool example()
{
    const asc::std::bitset<8> first_bits(5), second_bits(5);
    const asc::std::hash<asc::std::bitset<8>> bits_hash;
    return first_bits == second_bits && bits_hash(first_bits) == bits_hash(second_bits)
        && example_key_hash();
}
```

## 关联API

- [unordered_map的哈希及相等约束](../../containers/asc_std_unordered_map/unordered_map.md)
- [unordered_set的哈希及相等约束](../../containers/asc_std_unordered_set/unordered_set.md)
- [本头文件的接口列表](asc_std_bitset.md)
