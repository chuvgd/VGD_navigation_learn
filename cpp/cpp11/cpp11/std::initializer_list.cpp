#include <iostream>
#include <string>

void traversal(std::initializer_list<int> a){
    for(auto it = a.begin();it != a.end();++it){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
}

int main(){
    std::initializer_list<int> list;
    std::cout<<"current list size:"<<list.size()<<std::endl;
    traversal(list);
    std::cout<<std::endl;

    std::initializer_list<int> list1 = {1,2,3,4,5,6,7,8,9,0};
    std::cout<<"current list size:"<<list1.size()<<std::endl;
    traversal(list);
    std::cout<<std::endl;

    std::initializer_list<int> list2 = {1,3,5,7,9};
    std::cout<<"current list size:"<<list2.size()<<std::endl;
    traversal(list);
    std::cout<<std::endl;

    //直接列表初始化传递参数
    traversal({2,4,6,8,0});
    std::cout<<std::endl;

    traversal({11,12,13,14,15,16});
    std::cout<<std::endl;


    return 0;
}