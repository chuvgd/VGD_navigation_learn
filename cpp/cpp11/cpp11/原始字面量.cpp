#include <iostream>

using namespace std;

int main(){
    // string str = "D:\hello\world\test.text";
    // cout<<str<<endl;
    string str1 = "D:\\hello\\world\\test.text";
    cout<<str1<<endl;
    string str2 = R"this(D:\hello\world\test.text)this";
    cout<<str2<<endl;

    return 0;
}