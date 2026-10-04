#include <iostream>

using namespace std;

template<typename T = int>
void func(T t){
    cout<<"current value:"<<t<<endl;
}

int main(){
    func<int>(100);
    func<double>(100.1);

    return 0;
}