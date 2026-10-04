#include <iostream>

using namespace std;

class VGD{
    private:
        int a;
        int b;
    
    public:
        void setA(int a){
            this -> a = a;
        }
        void setB(int b){
            this -> b = b;
        }
        int add(){
            return a + b;
        }
        friend VGD operator + (const VGD& vgder1 , const VGD& vgder2){
            VGD vgder;
            vgder.a = vgder1.a + vgder2.a;
            vgder.b = vgder1.b + vgder2.b;
            return vgder;
}
};


// VGD operator + (const VGD& vgder1 , const VGD& vgder2){
//             VGD vgder;
//             vgder.a = vgder1.a + vgder2.a;
//             vgder.b = vgder1.b + vgder2.b;
//             return vgder;
// }

int main(){
    VGD vgder1;
    vgder1.setA(10);
    vgder1.setB(2);
    cout<<"add of vgder1:"<<vgder1.add()<<endl;

    VGD vgder2;
    vgder2.setA(1);
    vgder2.setB(1);
    cout<<"add of vgder2:"<<vgder2.add()<<endl;

    VGD vgder3;
    vgder3 = vgder1 + vgder2;
    // vgder1 + vgder2 = vgder3;
    // vgder3.setA(10);
    // vgder3.setB(2);
    cout<<"add of vgder3:"<<vgder3.add()<<endl;

    return 0;
}