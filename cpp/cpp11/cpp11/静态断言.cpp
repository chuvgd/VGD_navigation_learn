#include <iostream>
using namespace std;

int main(){
    static_assert(sizeof(long) == 8,"错误,不是64位平台...");
    cout<<"64bit linux指针大小是"<<sizeof(char*)<<endl;
    cout<<"64bit linux long大小是"<<sizeof(long)<<endl;

    return 0;
}