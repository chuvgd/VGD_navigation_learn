#include <iostream>
//这里来引入深拷贝
typedef int DataType;

class Stack{
	public:
		Stack(size_t capacity = 10){
			_array = (DataType*)malloc(capacity * sizeof(DataType));
			if(nullptr == _array){
				perror("malloc申请空间失败");
				return;
			}
			_size = 0;
			_capacity = capacity;
		}

		void Push(const DataType &data){
			//const引用传参可以直接传入右值进行绑定，但是非const不行
			//CheckCapacity();
			_array[_size] = data;
			_size++;
		}

		~Stack(){
			if(_array){
				free(_array);
				_array = nullptr;
				_capacity = 0;
				_size = 0;
			}
		};

	private:
		DataType* _array;
		size_t _size;
		size_t _capacity;
};

int main(){
	Stack s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	Stack s2(s1);
	
	return 0;
}

//s1对象创建时，调用了构造函数，默认申请了10元素空间，通过push()函数存放了4个元素：1,2,3,4
//s2对象使用s1拷贝构造，而Stack类没有显式定义拷贝构造函数。则编译器会给Stack类生成一份默认的拷贝构造函数，默认拷贝构造函数是按照值拷贝的，即将s1中内容原封不动地拷贝到s2中，因此s1和s2指向同一块内存空间
//当程序退出时，s2和s1都要销毁，s2先销毁，s2销毁时调用析构函数，已经当时开辟的内存空间释放了一次，到s1销毁时，会对同一块即已经释放的内存再进行一次释放，必然会造成程序的崩溃


