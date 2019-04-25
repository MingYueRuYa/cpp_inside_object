/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

/*
	���Ա��������Ż����⣬�ӱ������ĽǶȿ�����
*/

#ifndef compiler_optimization_h
#define compiler_optimization_h

#include <iostream>

using std::cout;
using std::endl;

namespace compiler_optimization
{
class OptimizationA
{
public:
	OptimizationA() 
		: type_compiler(0),
		  type_level(0)
	{}

	OptimizationA(int compiler, int level) 
		: type_compiler(compiler),
		  type_level(level)
	{ 
        cout << "compiler:" << type_compiler 
             << " level:" << type_level
             << " call ctor" << endl; 
    }

	OptimizationA(const OptimizationA &rhs)
		: type_compiler(rhs.type_compiler+1),
		  type_level(rhs.type_level+1) 
	{ 
        cout << "compiler:" << type_compiler 
             << " level:" << type_level
             << " call copy ctor" << endl; 
    }

	virtual ~OptimizationA()
	{ 
        cout << "compiler:" << type_compiler 
             << " level:" << type_level
             << " call dtor" << endl; 
    }

	void test_function() { cout << "test function" << endl; }

private:
	int type_compiler;
	int type_level;
};

// ����Ա�ӽ�
OptimizationA ProgramerPerspective()
{
	// ����OptimizationA���캯��
	OptimizationA oatemp(1, 2);
	return oatemp;
	// ����������һ����ʱ����tempobj��Ȼ�����tempobj�Ŀ������캯������oa�����ݿ�����
	// tempobj�У�Ȼ���ڵ���oa������������
	// ���������������һ��oa�ģ����������������tempobj�Ŀ����������������

//  return OptimizationA(1, 2);
    //  linux������رտ��Ż�ѡ��Ļ����������еĴ���Ч����һ����
//  result:
//    compiler:1 level:2 call ctor
//    compiler:2 level:3 call copy ctor
//    compiler:1 level:2 call dtor
//    compiler:3 level:4 call copy ctor
//    compiler:2 level:3 call dtor
//    compiler:3 level:4 call dtor
    // ��linux�ϴ��Ż�ѡ��
    // �������д���Ч��һ��
//    compiler:1 level:2 call ctor
//    compiler:1 level:2 call dtor

//	OptimizationA oa(1, 2);
//	return oa;
    // ��windows��
//    compiler:1 level:2 call ctor
//    compiler:2 level:3 call copy ctor
//    compiler:1 level:2 call dtor
//    compiler:2 level:3 call dtor

//  return OptimizationA(1, 2);
    // ��windows��
//    compiler:1 level:2 call ctor
//    compiler:1 level:2 call dtor
}

// ���������ӽ�
void CompilerPerpective(OptimizationA &temp)
{
	return;
}


void test_compiler_optimization()
{
	// 1.����Ա�ĽǶȿ���class��Ϊ����ֵ����
	OptimizationA oa = ProgramerPerspective();	
	// �������ĽǶȿ�
//	OptimizationA oa;
//	CompilerPerpective(oa);

	// 2.����Ա�ĽǶȿ���copy��������
	OptimizationA oc = oa;
	// �������ĽǶȿ�����
//	OptimizationA oc; // �������OptimizationA�Ĺ��캯��
//	oc.OptimizationA::OptimizationA(oc);

	// 3.����Ա���ӽǣ�class��Ϊ����ֵ������ó�Ա����
	ProgramerPerspective().test_function();
	// �л���������
	OptimizationA od; // �������OptimizationA�Ĺ��캯��
	(CompilerPerpective(od), od).test_function();
	
	// 4.����Ա���ӽǣ�����ָ��
	OptimizationA (*pf)();
	pf = ProgramerPerspective;
	pf().test_function();	
	// �л���������
	OptimizationA oe;	
	void (*pf1)(OptimizationA &);
	pf1 = CompilerPerpective;
	(pf1(oe), oe).test_function();

	// �������Ƕ��ǲ������OptimizationA�Ĺ��캯��
	OptimizationA ob; // ����Ĳ��ǵ���
	// �ֶ����ù��캯��
	ob.OptimizationA::OptimizationA(10, 20);
	// ���������Ҳ������ù��캯��
	OptimizationA tempobj;
	// �ֶ�����copy���캯��
	tempobj.OptimizationA::OptimizationA(ob);

}

}

#endif // compiler_optimization_h
