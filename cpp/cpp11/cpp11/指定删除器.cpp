#include <iostream>
#include <memory>

//自定义删除器函数，释放int类型内存
//这是回调函数，在函数需要被执行的时候去注入执行
void deletePtr(int* p){
    delete p;
    std::cout<<"int型内存被释放了..."<<std::endl;
}

int main(){
    std::shared_ptr<int> ptr(new int(250) , deletePtr);
    return 0;
}

// 删除器函数也可以是lambda表达式
// int main(){
//     std::shared_ptr<int> ptr(new int(250),[](int* p){delete p;});
//     return 0;
// }