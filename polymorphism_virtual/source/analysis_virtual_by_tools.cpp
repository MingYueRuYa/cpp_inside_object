/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include <iostream>

using std::cout;
using std::endl;

/*
 * 使用工具导出virtual table 内容
 * cl.exe：编译链接工具
 * cl /d1 reportSingleClassLayoutDerived analysis_virtual_by_tools.cpp
 * g++ -fdump-class-hierarchy -fsyntax-only analysis_virtual_by_tools.cpp
 * */

class BaseOne
{
public:
	virtual void f() { cout << "baseone::f()" << endl; }
	virtual void g() { cout << "baseone::g()" << endl; }
};

class BaseTwo
{
public:
	virtual void h() { cout << "basetwo::h()" << endl; }
	virtual void i() { cout << "basetwo::i()" << endl; }
};

class Derived :public BaseTwo, public BaseOne
{
public:
	virtual void f() { cout << "derived::f()" << endl; }
	virtual void i() { cout << "derived::i()" << endl; }

	virtual void mh() { cout << "derived::mh()" << endl; }
	virtual void mi() { cout << "derived::mi()" << endl; }
	virtual void mj() { cout << "derived::mj()" << endl; }
};

int main()
{	
	//多重继承
	cout << sizeof(BaseOne) << endl;
	cout << sizeof(BaseTwo) << endl;
	cout << sizeof(Derived) << endl;

	// vptr(虚函数表指针）什么时候创建出来的？
	// vptr跟着对象走，所以对象什么时候创建出来，vptr就什么时候创建出来。
        // 运行的时候；
	// 实际上，对于这种有虚函数的类，在编译的时候，
        // 编译器会往相关的构造函数中增加 为vptr赋值的代码，这是在编译期间编译器为构造函数增加的。
	//当程序运行的时候，遇到创建对象的代码，执行对象的构造函数。
        // 那么这个构造函数里有给对象的vptr(成员变量)赋值的语句，自然这个对象的vptr就被赋值了；

	// 虚函数表是什么时候创建的？
	// 实际上，虚函数表是编译器在编译期间（不是运行期间）
        // 就为每个类确定好了对应的虚函数表vtbl的内容。
	// 然后也是在编译器期间在相应的类构造函数中添加给vptr赋值的代码，
        // 这样程序运行的时候，当运行到成成类对象的代码时，会调用类的构造函数，
        // 执行到类的构造函数中的给vptr赋值的代码，这样这个类对象的vptr(虚函数表指针)就有值了；

	return 1;
}
