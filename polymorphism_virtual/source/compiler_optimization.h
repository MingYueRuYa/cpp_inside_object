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
	OptimizationA oa(1, 2);
	return oa;
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
	OptimizationA oa = ProgramerPerspective();	
}

}

#endif // compiler_optimization_h
