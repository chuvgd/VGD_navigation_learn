#include <iostream>

//冒泡排序函数（参数1：数组首个地址，参数2：数组长度）
//int arr[] = int* arr ->数组名代表数组首地址
void bubbleSort(int arr[],int len)//arr是指针,指向原数组（其实传入的就是数组首元素的地址值）
{
    for(int i = 0 ; i < len - 1 ; i++){
        for(int j = 0 ; j < len - i- 1 ; j++){
            //如果j>j+1,就交换数字
            if (arr[j] > arr[j+1]){            
            int temp = arr[j];
            arr[j] = arr[j+1];//改的是原数组的那块内存存储的值
            arr[j+1] = temp;
            }
        }
    }
}//函数传递的是地址，复制的也是地址值，但是是拿到那块地址后是对地址存储的实际值进行修改，函数运行结束之后也是直接自动释放掉复制的地址，原先在main()栈上的数组地址仍然存在
//数组在作为参数传递时会退化成指针，在函数参数里,int arr[]和int* arr完全等价
//当在main()里调用bubbleSort(arr,len)时，数组名arr退化成元素首地址，传递给函数的是一个int*类型的地址
//arr[j]本身就是解引用：arr[j] = *(arr + j)：1.arr+j——指针运算，算出第j个元素地址，这个因为本身arr就是int*类型的首元素地址，arr+j就是对指针地址进行操作，是按照int*地址类型进行的操作
//*：解引用，取出地址上实际存储的int值
//整个流程就是：先是传入地址（复制一遍地址），对复制的地址直接进行操作，因为是都是同一块内存地址，在函数运行完毕之后销毁复制的那块地址，但是地址背后存储的变量值已经被修改（通过解引用穿透过去）

void printArray(int* arr,int len){
    for(int i = 0 ; i < len ; i++){
        std::cout<<arr[i]<<std::endl;
    }
}

int main(){
    //先创建数组
    int arr[] = {4,5,3,87,45,1,2,7};//栈上变量数据，main()运行结束后自动释放

    //数组长度
    int len = sizeof(arr)/sizeof(arr[0]);
    //创建函数，实现冒泡排序
    bubbleSort(arr,len);
    //打印
    printArray(arr,len);

    return 0;
}