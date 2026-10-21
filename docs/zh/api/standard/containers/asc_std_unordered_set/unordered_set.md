# asc::std::unordered_set

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

头文件路径为：`<asc/std/unordered_set>`。

`asc::std::unordered_set`按哈希桶组织唯一键。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `unordered_set`](https://en.cppreference.com/w/cpp/header/unordered_set)。

## 声明

```cpp
namespace asc::std {
template<class Key, class Hash, class Equal, class Allocator> class unordered_set;
} // namespace asc::std
```

## 约束说明

- Host及AI Core SIMT编程下unordered_set<Key,Hash,Equal,A>显式GM arena。
- empty/size/bucket_count/begin/end/insert/find/count/clear。
- allocator回绑桶数组并在默认负载阈值上自动rehash。
- 碰撞链、重复键拒绝、rehash节点地址稳定、移动后旧迭代器有效与析构。
- 仅容量充足和不抛出异常域。
- Host和AI Core SIMT编程。
- `Hash`和`Equal`须可默认构造、复制，并能在调用位置处理相应键；本容器要求这些调用不抛出异常。`Equal`须构成键的等价关系，且`Equal(a, b)`成立时`Hash(a)`与`Hash(b)`必须相同。
- 只对参与相等判断的键值计算哈希；若键含填充、被相等判断忽略的缓存字段或非平凡状态，须显式提供合适的`Hash`。泛型对象字节回退的条件见[hash说明](../../utilities/asc_std_bitset/hash.md)。
- 键位于容器期间，不得修改所选`Hash`或`Equal`依赖的内容；哈希值相同的不同键由`Equal`进一步区分。

## 调用示例

以下Host示例使用两个`id`相同、`cache`不同的相等键；自定义哈希只处理参与相等判断的`id`。

```cpp
#include <asc/memory>
#include <asc/std/functional>
#include <asc/std/unordered_set>

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

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    const example_key first{7, 1};
    const example_key second{7, 99};
    const example_hash key_hash;
    using allocator = asc::arena_allocator<example_key>;
    using set_type = asc::std::unordered_set<example_key, example_hash, example_equal, allocator>;
    set_type values(allocator{arena});
    const auto inserted = values.insert(first);
    const auto duplicate = values.insert(second);
    const auto found = values.find(second);
    return first == second && first.cache != second.cache && key_hash(first) == key_hash(second)
        && inserted.second && !duplicate.second && values.size() == 1 && found != values.end()
        && found->id == 7 && found->cache == first.cache;
}
```

## 关联API

- [本头文件的接口列表](asc_std_unordered_set.md)
