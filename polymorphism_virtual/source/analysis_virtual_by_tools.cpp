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
 * cl /d1 reportSingleClassLayoutMultiDerive analysis_virtual_by_tools.cpp
 * g++ -fdump-class-hierarchy -fsyntax-only analysis_virtual_by_tools.cpp
 * */

class BaseOne
{
public:
    int m_b = 0;
    virtual void i() { cout << "BaseOne::i()" << endl; }
    virtual void j() { cout << "BaseOne::j()" << endl; }
    virtual void k() { cout << "BaseOne::k()" << endl; } 
};

class Base
{
public:
    int m_a = 0;
    virtual void f() { cout << "Base::f()" << endl; }
    virtual void g() { cout << "Base::g()" << endl; }
    virtual void h() { cout << "Base::h()" << endl; }
};

class MultiDerive :public BaseOne, public Base
{
public:
    int m_e = 0;
    virtual void h() { cout << "MultiDerive::h()" << endl; }
    virtual void k() { cout << "MultiDerive::k()" << endl; }
    virtual void m() { cout << "MultiDerive::m()" << endl; }
};

class AbstractBase
{
public:
    AbstractBase()      { CallAbsFunc(); }
    void CallAbsFunc()  { AbsFunc(); }
    virtual void AbsFunc() = 0;
    virtual void AbsFunc2() = 0;
};

class Child : public AbstractBase
{
public:
    Child() { AbsFunc(); }
    void AbsFunc() { cout << "" << endl; }
    void AbsFunc2() { cout << "" << endl; }
};


class Base7
{
public:
    void MemberFunction() { cout << "Base function" << endl; }
    virtual void VirtualFun(int age = 1) 
    { cout << "Base age = " << age << endl; }
	virtual ~Base7() {}
};

//class Child : public Base
//{
//public:
//    void MemberFunction() { cout << "Child function" << endl; }
//    virtual void VirtualFun(int age = 2) 
//    { cout << "Child age = " << age << endl; }
//};

class Child2 : public Base
{
public:
    void MemberFunction() { cout << "Child2 function" << endl; }
    virtual void VirtualFun(int age = 3) { cout << "age = " << age << endl; }
};

class Parent
{
public:
    virtual void ParFun() { cout << "parent function" << endl; }
	virtual ~Parent() {}

public:
    int mParent;
};

class Child3 : public Base7
{
public:    
	void ParFun() { cout << "Child3" << endl; }
	virtual void VirChild3() {}
	void Child3SeflFun() 
	{ 
		// 间接调用，是通过虚表查找找虚函数的地址
		// VirChild3(); 
		// 通过这种方式是直接调用
		Child3::VirChild3();
        cout << "child3 self fun" << endl;
	}
    int mChild3;
};


class CloneBase1
{
public:
    CloneBase1() { cout << "CloneBase1" << endl; }
    virtual ~CloneBase1() {}
    virtual CloneBase1 *clone() { return new CloneBase1(); }

};

class CloneBase2
{
public:
    CloneBase2() { cout << "CloneBase2" << endl; }
    virtual ~CloneBase2() {}
    virtual CloneBase2 *clone() { return new CloneBase2(); }
};

class CloneChild : public CloneBase1, public CloneBase2
{
public:
    CloneChild() { cout << "CloneChild" << endl; }
    virtual ~CloneChild() {}
    virtual CloneChild *clone() { return new CloneChild(); }
};

void test_multi_inherit()
{
    CloneBase1 *base1 = new CloneChild();
    base1->clone();
    cout << "--------------------------" << endl; 

    CloneBase2 *base2 = new CloneChild();
    base2->clone();
	delete base2;
    cout << "--------------------------" << endl; 

    CloneChild *child = new CloneChild();
    child->clone();
    cout << "--------------------------" << endl; 
}

class Animal
{
public:
    virtual ~Animal() { cout << "~Animal" << endl; }
    virtual void Name() { cout << "Animal" << endl; }
    void Size() { cout << "Animal Size" << endl; }
};

class BigTiger: public virtual Animal
{
public:
    virtual ~BigTiger() { cout << "~Big Tiger" << endl; }
    virtual void Name() { cout << "Big Tiger" << endl; }
};

class FatTiger: public virtual Animal
{
public:
    virtual ~FatTiger() { cout << "~Fat Tiger" << endl; }
    virtual void Name() { cout << "Fat Tiger" << endl; }
};

class Tiger: public  BigTiger, public  FatTiger
{
public:
    virtual ~Tiger() { cout << "~Tiger" << endl; }
    virtual void Name() { cout << "Tiger" << endl; }
    virtual void CanFly() { cout << "Tiger Fly" << endl; }
};


// int analysis_virtual_by_tools_main()
int main()
{	
	//多重继承
//	cout << sizeof(BaseOne) << endl;
//	cout << sizeof(Base) << endl;
//	cout << sizeof(MultiDerive) << endl;

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


inline int max(int left, int right)
{
	return left > right ? left : right;
}


max(foo(), bar()+1)

// inline 被扩展之后
int t1;
int t2;

maxvale = (t1=foo()),(t2=bar()+1), t1 > t2 ? t1 : t2;



inline int max(int left, int right)
{
	int max_value = left > right ? left : right;
	return max_value;
}

{
	int local_var;
	int maxval;
	maxval = max(left, right);
}

// inline 被扩展之后
// max里面的max_value会被mangling，现在假设为__max_maxval
int __max_maxval;
maxval = (__max_maxval = left > right ? left : right), __max_maxval;












