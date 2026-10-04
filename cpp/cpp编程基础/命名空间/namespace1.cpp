#include "namespace_part1.hpp"
#include "namespace_part2.hpp"

void MyNamespace::function1(){
    std::cout<<"hello world"<<std::endl;
}

void MyNamespace::function2(){
    std::cout<<"hello vgd"<<std::endl;
}


int main(){
    MyNamespace::function1();
    MyNamespace::function2();

    return 0;
}