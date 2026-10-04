# cpp11新特性

## 一.原始字面量

语法：

```cpp
R"xxx(原始字符串)xxx"
//其中()两边的字符串可以省略，原始字面量R可以直接表示字符串的实际含义，而不需要额外对字符串做转义或者连接等操操作，两边的字符窜必须相同
```

## 二.类成员的快速初始化

### 1.cpp98标准的类成员初始化

98的标准中，支持了在类声明中使用```等号 = 加初始值```的方式，来初始化类中的静态成员常量——“就地声明”，而非静态成员变量的初始化则必须在构造函数中进行

```cpp
struct Base{
	Base():a(250){}
    Base)(int num):a(num){}
    
    int a;
    int b = 1;//类的非静态成员，必须在构造函数中进行初始化
    static int c = 0;//类的静态成员，必须在类的外部初始化
    static const double d = 3.14;//类的静态常量成员，但不是整型或者枚举，无法通过编译
    static const char* const e = "i am luffy";//同上
    const static int f = 0;
}
```

### 2.cpp11标准的类成员初始化

#### 2.1 初始化类的非静态成员

在进行类成员变量初始化的时候，cpp11允许在定义类的时候在类内部直接对非静态成员变量进行初始化

方式： = / {}(等号可以省略不写)

```cpp
class Test{
    private:
    	int a = 9;
   		int b = {5};
    	int c{12};
    	double array[4] = {3.14,3.25,3.16,2.23};
    	double array1[4]{3.14,3.15,3.16,3.17};
    	string s1("hello");//error
		string s2{"hello,world"};
}
```

#### 2.2类内部赋值和初始化列表

除了在构造函数内部进行赋值，也可以在类的初始化列表进行初始化（这种方式比在构造函数内部赋值效率高）

```cpp
class Init{
	public:
    	Init(int x , int y , int z):a(x),b(y),c(z){
			int a = 1;
            int b = 2;
            int c = 3;
        }
    
};
```

在类内部就地初始化和初始化列表并不冲突，程序员可以为同一成员变量既在类内部就地初始化，又在初始化类表中进行初始化，只不过初始化列表总是看起来**后作用于**非静态成员，也就是说，通过**初始化列表指定的值会覆盖就地初始化时指定的值**

## 三.Final和Override

cpp中增加了final关键字来限制某个**类不能被继承**，或者**某个虚函数不能被重写**

如果使用final修饰函数，只能修饰虚函数，并且需要把final关键字放到类或者函数的后面

### final修饰函数 

```cpp
class Base{
    public:
    	virtual void test(){
			cout<<"Base class..."<<endl;
        }
};

class Child : public Base(){
	public:
    	void test() final{
			cout<<"Child class..."<<endl;
        }
};

class GrandChild : public Child{
    public:
    	//错误语法,不允许重写
    	void test(){
            cout<<"GrandChild class..."
        }
}
```

test()是基类中的一个虚函数，在子类重写这个方法，但是不希望孙子类中继续重写这个方法，因此在子类中将test()方法标记为final，孙子类中对这个方法就只有使用的权限了

### final修饰类

使用final关键字修饰过的类是不允许被继承的，也就是说这个类不能有派生类

```cpp
class Base{
    public:
    	virtual void test(){
            cout<<"Base class..."<<endl;
        }
};

class Child final : public Base{
    public:
    	void test(){
            cout<<"Child class..."<<endl;
        }
};

//error,语法错误
class GrandChild : public Child{
    public: 
};
```

Child类是被fianl修饰过的，因此Child类不允许有派生类GrandChild类继承，Child是个断子绝孙类

### override修饰虚函数

override关键字确保在派生类中声明的重写函数与基类的虚函数有相同的函数签名，同时也明确表明将会重写基类的虚函数，保证重写虚函数的正确性，提高代码可读性，和final一样这个关键字要写到方法的后面

使用了override关键字之后，假设在重写过程中因为误操作，写错了函数名或者函数参数或者返回值类型编译器都会提示语法错误，提高了程序的正确性

## 四.模板的优化

### 1.模板的右括号

在泛型编程中，模板实例化对于连续两个右尖括号（>>）会被编译器解析成右移操作符，而不是模板参数表的结束

**这里先简单介绍一下stl标准模板库（stl库的设计基于泛型编程）**

stl库是一套强大的cpp模板类和函数的集合，它提供了一系列通用的，可复用的算法和数据结构，stl分为多个组件，包括容器，迭代器，算法，函数对象和适配器

- 容器：提供了各种数据结构，包括向量(vector)，链表(list)，队列(queue)，栈(stack)，集合(set)，映射(map)

- 算法：用于对容器中元素进行各种操作，包括排序，搜索，复制，移动，变换等
- 迭代器：用于遍历容器中的元素，允许以统一的方式访问容器中的元素，而不用关心容器的内部实现细节
- 函数对象：函数对象是可以像函数一样调用的对象，可以用于算法中的各种操作
- 适配器：适配器将用于将一种容器或者迭代器适配成另一种容器或者迭代器，以满足特定需求

常见头文件：

- <iostream>：提供输入输出流（std::cin和std::cout）
- <vector>：提供了向量的实现，向量是一个动态数组，可以在运行时动态调整大小
- <cmath>：提供了常用的数学函数，常用于数值计算
- <string>：提供了字符串类的实现
- <algorithm>：提供了很多常用算法，如排序，查找以及遍历等，应用于各种容器

先来介绍一下：**std::vector**

<vector>是stl中的一个**容器类**，用于存储动态大小的数组

<vector>是一个序列容器，它允许用户在容器的末尾快速地添加或者删除元素

- 声明一个vector：

```cpp
std::vector<int> myVector;
```

- 添加元素：

```cpp
myVector.push_back(10);
```

- 访问元素：

```cpp
int firstElement = myVector[0];
```

- 获取元素数量:

```cpp
size_t size = myVector.size();
```

- 清空vector：

```cpp
myVector.clear();
```

在这里只去介绍对这个类的声明和初始化，后续学习相关成员函数可以查阅菜鸟文档（或者其他文档）相关内容

```cpp
#include <iostream>
#include <vector>

int main(){
    std::vector<int> vec1;  //空的vector模板类对象
    std::vector<int> vec2(5); //长度是5的vector，元素默认初始化
    std::vector<int> vec3(5,10); //长度是5的vector，元素值是10
    std::vector<int> vec4 = {1,2,3,4}; //使用初始化列表初始化
	
    return 0;
} 
```

回到上述的模板右尖括号，cpp11改进了编译器地解析规则，尽可能地将多个右尖括号(>)解析成模板参数结束符，方便我们编写模板相关地代码

### 3.默认模板参数

在cpp98中，类模板可以有默认的模板参数

但是不支持函数默认参数，在cpp11添加了对函数模板默认参数的支持

当所有模板参数都有默认参数时，函数模板的调用如同一个普通函数，但是对于类模板而言，哪怕所有参数都有默认参数，在使用的时候必须在模板名后跟随<>来实例化

**另外：函数模板的默认模板参数在使用规则上和其他默认参数也有一些不同，它没有必须写在参数表的最后的限制**

```
当默认模板参数和模板参数自动推导同时使用：
- 如果可以推导出参数类型则使用推导出的类型
- 如果函数模板无法推导出参数类型，那么编译器会使用默认模板参数
- 如果无法推导出模板参数类型并且没有设置默认模板参数，编译器就会报错
注意：1.模板参数类型的自动推导是根据模板函数调用时指定的实际参数进行推导的，没有实参则无法推导
2.模板参数类型的自动推导不会参考函数模板中指定的默认参数
```

## 五.数值类型和字符串之间的转换

