# asc::std::vector::vector

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

头文件路径为：`<asc/std/vector>`。

`asc::std::vector::vector` 按本页所列构造形态初始化 `vector` 对象。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 函数原型

### 原型 1

```cpp
vector(const Allocator& allocator) noexcept;
```

### 原型 2

```cpp
vector(vector<T, Allocator>&& other) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 约束说明

- vector<T,A>显式allocator构造
- empty/size/capacity/data/begin/end/operator[]/front/back
- reserve与容量内push_back/emplace_back/pop_back/clear
- 同allocator或允许传播域的移动构造/赋值与析构
- 仅A为Device可调、容量充足、元素和allocator操作不抛出异常的域

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/vector>

template <class T, class Allocator, class... Args>
asc::std::vector<T, Allocator> make_object(Args&&... args)
{
    return asc::std::vector<T, Allocator>(static_cast<Args&&>(args)...);
}
```

对应完整工程使用 `C++17`，并通过Host 编译与运行验证。

完整示例源码：[explicit_allocator_vector.cpp](../../../../examples/explicit_allocator_vector.cpp)。
