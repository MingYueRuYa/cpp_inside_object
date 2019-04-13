/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

/*
	测试编译器的优化问题，从编译器的角度看问题
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

// 程序员视角
OptimizationA ProgramerPerspective()
{
	// 调用OptimizationA构造函数
	OptimizationA oatemp(1, 2);
	return oatemp;
	// 先是生成了一个临时对象tempobj，然后调用tempobj的拷贝构造函数，将oa的数据拷贝到
	// tempobj中，然后在调用oa的析构函数。
	// 这个过程中消耗了一个oa的，构造和析构函数，tempobj的拷贝构造和析构函数

//  return OptimizationA(1, 2);
    //  linux上如果关闭开优化选项的话，上面三行的代码效率是一样的
//  result:
//    compiler:1 level:2 call ctor
//    compiler:2 level:3 call copy ctor
//    compiler:1 level:2 call dtor
//    compiler:3 level:4 call copy ctor
//    compiler:2 level:3 call dtor
//    compiler:3 level:4 call dtor
    // 在linux上打开优化选项
    // 上面三行代码效率一样
//    compiler:1 level:2 call ctor
//    compiler:1 level:2 call dtor

//	OptimizationA oa(1, 2);
//	return oa;
    // 在windows上
//    compiler:1 level:2 call ctor
//    compiler:2 level:3 call copy ctor
//    compiler:1 level:2 call dtor
//    compiler:2 level:3 call dtor

//  return OptimizationA(1, 2);
    // 在windows上
//    compiler:1 level:2 call ctor
//    compiler:1 level:2 call dtor
}

void test_compiler_optimization()
{
	// 程序员的角度看
	OptimizationA oa = ProgramerPerspective();	

	// 编译器的角度看
//	OptimizationA ob;	编译器角度是不会调用OptimizationA的构造函数，下面的才是调用
//	ob.OptimizationA::OptimizationA(10, 20);
//	OptimizationA tempobj; 这里编译器也不会调用构造函数
//	tempobj.OptimizationA::OptimizationA(ob);
}

}

#endif // compiler_optimization_h
