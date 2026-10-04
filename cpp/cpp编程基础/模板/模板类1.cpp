#include <iostream>

using namespace std;

template <class T>
class A{
    public:
        template <class T2>
        void Func(T2 k){
            cout<<k<<endl;
        }
};

int main(){
    A<int> a;

    a.Func<char>('k');
    a.Func<std::string>("hello");

    return 0;
}