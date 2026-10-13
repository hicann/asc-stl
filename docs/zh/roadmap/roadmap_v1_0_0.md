# ASC-STL Development Roadmap (v1.0.0 · 完整版本 · 标准库、昇腾扩展与Runtime能力全量)

> **版本目标**：v1.0.0 · **发布日期**：2026年10月16日（10月第2周） · **状态**：按周更新，随v1.0.0发布
>
> **总路线图**：[ASC-STL ROADMAP](roadmap.md)

ASC-STL是面向昇腾设备核函数编程的纯头文件C++ 库。核函数开发需要类型系统、容器与视图、算法、数值、原子与同步等通用C++ 能力，也需要地址空间与内存视图、设备并行算法、设备管理与核函数调用等昇腾平台能力；v1.0.0作为**完整版本**一次性提供全部三类接口——`asc::std`接口层16类标准能力模块、昇腾扩展接口（9类）与Runtime接口（4类）共29类能力域的全部公共头，使Host与Device代码共用同一套公共Header组织：写Kernel就像写普通C++。

v1.0.0的能力随10月前两周的代码更新合入：第1周补齐C++ 标准库16类标准能力模块；第2周合入昇腾扩展接口与Runtime接口全部能力并完成集成验证，于10月16日发布完整版本。

## Focus

- **类型系统与通用工具**：类型查询与变换、值语义类型、函数对象与错误表示全量提供；
- **顺序算法、迭代器与范围**：全量标准算法、迭代器与基于范围的视图组合；
- **容器与视图**：固定容量容器、动态容器与非拥有视图；
- **字符串与文本处理**：字符串存储与视图、字符分类、数值转换与格式化；
- **数值与时间**：数值算法、数学函数、复数、随机数与时间运算；
- **标准原子与同步**：原子操作与内存序、屏障、信号量与互斥；
- **内存管理与语言支持**：智能指针与分配器、语言支持基础宏与类型；
- **昇腾扩展接口**：设备原子与线程同步、执行层次与集体操作、Device并行算法、地址空间与内存视图、多维视图与异步搬运、设备侧数值与类型工具；
- **Runtime接口**：设备/Stream/Event管理、核函数调用、执行策略与内存资源。

## 类型系统与通用工具

### 类型查询与变换

- **Goal**：提供完整的编译期类型判断、类型关系查询与类型变换能力，作为全部公共能力的约束底座。
- **Key Features**：
  - `type_traits`全量公共头与`ratio`编译期有理数运算
  - `concepts`标准概念（concept）与模板参数约束
  - `compare`三路比较结果类别与比较辅助工具
  - `version`标准功能特性检测宏
