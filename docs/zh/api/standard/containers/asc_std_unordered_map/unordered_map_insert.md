# asc::std::unordered_map::insert

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

头文件路径为：`<asc/std/unordered_map>`。

`asc::std::unordered_map::insert`在指定位置插入元素并按容器规则更新迭代器。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `unordered_map`](https://en.cppreference.com/w/cpp/header/unordered_map)。

## 函数原型

所属类型：[`asc::std::unordered_map`](unordered_map.md)。

### 原型1

```cpp
// asc::std::unordered_map 类内的声明节选；模板形参和其他成员由所属类提供。
pair<iterator, bool> insert(const value_type& value);
```

### 原型2

```cpp
// asc::std::unordered_map 类内的声明节选；模板形参和其他成员由所属类提供。
pair<iterator, bool> insert(value_type&& value);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待插入的键值对（使用容器自己的value_type，具有first键与second值成员）；按键的哈希值定位目标桶，键不存在时复制构造新元素，键已存在时不插入。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待插入的键值对；按键的哈希值定位目标桶，键不存在时以移动方式构造新元素，键已存在时不插入且源对象不被消耗。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `pair<iterator, bool>` | 返回插入位置及是否新增元素的信息；具体结果形式由所选原型确定。 |
| 原型2 | `pair<iterator, bool>` | 返回插入位置及是否新增元素的信息；具体结果形式由所选原型确定。 |

## 约束说明

- Host及AI Core SIMT编程下unordered_map<Key,T,Hash,Equal,A>显式GM arena。
- empty/size/bucket_count/begin/end/insert/find/count/`operator[]`/clear。
- allocator回绑桶数组并在默认负载阈值上自动rehash。
- 碰撞链、重复键拒绝、rehash节点地址稳定、移动后旧迭代器有效与析构。
- 仅容量充足和不抛出异常域。
- Host和AI Core SIMT编程。
- 本操作使用容器选定的`Hash`及`Equal`定位键；等价键必须产生相同哈希，且键相关状态须保持有效。自定义键、忽略字段和对象字节回退的要求见[unordered_map约束](unordered_map.md)。

## 调用示例

以下Host片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/unordered_map>
#include <memory>
#include <functional>
#include <utility>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = example_allocator<U>;
    };
    example_allocator() = default;
    template <class U>
    example_allocator(const example_allocator<U>&) noexcept
    {}
};

bool example()
{
    using sequence = asc::std::unordered_map<int, int, ::std::hash<int>, ::std::equal_to<int>,
        example_allocator<::std::pair<const int, int>>>;
    sequence values(example_allocator<::std::pair<const int, int>>{});
    values.insert(typename sequence::value_type(7, 9));
    return values.size() == 1 && values.count(7) == 1 && values.find(7)->second == 9;
}
```

## 关联API

- [`asc::std::unordered_map`](unordered_map.md)
- [本头文件的接口列表](asc_std_unordered_map.md)
