#include <stdlib.h>
#include <stdio.h>

int main(){
    const char* str1 = "2478abc";
    const char* str2 = "abd456";
    const char* str3 = "abc";

    printf("%lld\n",atoll(str1));
    printf("%lld\n",atoll(str2));
    printf("%lld\n",atoll(str3));

    return 0;
}