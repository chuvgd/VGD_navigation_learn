#include  <iostream>

//在成员函数参数列表后面加const，表示该函数不会修改对象状态
class Myclass{
    public:
        int getValue() const;//const成员函数声明
        Myclass(){};
        void setValue(){};
    private:
        int value;
        void helper() const{};//另一个const成员函数
};

int Myclass::getValue() const{
    helper();//合法
    //value = 10;错误，const成员函数不能修改成员函数
    return value;//只能读取，不能修改成员变量
}



//核心限制规则：
//1.禁止修改成员变量，在const成员函数内不能直接修改非静态成员变量
//2.调用限制：const成员函数只能调用其他const成员函数或者静态成员函数
//3.常量对象调用：只有const成员函数能被常量对象调用

int main(){
    const Myclass obj;//const对象 = 只能读，不能写；对象一旦构造完成，所有的成员都只读
    obj.getValue();
    std::cout<<obj.getValue()<<std::endl;
// obj.setValue();//错误，非const成员函数不能被const对象调用

return 0;
}

//底层：const成员函数通过将this指针声明为指向常量对象的指针实现限制
//普通成员函数：void func(A* const this) A* const this是指针常量——即不能修改指针指向
//const成员函数：void func(const A* const this)


//析构函数/构造函数不能声明为const，因此需要初始化或释放对象状态
//返回值与const：若返回成员的非const引用，可能会破坏const语义

//const成员函数：把A* const this变成const A* const this，变成了禁止通过this修改成员，而构造函数的职责恰恰就是初始化写入成员，构造函数声明为const，就变成可读，无法写入即无法完成初始化
//析构函数同理
//const对象构造完成后状态就被冻结，之后任何成员修改不了，所以“写成员”只能发生在构造函数里，构造函数是唯一一次合法初始化的机会
//const对象构造之后就不能进行修改，构造时就必须把所有成员初始化完成，隐式构造不给value赋值