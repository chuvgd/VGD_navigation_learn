# 行为树

本文档只是作为使用手册进行查询，不是教程文档

## tick

tick在行为树相当于一个脉冲信号，会从root开始执行整个行为树，行为树是一个一个节点组成的，其中分为控制节点，装饰节点和子叶节点，而其中子叶节点分为动作节点和条件节点；切记：一次tick会执行完一整个树的完整逻辑，直到返回```success```或者```failure```，如果有节点返回```running```则需要下一次tick，即需要下一次脉冲信号

注意：tick是有时间调度的，外部调度器执行行为树时，两次调度之间的时间间隔（最大触发频率），但是不是单次tick()内部执行的时间上限

这里理解为tick是一次脉冲信号，要走完完整的路才能结束自己的任务

```
调度周期 = 单次tick() + 休眠时间
这个休眠时间就是相当于在执行完一次tick后将调度减去tick的时间
而一次tick的时间就是调用行为树，从root向下执行到最后执行完子节点后向根节点返回树的状态并退出的一次时间
```

```
这里还需要注意的是：局部和整体的区别——必须是从根节点返回的树的状态才算是tick结束；注意控制节点对相关子叶节点的控制和调度完成整个树的逻辑；同时可能还有会装饰节点对相关的子叶节点和控制节点进行相关的装饰；一直要到所有需要评估的分支走完，状态逐层向上汇总最后返回整个树的状态才算一次tick的完整结束
```

## 回退节点

也叫选择节点，分为：

- ```Fallback```
- ```AsyncFallback```(异步)
- ```ReactiveFallback```

规则：

- 在tick第一个子节点之前，节点状态变为"运行中"
- 如果一个子节点返回失败，则回退节点会tick下一个节点
- 最后一个返回失败，则所有子节点都会被终止，并且回退节点返回失败
- **如果一个子节点返回成功，则回退节点停止并返回成功，所有子节点均会被终止**

注意：这里和c语言中的```||```一样，遇真则停，但是一般在复杂持续监控的行为树中：```reactivefallback```是最常用的，这是因为，如果第一个返回失败，它会接着执行其他子节点，但是每次tick仍然从头开始，一旦条件改变，会中断其他子节点，并从第一个子节点重新开始，如果第一个返回成功，也会直接返回成功并结束整个```reactivefallback```

## 顺序节点

按照顺序进行执行节点，完成顺序节点下的子节点后再返回相关状态

顺序节点和c语言中的&&语法逻辑一致

分为：

- ```sequence```
- ```AsyncSequence```（异步）
- ```SequenceWithMemory```(带记忆地的序列)
- ```ReactiveSequence```

注意：```SequenceWithMemory```——子节点成功就不再执行；即使后续失效也不会重置已经成功的子节点；就是下一次tick不会重新执行前面节点

但是普通的```sequence```是当一个子节点返回```RUNNING```，下次tick会继续从```RUNNING```开始执行不执行前面的子节点；但是失败后还是会从头开始执行

```reactivesequence```则是每次tick从头执行判断每一个节点状态

## 并行节点

并行节点是唯一允许同时有多个子节点处于“运行中”状态的节点

- ```Parallel```（并行）
- ```ParalleAll```（全并行）

```Parallel```节点当按照tick执行子节点时如果当达到成功或者失败的阈值时，这个节点完成；其他处于运行中的节点被终止

```ParallelAll```节点是在一个tick中执行完所有子节点直到完成，不会因为阈值提前终止子节点，直到完成所有再按照阈值判断成功或者失败

## 条件控制与switch节点

- ```IfThenElse```
- ```WhileDoElse```

```IfThenElse```是一次性条件判断：如果第一个子节点是条件(if)，如果条件返回成功，则执行第二个节点；如果失败则执行第三个节点（可选）

如果只有两个节点且条件返回失败，则此节点返回失败；条件仅评估一次，如果第二个或者第三个子节点返回“运行中”，后续tick不会重新评估

```WhileDoElse```是反应式循环判断：每次tick重新评估条件，第一个子节点是条件，每当条件返回成功，执行第二个子节点；否则是执行第三个

