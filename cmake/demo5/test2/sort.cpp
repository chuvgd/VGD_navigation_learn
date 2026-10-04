#include <iostream>
#include "sort.h"

int main(int argc,char* argv[]){
    int a[] = {5,2,6,4,1,3};
    int b[] = {2,5,3,6,7,9};
    auto n = sizeof(a)/sizeof(int);
    insert_sort(a,n);
    select_sort(b,n);

    for(int i = 0;i < n;i++){
        std::cout<<a[i]<<" ";
    }

    std::cout<<std::endl;

    for(int i =0;i < n;i++){
        std::cout<<b[i]<<" ";
    }

    std::cout<<std::endl;

    return 0;

}