在cpp11中提供了专门的类型转换函数

### 1.数值转换成字符串

使用to_string()方法可以非常方便地将各种数值类型转换成字符串类型，这是一个重载函数声明于头文件<string>中

```cpp
#include <string>

std::string to_string(int val);
```

其实就是将数值val转换成字符串

### 2.字符串转换为数值

由于cpp中的数值类型包括整型和浮点型，因此针对不同的类型提供了不同的函数，通过调用这些函数可以将字符串转换为对应的数值类型

```cpp
// 定义于头文件 <string>
int stoi( const std::string& str, std::size_t* pos = 0, int base = 10 );
long stol( const std::string& str, std::size_t* pos = 0, int base = 10 );
long long stoll( const std::string& str, std::size_t* pos = 0, int base = 10 );

unsigned long stoul( const std::string& str, std::size_t* pos = 0, int base = 10 );
unsigned long long stoull( const std::string& str, std::size_t* pos = 0, int base = 10 );

float stof( const std::string& str, std::size_t* pos = 0 );
double stod( const std::string& str, std::size_t* pos = 0 );
long double stold( const std::string& str, std::size_t* pos = 0 );
```

- str：要转换的字符串
- pos：传出参数，记录从哪个字符开始无法继续进行解析，eg.123abc，传出的位置为3
- base：若base为0，则自动检测数值进制；若前缀为0，则为8进制，若前缀为0x或者0X，则为16进制，否则为十进制

这些函数虽然有多个参数，但是除去第一个参数外其他都有默认值，一般情况下使用默认值就能满足需求

注意：

- 如果字符串中所有的字符都是数值类型，整个字符串会被转换为对应的数值，并通过**返回值返回**
- 如果字符串的前半部分字符是数值类型，后半部分不是，那么前半部分会被转换成对应的数值，并通过返回值返回
- 如果字符第一个字符不是数值则类型转换失败

## 六.静态断言static_assert

### 1.断言

断言就是将一个返回值总是需要为真的判断表达式放在语句中，用于排除在设计的逻辑上不应该产生的情况

从一些意义上说，断言并不是正常程序所必须的，不过对于程序调试来说，通常断言能帮助程序开发者快速定位那些违反了某些前提条件的程序错误

```cpp
#include <iostream>
#include <cassert>

//创建一个指定大小的char类型数组
char* creatArray(int size){
    //通过断言判断数组大小是否大于0
    assert(size>0);//必须大于0,否则程序中断
    char* array = new char[size];
    return array;
}

int main(){
    char* buf = creatArray(0);
    strcpy_s(buf , 16 , "hello,world!");
    cout<<"buf = "<<buf<<endl;
    delete[] buf;
    return 0;
}
```

### 2.静态断言

assert是一个运行时断言，也就是说它只有在程序运行时才能起作用，这意味这不运行程序时我们不知道某些条件是否是成立的

cpp11提高了静态断言：static_assert，在编译时就能进行检查的断言，使用时不需要引入头文件

静态断言可以自定义违反断言时的错误提示信息

两个参数：

- 参数1：断言表达式，这个表达式通常需要返回一个bool值
- 参数2：警告信息，它通常是一段字符串，在违反断言（表达式是false）时提示该信息

**注意：由于静态断言的表达式是在编译阶段进行检测，所以在它的表达式中不能出现变量，也就是说这个表达式必须是常量表达式**

## 七.noexcept

### 1. 异常

在程序中将各种类型的异常抛出，从而强制终止程序运行

异常被抛出后，从进入try块起，到异常被抛掷前，这期间在栈上构造的所有对象，都会被自动析构，析构的顺序与构造相反——栈解旋

### 2.异常接口声明

- 显式指定可以抛出的异常类型

```cpp
struct MyException
{
    MyException(string s) :msg(s) {}
    string msg;
};

double divisionMethod(int a, int b) throw(MyException, int)
{
    if (b == 0)
    {
        throw MyException("division by zero!!!");
        // throw 100;
        //抛出异常
    }
    return a / b;
}

int main()
{
    try
    {	
        double v = divisionMethod(100, 0);
        cout << "value: " << v << endl;
    }
    catch (int e)//e就是抛出异常类型的实例化，即throw异常之后将具体的异常赋值给e这个栈上变量
    {
        cout << "catch except: "  << e << endl;
    }//捕获到b=0
    catch (MyException e)
    {
        cout << "catch except: " << e.msg << endl;
    }//捕获到struct MyException下的msg："division by zero!!!"
    return 0;
}
```

divisionMethod函数后添加了throw异常接口声明，其参数表示可以抛出的异常类型，分别为int 和MyException 类型

**注意：C++ 里一个函数一次只能抛出一个异常，不存在"连续抛出多个"让多个 `catch` 依次捕获的机制，抛出一个异常后，函数就结束了，后面的代码都不会再执行**

- 抛出任意异常类型

```cpp
struct MyException{
    MyException(string s) : msg(s){}
    string msg;
};

double divisionMethod(int a , int b){
    if(b==0){
        throw MyException("division by zero!!!");
    }
    
    return a/b;
}
```

divisionMethod函数后没有添加异常接口声明，表示在该函数中可以抛出任意类型的异常

- 不抛出任何异常

```cpp
struct MyException
{
    MyException(string s) :msg(s) {}
    string msg;
};

double divisionMethod(int a, int b) throw()
{
    if (b == 0)
    {
        cout << "division by zero!!!" << endl;
    }
    return a / b;
}
```

divisionMethod函数后添加了throw异常接口声明，其参数列表为空，表示该函数不允许抛出异常

### 3.noexcept

表示其修饰的函数不会抛出异常，cpp11中如果noexcept修饰的函数抛出了异常，编译器可以直接选择调用std::terminate()函数来终止程序的运行，比throw()效率更高——优势在栈解旋上

```cpp
double divisionMethod(int a , int b) noexcept{
    if(b==0){
        cout<<"division by zero!!!"<<endl;
        return -1;
    }
    return a/b;
}
```

- noexcept可以接受一个常量表达式作为参数，其常量表达式会被转换成一个bool类型
  - 值为true，表示函数不会出现异常
  - 值为false，表示有可能抛出异常这里
  - 不带常量表达式的noexcept相当于声明了noexcept(true)，即不会抛出异常

## 八.自动类型推导

### 1.auto

#### 1.1 推导规则

使用auto声明的变量必须要进行初始化，让编译器推导出它的实际类型，在编译时将ato占位符替换成真正的类型

```cpp
auto 变量名 = 变量值;
```

#### 1.2 auto的限制

- 不能作为函数的参数使用，因为只有在函数调用的时候才会给函数参数传递实际参数，auto要求要给修饰的变量赋值

```cpp
int func(auto a,auto b)//错误
```

- 不能用于类的非静态成员变量的初始化

```cpp
class Test{
    auto v1 = 0; //error
    static auto v2 = 0; //error，类的静态非常量成员不允许在类内部直接初始化
    static const auto v3 = 10; //ok
}
```

- 不能用auto关键字来定义数组

```cpp
int func(){
    int array[] = {1,2,3,4} //定义数组
    auto t1 = array; //ok，t1被推导成int*
    auto t2[] = array; //error
    auto t3[] = {1,2,4,5}; //error
}
```

- 无法使用auto推导出模板参数

```cpp
template <typename T>
struct Test{}

int func(){
    Test<double> t;
    Test<auto> t1 = t;//error
    return 0;
}
```

### 2.decltype

在某些情况下，不需要或者不能定义变量，但是希望得到某种类型，可以用到decltype关键字

它的作用是在编译器的时候推导出一个表达式的类型

```cpp
decltype (表达式)
```

