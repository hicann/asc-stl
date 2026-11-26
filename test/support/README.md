# 共享语义回归

## SIMT视图测试的运行期输入

[cxx17_views_semantics.h](../cases/asc/std/ranges/support/cxx17_views_semantics.h)的`evaluate_filter_transform()`在纯SIMT路径通过一次volatile读取构造数值为1、2、3、4的测试数组。Host和SIMD保留常量初值。两条路径使用相同的bool标志、迭代器操作、接口调用和期望值；正向、反向遍历以及transform的所有断言均保留。测试和库的优化级别没有降低。

该输入适配针对CANN 9.2.0-beta.2、BiSheng/CCE 15与Ascend950PR_9589模拟器组合中观察到的限制：具有常量初值的局部数组连续进行两次逆向查找，在纯SIMT的高优化构建中可能得到错误结果。C++17和C++20的原始`-O3`回归均复现，C++17定向`-O2`构建也复现。C++17的无ASC-STL头文件对照可以用普通指针和直接成员访问复现，其内核内的关键片段如下：

```cpp
struct item {
    int value;
    bool enabled;
};
item values[] = {{1, false}, {2, true}, {3, false}, {4, true}};
item* current = values + 4;
do {
    --current;
} while (!current->enabled);
const int first = current->value;
do {
    --current;
} while (!current->enabled);
const bool passed = first == 4 && current->value == 2;
```

上述普通C++逻辑应使`passed`为true。独立Host runner的GCC 13在C++17/C++20和`-O3`下符合预期；受影响的SIMT模拟组合中，第二次查找及其数值检查异常。包含ASC-STL的C++17原测试在`-O1`下通过，运行期输入控制也通过。这些对照尚未分离编译器与模拟器的责任，不能据此声称其中一方已被修复，也不能推断真机表现。

2026-10-20的补充对照进一步界定了触发条件（CANN 9.2.0-beta.2，BiSheng/CCE 15指纹`c4866a4d…f84c6a`，cannsim以`-s Ascend950`运行，C++17/C++20行为一致）：

- 触发需要第二次逆向do-while**延续**上一循环的退出指针。第二循环从新开的一past末指针重新出发、对另一个常量数组的独立逆向查找、逐成员赋值初始化、`__builtin_memcpy`初始化、按索引的逆向while循环，以及8元素连续三次逆向查找，全部得到正确结果。
- 失败内核在循环前用普通标量读取同一数组的`enabled`字节得到正确的1，随后的第二次do-while仍越过应为true的元素；失败时最终读到的数值恒等于第一次查找找到的值（数组改为{11,12,13,14}时读到14，原数组读到4），与该地址应有的数组内容无关。
- 聚合常量初始化写入的内存字节经直接转储验证正确；顺序索引读取与第一次逆向查找正确。
- 模拟器指令轨迹显示，通过对照与失败内核的第二次循环使用同构的`SIMT_LDK`/`SIMT_IADD_I`/`SIMT_ISETP_I`/`SIMT_BRANCH`指令序列，仅寄存器分配不同；同一内核内第一次与第二次循环执行的指令编码完全相同而结果不同。
- 同一内核形状在`-O1`/`-O2`/`-O3`下的行为可以不同（读取全部元素的代码形状会掩盖失败），说明现象依赖具体代码形状与寄存器分配，而非单一优化级别。

据此，错误定位在第二次延续循环中`enabled`读取所依赖的数据通路：内存内容与标量读取均正确，同构指令序列在其他寄存器分配下正确。CCE生成代码的具体编码与模拟器数据通路之间的最终责任仍需以同一设备二进制在真机上运行对照来分离；在获得该对照前，本README不判定责任方。

2026-10-20真机对照完成（Ascend950PR第三套环境，`/dev/davinci6`，CANN 9.2.0-beta.2，BiSheng/CCE指纹`c4866a4d…f84c6a`，与模拟运行相同指纹）。上述五个最小内核按单kernel发射、逐个同步的方式在真机运行，二进制SHA-256：C++17为`348519e0…9cd7e25d`，C++20为`cc35ef64…40d6ae27`，两种语言结果一致：

