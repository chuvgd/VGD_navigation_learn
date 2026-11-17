#include "behaviortree_cpp/action_node.h"

class ThinkWhatToSay : public BT::SyncActionNode{
    ThinkWhatToSay(const std::string& name,const BT::NodeConfig& config) : SyncActionNode(name,config)
    {}

    static BT::PortsList providedPorts(){
        return { BT::OutputPort<std::string>("text") };
    }

    // 这个动作将值写入端口"text"
    BT::NodeStatus tick() override{
        setOutput("text","答案是42");
        return BT::NodeStatus::SUCCESS;
    }
};