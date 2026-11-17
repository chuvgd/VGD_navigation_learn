#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

int main(){
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<DummyNodes::SaySomething>("SaySomething");


    // 查找文件夹中的所有xml文件并注册它们
    std::string search_directory = "./";

    using std::filesystem::directory_iterator;
    for(auto const& entry : directory_iterator(search_directory)){
        if(entry.path().extension() == ".xml"){
            factory.registerBehaviorTreeFromFile(entry.path().string());
        }
    }
    // 相当于：
    // factory.registerBehaviorTreeFromFile("./main_tree.xml");
    // factory.registerBehaviorTreeFromFile("./subtree_A.xml");
    // factory.registerBehaviorTreeFromFile("./subtree_B.xml");
    
    // 创建MainTree，子树将被自动添加
    std::cout<<"----MainTree tick----"<<std::endl;
    auto main_tree = factory.createTree("MainTree");
    main_tree.tickWhileRunning();

    return 0;
}