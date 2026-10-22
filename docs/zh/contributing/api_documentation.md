# API文档维护与校验

API文档以当前产品Header和测试为准。修改接口文档时先确认声明所属命名空间、类型及语言／执行模式，再写原型、参数、生命周期和示例。

- 标题保留完整公共名；成员原型注明所在类，展示类内声明节选。说明性摘要须明确省略了什么，不把内部名字机械改写成新的公共名字。
- 同名比较运算按参与比较的类型归属；迁移说明时保留旧页面和导航，不删除有效重载。类内非模板友元与函数模板应分别标识。
- 实例化一个类型或执行sizeof不能代替用法示例。值操作给出可检查结果，类型特征给出独立预期；资源示例完整处理失败和释放路径。
- Device示例须保留GM／UB地址空间及执行模式。原子对象不得在不支持的Device局部存储中创建。
- 文档变化直接随产品提交维护。历史设计快照和旧生成器不作为覆盖当前文档的输入。

## 检查入口

```bash
python scripts/check_api_docs.py
python test/scripts/test_api_docs.py
python scripts/check_api_docs.py --examples --standard 17 --compiler g++
python scripts/check_api_docs.py --examples --standard 20 --compiler g++
python scripts/check_api_docs.py --examples --mode runtime --standard 20 --compiler g++
python scripts/check_api_docs.py --examples --mode simd --standard 17 --compiler bisheng
python scripts/check_api_docs.py --examples --mode simt --standard 20 --compiler bisheng
```

Device示例还应分别覆盖其适用的C++17/C++20模式。结构检查及其回归已进入CTest；示例登记在`test/docs/examples.json`，每页单独编译，不靠其他示例的include掩盖依赖。

Host检查区分运行、静态断言与低语言模式的头文件解析；Device编译成功不代表设备执行成功。真实运行应使用产品仿真或硬件用例并记录对应提交。DLPack等外部依赖缺失时明确记录不适用，不计为通过；使用真实依赖时可通过`--extra-include`显式指定头文件根目录。

自动检查覆盖链接、围栏、表格、章节、导航标题和已知示例回归模式，仍不证明所有声明与语义正确。新增／修改的具体示例应登记、实编译；涉及行为变化时还须补产品回归。官方CI和发布站点的验收独立于本地检查。

Runtime示例通过`--mode runtime`单独运行，需要可用设备及CANN。检查器读取`ASCEND_HOME_PATH`和可选`ASCEND_DRIVER_PATH`定位SDK与驱动库，在示例进程中使用明确的链接路径；不修改系统库。普通Host示例不隐式启动设备。
