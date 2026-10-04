#include <iostream>

enum class China {Shanghai,Dongjing,Beijing,Nanjing,};
enum class Japan:char {Dongjing,Daban,Hengbin,Fudao};

int main(){
    // int m = Shanghai;//error
    // int n = China::Shanghai;//error
    if((int)China::Beijing>=2){
        std::cout<<"ok"<<std::endl;
    }

    std::cout<<"size1:"<<sizeof(China::Dongjing)<<std::endl;
    std::cout<<"size2:"<<sizeof(Japan::Dongjing)<<std::endl;

    return 0;
}