// 右值_引用_返回值_堆栈.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <iomanip>
#include <inttypes.h>

using namespace std;
// Debug + x64

class DefClass {
public:
							// vptr  
	uint64_t self;			// vptr +8
	uint64_t temp[100];		// vptr +8 +8   
	uint64_t other;			// vptr +8 +8 +8*100
	uint64_t isMove;		// vptr +8 +8 +8*100 +8 
							// sizeof(DefClass)  = 832 

	DefClass() :self((uint64_t)this), other(0),isMove(0){
		cout << "DefClass() " << this << endl;
	}
	virtual ~DefClass() {
		cout << "~DefClass() " << this << endl;
	}
	DefClass(DefClass&& other):self((uint64_t)this), other((uint64_t)&other),isMove(1) {
		cout << "DefClass(DefClass&& other)       this:" << this << " other: " << &other << endl;
	}

	DefClass(const DefClass& other):self((uint64_t)this), other((uint64_t)&other), isMove(0) {
		cout << "DefClass(const DefClass& other)  this:" << this << " other: " << &other << endl;
	}

	DefClass& operator=(const DefClass& other) {
		cout << "operator=(const DefClass& other)  this:" << this << " other: " << &other << endl;
		return *this;
	}

	DefClass& operator=(DefClass&& other) {
		cout << "operator=(DefClass&& other)       this:" << this << " other: " << &other << endl;
		return *this;
	}

	void dump() const {
		printf("this %0" PRIx64 " other %0" PRIx64 " %s\n"  , self,  other , (isMove ? " Move " : "Non-Move") );
	}
};

#if 0 
DefClass && getLeftRef() {
	cout << "--getLeftRef entry " << endl;
	DefClass local;
	cout << "--getLeftRef &local = " << &local << endl;
	return std::move(local); // local 是左值  在离开函数体后会销毁  右值引用并不会延长左值得寿命
} // 返回右值引用有危险   无论是 左值引用,常量左值引用,右值引用，只要最终引用的对象析构了(局部对象/左值)，那么这个引用就有危险


const DefClass& getConstValue() {		// 错误 xxx 
	cout << "--getConstValue entry " << endl;
	DefClass local;
	local.dump();
	cout << "--getConstValue exit " << endl;
	return local; // -Wreturn-stack-address  local是左值 会析构
}				  // 返回后局部变量就释放了，常量引用指向内容不确定，调用dump内存不确定

const DefClass& getConstValueStdMove() { // 错误 xxx 
	cout << "--getConstValueStdMove entry " << endl;
	DefClass local;
	local.dump();
	cout << "--getConstValueStdMove exit " << endl;
	return std::move(local);  // 没有编译错误和警告  但是 引用的是局部变量,左值,函数返回 dump的话 还是出错
}
#endif


DefClass getValue() {
	cout << "--getValue entry " << endl; 
	uint64_t local_before = 4;  cout << "--getValue local_before " << &local_before << endl;
	DefClass local;
	uint64_t local_after  = 5;  cout << "--getValue local_after  " << &local_after  << endl;
	cout << "--getValue  exit " << endl;
	return local; // 编译器在不优化的时候 返回值是复杂类型 返回局部变量时候  优选移动构造函数 
}

/*
									VS2015							Clang++
const DefClass& cc = getValue();	无参构造local+移动构造cc		无参构造local(返回值优化 常量左值引用 直接绑定 到 局部变量   )
																	sizeof(DefClass) = 832
																	返回值优化: (都在栈上 栈往下生长 )
																	cbe8	 <= before		 < cbe8(H) - 832(D) = c8a8(H) ? -8 = local = c8a0
																		c7a0 <= local_before - 16个字节 =  local_after
																		c8a0 <= local		 < 这个local对象的栈地址 是调用函数之前的，相当于先分配栈内存，然后进入函数中，再构造初始化
																		c790 <= local_after  < 这个紧跟着 local_before
																	c888     <= after        < c8a0(H) - c888(H) = 24(D) local - 8(cc引用变量) - 8(after自己) -8(???) = after(after的低字节地址)

																	clang++ main.cpp -o main --std=c++11 -fno-elide-constructors
																	无参构造local+移动构造cc

DefClass& cc = getValue();			无参构造local+移动构造cc		error: non-const lvalue reference to type 'DefClass' cannot bind to a temporary of type 'DefClass'
																	非常量左值引用 不能绑定 临时变量(右值)
*/
int main()
{
#if 0 
	{
		int64_t before = 3;
		const DefClass& defCls = getConstValue();
		int64_t after = 3;
		printf("before = %p defCls = %p after = %p\n", &before, &defCls, &after );
		defCls.dump();
		cout << "   " << endl;
	}cout << " } " << endl;
	
#endif 

#if 0
	{	// 引用变量 本来也占内存 ，但是对引用变量进行&取地址 会取到‘被引用对象’的地址(可以看成 引用 重载了& ??)
		int64_t a = 0;
		//int64_t& c = a;
		int64_t b = 0;
		// 没有int64_t& c 情况下: a = 0xffffcbf0  b = 0xffffcbe8  a-b = 8个字节 
		// 有  int64_t& c 情况下: a = 0xffffcbf0  b = 0xffffcbe0  a-b = 16个字节 
		printf("a = %p b = %p sizeof(int64_t) = %zd \n", &a, &b, sizeof(int64_t));
		//printf("a = %p b = %p c = %p \n", &a, &b, &c );
	}
#endif 

#if 0
	{	// 引用变量是占64bits/8个字节长度
		int32_t a = 0;
		int32_t& c = a;
		int64_t b = 0;
		printf("a = %p b = %p \n", &a, &b ); 
		// a = 0xffffcbf8 b = 0xffffcbe8 
		// 高 ---> 低 
		//			   a  对齐                   c               b
		// |--4个字节--|----4----|----8个字节----|----8个字节----|								
	}
#endif

#if 1 
	{
		cout << "sizeof(DefClass) = " << sizeof(DefClass) << endl;
		uint64_t* before_new = new uint64_t(3); cout << "before_new " << before_new << endl;
		uint64_t before = 4;					cout << "before     " << &before << endl;
		const DefClass& cc = getValue();		cout << "cc	        " << &cc << endl; 
		cc.dump();
		uint64_t after = 5;						cout << "after      " << &after << endl;
		uint64_t* after_new = new uint64_t(6);	cout << "after_new  " << after_new << endl;

		cout << "   " << endl;
	}cout << " } " << endl;
#endif 

	return 0;
}
