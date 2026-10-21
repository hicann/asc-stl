# asc::std::queue::queue

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

头文件路径为：`<asc/std/queue>`。

`asc::std::queue::queue`按本页所列构造形态初始化`queue`对象。

标准语义参考：[cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue)。

## 函数原型

所属类型：[`queue`](queue.md)。编译器生成的复制/移动特殊成员是否可用取决于Container及比较器；没有allocator或迭代器范围构造入口。

### 原型1

```cpp
constexpr queue() = default;
```

### 原型2

```cpp
constexpr explicit queue(const Container& container);
```

### 原型3

```cpp
constexpr explicit queue(Container&& container);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入 | 复制为底层存储的Container对象。 |

### 原型3的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入 | 移动为底层存储的Container对象；来源状态由其移动构造规则决定。 |

## 返回值说明

无返回值。

## 约束说明

- 默认形式要求Container可默认构造；Container来源形式要求对应复制或移动构造有效。
- Device使用的Container、元素操作及Compare须可在对应执行位置调用并满足其非抛出要求；Host的异常行为遵循所调用对象，未额外声明noexcept时不承诺不抛出。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <deque>
#include <asc/std/queue>

bool example()
{
    asc::std::queue<int, ::std::deque<int>> values;
    values.push(1);
    values.push(3);
    return values.size() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_queue.md)