decltype是在编译期完成推导的，它只是用于表达式类型的推导，并不会计算表达式的值

```cpp
int a = 10;
decltype(a) b = 99;//b=>int
```

#### 2.1推导规则

- 表达式为普通变量或者普通表达式或者类表达式，在这种情况下，使用decltype推导出的类型和表达式类型是一致的

- 表达式是函数调用的，使用decltype推导出的类型和函数返回值一致
- 表达式是一个左值，或者被括号()包围，使用decltype推导出的是表达式类型的引用

### 3. 返回类型后置

在泛型编程中，可能需要通过参数的运算来得到返回值的类型

在C++11中增加了返回类型后置语法，说明白一点就是将decltype和auto结合起来完成返回类型的推导

```cpp
//符号->后面跟随的是函数返回值的类型
auto func(参数列表) -> decltype(参数表达式)
//auto会追踪decltype()推导出的类型
```

## 九. for循环

基于范围的for循环可以简洁，统一的方式来遍历容器和数组

在基于范围的for循环中，不需要再传递容器两端，循环会自动以容器为范围展开，并且循环中也屏蔽掉了迭代器中的遍历细节，直接抽取容器中的元素进行计算

**优点：便于维护和变得简洁**

语法：in

```cpp
for(declaration:expression){
   //循环体
}
```

- declaration：表示遍历声明，在遍历过程中，当前被遍历的元素会被存储到声明的变量中
- expression是要遍历的对象，可以是表达式，容器，数组，初始化列表

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main(){
    std::vector<int> t = {1,2,3,4,5};
    for(auto value : t){
        cout<<value<<"";
    }
    cout<<endl;
    
    return 0;
}
```

此处是将容器中遍历的当前元素拷贝到了声明的变量value中，因此无对容器中的元素进行写操作，如果需要在遍历过程中修改元素的值，需要使用引用

对容器的遍历过程中，如果是只读数据，不允许修改元素的值，可以使用const定义保存元素的数据变量，在定义的时候建议使用const auto&，这样的效率更高

**注意：对应基于范围的for循环来说，冒号后面的表达式只会被执行一次，得到遍历对象之后会先确定好迭代的范围，基于这个范围直接进行遍历；如果是普通的for循环，在每次迭代的时候都需要判断是否已经到了结束边界**

## 十.Lambda表达式

### 1.基本用法

```cpp
[capture](params) opt -> ret{body;};
```

capture是捕获列表，params是参数列表，opt是函数选项，ret是返回值类型，body是函数体

- 捕获列表[]：捕获一定范围的变量
- 参数列表()：和普通函数的参数列表一样，如果没有参数，参数列表可以省略不写
- opt选项，不需要可以省略
  - mutable：可以修改按值传进来的拷贝（还是注意是修改拷贝，而不是修改本身）
  - exception：指定函数抛出的异常
- 返回值类型：在cpp11中，匿名表达式的返回值是通过返回值后置语法来定义的
- 函数体：函数的实现，这部分不能省略，但是函数体可以为空

### 2.捕获列表

lambda表达式的捕获列表可以捕获一定范围内的变量：

- []——不捕获任何变量
- [&]——捕获外部作用域中所有的变量，并作为引用在函数内使用（按引用捕获）
- [=]——捕获外部作用域中所有的变量，并且作为副本在函数体内使用（按值捕获）
  - 拷贝的副本在匿名函数体内部是只读的
- [=,&foo]——按值捕获外部作用域中所有的变量，并按照引用捕获外部变量foo
- [bar]——按值捕获bar变量，同时不捕获其他变量
- [&bar]——按引用捕获bar变量
- [this]——捕获当前类中的this指针
  - **让lambda表达式有了和当前类成员函数同样的访问权限**
  - 如果已经使用了 & 或者 =, 默认添加此选项

````
注意：在匿名函数内部，需要通过lambda表达式的捕获列表控制如何捕获外部变量，以及访问哪些变量，默认状态下lambda表达式无法修改通过复制方式捕获外部变量，如果希望改变这些外部变量，需要通过引用的方式捕获
````

### 3.返回值

很多时候，lambda表达式的返回值是非常明显的——cpp11中允许省略lambda表达式的返回值

```cpp
//完整的lambda表达式含义
auto f = [](int a) -> int{
    return a+10;
};

//忽略返回值的lambda表达式定义
auto f = [](int a){
	return a+10;
};
```

一般情况下，不指定lambda表达式的返回值，编译器会根据return语句自动推导返回值类型，但是需要注意：**lambda表达式不能通过列表初始化自动推导出返回值类型**

```cpp
//ok，可以自动推导出返回值类型
auto f = [](int i){
    return i;
};

//error，不能推导出返回值类型
auto f1 = [](){
    return {1,2};//基于列表初始化推导返回值，错误
}
```

### 4.函数本质

使用lambda表达式捕获列表捕获外部变量，如果希望去修改**按值捕获的外部变量**，需要mutable选项，被mutable修改lambda表达式就算没有参数也要写明参数列表，并且可以去掉按值捕获的外部变量的只读属性(const)

```cpp
int a = 0;
auto f1 = [=]{return a++;}; //error，按值捕获外部变量，a只读
auto f2 = [=]()mutable {return a++;};
```

- lambda表达式的类型在cpp11中会被看做一个带有**operator()的类**，即仿函数
- 按照cpp标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量值的

**mutable选项的作用就是在与取消operator()的const属性**

对于没有捕获任何变量的lambda表达式，还可以转换成一个普通的函数指针：

```cpp
using func_ptr = int(*)(int);
//没有捕获任何外部变量的匿名函数
func_ptr f = [](int a){
    return a;
};
//函数调用
f(1314)
```

这里为了更去理解lambda函数，需要去讲解operator()函数调用操作符

operator()使得开发者能够为自定义类型定义或者修改操作符的行为，也称为“仿函数”，允许对象像函数一样被调用

- 1.operator()定义

```cpp
return_type operator()(param_lists);
```

函数调用操作符operator()是cpp的一个可重载操作符，**允许类的实例以函数的方式被调用**

```cpp
#include <iostream>

class Adder{
	public:
    	//构造函数，初始化加数
    	Adder(int a) : value(a){}
    
    	//重载函数调用操作符
    	int operator()(int b) const{
            return value + b;
        }
    private:
    	int value;
};

