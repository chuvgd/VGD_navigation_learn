#include <iostream>

using namespace std;

class Parent{
    public:
        int pub_var;
    protected:
        int pro_var;
    private:
        int pri_var;//只有Parent类自己可以操作

    public:
        Parent(){
        pub_var = 1;
        pro_var = 2;
        pri_var = 3;}//构造函数

};

//公有继承：
class chlidA : public Parent{
    public:
        void test(){
            cout<<pub_var<<endl;
            cout<<pro_var<<endl;
            // cout<<pri_var<<endl;错误——父类私有成员不可见
        }
};

//受保护继承：
class childB : protected Parent{
    public:
        void test(){
            cout<<pub_var<<endl;//这个是可以访问到的，但是在childB这个类中，它是protected
            //即：protected:   pub_var;
            cout<<pro_var<<endl;
        }
};

//私有继承：
class childC : private Parent{
    public:
        void test(){
            cout<<pub_var<<endl;//继承的情况下只有私有成员继承后不可进行访问
            cout<<pro_var<<endl;//这个只是在childC来看，它是private的
        }
};

int main(){
    chlidA a;
    cout<<a.pub_var<<endl;
    // cout<<a.pro_var<<endl;//错误，外部不可以访问protected

    childB b;
    // cout<<b.pub_var<<endl;//错误，因为是protected继承，pub_var在外部变成了protected

    childC c;
    // cout<<c.pub_var<<endl;//错误，和上述同理

    return 0;
}

