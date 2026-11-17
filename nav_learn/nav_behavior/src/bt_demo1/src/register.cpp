#include "behaviortree_cpp/bt_factory.h"
#include <iostream>

int main(){
    Gripper gripper;
    g_gripper = &gripper;

    BT::BehaviorTreeFactory factory;

    // 直接通过函数指针注册（无lambda包装，签名已经符合）
    // 注意：函数签名是函数名称加函数参数列表
    factory.registerSimpleCondition("CheckBattery",CheckBatteryFunc);
    factory.registerSimpleAction("OpenGripper",OpenGripperFunc);
    factory.registerSimpleAction("CloseGripper",CloseGripperFunc);

    //ApporachObject仍然保持为节点类(更多扩展和定制)
    factory.registerNodeType<ApproachObject>("ApproachObject");

    auto tree = factory.createTreeFromFile("src/bt_demo1/behavior_trees/demo.xml");

    while(tree.tickOnce() == BT::NodeStatus::RUNNING){
        // 循环或者spin
    }

    return 0;
}