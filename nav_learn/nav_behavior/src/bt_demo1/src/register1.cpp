#include "behaviortree_cpp/bt_factory.h"

int main(int argc,char** argv){
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    auto tree = factory.createTreeFromFile("../behavior_tree/demo1.xml");
    tree.tickWhileRunning();
    // tickWhileRunning()反复tick()根节点，直到树返回成功或者失败，注意这里运行的是根节点
    // 行为树是由根节点串连而成的树状结构
    return 0;
}