如果第二个或者第三个子节点处于“运行时”状态，并且条件结果发生变化；则在切换到另一个分支之前，在正在运行的子节会被终止

- ```Switch```

```Switch```节点等同于c语言的switch语句：根据黑板变量的值选择执行哪个子节点

每次tick会重新检查变量，如果当前正在运行的子节点的所属的case不再匹配，会先halt当前执行的子节点，再立即切换到新匹配的case或者default分支

一个```SwitchN```节点必须恰好有N+1个子节点

## 子树端口重映射

一颗主树包含子树时，每个子树拥有自己独立的黑板，避免不同树黑板键名的冲突，需要通过重映射将主树的端口与子树的端口进行显式连接

```xml
<SubTree ID="MoveRobot" target="{move_goal}" result="{move_result}"/>
```

- ```target="{move_goal}"```表示：子树的**target**输入端口将读取主树黑板的**move_goal**键的值
- ```result="{move_result}"```表示：子树的```result```输出端口将写入主树黑板中```move_result```键的值（子树内部通过**setOutput**写入自己的**result**端口，但是实际数据会被映射到主树的```move_result```）

在这里的```target```和```result```是子树内部定义的端口名，```move_goal```和```move_result```是主树黑板上的键名

```xml
<TreeNodesModel>
	<SubTree ID="MoveRobot">
		<input_portname="target" default="{move_goal}"/>
		<input_portname="frame" default="world"/>
		<output_port name="result" default={error_code}"/>
	</SubTree>
</TreeNodesModel>
```

在xml中可以为<TreeNodeModel>为这个子树声明端口的默认重映射值，就和普通节点端口设置默认值一样

子树还有自动重映射的机制，如果子树中的端口名与主树中想要使用的黑板键名完全相同时，```_autoremap="true"```用来进行解决，即```target = {target}``` ```result = {result}```等等

## 节点参数与默认值配置

### 向节点传递额外参数

```cpp
MyCustomNode(const std::string& name,const NodeConfig& config);
// 标准构造函数
```

**某些情况下，希望向类的构造函数额外的参数，指针，引用**

从理论上来说，**这些参数可以使用输入端口传递**，但是如果：

- 黑板/端口适合运行时动态变化的数据，比如传感器读数，目标位置等；
- 如果参数在构建树时就已经确定（算法参数，硬件接口指针），并且不会在运行时改变，那么用黑板/端口反而会增加不必要的复杂性和开销
- **注意：不要滥用黑板，固定应该直接通过构造函数或初始化函数传入**

#### 方式1：修改构造函数，直接传递参数

- 在自定义节点的构造函数中，除了必需的**name**和**config**，再添加你需要的参数
- 注册节点时，将这些参数一并传给工厂

```cpp
// Action_A的构造函数与默认的不同
class Action_A : public BT::SyncActionNode{
    public:
    	// 传递给构造函数的额外参数
    	Action_A(const std::string& name,const NodeConfig& config,int arg_int,std::string arg_str):SyncActionNode(name,config),_arg1(arg_int),_arg2(arg_str){}
    
    BT::NodeStatus tick() override;
    
    private:
    	int _arg1;
    	std::string _arg2;
}

// 注册方式
BT：：BehaviorTreeFactory factory;
// 将参数42和"hello world"传递给每个新建的Action_A实例
factory.registerNodeType<Action_A>("Action_A",42,"hello world");
// 或者显式指定模板参数类型
//factory.registerNodeType<Action_A,int,std::string>("Action_A",42,"hello world");
```

注意：所有用"Action_A"标签创建的节点都会获得相同的参数值，如果每个实例需要不同值，看第二个方法

#### 方法2：使用initialize方法，按需初始化

- 同一个节点类型的不同实例需要不同的参数值
- 只是在xml中写标签，参数值在代码中按实例分别设置
- 节点仍然使用标准构造函数（只有```name```和```config```）
- 添加一个自定义的```initialize```方法，在树创建后，执行前，通过遍历树的方式为每个节点实例设置参数

