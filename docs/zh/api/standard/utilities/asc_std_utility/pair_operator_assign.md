# asc::std::pair::`operator=`

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

头文件路径为：`<asc/std/utility>`。

`asc::std::pair::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

以下为`pair<T1, T2>`类内的**调用形态摘要**，省略实现选择器。各形态只在对应元素可构造或可赋值时参与；默认/值构造是否explicit按元素的隐式转换能力分层，不能把摘要合并为无条件重载定义。

```cpp
pair<T1, T2>& operator=(const pair<T1, T2>& other) = default;
```

```cpp
pair<T1, T2>& operator=(pair<T1, T2>&& other) = default;
```

```cpp
template<class U1, class U2> constexpr pair<T1, T2>& operator=(pair<U1, U2>&& other) noexcept(is_nothrow_assignable_v<T1&, U1>&& is_nothrow_assignable_v<T2&, U2>);
```

```cpp
template<class U1, class U2> constexpr pair<T1, T2>& operator=(const pair<U1, U2>& other) noexcept(is_nothrow_assignable_v<T1&, const U1&>&& is_nothrow_assignable_v<T2&, const U2&>);
```

```cpp
template<class U1, class U2> constexpr const pair<T1, T2>& operator=(pair<U1, U2>&& other) const noexcept(is_nothrow_assignable_v<const T1&, U1>&& is_nothrow_assignable_v<const T2&, U2>);
```

```cpp
template<class U1, class U2> constexpr const pair<T1, T2>& operator=(const pair<U1, U2>& other) const noexcept(is_nothrow_assignable_v<const T1&, const U1&>&& is_nothrow_assignable_v<const T2&, const U2&>);
```

```cpp
template<class PairLike> constexpr pair<T1, T2>& operator=(PairLike&& other);
```

## 参数说明

摘要省略的选择参数已转为本页公开参与条件，调用方按普通实参调用。

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

### 原型6的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

### 原型7的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `PairLike` | 提供两个元素及相应get访问的pair-like类型，两个元素须可用于对应构造或赋值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型2 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型3 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型4 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型5 | `const pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型6 | `const pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型7 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 跨类型赋值要求两个目标元素分别可从对应来源赋值；const成员形式还要求const元素表达式可赋值。泛型pair-like来源须具有两个可通过get访问的元素，且不是pair特化；引用元素赋值作用于所引用对象。

- 异常规格以对应声明为准；Device侧使用的元素操作须不抛出异常。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/utility>

void example()
{
    asc::std::pair<int, int> left(1, 2), right(3, 4);
    left = right;
}
```

## 关联API

- [`asc::std::pair`](pair.md)
- [本头文件的接口列表](asc_std_utility.md)
