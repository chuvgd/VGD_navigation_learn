#include "behaviortree_cpp/action_node.h"

class Calculategoal : public BT::SyncActionNode{
    public:
        Calculategoal(const std::string& name,const BT::NodeConfig& config) : SyncActionNode(name,config){}

        static BT::PortsList providedPorts(){
            return { BT::OutputPort<Position2D>("goal")};
        }

        BT::NodeStatus tick() override{
            Position2D mygoal = {1.1,1.2};
            setOutput<Position2D>("goal",mygoal);
            return BT::NodeStatus::SUCCESS;
        }
};
// 在整体上是符合端口名，黑板键进行映射的规则
// 黑板键保持唯一且确定，但是端口可以给黑板键进行映射以更新

class PrintTarget : public BT::SyncActionNode{
    public:
        PrintTarget(const std::string& name , const BT::NodeConfig& config):
        SyncActionNode(name,config){}

        static BT::PortsList providedPorts(){
            // 可选的描述方式
            const char* description = "在控制台上简单地打印目标...";
            return { BT::InputPort<Position2D>("target",description) };
        }

        BT::NodeStatus tick() override{
            auto res = getInput<Position2D>("target");
            if(!res){
                throw RuntimeError("读取端口[target]时出错：",res.error());
            }
            Position2D target = res.value();
            printf("目标位置:[%.1f,%1f]\n",target.x,target.y);
            return BT::NodeStatus::SUCCESS;
        }
};