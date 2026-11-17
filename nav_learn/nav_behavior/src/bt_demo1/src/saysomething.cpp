#include "behaviortree_cpp/action_node.h"

class SaySomething : public BT::SyncActionNode{
    public:
        // 如果你的节点有端口，必须使用这个构造函数签名
        SaySomething(const std::string& name , const BT::NodeConfig& config) : BT::SyncActionNode(name,config){}

        // 必须定义这个静态方法
        // providedPorts()告诉工厂这个节点有一个输入端口，名为message，类型是std::string
        static BT::PortsList providedPorts(){
            // 名为"message"输入端口
            return { BT::InputPort<std::string>("message")};
        }

        // 重写虚函数tick()
        // 在tick()中使用getInput<T>("端口名")读取数据
        // 返回一个Expected<T>对象，需要检查有效性
        BT::NodeStatus tick() override{
            BT::Expected<std::string> msg = getInput<std::string>("message");
            // 检查期望值是否有效
            if(!msg){
                throw BT::RuntimeError("缺少必须的输入[message]:",msg.error());
            }
            std::cout<<"机器人说:"<<msg.value()<<std::endl;

            return BT::NodeStatus::SUCCESS;
        }
};