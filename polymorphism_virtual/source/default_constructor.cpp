/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

/*
	���Ա������ں��������ϳ�Ĭ�ϵĹ��캯��
	ͬ���֤���ں�������±�������ϳ�Ĭ�ϵĿ������캯��
*/

#ifndef default_constrcuctor_h
#define default_constrcuctor_h

#include <iostream>

using std::cout;
using std::endl;

namespace defualt_constructor
{

// ����ȱʡ�Ĺ��캯����Ա�����
// #define has_default_ctor_member 1

// �̳к���ȱʡ�Ĺ��캯��
// #define has_inherit_ctor_base 1

// �����麯����Ա����
// #define has_virtual_function 1

// ����virtual�����ĳ�Ա�����
// #define has_virtual_func_member 1

// ���ຬ���麯��
// #define has_inherit_virtual_func_base 1

// MatrixC, MatrixB ��̳�MatrixD
// #define has_virtual_inherit_base 1

// ���Ա��������copy ctor
// #define has_default_copy_ctor_member 1

// ���ຬ�п������캯��
#define has_inherit_copy_ctor_base 1

// �����麯����Ա����
// #define has_virtual_function_copy_ctor 1

// ������Ա�����麯��
// #define has_virtual_function_copy_ctor_member 1

// ���ຯ���麯��
// #define has_inherit_virtual_function_copy_ctor_base 1

// ��̳�copy ctor
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

// û��������������
class NoDctorClass
{
public:
    int m_a;
};

void test_compiler_generator_def_ctor()
{
	//��dumpbin��.obj�ļ����ݵ����ɿɲ鿴�ļ�my.txt��
	// ���my.txt��ʽ��һ�㱻��Ϊ��COFF��ͨ�ö����ļ���ʽ(Common Object File Format);

	MatrixA matrix;
	matrix.m_age = 0;

	// ������������Щ����ºϳ�Ĭ�ϵĹ��캯����
	// 1.����һ�����Ա�������˳�Ա��������Ĭ�ϵ�ȱʡ���캯������ʱ�������ͻ�
	// ����Ĭ�ϵĹ��캯����������ϳɵĹ��캯���в��������ó�Ա�����Ĺ��캯��
	// 2.�̳еĸ��ຬ��ȱʡ�Ĺ��캯������ʱ������Ҳ�ṹ��Ĭ�ϵĹ��캯����������ϳɵĹ���
	// �����в�����룬���ø����ȱʡ����
	// 3.�����麯�������������࣬���࣬���ǰ����ĳ�Ա����󣨲������κι��캯������ֻҪ
	// ������virtual function������������ϳ�Ĭ�ϵĹ��캯��
	// 4.������̳�����grandfather, parent(��̳�grand),child�ټ̳У�
	// Ϊ���ڹ��캯��������vbtable��������

	// ͬ���ĵ���copy constrcutorҲ��constructorҲ����ͬ��������£���������ϳ�Ĭ��
	// �Ĺ��캯��

	// A.����Ĭ�ϵĹ��캯��
	//	1.������Ĭ�ϵĹ��캯��
	//	2.���������ĳ�Ա��������Ĭ�Ϲ��캯��

	// B.�麯��
	//	1.�������Լ������麯�����������Ա�������麯�������Ǹ������麯��

	// C.��̳�
	//	1.������Ϊ���ڲ���vbtable ������
}

void test_compiler_generator_def_copy_ctor()
{
	MatrixA ma;

	MatrixA	mb = ma;
	// �������ϳ�Ĭ��copy ctorʱ����ctor��һ����
}

// ���Ա������ϳ���������
void test_compiler_geneator_def_dctor()
{
    NoDctorClass no_dctor_class;
    // ���ù��캯��
    // no_dctor_class.NoDctorClass::NoDctorClass();
    // ������������
    no_dctor_class.~NoDctorClass();
    no_dctor_class.m_a = 0;
}

}

#endif // default_constrctor_h