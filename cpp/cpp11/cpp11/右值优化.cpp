#include <iostream>

class Test{
public:
    Test():m_num(new int(100)){
        std::cout<<"construct:my name is jerry"<<std::endl;
    }

    Test(const Test& a):m_num(new int(*a.m_num)){
        std::cout<<"copy construct:my name is tom"<<std::endl;
    }

    //添加移动构造函数
    Test(Test&& a):m_num(a.m_num){
        a.m_num = nullptr;
        //移动构造函使用了右值引用，会将临时对象中的堆内存所有权转移给对象t
        std::cout<< "move construct: my name is sunny"<<std::endl;
    }

    ~Test(){
        delete m_num;
        std::cout<<"destruct Test class..."<<std::endl;
    }

    int* m_num;
};

Test getObj(){
    Test t;
    //创建一个对象
    return t;
    //临时对象就是将亡右值
}

int main(){
    Test t = getObj();
    //在这里就是直接调用移动构造函数直接进行临时对象的浅拷贝，全部移动过来，所有的地址和数据都是Test getObj()函数中的对象t的相关成员
    std::cout << "t.m_num: " << *t.m_num << std::endl;
    return 0;
}

