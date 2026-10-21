# asc::std::queue::front

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

`asc::std::queue::front`返回首元素的引用；对象必须非空。

标准语义参考：[cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue)。

## 函数原型

所属类型：[`asc::std::queue`](queue.md)。

### 原型1

```cpp
// asc::std::queue 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr const_reference front() const;
```

### 原型2

```cpp
// asc::std::queue 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr reference front();
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `const_reference` | 返回首元素的引用。 |
| 原型2 | `reference` | 返回首元素的引用。 |

## 约束说明

- 调用前容器必须非空。
- 返回引用借用底层元素；原容器及元素须覆盖引用使用期，修改失效规则遵循Container。
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
    return values.front() == 1;
}
```

## 关联API

- [`asc::std::queue`](queue.md)
- [本头文件的接口列表](asc_std_queue.md)
