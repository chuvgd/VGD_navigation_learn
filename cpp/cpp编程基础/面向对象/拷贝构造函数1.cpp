#include <iostream>
//复制对象把它作为参数传递给函数

class Line
{
    public:
        int  getLength(void);
        Line(int len);//简单构造函数
        Line(const Line &obj);//拷贝构造函数
        ~Line();//析构函数

    private:
        int* ptr;
};

//成员函数定义，包括构造函数
Line::Line(int len){
    std::cout<<"调用构造函数"<<std::endl;
    //为指针分配内存
    ptr = new int;
    *ptr = len;
}

Line::Line(const Line &obj)
//在这里，obj是一个对象引用，该对象是用于初始化另一个对象的
{
    std::cout<<"调用拷贝构造函数并为指针ptr分配内存"<<std::endl;
    ptr = new int;
    *ptr = *(obj.ptr);//拷贝值
    //*obj.ptr等价于*(obj.ptr)，因为.优先级高于*
}
Line::~Line(void){
    std::cout<<"释放内存"<<std::endl;
    delete ptr;
}

int Line::getLength(void){
    return *ptr;
}

void display(Line obj){
    std::cout<<"line大小:"<<obj.getLength()<<std::endl;
}

int main(){
    Line line(10);

    display(line);

    return 0;
}
