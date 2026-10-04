#include <iostream>
using namespace std;

class animal{
   protected:
    	int height;
    	int weight;
   public:
    	animal(int height,int weight){
			this -> height = height;
            this -> weight = weight;
            cout<<"animal的带参构造函数被调用"<<endl;
        }
    	virtual ~animal(){
			cout<<"animal的析构函数被调用"<<endl;//生成虚函数表，和下面的new和delete对应起来
        }
};

class fish : public animal{
    public:
    fish():animal(100,200)//初始化列表中先显式调用父类的构造函数
    {
        cout<<"fish的构造函数被调用"<<endl;
    }
    virtual ~fish(){
		cout<<"fish的析构函数被调用"<<endl;
    }
};

int main(int argc,char* argv[]){
    //在堆上开辟地址资源，地址类型是animal，但是实际指向的对象是fish类的实例化对象
    animal* fish_obj = new fish();
    //此处是动态绑定——虚析构函数本身就是在做多态
    delete fish_obj;
    return 0;
}