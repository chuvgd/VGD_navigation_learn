#include <iostream>
using namespace std;

double division(int a,int b){
    if(b == 0){
        throw "Division by zero condition!";
    }//throw抛出异常——抛出异常的是const char*(常量字符数组)
    return (a/b);
}

int main(){
    int x = 50;
    int y = 0;
    double z = 0;

    try{
        z = division(x,y);
        cout<<z<<endl;
    }catch(const char* msg){
        cerr<<msg<<endl;//cerr就是输出抛出异常
        //catch是捕捉异常——捕捉到抛出的异常
    }

    return 0;
}