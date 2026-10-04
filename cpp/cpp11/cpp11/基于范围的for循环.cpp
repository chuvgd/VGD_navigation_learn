#include <iostream>
#include <vector>

using namespace std;

int main(){
    std::vector<int> t = {1,2,3,4,5};
    for(auto& value : t){
        cout<<++value<<endl;
        //注意++value和value++的区别：前者先计算再输出，后者先输出后计算
    }

    return 0;
}