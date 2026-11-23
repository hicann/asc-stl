# 头文件asc/functional

按值取极值、筛选输入及查询运算性质。最低C++17，同时支持C++20。

## 使用方式

```cpp
#include <asc/functional>
```

## API列表（17项）

| API | 类型 |
| --- | --- |
| [asc::maximum](maximum.md) | 类模板 |
| [asc::maximum::operator()](maximum_operator_call.md) | 成员函数 |
| [asc::minimum](minimum.md) | 类模板 |
| [asc::minimum::operator()](minimum_operator_call.md) | 成员函数 |
| [asc::equal_to_value](equal_to_value.md) | 类模板 |
| [asc::equal_to_value::equal_to_value](equal_to_value_equal_to_value.md) | 成员函数 |
| [asc::equal_to_value::operator()](equal_to_value_operator_call.md) | 成员函数 |
| [asc::always_true](always_true.md) | 类 |
| [asc::always_true::operator()](always_true_operator_call.md) | 成员函数 |
| [asc::always_false](always_false.md) | 类 |
| [asc::always_false::operator()](always_false_operator_call.md) | 成员函数 |
| [asc::is_associative_v](is_associative_v.md) | 变量模板 |
| [asc::is_commutative_v](is_commutative_v.md) | 变量模板 |
| [asc::has_identity_element_v](has_identity_element_v.md) | 变量模板 |
| [asc::has_absorbing_element_v](has_absorbing_element_v.md) | 变量模板 |
| [asc::identity_element](identity_element.md) | 函数模板 |
| [asc::absorbing_element](absorbing_element.md) | 函数模板 |

## 运算支持表

以下对象均登记匹配T的指定类型形式及void透明形式。U为五种标准无符号整数，S为对应五种有符号整数，I为全部标准整数（含bool和字符类型，char8_t仅C++20）。M/L为T的最大值/最低值。

| 对象模板 | T | 结合律 | 交换律 | 单位元 | 吸收元 |
| --- | --- | --- | --- | --- | --- |
| `asc::std::plus` | U | A | A | 0 | — |
| `asc::std::multiplies` | U | B | B | 1 | 0 |
| `asc::std::plus` | S | false | false | 0 | — |
| `asc::std::multiplies` | S | false | false | 1 | 0 |
| `asc::std::bit_and` | U | true | true | M | 0 |
| `asc::std::bit_or` | U | true | true | 0 | M |
| `asc::std::bit_xor` | U | true | true | 0 | — |
| `asc::std::logical_and` | bool | true | true | true | false |
| `asc::std::logical_or` | bool | true | true | false | true |
| `asc::maximum` | I | true | true | L | M |
| `asc::minimum` | I | true | true | M | L |

P=decltype(+T{})为提升类型。A要求P无符号或M<=max(P)/2；B要求P无符号或M<=max(P)/M，界限按非负精确值比较，避免登记本身发生溢出。每个二元节点都转换回T；透明标准对象返回提升类型时也须显式转换。

F(a,b)=T(Operator{}(a,b))，输入按const左值读取。结合/交换要求全值域上的每个运算合法且封闭；单位元满足F(e,x)=F(x,e)=x，吸收元满足F(z,x)=F(x,z)=z，特殊元素可独立登记。结果按内建数值==比较。

表外、cv/ref、不匹配类型、宿主std的不同类型、浮点、低精度格式和用户类型均为false，不开放用户特化。false表示未提供保证；取值函数仅在相应has_*为true时可调用。性质不授权省略实参副作用。

maximum/minimum比较一次，等价取左，返回值；透明版以原类型const左值比较后转发构造公共类型。混合符号和精度转换遵循普通C++。严格浮点模式下NaN比较假取左，正负零取左符号，不提供fmin/fmax的数值优先语义。

## 变更说明

[接口变化与迁移说明](../../../../../release/functional_changes.md)
