#include <iostream>
#include <memory>
using namespace std;

template <typename T>
shared_ptr<T> make_share_array(size_t size)
{
    // 返回匿名对象
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}

int main()
{
    shared_ptr<int> ptr1 = make_share_array<int>(10);
    // 拿到数组每个元素的地址进行操作（裸指针操作）
    // *(ptr1.get()) = 10;
    // *(ptr1.get()+1) = 11;
    //或者：拿到首个地址给接收对象进行操作（取出数组首个地址——裸指针）
    // int* p = ptr1.get();
    cout << ptr1.use_count() << endl;
    shared_ptr<char> ptr2 = make_share_array<char>(128);
    cout << ptr2.use_count() << endl;
    
    return 0;
}

//对于初始化：由于是智能指针对象，我们需要拿到裸指针去修改存储的数据,用get()函数