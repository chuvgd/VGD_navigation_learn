#include <iostream>
#include <string>
#include <vector>

class Test{
    public:
        Test(std::initializer_list<std::string> list){
            for(auto it = list.begin();it != list.end(); ++it){
                std::cout<<*it<<" ";
                m_names.push_back(*it);
            }
            std::cout<<std::endl;
        }
    private:
        std::vector<std::string> m_names;
};

int main(){
    Test t1({"RM","VGD","CHD"});
    Test t2({"RM1","VGD1","CHD1"});

    return 0;
}