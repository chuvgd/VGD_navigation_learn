#include "behaviortree_cpp/action_node.h"
#include <thread>

struct Pose2D{
    double x,y,theta;
};

namespace chr = std::chrono;

class MoveBaseAction : public BT::StatefulActionNode{
    public:
        // 任何带有端口的树节点都必须使用此签名的构造函数
        MoveBaseAction(const std::string& name , const BT::NodeConfig& config):StatefulActionNode(name,config){}


        // 必须定义此静态方法
        static BT::PortsList providedPorts(){
            return { BT::InputPort<Pose2D>("goal") };
        }

        // 此函数在开始时被调用一次
        BT::NodeStatus onStart() override;

        // 如果onStart()返回除RUNNING以外的内容，会持续调用此方法直到返回除RUNNING以外的
        BT::NodeStatus onRunning() override;

        void onHalted() override;

        private:
            Pose2D _goal;
            chr::system_clock::time_point _completion_time;
};

BT::NodeStatus MoveBaseAction::onStart(){
    if(!getInput<Pose2D>("goal",_goal)){
        throw BT::RuntimeError("缺少必须输入的目标[goal]");
    }
    printf("[MoveBase:发送请求].目标:x=%f y=%f theta=%f\n",_goal.x,_goal.y,_goal.theta);

    // 模拟需要220ms
    _completion_time = chr::system_clock::now()+chr::microseconds(220);

    return BT::NodeStatus::RUNNING;
}

BT::NodeStatus MoveBaseAction::onRunning(){
    std::this_thread::sleep_for(chr::milliseconds(10));

    if(chr::system_clock::now()>=_completion_time){
        std::cout<<"已经完成"<<std::endl;
        return BT::NodeStatus::SUCCESS;
    }
    return BT::NodeStatus::RUNNING;
}

void MoveBaseAction::onHalted(){
    printf("已经终止");
}