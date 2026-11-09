#include <ament_index_cpp/get_package_share_directory.hpp>
#include <behaviortree_cpp/bt_factory.h>
#include <rclcpp/rclcpp.hpp>

#include <iostream>
#include <string>

BT::NodeStatus sayHello(BT::TreeNode&){
    std::cout<<"hello from behavior tree"<<std::endl;
    return BT::NodeStatus::SUCCESS;
}

int main(int argc , char** argv){
    rclcpp::init(argc,argv);

    BT::BehaviorTreeFactory factory;
    factory.registerSimpleAction("SayHello",sayHello);

    const std::string tree_path = ament_index_cpp::get_package_share_directory("bt_demo") + "/behavior_trees/demo.xml";

    auto tree = factory.createTreeFromFile(tree_path);
    tree.tickOnce();

    rclcpp::shutdown();
    return 0;
}