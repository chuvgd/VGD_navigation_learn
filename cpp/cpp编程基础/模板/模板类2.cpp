#include <iostream>

template <class T , int size>
class CArray{
    public:
        void Print(){
            for(int i = 0 ; i < size ; ++i){
                std::cout<<array[i]<<std::endl;
            }
        }

    private:
            T array[size];
};

int main(){
    CArray<int , 40> a1;
    CArray<double , 50> a2;

    return 0;
}