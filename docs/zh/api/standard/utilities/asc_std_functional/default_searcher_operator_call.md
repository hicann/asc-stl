# asc::std::default_searcher::`operator()`

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

头文件路径为：`<asc/std/functional>`。

`asc::std::default_searcher::operator()`按`default_searcher`的可用运算符规则处理当前对象及操作数。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

所属类型：[`asc::std::default_searcher`](default_searcher.md)。

```cpp
// asc::std::default_searcher 类内的声明节选；模板形参和其他成员由所属类提供。
template<class ForwardIterator2> asc::std::pair<ForwardIterator2, ForwardIterator2> operator()(ForwardIterator2 first, ForwardIterator2 last) const;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::pair<ForwardIterator2, ForwardIterator2>` | 返回匹配子序列的起止迭代器；未找到时返回结束位置。 |

## 约束说明

- 模式迭代器指定有效的前向范围；该范围的底层存储须在搜索器使用期间保持有效。谓词及被搜索范围须满足比较和迭代要求，用户谓词自身是否分配由其实现决定。

## 调用示例

以下Host片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/functional>

decltype(auto) example(int* pattern, int* values)
{
    asc::std::default_searcher<int*> searcher(pattern, pattern + 2);
    return searcher(values, values + 4);
}

bool verify_example()
{
    int pattern[] = {2, 3};
    int values[] = {1, 2, 3, 4};
    const auto result = example(pattern, values);
    return result.first == values + 1 && result.second == values + 3;
}
```

## 关联API

- [`asc::std::default_searcher`](default_searcher.md)
- [本头文件的接口列表](asc_std_functional.md)