int main(){
    Adder addFive(5);//创建一个加5的加法器
    std::cout<<"5+3 = "<<addFive(3)<<std::endl;//输出8
    return 0;
}
```

Adder类重载了operator()，使得其实例addFive能够像函数一样接受一个整数参数并返回两个整数和

- 2.用途

  operator()的重载提供了将对象用作函数的能力

  - 2.1 仿函数

  ```
  仿函数是具有状态的函数对象，通过重载operator()，对象可以携带额外的状态信息，使其在执行函数能够利用这些信息
  ```

  - 2.2 回调函数

  ```
  在需要回调函数的场景中，仿函数可以替代传统的函数指针，提供更强大的功能和灵活性
  仿函数可以存储上下文信息，而普通函数指针无法做到这一点
  ```

  - 2.3 与标准库算法结合

  ```
  许多标准库算法接受(std::sort,sort::for_each)函数对象作为参数，重载operator()使得类的实例可以直接作为这些算法的参数传递
  ```

  - 保持状态

  ```
   与普通函数不同，仿函数可以保持内部状态，这对于需要在多次调用之间保存信息的场景非常有用
  ```

- 实现

  - 1.定义一个类或者结构体：将该类或结构体重载operator()
  - 重载operator()：在类中定义operator()：在类中定义operator()，并根据需要设置参数和返回类型
  - 使用实例：通过创建类的实例，可以像调用函数一样使用它

- 3.工作原理：当一个类重载了operator()后，其实例就可以像普通函数一样被调用了，编译器在遇到对象的函数调用时，会检查类是否重载了operator()，如果重载了，就会调用相应的成员函数

```
注意：重载operator()不会引入额外的运行时开销，因为它仅仅是类成员函数的调用，然而，仿函数可以保持状态，这可能会涉及额外的内存分配和管理
为了提高效率，应该避免在operator()中执行昂贵的操作，尤其在高频调用的情况
```

## 十一.指针函数和函数指针

注意：指针就是地址，指针变量是用来保存这些地址的变量

```cpp
int* arr[10]//声明一个指针数组，该数组有10个元素，其中每个元素都是指向int类型对象的指针
int (*arr)[10]//声明一个数组指针，这个指针指向一个int类型的一维数组
```

声明一个指针变量并不会自动分配任何内存，在对指针进行间接访问之前，**指针必须进行初始化**：或是使它指向现有的内存，或者给它动态分配内存，否则我们不知道指针指向哪里（野指针）

### 1.函数指针

函数指针是指向函数的指针变量，因此“函数指针”本身首先应是指针变量，指向函数

```cpp
类型说明符 (*函数名)(参数)
```

```cpp
int (*func)(int x);
```

用途：

- 调用函数
- 做函数的参数

```cpp
int (*fun)(int x , int y)//函数指针的定义
fun = &Function; //赋值方式1
fun = Function; //赋值方式2
x = (*fun)(); //调用方式1
x = fun(); //调用方式2
```

函数赋值的时候取地址运算符&不是必需的，因为一个函数标识符就表示了它的地址，并且赋值的时候函数不需要带括号（带了就是调用了）

如果是函数调用，还必须包含一个圆括号括起来的参数表

用法：

函数指针通过（*pf）取出存在这个地址上的函数，然后调用它

### 2.指针函数

指针函数的落脚点就是是一个函数，这个函数的返回值是一个指针，与普通函数

这个其实就只是返回值是指针类型而已

总结：

```
1.定义不同：
- 指针函数本质时一个函数，返回值时指针
- 函数指针本质时一个指针，其指向一个函数

2.写法不同
- 指针函数：int* fun(int x,int y);
- 函数指针：int (*fun)(int x,int y);
```

函数指针：深入去看函数指针与回调函数；非静态成员函数指针

## 十二.指针空值类型——nullptr

在cpp中，为了提高程序的健壮性，一般会在定义指针的同时完成初始化操作，或者在指针的指向尚未明确的情况下，给指针初始化为NULL，避免野指针（没有明确指向的指针，操作这种指针极容易导致程序发生异常）

```cpp
//在cpp98中
char* ptr = 0;
char* ptr = NULL;
```

NULL这个宏定义：

```cpp
#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif
```

cpp——NULL是0，c就是NULL表示```(void*)0```：主要是```void*```类型无法转换为其他类型的指针在cpp中，此时用0代替，这个0（0x0000 0000——16进制是1个数字4位，2个数字就是1个字节）表示虚拟地址空间0的地址，这块地址只可读

主要是NULL和0直接等价（会发生隐式转换）=>某些场景会混在一起，因而cpp11引入nullptr

nullptr专门用于初始化空指针类型，不同类型的指针变量都可以nullptr

## 十三.共享智能指针shared_ptr

cpp中没有垃圾回收机制，必须自己释放分配的内存，否则就会造成内存泄漏——为了解决这个问题：智能指针

智能指针是存储指向动态分配堆对象指针的类，用于生存期的控制，能够确保在离开指针所在的作用域时，自动地销毁动态分配地对象，防止内存泄露

**智能指针地核心实现技术是引用计数，每使用它一次，内部引用计数加1，每析构一次内部的引用计数减1,减为0时，删除所指向的堆内存**

头文件：```<memory>```

- std::shared_ptr：共享的智能指针
- std::unique_ptr：独占智能指针
- std::weak_ptr：弱引用的智能指针，它不共享指针，不能操作资源，用来监视shared_ptr

### 1.shared_ptr初始化

共享智能指针是多个智能指针可以同时管理同一块有效的内存，共享智能指针shared_ptr是一个模板类

- 通过构造函数
- std::make_shared辅助函数
- reset方法

共享智能指针对象初始化完毕之后就指向了要管理的那块堆内存，要查看当前有多少个智能指针同时管理这块内存=>共享智能指针提供的一个成员函数use_count

```CPP
//函数原型
long use_count() const noexcept;
```

#### 1.1 通过构造函数初始化

```cpp
//shared_ptr<T>类模板中，提供了多种实用的构造函数，语法：
std::shared_ptr<T> 智能指针名字(创建堆内存)
```

```cpp
int* p = new int;
shared_ptr<int> p1(p);
shared_ptr<int> p2(p); //错误
```

如果智能指针被初始化了一块有效内存，那么这块内存的引用计数+1，如果智能指针没有被初始化或者被初始化为nullptr空指针，引用计数不会+1

**不要使用一个原始指针初始化多个shared_ptr**

#### 1.2 通过拷贝和移动构造函数初始化

当一个智能指针被初始化后，**就可以用这个智能指针初始化其他新对象**，在创建新对象的时候，对应的拷贝构造函数或者移动构造函数就被自动调用了，这里讲解一下移动构造函数

- 移动语义：cpp11才实现的，意义在与对于一些即将被销毁的对象，可以不复制，直接窃取它的资源，以此来减少一次复制，提高性能

```
例如，函数返回非引用的返回值时，会先构造一个临时对象作为返回值，函数调用时将该临时对象赋值给接收对象，调用结束后会销毁这个临时对象
这个临时对象是会被销毁的，如果能将临时对象的资源直接移交给接收对象，可以减少一次拷贝
```

- 左值（lvalue）

左值——locator value意为在内存中，有明确存储地址（可寻地址）的数据，本质是可以操作的一块内存区域，一般是通过&取到该内存的起始地址，这块内存的值可以被修改（const对象除外）

```
- 变量（对象）
- const变量（对象）
- 对指针的解引用
- 数组元素
- 结构体成员，类成员
```

- 右值（rvalue）

右值——read value，指的是那些可以提供数据值的数据（不一定是寻地址），右值指的是一种表达式，其结果是值而非所在位置，没有明确的地址位置，无法使用&获取地址，值不能被修改

**注意：在需要右值的地方（除了移动构造函数）可以用左值来替代，但是不能把右值当成左值（也就是位置）使用，当一个左值被当成右值使用的时候，实际使用的是它的内容值**

```
- 字面常量，字符串除外（它们由地址表示）
- 算术运算符的求值结果
- 逻辑运算符的求值结果
- 函数的非引用返回值——临时对象
- 当三目运算符的两个表达式都是左值或者能转换成同一种左值类型时，运算的结果时左值；否则是右值
```

- 左值引用（传统的引用）

const左值引用既可以绑定到左值，也可以绑定到右值，但不能修改const左值引用绑定的内容

```cpp
类型& 变量名 = 变量
//左值引用定义必须初始化，且初始化后无法改变该引用关联的对象（类型* const p——指针常量：不能修改其指向（地址））
//非const引用初始化不能是右值
```

- 右值引用——为了支持移动的操作（只要是引用都当别名来理解）

右值引用——实现移动操作，右值引用只能关联到右值，右值一般是字面量，要么是求值过程中产生的临时对象

```cpp
int&& rri = 13;//定义了右值引用rri
```

```cpp
int&& rl = 13;
int* p = &rl;
```

将右值关联到右值引用导致该右值被存储到特定的位置，且可以获取该位置的地址——将数据与特定的地址关联

**右值引用只能绑定到一个右值，右值要么是字面常量，要么是在表达式求值过程中创建的临时对象**

```
临时对象有两个特点：
- 该对象将要被销毁
- 该对象没有其他用户再使用它
说明右值引用的代码是最后使用这个对象了，可以自由地接管所引用地对象的资源
```

 cpp11通过右值引用来完全地接管这些临时对象，然后将临时对象的资源移动到接收对象，并且要保证这个临时对象可以被正常销毁

**临时值也是在内存中有地址的**

![右值引用](/home/ubuntu/VGD_navigation/cpp/cpp编程基础/cpp相关图片/2026-09-17_11-13.png)

没有右值引用前，这个临时值使用后完就被销毁——我们不知道这个内存地址，现在这个内存地址可以被右值引用关联，关联后，右值引用可以改变内存的内容，等右值引用完再销毁

- std::move

虽然不能将一个右值引用直接绑定到一个左值上，但是我们可以显式地将一个左值转换为对应的右值引用类型，std::move的标准库函数可以获取绑定到左值上的右值引用

```cpp
int i = 0;
int&& rri = std::move(i);
//虽然是左值，但是希望像右值一样去处理
```

注意：std::move处理后的对象，比如这个i，**也应该理解为即将被销毁的对象**，如果这个对象的值可以被修改，但是不可以再进行调用

- 移动构造函数

在创建对象时移动旧对象资源的构造函数

```cpp
CDate(CDate&& date);
```

​          - 没有返回值，属于构造函数的一种

​          - 第一个参数必须是一个自身类类型的右值引用，且其他参数都有默认值

​          - 第一个参数不能声明为const右值引用的原因是该引用在函数内被修改（移动资源）

​          - 移动构造函数执行后，需要保证右值引用的对象能够被正常销毁

```
移动构造函数：如果使用一个右值（即将被销毁的对象）去初始化同类型的对象，就调用该类的移动构造函数
该类的成员存在指向new分配的堆内存，则可以跟进需要定义移动构造函数
如果该类没有定义拷贝构造函数，且没有定义移动构造函数，编译器会提供一个默认的移动构造函数
如果该类没有定义拷贝构造函数，则编译器不会提供默认的移动构造函数，需要用到移动构造的地方都会调用拷贝构造函数
如果该类定义了移动构造函数，则编译器不会提供默认的拷贝构造函数，需要用到拷贝构造的时候，编译器报错
默认移动构造函数所做的工作和默认拷贝构造函数的工作一样，执行逐成员初始化并复制内置类型，如果成员是类对象，将使用相应类的构造函数和赋值运算符，就像参数为右值一样
```

移动构造函数的目的就是为了减少一次拷贝，提升性能，cpp11主要通过右值引用来实现移动语义，**如果使用一个右值（即将被销毁的对象）去初始化同类型的对象，就调用该类的移动构造函数**

- 拷贝构造函数——使用同一类中之前创建的对象来**初始化**新创建的对象

```
为什么需要深拷贝：相互不影响
```

```
浅拷贝：只复制指向某个对象的指针，而不复制对象本身，新旧还是共享一块内存
浅拷贝会创建一个新对象，这个对象有着原始对象属性值的一份精确拷贝
如果属性是基本类型，拷贝就是基本类型的值；如果属性是内存地址，拷贝的就是内存地址（两个对象相互影响）
深拷贝：会另外创造一个一模一样的对象，新对象和原对象不共享内存，修改新对象不会改到原对象
```

**区分标准：成员背后有没有一块被间接指向的资源，以及那块资源要不要独立**

#### 1.3通过std::make_shared初始化

通过cpp提供的std::make_shared()就可以完成内存对象的创建并将初始化给智能指针

```cpp
template<class T,class...Args>
shared_ptr<T> make_shared(Args&& ...args);
```

- T：模板参数的数据类型
- Args&&... args：要初始化的数据，如果是通过make_shared创建对象，需按照构造函数的参数列表指定

```
使用std::make_shared()模板函数可以完成内存地址的创建，并将最终得到的内存地址传递给共享指针对象管理
如果申请的内存是普通类型，通过函数的()可完成地址的初始化，如果要创建一个类对象，函数的()内部需要指定构造对象需要的参数，也就是类构造函数的参数
和new和delete一致
```

#### 1.4 通过reset方法初始化

共享智能指针类提供的std::shared_ptr::reset方法函数原型如下：

```cpp
void reset() noexcept;

