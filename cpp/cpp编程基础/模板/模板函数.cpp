#include <iostream>

using namespace std;

template <class T>
void Swap(T& x,T& y){
    T tmp = x;
    x = y;
    y = tmp;
}

int main(){
    int n = 1,m = 2;
    Swap<int>(n,m);

    cout<<"n = "<<n<<" m = "<<m<<endl;

    return 0;
}