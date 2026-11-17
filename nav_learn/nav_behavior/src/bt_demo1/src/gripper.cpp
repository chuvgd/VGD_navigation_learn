// 通过全局指针访问
// 类成员函数形式，成员函数本身并不符合BT::NodeStatus(BT::TreeNode&)
#include "bt_demo1/gripper.hpp"
#include "rclcpp/rclcpp.hpp"
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

class Gripper{
    public:
        BT::NodeStatus open(){
            is_open_ = true;
            std::cout<<"Gripper::open"<<std::endl;
            return BT::NodeStatus::SUCCESS;
        }
        BT::NodeStatus close(){
            is_open_ = false;
            std::cout<<"Gripper::close"<<std::endl;
            return BT::NodeStatus::SUCCESS;
        }
        bool isOpen() const { return is_open_; }
    private:
        bool is_open_ = true;
};

int main(int argc , char** argv){
    Gripper* g_gripper;

    BT::NodeStatus OpenGripper(BT::TreeNode& self){
        (void)self;
        if(g_gripper) return g_gripper->open();
        return BT::NodeStatus::FAILURE;
    }

    BT::NodeStatus CloseGripper(BT::TreeNode& self){
        (void)self;
        if(g_gripper) return g_gripper->close();
        return BT::NodeStatus::FAILURE;
    }

    Gripper gripper;

    BT::BehaviorTreeFactory factory;

    // 使用lambda函数捕获gripper对象，并将调用适配为所需签名
    factory.registerSimpleAction("CloserGripper",[&](BT::TreeNode& self)
    {
        (void)self;
        return gripper.close();
    })
}