template <class T>
void reset(Y* ptr);

template <class Y,class Deleter>
void reset(Y* ptr , Deleter d);

template <class Y,class Deleter,class Alloc>
void reset(Y* ptr,Deleter d,Alloc alloc);
```

- ptr：指向要取得所有权的对象的指针
- d：指向要取得所有权的对象的指针
- aloc：内部存储所用的分配器

```
对于一个未初始化的共享智能指针，可以通过reset方法来初始化，当智能指针中有值的时候，调用reset会使引用计数减1
```

#### 1.5 获取原始指针

通过智能指针可以管理一个普通变量或者对象的地址，**此时原始地址就不见了**

**当我们想去修改变量或者对象中的值的时候，就需要从智能指针对象中先取出数据的原始内存的地址再操作**，解决方案是调用共享指针类提供的get()方法

```
T* get() const noexcept;
```

补充：memset()函数

```c
void* memset(void* str,int c,size_t n)
```

- str——指向要填充的内存区域的指针
- c——要设置的值，通常是一个无符号字符
- n——要被设置为该值的字符数

- 返回一个指向存储区的str指针

这个函数将指定的c赋值到str所指向的内存区域的前n个字节，可以用于将内存清零或者设置成特定值

初始化大块内存为0或者特定值——清空内存区域或者为内存区域赋值

注意：

```
- memset()并不对指针ptr指向的内存区域做边界检，因此使用时需要确保ptr指向的内存区域足够大，避免发生越界访问
- memset()的第二个参数value通常是int类型的值，但实际上只使用了该值的低8位，所以第二个参数尽量在0到255之间
- num参数表示要设置的字节数，通常是sizeof()或者其他手段
```

### 2.指定删除器

当智能指针管理的内存对应的引用计数变为0时，这块内存就会被智能指针析构掉了，另外，我们在初始化智能指针的时候也可以自己指定删除动作，这个删除操作对应的函数被称之为删除器，这个删除器函数本质是一个回调函数，只需要进行实现，调用是智能指针完成的

在cpp11使用shared_ptr管理动态数组的时候，需要指定删除器=>std::shared_ptr的默认删除器不支持数组对象

```cpp
int main(){
    std::shared_ptr<int> ptr(new int[10],[](int* p){delete[] p;});
    return 0;
}
```

在删除数组内存时，除了自己编写的删除器，也可以使用cpp提供的std::default_delete<T>()函数作为删除器，这个函数内部的删除功能也是调用delete来实现的，要释放什么类型的内存就将模板类型T指定为什么类型即可

```cpp
int main(){
    std::shared_ptr<int> ptr(new int[10] , default_delete<int[]>());
    return 0;
}
```

封装一个make_share_array方法来让shared_ptr支持数组

```cpp
#include <iostream>
#include <memory>

template <typename T>
std::shared_ptr<T> make_share_array(size_t size){
    //返回匿名对象
    return std::shared_ptr<T>(new T[size],default_delete<T[]>());
}