- `shifted`与`continuing`：真机同步成功并返回与模拟器**完全相同的错误结果**（第二次查找越过数组前端，索引为-1，读到的值恒为第一次查找的14）。同一设备二进制在真机与模拟器上产生相同错误数据，证明生成的指令序列本身错误。
- `fresh_restart`与`plain_bool`：真机同步返回507035（向量核GM越界故障）。模拟器对同一二进制返回错误数据而非故障，说明模拟器对越界访问比硬件宽容。
- `two_arrays`：真机正确（第一次4、第二次8）。
- 同环境的ASC-STL W13/W14纯SIMT硬件载荷（含本README所述运行期输入适配）通过`ASC_STL_W13_W14_HARDWARE_PASS`。

结论：责任为**BiSheng/CCE 15（指纹`c4866a4d…f84c6a`）在`--enable-simt`下对常量初始化局部数组的连续逆向指针遍历生成错误代码**；模拟器忠实执行了错误代码。该问题不依赖ASC-STL：任何使用者在纯SIMT下以常量初值局部数组进行上述遍历都可能得到错误结果或向量核越界故障。ASC-STL库本身语义正确；本目录的运行期输入适配保留库行为断言并绕开该编译器缺陷，应在编译器修复并复验后移除。原始失败门禁、最小复现、模拟器与真机对照证据分别在工具仓记录，不互相替代。

## B022算法回归的SIMT运行期输入

B022的[共享语义载荷](../cases/asc/std/atomic/runtime/semantics.h)在纯SIMT路径
通过[共享输入helper](b022_runtime_inputs.h)读取Host显式上传到GM的数组原值，
再构造局部测试数组。`initialize()`准备原值与零seed，两个Host驱动均显式执行H2D
上传，D2H回读后由`unchanged()`确认输入未被覆盖，并要求`runtime_inputs_unchanged=1`。
输入使用64个`int`结果槽中的52至62槽，与visibility的40至45槽、窄整数CAS的
48至51槽分开。
Host与SIMD继续使用原常量初值。该适配保留既有算法API、调用顺序、全部比较断言、
golden与`-O3`；模拟入口继续执行原子与算法段，真机入口继续执行main与visibility段。

这项适配针对另一组独立观察：产品提交`486eb08da5712b93ab9d1aeef84600439c45a272`
在CANN 9.2.0-beta.2、BiSheng/CCE 15（指纹`c4866a4d…f84c6a`）与Ascend950上，
C++17完整B022模拟由CTest在1500.10秒超时判为失败。同一源码的真机main kernel
返回507035；PID 1648125专属日志记录error 340，即VEC访问UB地址未对齐，
kernel名及grid/block均对应main。该日志尚未提供可定位到算法源码的故障指令。

保持原编译参数重编译后，linked `.text`与原真机对象逐字节一致。对应优化LLVM IR
剩下两组`[5 x i32]`局部数组，均为`align 4`，分别从`align 4`常量源复制20字节。
同为C++17、`-O3`的算法独立对照得到以下结果：

| 输入形态 | 模拟结果 | 验证范围 |
| --- | --- | --- |
| 原常量初始化 | 120秒未退出 | 完整算法段，未包含原子与visibility段 |
| 全部局部数组增加`alignas(32)` | 正常结束，`failures=3` | 对应IR的两组局部数组及常量源均为`align 32` |
| 从Host上传的相同原值构造，诊断seed为0 | 正常结束，`failures=0` | 算法API调用顺序与全部比较断言保持不变 |

这些对照将调查范围收窄到该常量初始化与组合代码形态；B022的根因和精确故障指令
仍待定位，尚无算法源码存在未定义行为的结论。上节视图案例已有独立最小复现与
同二进制真机证据，其编译器归因不能直接推广到本案例，也不能据此宣称所有常量
局部数组均受影响。

