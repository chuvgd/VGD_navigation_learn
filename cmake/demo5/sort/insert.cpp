#include <iostream>
#include "sort.h"

//插入排序：把 arr[i] 插入到前面已经有序的区间 arr[0..i-1] 中
//函数中传入数组形参，int arr[] = int* arr是等价的，即传入数组的首地址和传入数组名是等价的
void insert_sort(int arr[], int n){
    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i - 1;
        //比 key 大的元素统一后移一位
        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