int main(){
    std::share_ptr<int> ptr1 = make_share_array<int>(10);
    //int类型的数组，大小是10
    std::cout<<ptr1.use_count()<<std::endl;
    std::share_ptr<char> ptr2 = make_share_array<char>(128);
    //char类型的数组，大小是128
    std::cout<<ptr2.use_count()<<std::endl;
    
    return 0;
}
```

## 十四.独占智能指针unique_ptr

### 1.初始化

std::unique_ptr是一个独占类型的智能指针，它不允许其他的智能指针共享其内部的指针，可以通过它的构造函数初始化一个独占智能指针对象，但是不允许通过赋值将一个unique_ptr赋值给另一个unique_ptr

```cpp
//通过构造函数初始化对象
unique_ptr<int> ptr1(new int(10));
//error，不允许将一个unique_ptr赋值给另一个unique_ptr
unique_ptr<int> ptr2 = ptr1;
```

注意：std::unique_ptr不允许复制，但是可以通过函数返回给其他的std::unique_ptr，还可以通过std::move来转移给其他的std::unique_ptr，这样原始指针的所有权就被转移了，这个原始指针还是被独占的

通过reset方法可以让unique_ptr解除对原始内存的管理，也可以用来初始化

```cpp
void reset(pointer ptr = pointer()) noexcept;
```

如果要获取独占指针管理的原始地址，可以调用get()方法，函数原型：

```cpp
pointer get() const noexcept;
```

### 2.删除器

unique_ptr指定删除器和shared_ptr指定的删除器是有区别的，unique_ptr指定删除器的时候需要确定删除器的类型，不能像shared_ptr那样直接指定删除器

删除器如果是lambda表达式没有捕获任何外部变量时，可以直接转换为函数指针，一旦捕获了就无法转换，如果想要让编译器成功编译，需要使用可调用对象包装器来处理声明的函数指针

## 十五.弱引用智能指针——weak_ptr

std::weak_ptr：弱引用指针，它不共享指针，不能操作资源，是用来监视shared_ptr

### 1.基本使用方法

std::weak_ptr可以看作是shared_ptr的助手，它不管理shared_ptr内部的指针，它不共享指针也不能操作资源，它的构造不会增加引用计数，析构也不会减少，唯一的作用是作为一个旁观者监视shared_ptr中管理的资源是否存在

####  1.1初始化

```cpp
//默认构造函数
constexpr weak_ptr() noexcept;
//拷贝构造函数
weak_ptr (const weak_ptr& x) noexcept;
template<class U>
weak_ptr(const weak_ptr<U>& x) noexcept;
//通过shared_ptr对象构造
template<class U>
weak_ptr(const shared_ptr<U>& x) noexcept;
```

#### 1.2 use_count()

可以获取当前所观测资源的引用计数

```cpp
//函数返回所监测的资源的引用计数
long int use_count() const noexcept;
```

#### 1.3 expired()

std::expired()方法来判断观测的资源是否已经被释放

```cpp
//返回true表示资源已经被释放，返回false表示资源没有被释放
bool expired() const noexcept;
```

#### 1.4 lock()

通过lock()方法来获取管理所监测资源的shared_ptr对象，函数原型：

```cpp
shared_ptr<element_type> lock() const noexcept;
```

#### 1.5 reset()

通过reset()方法来清空对象，使其不监测任何资源

```cpp
void reset() noexcept;
```

### 2. 返回管理this的shared__ptr

```cpp
#include <iostream>
#include <memory>

struct Test
{
    std::shared_ptr<Test> getSharedPtr(){
        return std::shared_ptr<Test>(this);
    }

    ~Test(){
        std::cout<<"class Test is disstruct..."<<std::endl;
    }
};

int main(){
    std::shared_ptr<Test> sp1(new Test);//只new了一次，只有一个对象，第一个this
    std::cout<<"use_count:"<<sp1.use_count()<<std::endl;
    std::shared_ptr<Test> sp2 = sp1->getSharedPtr();//调用的是sp1管理的对象的this指针去new一个新的共享指针，实际上sp2拿到的是sp1对象的指针
    //相当于sp1和sp2都是管理同一个对象的地址，但是相互不知道
    std::cout<<"use_count:"<<sp1.use_count()<<std::endl;

    return 0;
}

//此代码从头到尾只有一个Test对象，sp1和sp2指向的是同一个对象，但是各自拿着一套独立的引用计数，最后会把同一个对象delete两次
```

分析一下这个原因（ai输出）：shared_ptr内部其实是两个指针——1.对象指针->指向裸指针；2.控制块指针->指向堆上的控制块（里面存着引用计数，删除器等）

**引用计数是跟着控制块走的，不是跟着对象走的**

std::shared_ptr<Test>(this)时，开辟的Test类型的内存把this这个裸指针传递进去创建智能指针对象，只是一个地址，控制块是自己开辟的，所以计数都是1，最后删除器执行的时候都释放同一块内存（即同一个对象两次）

为了解决这个问题：weak_ptr，通过weak_ptr返回管理this资源的共享智能指针对象shared_ptr

std::enable_shared_from_this<T>，这个类中方法shared_from_this()，这个方法可以返回一个共享智能指针，在函数内部就是使用weak_ptr来监测this对象，并通过调用weak_ptr的lock()方法返回一个shared_ptr对象

**enable_shared_from_this类的shared_from_this()方法之前，必须要先初始化函数内部weak_ptr对象，否则该函数无法返回一个有效的shared_ptr对象**

### 3. 解决循环引用的问题

智能指针如果循环引用会导致内存泄漏，利用weak_ptr可以很好地解决

## 十六.constexpr

### 1. constxepr

#### 1.1 const

在cpp11前只有const关键字，从功能上来说这个关键字有双重语义：变量只读，修饰常量

#### 1.2 constexpr

这个关键字是用来修饰常量表达式的，所谓常量表达式，指的是由多个（>=1）常量（值不会改变）组成并在编译过程中就得到计算结果的表达式

常量表达式和非常量表达式的计算时机不同，非常量表达式只能在程序运行阶段计算得出，常量表达式的计算往往发生在程序的编译阶段——极大提高程序执行效率

- const——只读
- constexpr——常量

在定义常量时，const和constexpr是等价的，都可以在程序的编译阶段计算出结果

eg.

```cpp
const int m = f();//不是常量表达式，m的值只有在运行时才会获取
const int i = 520;//是一个常量表达式
const int j = i + 1;//是一个常量表达式

constexpr int i=520;    // 是一个常量表达式
constexpr int j=i+1;    // 是一个常量表达式
```

对于cpp内置类型的数据，可以直接用constexpr修饰，但如果是自定义的数据类型（struct/class）直接使用constexpr修饰是不行的

### 2.常量表达式函数

常量——值不需要发生变化的变量

可以用constexpr修饰函数的返回值，这种函数是常量表达式函数：普通函数/类成员函数，类的构造函数，模板函数

#### 2.1 修饰函数

constexpr并不能修饰任意函数的返回值，使这些函数成为常量表达式函数，必须满足：

- 函数必须有返回值，且return返回的表达式必须是常量表达式

- 函数在使用前，必须有对应的定义语句
- 整个函数的函数体中，不能出现非常量表达式之外的语句(using,typedef,static_assert,return除外)

对类的成员函数也是适用的

#### 2.2 修饰模板函数

如果constexpr修饰的模板函数实例化结果不满足常量表达式函数的要求，则constexpr会被自动忽略，该函数就是一个普通函数

#### 2.3 修饰构造函数

如果想得到一个常量对象——constexpr修饰一个构造函数：构造函数函数体为空且用初始化列表去为各个成员赋值

**变量只读不等于常量，前者const，后者constexpr**

## 十七.委托构造和继承构造函数

### 1.委托构造函数

委托构造函数允许使用同一个类中的一个构造函数调用其它的构造函数，从而简化相关变量的初始化

- 链式构造函数调用不能形成一个循环（闭环），否则会在运行期抛异常
- 如果要进行多层构造函数的链式调用，建议将构造函数的调用的写在初始化列表中而不是函数体内部，否则编译器会提示形式参数的重复定义

```CPP
Test(int max){
    this -> m_max = max > 0 ? max : 100;
}

