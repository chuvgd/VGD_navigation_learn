#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Base{
    public:
        void traversal(T& t){
            auto it = t.begin();
            for(; it!= t.end() ; ++it){
                cout<<*it<<" ";
            }
            cout<<endl;
        }
};

int main(){
    std::vector<int> v  = {1,2,3,4,5,6,7,8};
    Base<std::vector<int>>b;
    b.traversal(v);

    return 0;
}