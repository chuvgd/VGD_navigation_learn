// 通过函数指针包装成节点进行执行，这里是普通函数
#include "rclcpp/rclcpp.hpp"
#include "bt_demo1/checknbattery.hpp"
#include "behaviortree_cpp/action_node.h"

BT::NodeStatus CheckBattery(BT::TreeNode& self){
    (void)self;
    bool battery_ok = true;
    std::cout<<"[Battery OK]"<<std::endl;
    return battery_ok ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}