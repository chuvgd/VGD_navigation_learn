#include <iostream>

/// @brief 
/// @tparam T1 
/// @tparam T2 
//类模板
template <class T1 , class T2>
class Pair{
    public:
        Pair(T1 k , T2 v):m_key(k),m_value(v){};
        //类内成员函数，对于后续比较就是将<左侧的实例类型绑定到this，同理右侧绑定到const  Pair<T1 , T2>& p
        bool operator < (const  Pair<T1 , T2>& p) const;
        // bool operator < (const Pair<T1 , T2>* this , const Pair<T1 , T2>& p) const

    private:
        T1 m_key;
        T2 m_value;
};


//类模板里面成员函数的写法
template <class T1 , class T2>
//对于模板类，就需要写成：类名<参数类型1,参数类型2>——表示这个是类的类（类的模板）的作用域下
bool Pair<T1,T2>::operator <(const Pair<T1 , T2>& p) const{
    return m_value < p.m_value;//两个类对象的成员进行大小比较
}

int main(){
    //对类的模板进行实例化，并对类的类进行对象实例化（一步到位的实例化）
    Pair<std::string , int> A("RM",20);
    Pair<std::string , int> B("RH",19);

    //A < B实际上是A.operator <(B),B现在的类型被A限定住了，但是本身是可以变的，但是主要是因为这个是类内成员函数所以T1和T2根据绑定的this而定
    //同一个模板可以被实例化很多次——泛型的意义
    std::cout<<(A < B)<<std::endl;
    
    return 0;
}