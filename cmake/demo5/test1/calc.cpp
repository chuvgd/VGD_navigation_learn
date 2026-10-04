#include <iostream>
#include "calc.h"

int main(int argc,char* argv[]){
    int a;
    int b;
    std::cin>>a>>b;
    std::cout<<"a+b: "<<add(a,b)<<std::endl;
    std::cout<<"a-b: "<<sub(a,b)<<std::endl;
    std::cout<<"a*b: "<<mult(a,b)<<std::endl;
    std::cout<<"a/b: "<<divide(a,b)<<std::endl;

    return 0;
}