Test(int max,int min){
    Test(max);//error，此处编译器会报错，提示形式参数max被重复定义
}
```

- 在初始化列表中调用了委托构造函数初始化某个类成员变量之后，就不能初始化列表再一次初始化这个变量了

```cpp
//error
Test(int max , int min):Test(max),m_max(max){
	///函数体
}
```

### 2.继承构造函数

cpp11提供的继承构造函数可以让派生类直接使用基类的构造函数，在有很多构造函数的情况下，可以极大地简化派生类构造函数的编写

在cpp11前，需要在子类重新定义一个和基类一样的构造函数，对于父亲的有参的构造函数而言——初始化列表进行父类构造函数的初始化之后才能子类构造函数

继承构造函数：

```cpp
using classname :: 构造函数名（构造函数名和classname一致）
```

这样子类就可以不定义相同的构造函数了，直接使用基类的构造函数

同理：如果在子类中隐藏了父类中的同名函数，也可以通过using的方式在子类中使用基类中的这些父类函数

## 十八.右值引用

### 1. 右值引用

#### 1.1 右值

- 左值：存储在内存中，有明确的存储地址（可取地址）

- 右值：可以提供数据值的数据（不可取地址）

可以对表达式取地址(&)就是左值，否则是右值，所有有名字的变量都是左值，而右值是匿名的

````cpp
int a = 520;
int b = 1314;
a = b;
````

其中：a，b都是左值，都是取地址

cpp11中右值：

- 将亡值：非引用返回的临时变量，运算表达式产生的临时变量，原始字面量和lambda表达式
- 纯右值：与右值引用相关的表达式，比如，T&&类型函数的返回值，std::move的返回值等

#### 1.2 右值引用

无论是声明左值引用还是右值引用都必须**立即进行初始化**，因为**引用类型本身并不拥有所绑定对象的内存**，只是该对象的一个别名

通过右值引用的声明，该**右值**又“重获新生”，其生命周期与右值引用类型**变量**的生命周期一样，该右值临时量将会一直存活下去

### 2. 性能优化

cpp在进行对象赋值操作的时候，很多情况下会发生对象之间的深拷贝，如果堆内存很大，这个拷贝代价比较大，在某些情况下，如果想要避免对象的深拷贝，就可以使用右值引用进行性能优化

```
对于需要动态申请大量资源的类，应该设计移动构造函数，以提高程序效率，我们一般在提供移动构造函数的同时，也会提供常量左值引用的拷贝构造函数，以保证移动不成还可以使用拷贝构造函数
```

### 3. &&的特性

在cpp中，并不是所有的情况下&&都代表是一个右值引用，具体的场景体现在模板和自动化类型推导中

- 模板参数T&&
- 自动类型推导auto&&

这俩种场景下&&被称作未定的引用类型

**注意：const T&&表示一个右值的引用**

其实就是

```cpp
int a = 10;
//int&& b = a;
//引用就是起别名，无法将右值引用绑定到左值（编译器解释）
//int& b = 20;
//同理：非常量引用的初始值必须为左值
```

在cpp11中会出现折叠引用：在进行类型推导时右值引用类型(&&)会发生变化

- 通过右值推导T&&或者auto&&得到的是一个右值引用类型
- 通过非右值（**右值引用**，左值，左值引用，常量右值引用，常量左值引用）推导T&&或者auto&&得到的是一个左值引用类型

## 十九. 转移和完美转发

### 1. move

左值初始化一个右值引用需要借助std::move()

使用std::move()可以将左值转换成右值，只是转移，没有内存拷贝

move几乎没有任何代价，只是转换为资源的所有权

```
同理给类编写相应的移动构造函数——T::T(T&& another)

和具有移动语义的赋值函数——T&& T::operator=(T&& rhs)
```

这些在构造对象和赋值的时候可能地进行资源的重复利用，因为它们都接收一个右值引用参数

### 2. forward

右值引用类型是独立于值的，一个右值引用作为函数参数的形参时，在函数内部转发该参数给内部其他函数时，就变成了一个左值，并不是原来的类型了

如果需要按照参数原来的类型转发到另一个函数，可以使用cpp11提供的std::forward()函数，该函数实现的功能称为完美转发

```cpp
std::forward<T>(t);
```

- 当T为左值引用类型时，t将被转换为T类型的左值
- 当T不是左值引用类型时，t将被转换为T类型的右值

## 二十.初始化列表

关于cpp中的变量，数组，对象等都有不同的初始化方法，为了统一初始化方式，并且让初始化行为具有确定的效果，在cpp11中提出了初始化列表的概念

### 1. 统一的初始化

cpp98中，对于普通数组和可以直接进行内存拷贝(memcpy())的对象是可以使用列表初始化来初始化数据的

```cpp
//数组的初始化
int array[] = {1,3,5,7,9};
double array1[3] = {1.2,1.3,1.4};

//对象初始化
struct Person{
    int id;
    double salary;
}zhang3{1,3000};
```

在cpp11中，列表初始化更加灵活

列表初始化可以对普通类型以及对象进行直接初始化，那么在使用new操作符创建对象的时候可以使用列表初始化进行对象的初始化

```cpp
int* p = new int{520};
//匿名对象使用列表初始化之后，再进行拷贝初始化
double b = double{52.134};
int* array = new int[3]{1,2,3};
```

### 2. 列表初始化细节

#### 2.1 聚合体

使用列表初始化对对象时候，还需要判断这个对象对应的类型是不是一个聚合体，如果是初始化列表中的数据就会拷贝到对象中

聚合体：

- 普通数组
- 满足以下条件的类（class,struct,union）：
  - 没有用户自定义的构造函数
  - 没有私有或者保护的**非静态**数据成员
  - 无基类
  - 无虚函数
  - 类中不能有使用{}和=直接初始化的非静态数据成员（cpp14开始支持）

#### 2.2 非聚合体

类中自定义一个构造函数，在构造函数中使用初始化列表对类成员变量进行初始化

```
对于一个聚合类型，使用列表初始化相当于对其中的每个元素分别赋值，而对于非聚合类型，则需要先自定义一个合适的构造函数，此时使用列表初始化将会调用它对应的构造函数
```

### 3. std::initializer_list（类模板）

特点：

- 一个轻量级的容器类型，内部定义了迭代器iterator等容器必须的概念，遍历时得到的迭代器是只读的
- std::initializer_list<T>而言，接收任意长度的初始化列表，但是要求元素必须是同类型T
- std::initializer_list内部有三个成员接口：size(),begin(),end()
- std::initializer_list对象只能被整体初始化**或者赋值（存疑）**

#### 3.1 作为普通函数参数

变参函数——将函数参数指定为std::initializer_list

注意：

```
std::initializer_list不拥有数据，只是一个指针+一个长度的轻量视图
std::initializer_list<int> list = {1,2,3}中的{1,2,3}只是const int[N]临时数组
上述直接初始化是可以的，{1,2,3}就像右值绑定到引用上去延长生命周期和list一样
但是
list = {1,0};这样只是让list的指针重新指向一个新的临时数组，赋值不触发生命周期延长，数组在分号处析构，即{1,0}这个地址不再存在，list里面存放的是释放过后数据的一个地址，属于未定义行为
```

std::initializer_list拥有一个无参构造函数，它可以直接定义实例，此时得到一个空视图

std::initalizer_list效率非常高，它的内部并不负责保存初始化列表中元素的拷贝，仅仅存储了初始化列表中元素的引用

#### 3.2 作为构造函数参数

同普通函数一样的传递参数方式

## 二十一. using的使用

### 1. 定义别名

cpp98：

```cpp
typedef 旧类型名 新的类型名;
typedef unsigned int uint_t;
```

cpp11：

```cpp
using 新的类型 = 旧的类型;
using uint_t = unsigned int;
```

对于函数指针：

```cpp
typedef int(*func_ptr)(int,double);
//func_ptr是一个别名，本质是一个函数指针，指向的函数返回类型是int，函数参数有两个为int和double
using func_ptr1 = int(*)(int,double);
```

### 2. 模板的别名

使用typename无法直接重定义一个模板，只能对模板进行实例之后进行重定义

```cpp
typedef map<int,string> m1;
typedef map<int,int> m2;
template<typename T>
typedef map<int ,T> type //error
```

想要用tpyedef实现，需要用到外敷类

```cpp
template<typename T>
//定义外敷类
struct MyMap{
    typedef map<int,T> type;
};

