#include <iostream>

//类模板
template <class T1 , class T2>
class Pair
{	
    private:
    	T1 key; //关键字
    	T2 value; //值
    
    public:
    	Pair(T1 k , T2 v):key(k),value(v){};
    
    	//友元函数模板
    	template <class T3,class T4>
        friend std::ostream& operator << (std::ostream& o , const Pair<T3,T4>& p);
};

//模板函数
template <class T3 , class T4>
std::ostream& operator << (std::ostream& o , const Pair<T3 , T4>& p){
	o<<"("<<p.key<<","<<p.value<<")";
    return o;
}

int main(){
	Pair<std::string , int> student("Tom" , 29);
    Pair<int , double> obj(12 , 3.14);
    
    std::cout<<student<<" "<<obj<<std::endl;
    //实际上：<<student就是将<<传入形式引用参数std::ostream& o;student传入const Pair<T3,T4>& p

    return 0;
}