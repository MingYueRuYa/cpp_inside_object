/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

/*
	测试编译器在何种情况会合成默认的构造函数
	同理可证：在何种情况下编译器会合成默认的拷贝构造函数
*/

#ifndef default_constrcuctor_h
#define default_constrcuctor_h

#include <iostream>

using std::cout;
using std::endl;

namespace defualt_constructor
{

// 含有缺省的构造函数成员类对象
// #define has_default_ctor_member 1

// 继承含有缺省的构造函数
// #define has_inherit_ctor_base 1

// 含有虚函数成员函数
// #define has_virtual_function 1

// 函数virtual函数的成员类对象
// #define has_virtual_func_member 1

// 父类含有虚函数
// #define has_inherit_virtual_func_base 1

// MatrixC, MatrixB 虚继承MatrixD
// #define has_virtual_inherit_base 1

// 类成员变量含有copy ctor
// #define has_default_copy_ctor_member 1

// 父类含有拷贝构造函数
#define has_inherit_copy_ctor_base 1

// 含有虚函数成员函数
// #define has_virtual_function_copy_ctor 1

// 类对象成员含有虚函数
// #define has_virtual_function_copy_ctor_member 1

// 父类函数虚函数
// #define has_inherit_virtual_function_copy_ctor_base 1

// 虚继承copy ctor
// #define has_virtual_inherit_function_copy_ctor_base 1

class MatrixD
{
};

#ifdef  has_virtual_inherit_base
class MatrixC : virtual public MatrixD
#elif has_virtual_inherit_function_copy_ctor_base
class MatrixC : virtual public MatrixD
#else
class MatrixC
#endif // has_virtual_inherit_base
{
public: 
#ifdef has_inherit_ctor_base
	MatrixC() { cout << "MatrixC" << endl; }
#elif has_inherit_copy_ctor_base
	MatrixC() {}
	MatrixC(const MatrixC &rhs) { cout << "MatrixC copy ctor" << endl; }
#elif has_inherit_virtual_function_copy_ctor_base
	virtual void VirFun() {}
#elif has_inherit_virtual_func_base
	virtual void VirFun() {}
#endif // has_virtual_inherit_base
};

#ifdef has_virtual_inherit_base
class MatrixB : virtual public MatrixD
#elif has_virtual_inherit_function_copy_ctor_base
class MatrixB : virtual public MatrixD
#else
class MatrixB
#endif // has_virtual_inherit_base
{
public:
#ifdef has_default_ctor_member
	MatrixB() { cout << "MatrixB" << endl; }
#elif has_virtual_func_member
	virtual void VirMatrixB() { cout << "virtual MatrixB" << endl; }
#elif has_default_copy_ctor_member
	MatrixB() {}
	MatrixB(const MatrixB &rhs) { cout << "copy ctor MatrixB" << endl; }
#elif has_virtual_function_copy_ctor_member
	virtual void VirMatrixB() { cout << "virtual MatrixB" << endl; }
#endif // has_default_ctor_member

	int m_high;
	int m_width;
};

#ifdef has_default_ctor_member
class MatrixA
#elif has_virtual_function
class MatrixA
#elif has_inherit_ctor_base
class MatrixA : public MatrixC
#elif has_inherit_copy_ctor_base
class MatrixA : public MatrixC
#elif has_virtual_func_member
class MatrixA
#elif has_virtual_inherit_base
class MatrixA : public MatrixB, public MatrixC
#elif has_inherit_virtual_func_base 
class MatrixA: public MatrixC
#elif has_inherit_virtual_function_copy_ctor_base
class MatrixA : public MatrixC
#elif has_virtual_inherit_function_copy_ctor_base
class MatrixA : public MatrixB, public MatrixC
#else
class MatrixA
#endif // has_default_ctor_member
{
public:
	int m_age;
	int m_score;

#ifdef has_default_ctor_member
	MatrixB matrixB;
#elif has_virtual_function
	virtual void VirFunc() { cout << "virtual function" << endl; }
#elif has_virtual_func_member
	MatrixB matrixB;
#elif has_default_copy_ctor_member
	MatrixA() {}
	MatrixB matrixB;
#elif has_inherit_copy_ctor_base
	MatrixA() {}
#elif has_virtual_function_copy_ctor
	virtual void VirFunc() { cout << "virtual function" << endl; }
#elif has_virtual_function_copy_ctor_member
	MatrixB matrixB;
#endif // has_default_ctor_member

};

// 没有析构函数的类
class NoDctorClass
{
public:
    int m_a;
};

void test_compiler_generator_def_ctor()
{
	//用dumpbin把.obj文件内容导出成可查看文件my.txt，
	// 这个my.txt格式，一般被认为是COFF：通用对象文件格式(Common Object File Format);

	MatrixA matrix;
	matrix.m_age = 0;

	// 编译器会在哪些情况下合成默认的构造函数？
	// 1.包含一个类成员变量，此成员变量含有默认的缺省构造函数。此时编译器就会
	// 生成默认的构造函数。在这个合成的构造函数中插入代码调用成员变量的构造函数
	// 2.继承的父类含有缺省的构造函数，此时编译器也会构造默认的构造函数，在子类合成的构造
	// 函数中插入代码，调用父类的缺省构造
	// 3.包含虚函数。不管是子类，父类，还是包含的成员类对象（不包含任何构造函数），只要
	// 包含了virtual function，编译器都会合成默认的构造函数
	// 4.含有虚继承现象，grandfather, parent(虚继承grand),child再继承，
	// 为了在构造函数中生成vbtable，虚基类表

	// 同样的道理，copy constrcutor也和constructor也是在同样的情况下，编译器会合成默认
	// 的构造函数

	// A.含有默认的构造函数
	//	1.父类有默认的构造函数
	//	2.包含类对象的成员变量含有默认构造函数

	// B.虚函数
	//	1.不管是自己包含虚函数，还是类成员变量有虚函数，还是父类中虚函数

	// C.虚继承
	//	1.编译器为了在插入vbtable 虚基类表
}

void test_compiler_generator_def_copy_ctor()
{
	MatrixA ma;

	MatrixA	mb = ma;
	// 编译器合成默认copy ctor时机和ctor是一样的
}

// 测试编译器合成析构函数
void test_compiler_geneator_def_dctor()
{
    NoDctorClass no_dctor_class;
    // 调用构造函数
    // no_dctor_class.NoDctorClass::NoDctorClass();
    // 调用析构函数
    no_dctor_class.~NoDctorClass();
    no_dctor_class.m_a = 0;
}

}

#endif // default_constrctor_h