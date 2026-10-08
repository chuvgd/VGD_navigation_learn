#include <stdio.h>

int main(int argc,char* argv[]){
    if(argc == 2){
        printf("The arguement supplied is %s\n",argv[1]);
    }
    else if(argc > 2){
        printf("Too many arguements supplied.\n");
    }
    else{
        printf("One argument expected.\n");
    }
}

//argc表示命令行参数数量，包括程序名本身，argc>=1
//argv表示命令行参数本身，因为命令行参数本来就是字符串类型，argv[0]通常为程序名称
