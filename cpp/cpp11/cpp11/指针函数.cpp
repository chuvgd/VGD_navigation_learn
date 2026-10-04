#include <iostream>

struct struct_data
{
    int a;
    int b;
};

using Data = struct_data;

Data* f(int a,int b){
    Data* data = new Data;
    data -> a = a;
    data -> b = b;

    return data;
}

int main(){
    Data* mydata = f(4,5);
    std::cout<<"f(4,5) = "<<mydata -> a <<","<<mydata -> b<<std::endl;

    return 0;
}