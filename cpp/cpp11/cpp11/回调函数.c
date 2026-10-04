#include <stdio.h>

int Callback_1(){
    printf("Hello,this is callback_1\n");
    return 0;
}

int Callback_2(){
    printf("Hello,this is callback_2\n");
    return 0;
}
int Callback_3(){
    printf("Hello,this is callback_3\n");
    return 0;
}

int Handle(int (*Callback)()){
    printf("Entering Hanedle Function\n");
    Callback();
    printf("Leaving Handle Function\n");
}

int main(){
    printf("Entering Main Function\n");
    Handle(Callback_1);
    Handle(Callback_2);
    Handle(Callback_3);
    printf("Leaving Main Function\n");

    return 0;
}

//Handle()函数里面的参数是一个指针，在main()函数里面调用Handle()函数的时候，给它传入了函数的指针，这里函数名就是对应函数指针
//回调函数其实就是函数指针的一种用法