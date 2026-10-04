#include <iostream>

using namespace std;

template<typename T = int , T t = 520>
class Test{
    public:
        void print(){
            cout<<"current value:"<<t<<endl;
        }
};

int main(){
    Test<> t;
    t.print();

    Test<int , 1024> t1;
    t1.print();

    return 0;
}