# ASC-STL Development Roadmap (Stage 1 · 通用编程能力)

> **里程碑**：ASC-STL v1.0.0-preview · **负责人**：待定 · **状态**：收尾中，随进展持续修订描述
>
> 版本目标：**v1.0.0-preview**

ASC-STL 是面向昇腾设备 Kernel 编程的纯头文件 C++ 库。Kernel 开发需要类型系统、容器与视图、算法、数值、原子与同步等通用 C++ 能力；本阶段交付其中与平台无关的**通用编程能力**（以及部分为后续设备能力提供支撑的基础头S），使 Host 与 Device 代码共用同一套公共 Header 组织——写 Kernel 就像写普通 C++。

本阶段目标是完成通用编程能力的全量公共头、配套质量工程与首个对外代码包发布：能力主体已就绪并验证，补齐剩余工作集、公共伞头入口归一与发布文档。

## Focus

- **类型系统与通用工具**：类型查询变换、值语义包装、函数对象与特性检测全量就绪
- **顺序算法与迭代**：顺序算法、迭代器与 range 主体补齐，公共入口收口为统一伞头
- **数值与时间**：数值算法、位操作、数学、复数与时间能力齐备
- **容器与视图**：固定容量容器与非拥有视图交付
- **标准原子与同步**：标准形态原子、内存序、屏障与锁交付
- **库基础设施与发布**：版本机制、检查、单测/仿真/真机验证、CI 与发布文档

## 类型系统与通用工具

### 类型查询与变换

- **Goal**：提供完整的编译期类型判断、类型关系查询与类型变换能力，作为全部公共能力的约束底座。
- **Key Features**：
  - `type_traits` 全量公共头与 `concepts` 模板参数约束
  - `compare` 三路比较辅助工具
  - `version` 特性检测宏与实现状态同步
- **Owner**：待定
- **Issue**：#X

### 值语义与通用工具

- **Goal**：提供 Kernel 代码直接可用的值组合、可选值与函数对象工具。
- **Key Features**：
  - `tuple` / `optional` / `variant` / `expected` 值语义类型
  - `utility`（移动、转发、交换、整数序列）与 `functional` 函数对象族
  - `limits`、`source_location` 等通用属性与位置描述
- **Owner**：待定
- **Issue**：#X

### 错误表示与生命周期

- **Goal**：提供错误码、异常基础类型与对象生命周期工具的标准形态。
- **Key Features**：
  - `system_error` 错误码/错误条件/错误类别
  - `exception` 基础类型与终止处理
  - `new` / `memory`（基础）分配与构造销毁工具
- **Owner**：待定
- **Issue**：#X

## 顺序算法与迭代

### 顺序算法与伞头归一

- **Goal**：交付查找、比较、复制、变换、排序、分区、集合操作等全量顺序算法，并收口为 `<asc/std/algorithm>` 统一入口。
- **Owner**：待定
- **Issue**：#X

### 迭代器与 range

- **Goal**：提供迭代器、迭代器适配器与基于 range 的遍历/过滤/变换能力。
- **Key Features**：
  - `iterator` 迭代器属性与遍历辅助
  - `ranges` range 处理与视图组合
  - `execution` 标准执行策略类型与常量
- **Owner**：待定
- **Issue**：#X

## 数值与时间

### 数值与位操作

- **Goal**：提供归约、扫描、内积等数值算法与位级操作能力。
- **Key Features**：
  - `numeric` 数值算法与 `bit` 计数/旋转/字节交换/位级转换
  - `charconv` 字符序列与数值低开销转换
- **Owner**：待定
- **Issue**：#X

### 数学、复数与常量

- **Goal**：提供标量数学函数、复数运算与标准数学常量。
- **Key Features**：
  - `cmath` 标量数学与浮点分类
  - `complex` 复数类型与复数数学
  - `numbers` 标准数学常量
- **Owner**：待定
- **Issue**：#X

### 时间

- **Goal**：提供时钟、时间点、时间段运算与编译期有理数表示。
- **Key Features**：
  - `chrono` 时钟/时间点/时间段
  - `ratio`、`ctime` 兼容入口
- **Owner**：待定
- **Issue**：#X

## 容器与视图

### 固定容量容器与视图

- **Goal**：交付无需动态内存的容器、适配器与非拥有视图，覆盖 Kernel 侧主要数据组织需求。
- **Key Features**：
  - `array`、`inplace_vector`、`bitset`
  - `string` / `string_view`、`span`
- **Owner**：待定
- **Issue**：#X

### 动态容器支持度评估

- **Goal**：完成 `vector`、`list`、关联容器等动态容器在设备侧的支持边界评估并定界。
- **Key Features**：
  - 支持范围结论与不支持项的明确编译期/运行期错误
  - 评估结论决定动态容器是否留在本阶段（待定）
- **Owner**：待定
- **Issue**：#X

## 标准原子与同步

### 原子操作与内存序

- **Goal**：提供标准形态的原子读写、交换、比较交换与内存序控制（Host 侧）。
- **Key Features**：
  - `atomic` 标准原子与内存序
  - 设备侧范围原子属阶段二交付
- **Owner**：待定
- **Issue**：#X

### 屏障与锁

- **Goal**：提供屏障、信号量与互斥访问标准形态能力。
- **Key Features**：
  - `barrier` / `latch` / `semaphore`
  - `mutex` / `shared_mutex` 与锁对象管理
- **Owner**：待定
- **Issue**：#X

## 库基础设施与发布

### 配置与公共底座

- **Goal**：稳定统一配置入口、命名空间/可见性宏与执行空间标注体系。
- **Key Features**：
  - `asc/std/detail/__config` 统一配置入口
  - `_ASC_API` 执行空间标注与系统头隔离 pragma
  - C++17 基线
- **Owner**：待定
- **Issue**：#X

### 质量工程

- **Goal**：建立随包交付的完整质量检查体系。
- **Key Features**：
  - 每头 Host 单元测试与 cannsim 数值仿真
  - CI 脚本：quick-check / device-compile-check / cannsim-check
- **Owner**：待定
- **Issue**：#X



### 公共入口归一与发布文档

- **Goal**：完成公共伞头入口归一与阶段一发布文档，形成首个对外代码包。
- **Key Features**：
  - `<asc/std/algorithm>` 等统一伞头入口
  - README、功能清单、已知限制与环境要求
  - 发布包：通用能力公共头全集 + 测试 + CMake/CI + 文档
- **Owner**：待定
- **Issue**：#X

