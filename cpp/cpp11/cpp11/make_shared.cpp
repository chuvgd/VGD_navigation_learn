#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Test{
    public:
        Test(){
            cout<<"construct Test..."<<endl;
        }
        Test(int x){
            cout<<"construct Test , x = "<<x<<endl;
        }
        Test(string str){
            cout<<"construct Test , str = "<<str<<endl;
        }
        ~Test(){
            cout<<"destruct Test..."<<endl;
        }
};

int main(){
    //使用智能指针管理一块int型的堆内存，内部引用计数为1
    //申请的内存是普通类型，则直接通过()进行初始化其指向的堆地址即可
    std::shared_ptr<int> ptr1 = std::make_shared<int>(520);
    std::cout<<"ptr1管理的内存引用计数:"<<ptr1.use_count()<<endl;
    
    //使用智能指针管理Test对象的堆内存，调用Test()构造函数
    std::shared_ptr<Test> ptr2 = std::make_shared<Test>();
    std::cout<<"ptr2管理的内存引用计数:"<<ptr2.use_count()<<endl;

    //使用智能指针管理Test对象的堆内存，调用Test(int x)构造函数
    std::shared_ptr<Test> ptr3 = std::make_shared<Test>(520);
    std::cout<<"ptr3管理的内存引用计数:"<<ptr3.use_count()<<endl;
    //等价于
    // Test* p = new Test();
    // delete p

    //注意：std::make_shared<>模板函数传入类的数据类型必须和构造函数传入参数相对应，和new的用法一致
    std::shared_ptr<Test> ptr4 = std::make_shared<Test>("我是要成为海贼王的男人!!!");
    std::cout<<"ptr4管理的内存引用计数:"<<ptr4.use_count()<<endl;

    Test* p = new Test();
    delete p;

    Test* p1 = new Test(12);
    delete p1;

    Test* p2 = new Test("VGD");
    delete p2;
   
    return 0;
}