原始常量形态的源码、失败日志、二进制与对照结果继续保存在工具仓忽略的诊断证据中。
运行期输入适配保留原值与行为检查，原始常量形态仍需在相关工具链修复或责任定位后
复验。验证修正后的完整检查点时，须执行C++17/C++20 Host、O3 Device编译、cannsim，以及包含
visibility与新增窄整数CAS边界的真机回归；算法独立对照通过不替代这些结果。

<a id="b027-simt-phased-fixtures-for-full-semantics"></a>

## B027完整语义的SIMT分阶段夹具

`b027_core_semantics.h`保存bitset、inplace_vector、default_searcher、gcd/lcm、
整型/指针/浮点midpoint及hash的原调用与golden。Host和SIMD的`evaluate_core()`
先执行这些检查，再执行原[string_aliasing_semantics.h](../cases/asc/std/string/support/string_aliasing_semantics.h)，保留原顺序和全部检查。

纯SIMT的cannsim与hardware共用`bitset/runtime/staged/`中的ASC模块及`stage_table.def`。
每个stage只有一个ASC翻译单元、一个SHARED模块，普通version script仅导出唯一
launcher；运行程序使用`RTLD_NOW | RTLD_LOCAL`，注册符号在模块内部解析。
完整顺序为core、长字符串构造、自追加检查1–3、reserve、后缀追加检查4–5、
后缀赋值检查6、自赋值检查7、空串赋值检查8、长字符串析构、局部SSO检查9、
最终计数检查10。reserve阶段保存实际的`before_append`和`data()`地址，检查4与6
使用这个跨阶段保存的地址。

长字符串的state、对象和256字节arena分别位于Host分配的GM中，placement构造后的
对象跨kernel保持同一生命周期。预期分配大小为25、49、97字节，最终计数3:3；
原`allocations == deallocations`谓词保留，实际大小、用量及计数通过结果包回读。
SSO阶段另建原形状的局部arena，使用局部`abc`初值及自动对象，保留原no-allocation
谓词；析构后的局部计数也进入最终balance检查。GM夹具与局部夹具使用不同namespace，
避免将不同storage布局赋予同一个C++类型名。

所有stage在同一进程、ACL context、stream和GM分配上运行；每次提交前显式H2D
上传非零结果sentinel，随后同步并D2H检查，首个失败后停止后续stage。成功路径在
字符串和state均已析构且同步完成后逐项核对`dlclose`，再释放ACL资源。同步失败时
不卸载模块、不释放可能仍在使用的buffer或stream，仅尝试并记录context reset与
finalize，结果保持失败。hardware使用`hardware_runtime`的10秒任务时限和10秒stream
同步保护；外层进程时限仍是必需条件。模拟程序保留Host运行库路径，并允许cannsim
通过其进程局部环境选择camodel，不能强制SDK的DT_RPATH覆盖模拟runtime。

在CANN 9.2.0-beta.2、BiSheng 15.0.5（指纹`c4866a4d…f84c6a`）下，
原38b9提交的C++17单kernel综合载荷已完成编译，但SIMT真机执行发生设备地址
访问故障（设备错误355；日志记录GM地址超过48位，同步返回507035）。后续多组
将长对象或arena移到GM的
等价诊断候选在60秒或90秒的emit-object时限内未完成；这与原载荷的真机失败属于
不同证据，均尚未唯一归因到某个API。不能据此宣称所有局部arena均不可用或SDK
缺陷已经确诊。公开使用边界见[basic_string](../../docs/zh/api/standard/strings/asc_std_string/basic_string.md#simt工具链验证边界)。

这是当前工具链验证夹具的内存域与模块隔离方案。ASC-STL公共Header没有因此改变，
原单kernel中组合长字符串和局部arena的形态仍需独立复验；分阶段通过不能作为SDK
已修复或该原形态恢复的证据。每个新产品提交均须执行完整C++17/C++20 Host、
SIMD/SIMT O3构建、完整cannsim和有保护的真机矩阵，不能以三阶段前缀结果替代
core、字符串1–10及局部SSO的完整结果。
