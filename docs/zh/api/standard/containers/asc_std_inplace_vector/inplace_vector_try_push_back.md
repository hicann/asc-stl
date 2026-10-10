# asc::std::inplace_vector::try_push_back

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

头文件路径为：`<asc/std/inplace_vector>`。

`asc::std::inplace_vector::try_push_back` 尝试在容器末尾追加 `value`。容量充足时构造新元素并返回其引用；容器已满时返回空结果，容器内容保持不变。

该接口的可用位置为 Host（完整接口）、Device（非抛出子集）。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

### 原型 1

```cpp
optional<reference> asc::std::inplace_vector::try_push_back(T&& value);
```

### 原型 2

```cpp
optional<reference> asc::std::inplace_vector::try_push_back(const T& value);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待复制或移动到容器末尾的元素。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待复制或移动到容器末尾的元素。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `optional<reference>` | 插入成功时返回包含新元素引用的 optional；容量不足时返回空 optional。 |
| 原型 2 | `optional<reference>` | 插入成功时返回包含新元素引用的 optional；容量不足时返回空 optional。 |

## 约束说明

- value 必须能够复制或移动构造为 T
- Device 侧所选构造操作必须不抛出异常
- 插入成功后返回的引用只在对应元素未被移除且容器仍然存活时有效。

## 调用示例

以下示例展示插入成功和容量耗尽两种结果，并检查容器最终状态。

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 2> values;
    const auto first = values.try_push_back(7);
    const auto second = values.try_push_back(9);
    const auto overflow = values.try_push_back(11);

    // 前两次插入成功；达到固定容量后，第三次插入返回空结果。
    return first.has_value() && *first == 7
        && second.has_value() && *second == 9
        && !overflow.has_value()
        && values.size() == 2;
}
```
