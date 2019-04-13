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

void test_compiler_optimization()
{
	// ����Ա�ĽǶȿ�
	OptimizationA oa = ProgramerPerspective();	

	// �������ĽǶȿ�
//	OptimizationA ob;	�������Ƕ��ǲ������OptimizationA�Ĺ��캯��������Ĳ��ǵ���
//	ob.OptimizationA::OptimizationA(10, 20);
//	OptimizationA tempobj; ���������Ҳ������ù��캯��
//	tempobj.OptimizationA::OptimizationA(ob);
}

}

#endif // compiler_optimization_h
