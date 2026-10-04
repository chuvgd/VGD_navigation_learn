#include <iostream>

int&& value = 520;
class Test{
    public:
        Test(){
            std::cout<<"construct:my name is jerry"<<std::endl;
        }
        Test(const Test& a){
            std::cout<<"copy construct:my name is tom"<<std::endl;
        }
};

Test getObj(){
    return Test();
}

int main(){
    int a1;
    // int&& a2 = a1;//error
    //a1写在=右边，但是它仍然是一个左值，使用左值初始化一个右值引用类型是不合法的
    // Test& t = getObj();//error
    //右值不能给普通的左值引用赋值
    Test&& t = getObj();
    //getObj()返回的临时对象被称为将亡值，t是这个将亡值的右值引用
    const Test& t1 = getObj();
    //常量左值引用是一个万能引用类型，它可以接受左值，右值，常量左值和常量右值
    return 0;
}