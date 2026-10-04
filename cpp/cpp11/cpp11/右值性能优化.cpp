#include <iostream>

class Test{
    public:
        Test():m_num(new int(100)){
            std::cout<<"construct:my name is jerry"<<std::endl;
        }

        Test(const Test& a):m_num(new int(*a.m_num)){
            std::cout<<"copy construct: my name is tom"<<std::endl;
        }
        ~Test(){
            delete m_num;
        }

        int* m_num;
};

Test getObj(){
    Test t;
    //对象里面有堆成员m_num=100
    //创建对象，调用构造函数
    return t;
    //复制创建的对象——临时对象用来返回
}

int main(){
    Test t = getObj();
    //深拷贝，将将亡值t传入Test(const Test& a)进行拷贝初始化成员
    //调用时，调用拷贝构造函数对返回的临时对象进行了深拷贝得到了对象t
    std::cout<<"t.m_num"<<*t.m_num<<std::endl;

    return 0;
}

//在getObj()函数中创建的对象虽然进行了内存的申请操作，但是没有使用就释放了
//如果能够使用临时对象已经申请的资源，既可以节省资源（减少复制），还能节省资源申请和释放的时间
//右值引用具有移动语义，移动语义可以将资源（堆，系统对象等）通过浅拷贝从一个对象转移到另一个对象，这样就可以减少不必要的临时对象的创建，拷贝和销毁


