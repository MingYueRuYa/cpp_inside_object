/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef initialization_list_h
#define initialization_list_h

#include <iostream>

using std::cout;
using std::endl;

/*
	测试成员初始化列表
*/

namespace initialization_list
{
class InitialzationA
{
public:
	int m_i;
	InitialzationA(int value = 0) :m_i(value) //类型转换构造函数
	{
		cout << "InitialzationA(int)构造函数被调用" << endl;
	}

	InitialzationA(const InitialzationA &tmpv)
	{
		cout << "InitialzationA拷贝构造函数被调用" << endl;
	}

	InitialzationA& operator=(const InitialzationA &tmp)
	{
		cout << "InitialzationA拷贝赋值运算符被调用" << endl;
		return *this;
	}

	~InitialzationA()
	{
		cout << "InitialzationA析构函数被调用" << endl;
	}
};

class InitialzationB
{
public:
	// 这里会耗费调用一次InitialzationA的构造函数机会
//	InitialzationB()
//	{}

	InitialzationB(int value):  m_IA(value), m_a(value), m_b(value)
		/*
			1.如果是在成员列表初始化，站在编译器的角度看
			m_IA.InitialzationA::InitialzationA(value)
		*/
	{
		/*
			m_IA = value;
			2.如果是在函数内部初始化，站在编译器的角度看
			A.先是生成一个临时对象
			InitialzationA oc;
			oc.InitialzationA::InitialzationA(value);
			B.在m_IA的copy ctor
			m_IA.InitialzationA::InitialzationA(oc);	
			C.临时对象再去销毁
			oc.InitialzationA::~InitialzationA();
			所以成员变量初始化会提高效率，但只针对类类型变量，对基本类型无影响。
			在初始化列表中，不要用类成员变量去初始化另外一个成员变量
		*/
	}

private:
	int m_a;
	int m_b;
	InitialzationA m_IA;
};

}

#endif // initialization_list_h