```cpp
class Action_B:public BT::SyncActionNode{
    public:
    	// 构造函数看起来和通常一样
    Action_B(const std::string& name,const NodeConfig& config):SyncActionNode(name,config){};
    
    	// 我们希望这个方法在第一个tick()之前被调用一次
    void initialize(int arg_int,const std：：string& arg_str){
        _arg1 = arg_int;
        _arg2 = arg_str;
    }
    
    // 此示例不需要任何端口
    static PortsList provoidedPorts(){ return{}; }
    
    // tick()
    BT::NodeStatus tick() override;
    
    private:
    	int _arg1;
    	std::string _arg2;
};

// 注册和初始化
BT：：BehaviorTreeFactory factory;
factory.registerNodeType<Action_B>("Action_B");//标准注册

// 从xml创建树（树中包含多个<Action_B>标签）
auto tree = factory.createTreeFromText(xml_text);

// 定义一个访问器，遍历所有节点，找到Action_B实例并调用initialize
auto visitor = [](BT::TreeNode* node){
    if(auto* action_b = std::dynamic_cast<Action_B*>(node)){
        action_b -> initialize(69,"interesting_value");
    }
};
tree.applyVisitor(visitor)
```

### 默认端口值

#### 输入端口默认值

```cpp
static BT::PortsList providedPorts(){
    return {
        BT::Inputport<Point2D>("pointA"，Point2D{1,2}),
        // 默认值是x=1,y=2
        BT::Inputport<Point2D>("pointB","3,4"),
        // 默认值是x=3,y=4
        // 需要convertFromString转换，从字符串解析为Point2D类型
        BT::Inputport<Point2D>("pointC","{point}"),
        // 默热值指向黑板条目{point}
        BT::Inputport<Point2D>("pointD","{=}"),
        // 默认值指向黑板条目{PointD}（同名）
    }
}
```

#### 输出端口默认值

```cpp
BT::Outport<Point2D>("result","{target}","默认写入黑板target键")
```

输出端口默认值相对受限，因为它们只能指向黑板条目（不能指定一个固定的值），但是仍然支持同名的语法```"{=}"```

注意：输出端口不能设置固定的数值默认值，因为输出端口的作用就是向黑板写数据，所以默认值必须是一个黑板键

## 脚本语言和前后置条件

- 初始化或者修改黑板条目（如```<Script code="">```）
- 在<Perconddition>节点中编写条件表达式，动态决定是否执行子树

**脚本中的变量名就是黑板键名，读写它们相当于操作黑板**

#### 脚本语言

赋值：

```
变量名:=值 //如果黑板中不存在该变量，则创建新条目
变量名=值 //如果黑板中不存在该变量，则抛出异常
```

- ```:=```用于首次赋值或后续修改，自动创建条目
- ```=```只能用于已存在的条目，否则报错

```xml
<Script code="msg:='hello world'" />
<Script code="A:=THE_ANSWER;B:=3.14;color:=RED" />
```

```Precondition```节点

用于条件判断，只有条件成立时才执行其唯一子节点，否则返回指定状态

```xml
<Precondition if="A>B && color!=BLUE" else="FAILURE">
    <Sequence>
        <!--子节点-->
    </Sequence>
</Precondition>
```

在这里可以到后期进行导航决策编写的时候往这方面去想一想和思考一下有关大事件决策的切换（比如云台手标点，比如如果真的很有优势去前压等等）

## 全局黑板和数据架构

全局黑板提供了一种便捷的方式，让所有子树都能直接访问同一份数据，不用写重映射

- 主树有自己的黑板BB1
- 主树下的子树有自己的黑板BB2，BB3——其父黑板是BB1

```cpp
auto global_bb = BT::Blackboard::create(); //全局黑板（最顶层）
auto maintree_bb = BT::Blackboard::create(global_bb); //主树黑板，父为global_bb
auto tree = factory.createTree("MainTree",maintree_bb);
```

全局黑板的生命周期独立于树，即是树被销毁，但是作为全局黑板它仍然存在

在```xml```和脚本中访问全局黑板，通过```@```访问全局数据

## xml模式参考

```xml
<root>
</root>
```



