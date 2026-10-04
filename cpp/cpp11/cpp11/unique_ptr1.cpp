#include <iostream>
#include <memory>

int main(){
    std::unique_ptr<int> ptr1(new int(10));
    std::unique_ptr<int> ptr2 = std::move(ptr1);

    ptr1.reset();
    ptr2.reset(new int(520));

    return 0;
}

//ptr1.reset(); 解除对原始内存的管理
//ptr2.reset(new int(250)); 先释放原始内存的管理，再去重新管理开辟出的新的原始内存