//后续实例
MyMap<string>::type m;
```

在cpp11中用using：


```cpp
//更方便
template<typename T>
using mymap = map<int,t>;

mymap<int,string> m;
```

## 二十二. 可调用对象包装器，绑定器

### 1. 可调用对象

- 是一个函数指针

```cpp
int print(int a,double b){
	std::cout<<a<<b<<std::endl;
}

//定义函数指针
int(*func)(int,double) = &print;
```

- 是一个具有operator()成员函数的类对象（仿函数）

```cpp
#include <iostream>
#include <string>
#include <vector>

struct Test{
    void operator()(std::string msg){
        std::cout<<"msg:"<<msg<<std::endl;
    };
};

int main(){
    Test t;
    t("我是要成为海贼王的男人!!!");//访函数
    return 0;
}
```

- 是一个可被转换成函数指针的类对象

```cpp
#include <iostream>
#include <string>
#include <vector>

using func_ptr = void(*)(int,std::string);
struct Test{
    static void print(int a,std::string b){
        std::cout<<"name:"<<b<",age:"<<a<<std::endl;
    }
    
    //将类对象转换为函数指针
   operator func_ptr(){
		return print;
   }
};

int main(){
	Test t;
    //对象转换为函数指针，并调用
    t(19,"Monkey D.luffy");
    
    return 0;
}
```

```
转换函数的写法为:operator 目标类型()，它必须是类的非静态成员，且没有返回值，表示将类类型可以转换成目标类型
```



- 是一个类成员函数指针或者类成员指针

```cpp
#include <iostream>
#include <string>
#include <vector>

struct Test{
    void print(int a,std::string b){
        std::cout<<"name:"<<b<",age:"<<a<<std::endl;
    }
    int n_num;
};

int main(){
    //定义类成员函数指针指向类成员函数
    void(Test::*func_ptr)(int,std::string) = &Test::print;
    //类成员指针指向类成员变量
    int Test::*obj_ptr = &Test::m_num;
    
    Test t;
    //类成员函数指针调用类成员函数
    (t.*func_ptr)(19,"Monkey D.luffy");
    //类成员指针初始化类成员变量
    t.*obj_pty = 1;
    std::cout<<"number is:"<<t.m_num<<std::endl;
    
    return 0;
}
```

由于有各种定义可调用对象的方式，试图用统一的方式去保存

std::function和std::bind统一了可调用对象的各种操作

### 2. 可调用对象包装器

std::function是可调用对象的包装器，是一个类模板，可以容纳除了类（非静态）成员指针之外的所有可调用对象，通过指定模板参数，可以统一处理函数，函数对象，函数指针，并允许保存和低延迟执行它们

#### 2.1 基本用法

```cpp
#include <functional>
std::function<返回值类型(参数类型列表)> diy_name = 可调用对象
```

#### 2.2 作为回调函数

因为回调函数本身就是通过函数指针实现的，使用对象包装器可以取代函数指针的作用

讲解一下回调函数：通过函数指针调用的函数（作为参数进行传递调用）

函数F1调用函数F2的时候，函数F1通过参数给函数F2传递了另外一个函数F3的指针，在F2执行过程中，函数F2调用了函数F3，这个动作就是回调，先被当作指针传入，在被回调的函数F3就是回调函数

```c
#include <stdio.h>
#include <softwareLib.h>

int callBack(){
    return 0;
}

int main(){
	Library(Callback);
    return 0;
}
```

这里就能看出：回调函数最大的作用就是解耦——只需要改变传入库函数的参数就可以实现不同的功能，不需要修改库函数的实现

### 3. 绑定器

std::bind用来将可调用对象与其参数一起进行绑定，绑定后的结果可以使用std::function进行保存，并延迟调用到任何我们需要的时候

- 将可调用对象与其参数一起绑定成一个仿函数
- 将多元（参数个数为n，n>1）可调用对象转换为一元或者（n-1）元可调用对象，即只绑定部分参数

```cpp
//绑定非类成员函数/变量
auto f = std::bind(可调用对象地址，绑定的参数/占位符);
//绑定类成员函数/变量
auto f = std::bind(类函数/成员地址，类实例对象地址，绑定的参数/占位符);
```

std::bind绑定器返回的是一个仿函数类型（函数指针），得到的返回值可以直接赋值给一个std::function，在使用的时候我们不用关心绑定器的返回值类型，使用auto进行自动类型推导就可以了

std::placeholders::_1是一个占位符，代表这个位置将在函数调用时被传入的第一个参数所代替

可调用对象包装器std::function是不能实现对类成员函数指针或者类成员指针的包装，但是通过std::bind配合，就可以解决

函数包装器是统一可调用对象，最后能统一调用；而函数包装器则是将可调用对象与其参数一起进行绑定，返回的是仿函数类型（函数指针），可以配合函数包装器一起使用

## 二十三. 强类型枚举

### 1. 枚举

#### 1.1 枚举的使用

```cpp
//匿名枚举
enum {Red,Green,Blue};
//有名枚举
enum Colors{Red,Green,Blue};
```

枚举类型中的枚举值编译器会默认从0开始赋值，而后依次向下传递，也就是说Red = 0，Green = 1，Blue = 2

枚举是对变量取值的枚举（变量可能的值）

#### 1.2 缺陷

具有名字的enum类型的名字，以及enum的成员的名字都是全局可见的

```cpp
enum China {Shanghai, Dongjing, Beijing, Nanjing};
enum Japan {Dongjing, Daban, Hengbin, Fudao};
//编译器出现报错
```

枚举的成员总是可以被隐式转换为整型

### 2. 强类型枚举

#### 2.1 优势

```cpp
enum class Corlos{Red,Green,Blue};
```

- 强作用域：强类型枚举成员的名称不会被输出到其父作用域空间
- 强类型枚举只能是有名枚举，如果是匿名枚举会导致枚举值无法使用（没有作用域名称）
- 转换限制，强类型枚举成员的值不可以与整型隐式转换
- 可以指定底层类型，强类型枚举默认的底层类型为int，但也可以显式地指定底层类型

```cpp
enum class Colors : char {Red,Green,Blue};
```

其中type可以是除wchar_t以外地任何类型

注意：

```
- 强类型枚举属于强作用域类型，不能直接使用，枚举值前必须加枚举类型
- 强类型枚举不会进行隐式类型转换，因此枚举不能直接给int变量赋值
```

#### 2.2 对原有枚举的扩展

- ```cpp
  enum Colors : char {Red,Green,Blue};
  ```

- ```cpp
  enum Colors : char {Red,Green,Blue};
  int main(){
      Colors c1 = Green; //cpp11之前
      Colors c2 = Colors::Green;//cpp11之后
      
      return 0;
  }
  ```

注：enum struct == enum class
