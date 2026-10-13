# asc::std::operator!=（array 重载）（函数模板）

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

头文件路径为：`<asc/std/array>`、`<asc/std/optional>`、`<asc/std/random>`、`<asc/std/string_view>`、`<asc/std/variant>`。

`asc::std::operator!=` 比较两个对象是否不相等。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 函数原型

### 原型 1

```cpp
template<class ...Types> [[nodiscard]] constexpr bool asc::std::operator!=(const variant<Types...>& left, const variant<Types...>& right);
```

此原型对应头文件：`<asc/std/variant>`。

### 原型 2

```cpp
template<class T, class U> constexpr bool asc::std::operator!=(const T& value, const asc::std::optional<U>& optional_value);
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 3

```cpp
template<class T, class U> constexpr bool asc::std::operator!=(const asc::std::optional<T>& left, const asc::std::optional<U>& right);
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 4

```cpp
template<class T, class U> constexpr bool asc::std::operator!=(const asc::std::optional<T>& optional_value, const U& value);
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 5

```cpp
template<class T> constexpr bool asc::std::operator!=(asc::std::nullopt_t, const asc::std::optional<T>& value) noexcept;
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 6

```cpp
template<class T> constexpr bool asc::std::operator!=(const asc::std::optional<T>& value, asc::std::nullopt_t) noexcept;
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 7

```cpp
template<class UIntType, size_t WordSize, size_t WordCount, size_t NumRounds, UIntType... Constants> constexpr bool asc::std::operator!=(const philox_engine<UIntType, WordSize, WordCount, NumRounds, Constants...>& left, const philox_engine<UIntType, WordSize, WordCount, NumRounds, Constants...>& right) noexcept;
```

此原型对应头文件：`<asc/std/random>`。

### 原型 8

```cpp
template<class T, size_t Size> [[nodiscard]] constexpr bool asc::std::operator!=(const array<T, Size>& left, const array<T, Size>& right);
```

此原型对应头文件：`<asc/std/array>`。

### 原型 9

```cpp
template<int T> [[nodiscard]] constexpr bool asc::std::operator!=(basic_string_view<CharT, Traits> left, type_identity_t<basic_string_view<CharT, Traits>> right) noexcept;
```

此原型对应头文件：`<asc/std/string_view>`。

### 原型 10

```cpp
template<unsigned int> [[nodiscard]] constexpr bool asc::std::operator!=(type_identity_t<basic_string_view<CharT, Traits>> left, basic_string_view<CharT, Traits> right) noexcept;
```

此原型对应头文件：`<asc/std/string_view>`。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Types` | variant 的备选项类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与不相等比较的左侧 variant；两侧处于不同备选项、或同备选项但值不等时结果为 true。 |
| `right` | 输入 | 参与不相等比较的右侧 variant。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 左侧比较值的类型，须可用 operator== 与 U 比较。 |
| `U` | 右侧 optional 所含值的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 与 optional 比较的普通值；optional 不含值或所含值与之不等时结果为 true。 |
| `optional_value` | 输入 | 被比较的 optional 对象。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 左侧 optional 所含值的类型。 |
| `U` | 右侧 optional 所含值的类型，须可用 operator== 与 T 比较。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与比较的左侧 optional；一侧为空另一侧含值、或两侧都含值但不等时结果为 true。 |
| `right` | 输入 | 参与比较的右侧 optional。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 左侧 optional 所含值的类型。 |
| `U` | 右侧比较值的类型，须可用 operator== 与 T 比较。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `optional_value` | 输入 | 被比较的 optional 对象。 |
| `value` | 输入 | 与 optional 比较的普通值；optional 不含值或所含值与之不等时结果为 true。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | optional 所含值的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `未命名参数1` | 输入 | 原型中的无名形参，类型为 nullopt_t，实参写作 asc::std::nullopt；optional 含值时比较结果为 true。 |
| `value` | 输入 | 被比较的 optional 对象。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | optional 所含值的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被比较的 optional 对象。 |
| `未命名参数1` | 输入 | 原型中的无名形参，类型为 nullopt_t，实参写作 asc::std::nullopt；optional 含值时比较结果为 true。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UIntType` | 引擎生成的整数类型。 |
| `WordSize` | 每个字的位宽，编译期常量。 |
| `WordCount` | 状态包含的字数，编译期常量。 |
| `NumRounds` | 混合轮数，编译期常量。 |
| `Constants` | 引擎常数包，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与不相等比较的左侧 philox 引擎。 |
| `right` | 输入 | 参与不相等比较的右侧 philox 引擎；两侧内部状态不同时结果为 true。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 数组元素类型，两侧须一致，须支持 operator==。 |
| `Size` | 数组长度，编译期常量，两侧须相同。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与逐元素比较的左侧数组。 |
| `right` | 输入 | 参与逐元素比较的右侧数组；任一对应元素不相等时结果为 true。 |

### 原型 9 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 原型声明中的占位模板参数（声明写作 template<int T>）；实际的字符类型 CharT 与特征类型 Traits 由字符串视图操作数推导。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与不相等比较的左侧字符串视图。 |
| `right` | 输入 | 参与不相等比较的右侧字符串视图；长度不同或任一位置字符不同时结果为 true。 |

### 原型 10 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `未命名参数1` | 原型声明中的无名占位模板参数；实际的字符类型 CharT 与特征类型 Traits 由字符串视图操作数推导。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与不相等比较的左侧字符串视图。 |
| `right` | 输入 | 参与不相等比较的右侧字符串视图；长度不同或任一位置字符不同时结果为 true。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 2 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 3 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 4 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 5 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 6 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 7 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 8 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 9 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 10 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- Device 侧备选类型以及所选构造、赋值和交换操作必须不抛出异常
- index、operator*、emplace、swap 和 visit 仅提供非抛出路径
- T 必须是普通的非引用对象类型
- Host 遵循有效的 C++17 操作
- Device 侧构造、赋值、调用和交换所依赖的操作必须不抛出异常
- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式
- 不提供 SeedSequence、流式输入输出或共享全局状态
- 支持包括零在内的所有 N
- 成员函数和自由函数均不抛出异常
- 提供构造、迭代和除 at 外的访问接口，以及 remove_prefix、remove_suffix、swap、data、size、starts_with、ends_with 和非抛出的比较/查找接口
- AI Core SIMD 编程 仅支持 local 或 generic 地址空间的普通字符指针

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/array>

decltype(auto) example()
{
    asc::std::array<int, 2> left{{1, 2}};
    asc::std::array<int, 2> right{{1, 3}};
    return asc::std::operator!=(left, right);
}
```
