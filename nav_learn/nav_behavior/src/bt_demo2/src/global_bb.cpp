#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"

class PrintNumber : public BT::SyncActionNode{
    public:
        PrintNumber(const std::string& name,const BT::NodeConfig& config) : BT::SyncActionNode(name,config){}

        static BT::PortsList providedPorts(){
            return { BT::InputPort<int>("val") };
        }

        BT::NodeStatus tick() override{
            const int val = getInput<int>("val").value();
            return BT::NodeStatus::SUCCESS;
        }
};

int main(){
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<PrintNumber>("PrintNumber");
    factory.registerBehaviorTreeFromText(xml_main);

    auto global_bb = BT::Blackboard::create();
    auto maintree_bb = BT::Blackboard::create(global_bb);
    auto tree = factory.createTree("MainTree",maintree_bb);

    // 直接和全局黑板交互
    // 写入全局黑板键"value"
    global_bb -> set("value",1);

    tree.tickOnce();

    // 读取黑板键"value_sqr"
    auto value_sqr = global_bb -> get<int>("value_sqr");
    
}