#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char* str;

    /*最初的内存分配*/
    str = (char*)malloc(15);
    strcpy(str,"runoob");
    printf("String = %s,Address = %lu\n",str,(unsigned long)str);
    // printf("String = %s,Address = %u\n",str,(unsigned int)str);//错误，数据类型对上了，但是数据被截断了，64位操作系统是8字节的地址值大小
    printf("String = %s,Address = %p\n",str,(void*)str);

    /*重新分配内存*/
    str = (char*)realloc(str,25);
    strcat(str,".com");
    printf("String = %s,Address = %lu\n",str,(unsigned long)str);
    printf("String = %s,Address = %p\n",str,(void*)str);

    free(str);
    return 0;
}


//malloc内的参数是需要动态分配的字节数，而不是可以存储的元素个数
//当动态分配内存时，存储的是字符型数据，每个元素1字节，所以字节数刚好等于需要存储的元素个数（字符数+1）
//如果存储的是整型或者浮点型，字节数等于需要存储的元素个数*一个元素的字节数，代码格式：
//type* var_name = (type*)malloc(sizeof(type)*num);