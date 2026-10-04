#include <iostream>
#include <string>

using namespace std;

int main(){
    string str1 = "45";
    string str2 = "3.14159";
    string str3 = "9527 with words";
    string str4 = "words and 2";

    int myint1 = std::stoi(str1);
    float myint2 = std::stof(str2);
    int myint3 = std::stoi(str3);

       // 错误： 'std::invalid_argument'
    // int myint4 = std::stoi(str4);

    cout << "std::stoi(\"" << str3 << "\") is " << str3 << endl;
    cout << "std::stoi(\"" << str1 << "\") is " << myint1 << endl;
    cout << "std::stof(\"" << str2 << "\") is " << myint2 << endl;
    cout << "std::stoi(\"" << str3 << "\") is " << myint3 << endl;
    // cout << "std::stoi(\"" << str4 << "\") is " << myint4 << endl;
}