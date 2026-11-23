# asc::static_for

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

头文件路径为：`<asc/utility>`。

`static_for` 生成按顺序执行的调用序列。每次调用的首参数是 `asc::std::integral_constant<IndexType, I>`，其 `value` 可用于模板实参。标准整数序列只表达索引，普通循环的运行时变量不能承担这一模板参数用途。

序列在编译期确定，回调可以在运行时执行。满足 C++17/C++20 常量表达式规则的调用也可常量求值；接口不承诺固定的机器指令形式或性能提升。

## 函数原型

### 原型1

```cpp
namespace asc {
template <auto Size, class Operator, class... Args>
constexpr void static_for(Operator&& operation, Args&&... args) noexcept(
    noexcept(static_for<decltype(Size), Size>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

### 原型2

```cpp
namespace asc {
template <auto Start, decltype(Start) End, decltype(Start) Step = decltype(Start){1}, class Operator, class... Args>
constexpr void static_for(Operator&& operation, Args&&... args) noexcept(
    noexcept(static_for<decltype(Start), Start, End, Step>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

### 原型3

```cpp
namespace asc {
template <class IndexType, IndexType Start, IndexType End, IndexType Step = IndexType{1}, class Operator, class... Args>
constexpr void static_for(Operator&& operation, Args&&... args) noexcept(
    noexcept(detail::static_for_range<IndexType, Start, End, Step>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

### 原型4

```cpp
namespace asc {
template <class SizeType, SizeType Size, class Operator, class... Args>
constexpr void static_for(Operator&& operation, Args&&... args) noexcept(
    noexcept(detail::static_for_count<SizeType, Size>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

## 参数说明

| 参数 | 含义 |
| --- | --- |
| `Size` | 计数形式的终点，依次处理 `[0, Size)`；非正数为空。 |
| `Start`、`End`、`Step` | 范围的起点、排除的终点及步长；`Step` 默认 1。 |
| `IndexType` / `SizeType` | 显式指定索引类型；自动形式从 `Start` / `Size` 推导。 |
| `operation` | 借用的函数对象，始终以同一个左值直接调用。 |
| `args...` | 每次按 `Args&&` 传递的额外实参；库不复制或保存这些对象。 |

## 返回值说明

返回 `void`，回调结果丢弃。前一次调用及其返回临时的销毁完成后，才进入下一次调用。所有实际调用表达式（包括参数构造和返回临时销毁）均不抛异常时，函数为 `noexcept(true)`；空范围也为 true。Host 异常向调用方传播，后续索引不再调用。

## 约束说明

- 最低 C++17，支持 C++20。索引仅接受无 cv 的 `signed char`、`short`、`int`、`long`、`long long` 及其无符号对应类型，包含以这些类型定义的 `size_t` 等别名。普通 `char`、`bool`、字符专用类型、枚举、浮点和扩展整型不参与重载。
- `End`、`Step` 与索引同类型，模板实参须满足转换常量表达式规则。无符号索引不表示负步长，反向范围用有符号类型。
- 正步长生成 `< End` 的索引，负步长生成 `> End` 的索引，均包含 `Start`。如 `<1, 8, 3>` 为 `1, 4, 7`，`<5, 0, -2>` 为 `5, 3, 1`。相等端点或方向不符为空；步长为零始终编译诊断。
- 仅生成实际访问的索引。末次调用后的数学索引无需可表示；端点间距离和最小负步长不会通过有符号溢出计算。展开规模须可由 `size_t` 表示，并受编译器资源限制。
- 函数对象以引用借用，不引入复制或移动，支持不可复制对象及 `operator() &`；仅有 `operator() &&` 的对象须自行适配。调用采用普通函数调用语法，不提供成员指针的 `invoke` 适配。
- 同一右值实参会被重复转发。若回调按值接收并移动它，后续调用看到其移动后的状态。需要重复读取时可传左值或用 const 引用接收，需要每次新值时在回调中构造。
- 空范围不实例化回调表达式，也不要求回调可调用。调用处的实参求值与临时对象构造、销毁照常发生。
- Host 包含无需 SDK。SIMT 和 SIMD 标量上下文要求回调、参数和存储访问在该执行位置合法；Device 不提供异常恢复。本接口不同步其他线程。

## 调用示例

以下 Host 示例将常量索引用作 `get<I>` 的模板参数，并检查运行时写入结果。

```cpp
#include <asc/utility>
#include <asc/std/tuple>

bool example()
{
    asc::std::tuple<int, float, long> fields{1, 2.0f, 3L};
    asc::static_for<3>([&](auto index) {
        asc::std::get<decltype(index)::value>(fields) = 0;
    });
    int sequence = 0;
    asc::static_for<1, 8, 3>([&](auto index) { sequence = sequence * 10 + index.value; });
    return asc::std::get<0>(fields) == 0 && asc::std::get<1>(fields) == 0.0f &&
        asc::std::get<2>(fields) == 0L && sequence == 147;
}
```

## 关联API

- [本头文件的接口列表](asc_utility.md)