- **Issue**：#22、#23
- **PR**：[#29](https://gitcode.com/cann/asc-stl/pulls/29)、[#33](https://gitcode.com/cann/asc-stl/pulls/33)

### 值语义与函数对象

- **Goal**：提供核函数代码直接可用的值组合、可选值与函数对象工具。
- **Key Features**：
  - `tuple` / `optional` / `variant` / `expected`值语义类型
  - `utility`（移动、转发、交换、整数序列）与`functional`函数对象族
  - `bit`计数、旋转、字节交换与位级转换，`bitset`固定长度位集合
  - `limits` / `source_location`数值属性与源码位置描述
- **Issue**：#31
- **PR**：[#38](https://gitcode.com/cann/asc-stl/pulls/38)、[#46](https://gitcode.com/cann/asc-stl/pulls/46)

### 错误表示与诊断

- **Goal**：提供断言与错误表达的标准形态。
- **Key Features**：
  - `cassert`断言宏与`cerrno`错误码宏
  - `system_error`错误码 / 错误条件 / 错误类别
- **Issue**：#48
- **PR**：[#60](https://gitcode.com/cann/asc-stl/pulls/60)

## 顺序算法、迭代器与范围

### 顺序算法

- **Goal**：提供查找、比较、复制、变换、排序、分区、集合操作等全量标准算法，入口统一为`<asc/std/algorithm>`。
- **Key Features**：
  - 非修改 / 修改序列操作、排序与分区、二分查找、集合操作、堆操作等
  - `execution`标准执行策略类型与常量
- **Issue**：#25
- **PR**：[#35](https://gitcode.com/cann/asc-stl/pulls/35)、[#46](https://gitcode.com/cann/asc-stl/pulls/46)

### 迭代器与范围

- **Goal**：提供迭代器、迭代器适配器与基于范围的遍历和视图组合能力。
- **Key Features**：
  - `iterator`迭代器属性、迭代器适配器与遍历辅助
  - `ranges`范围访问、过滤、变换与视图组合
- **Issue**：#25
- **PR**：[#35](https://gitcode.com/cann/asc-stl/pulls/35)、[#46](https://gitcode.com/cann/asc-stl/pulls/46)

## 容器与视图

### 固定容量容器与视图

- **Goal**：提供无需动态内存的容器与非拥有视图，覆盖核函数侧主要数据组织需求。
- **Key Features**：
  - `array` / `inplace_vector` / `bitset`
  - `span`连续序列视图与`mdspan`多维数据视图
- **Issue**：#31
- **PR**：[#38](https://gitcode.com/cann/asc-stl/pulls/38)

### 动态容器与适配器

- **Goal**：提供可动态变化的标准容器族与容器适配器。
- **Key Features**：
  - `vector` / `deque` / `list` / `forward_list`
  - `map` / `set` / `unordered_map` / `unordered_set`
  - `queue` / `stack`
- **Issue**：#31
- **PR**：[#38](https://gitcode.com/cann/asc-stl/pulls/38)、[#53](https://gitcode.com/cann/asc-stl/pulls/53)

## 字符串与文本处理

- **Goal**：提供字符序列的存储、访问、转换与格式化能力。
- **Key Features**：
  - `cstring` C字符串与字节序列操作，`string`拥有字符序列的字符串类型，`string_view`只读视图
  - `cctype` / `cwctype` / `cwchar` / `cuchar`字符分类与转换
  - `charconv`不依赖区域设置的字符序列与数值转换
  - `format`类型安全的格式化
- **Issue**：#48
- **PR**：[#60](https://gitcode.com/cann/asc-stl/pulls/60)

## 数值与时间

### 数值算法

- **Goal**：提供归约、扫描、内积等标准数值算法。
- **Key Features**：
  - `numeric`归约、扫描、内积、差分与序列生成
- **Issue**：#24、#48
- **PR**：[#34](https://gitcode.com/cann/asc-stl/pulls/34)、[#60](https://gitcode.com/cann/asc-stl/pulls/60)

### 数学、复数与随机数

- **Goal**：提供标量数学函数、复数运算、数学常量、线性代数与随机数能力。
- **Key Features**：
  - `cmath`标量数学函数与浮点分类
  - `complex` / `ccomplex` / `ctgmath`复数类型与复数数学
  - `numbers`标准数学常量
  - `linalg`面向向量与矩阵视图的线性代数算法
  - `random`随机数引擎、分布与生成辅助工具
- **Issue**：#26、#48
- **PR**：[#37](https://gitcode.com/cann/asc-stl/pulls/37)、[#60](https://gitcode.com/cann/asc-stl/pulls/60)

### 时间

- **Goal**：提供时钟、时间点、时间段运算与C兼容日期时间。
- **Key Features**：
  - `chrono`时钟、时间点、时间段及其运算
  - `ctime` C兼容日期时间类型与函数
- **Issue**：#48
- **PR**：[#60](https://gitcode.com/cann/asc-stl/pulls/60)

## 标准原子与同步

- **Goal**：提供标准形态的原子操作与线程同步原语。
- **Key Features**：
  - `atomic`原子读写、交换、比较交换与标准内存序控制
  - `barrier` / `latch` / `semaphore`屏障、倒计数与信号量
  - `mutex` / `shared_mutex`互斥访问与锁对象管理
  - 设备侧原子操作与线程同步（GM/UB作用域）随v1.0.0一并提供，见下文「昇腾扩展接口」
- **Issue**：#32
- **PR**：[#44](https://gitcode.com/cann/asc-stl/pulls/44)、[#47](https://gitcode.com/cann/asc-stl/pulls/47)

## 内存管理与语言支持

### 内存管理

- **Goal**：提供对象存储与生命周期管理、分配器体系的标准形态。
- **Key Features**：
  - `memory`智能指针、分配器、对象构造与销毁、未初始化内存操作
  - `scoped_allocator`向嵌套对象传递外层分配器
- **Issue**：#26
- **PR**：[#37](https://gitcode.com/cann/asc-stl/pulls/37)

### 语言支持

- **Goal**：提供C++ 语言功能所需的基础宏与类型。
- **Key Features**：
  - `cfloat` / `climits` / `cstdint` / `cstddef` / `cinttypes`数值特征宏与基础类型
  - `exception`异常基础类型、`new`分配函数与placement new
  - `ciso646` / `cstdalign` / `cstdbool` C兼容拼写与定义
- **Issue**：#22
- **PR**：[#29](https://gitcode.com/cann/asc-stl/pulls/29)

## 昇腾扩展接口

### 设备原子操作与线程同步

- **Goal**：提供作用于GM/UB地址空间的设备侧原子操作与线程同步原语。
- **Key Features**：
  - `atomic`线程块级/设备级整数原子操作与作用于UB的宽松原子操作
  - `barrier` / `latch` / `semaphore` Block/Device作用域屏障、倒计数与信号量
- **Issue**：#32
- **PR**：[#44](https://gitcode.com/cann/asc-stl/pulls/44)、[#47](https://gitcode.com/cann/asc-stl/pulls/47)

### 设备执行层次与集体操作

- **Goal**：提供设备执行层次查询、线程协作与动态任务获取能力。
- **Key Features**：
  - `hierarchy` / `warp` Grid/Block/Warp/Thread维度、规模与索引查询；线程束投票、匹配、数据交换与归约
  - `collectives`线程块级归约、扫描、广播与条件判断
  - `work_queue`基于GM原子游标的动态任务区间获取
- **Issue**：#36
- **PR**：[#53](https://gitcode.com/cann/asc-stl/pulls/53)

### Device并行算法与参数包装

- **Goal**：提供通过Device执行策略提交的并行算法与算法参数包装设施。
- **Key Features**：
  - `algorithm`并行变换、查找、归约、扫描、选择、分区、合并与排序
  - `argument`常量、立即值、延迟求值等算法参数包装
  - `functional` / `iterator`最小值/最大值函数对象与操作属性；常量、计数、跨步、变换、组合等迭代器适配器
- **Issue**：#36
- **PR**：[#53](https://gitcode.com/cann/asc-stl/pulls/53)

### 地址空间、内存视图与数据搬运

- **Goal**：提供GM/UB地址空间视图与多维异步数据搬运能力。
- **Key Features**：
  - `memory`全局内存（GM）与统一缓冲区（UB）非拥有内存视图、内存空间属性查询与对齐辅助
  - `mdspan` / `tensor_copy`覆盖Host、GM与UB的多维数据视图（支持DLPack数据结构转换）；支持1至5维形状、步长与填充的GM/UB异步数据搬运
  - `pipeline`基于事件ID组织的GM与UB异步搬运流水线
- **Issue**：#48
- **PR**：[#60](https://gitcode.com/cann/asc-stl/pulls/60)

### 设备侧数值、位操作与类型工具

- **Goal**：提供设备侧数值计算、位操作与类型特征工具。
- **Key Features**：
  - `bit`位反转、掩码与位域操作
  - `cmath` / `numeric`整数取整、对数、平方根、幂与`sincos`；溢出检测、饱和计算与窄化转换检查
  - `random` PCG64伪随机数引擎与确定性双射
  - `type_traits` / `utility` / `version`按位比较、扩展浮点、可平凡重定位等类型特征；`in_range`与`static_for`工具；版本宏与扩展能力检测宏
- **Issue**：#48
- **PR**：[#60](https://gitcode.com/cann/asc-stl/pulls/60)

## Runtime接口

### 设备、Stream与Event管理

- **Goal**：以公共C++ 接口提供设备与任务提交通道的管理能力。
- **Key Features**：
  - `devices`设备枚举、查询与选择
  - `stream` Stream/Event创建与接管、同步与完成状态查询、Event依赖与计时
- **Issue**：#32
- **PR**：[#44](https://gitcode.com/cann/asc-stl/pulls/44)

### 核函数调用与执行策略

- **Goal**：提供核函数调用与执行策略、执行要求组合能力。
- **Key Features**：
  - `launch`在指定Stream上异步调用核函数，按Stream顺序提交Host回调
  - `execution`及其子头（`execution.policy.h` / `execution.require.h` / `execution.determinism.h` / `execution.output_ordering.h` / `execution.tie_break.h`）关联Stream、工作空间与执行要求的执行策略；确定性、输出顺序、决胜规则等执行要求组合
- **Issue**：#32
- **PR**：[#44](https://gitcode.com/cann/asc-stl/pulls/44)

### 内存资源、内存池与缓冲区

- **Goal**：提供Device内存与Host锁页内存的资源管理能力。
- **Key Features**：
  - `memory_resource` Device内存与Host锁页内存资源
  - `memory_pool` Event完成后复用的内存池
  - `buffer`连续内存缓冲区管理
- **Issue**：#48
- **PR**：[#60](https://gitcode.com/cann/asc-stl/pulls/60)

## 获取与使用

- **使用形态**：纯头文件库，标准库能力以`<asc/std/...>`、昇腾扩展与Runtime能力以`<asc/...>`提供、均可单独包含，经CMake `INTERFACE`目标集成，无需链接库；
- **发布内容**：v1.0.0完整版本公共头全集（三类接口共29类能力域）、CMake安装与导出配置、Host与Device使用示例；
- **后续版本**：v1.1.0起按完善计划持续打磨质量、性能、文档与易用性，版本计划见[总路线图](roadmap.md)。
