//重写tick函数执行节点
#include <rclcpp/rclcpp.hpp>
#include <behaviortree_cpp/action_node.h>

class ApproachObject : public BT::SyncActionNode
// 创建一个类，继承namespace BT下的SyncActionNode（同步动作节点）
{
    public:
    //父类构造函数不是默认或者无参构造，需要显式传入参数
        ApproachObject(const std::string& name,const BT::NodeConfig& config) : BT::SyncActionNode(name,config){
      }

      // 节点核心，行为树执行到这个节点的时候会调用这个函数，这个函数必须返回一个NodeStatus
      // 也可以通过一个函数指针创建树节点
      // BT::NodeStatus myFunction(BT::TreeNode& self)
      // 参数列表必须只能有一个参数：BT::TreeNode& self，它是一个节点的引用，代表当前正在执行的这个节点本身
      BT::NodeStatus tick() override//自定义重写虚函数
      {
        std::cout<<"ApproachObject"<<this->name()<<std::endl;
        return BT::NodeStatus::SUCCESS;
      }

      static BT::PortsList providedPorts(){
        return{};
      }
};