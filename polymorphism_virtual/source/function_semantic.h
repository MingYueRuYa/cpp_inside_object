/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef function_semantic_h
#define function_semantic_h

#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

namespace function_semantic
{
class NormalCall
{
public:
    void Add(int number)
    {
        number+m_add;
    }

    static void ClassStatic()
    {
        cout << "ClassStatic" << endl;
    }

    virtual void ClassVirutal()
    {
        cout << "ClassVirutal" << endl;
    }

public:
    int m_add;
};

void Add(NormalCall *nc, int number)
{
    nc->m_add + number;
}

void test_normal_call()
{
    NormalCall nc;
    nc.Add(1);
    // 其实被编译器转成__ZN6NormalCall6AddEi(&nc, 1)
    // 编译器在调用类的普通成员函数时，会在函数的参数中隐式添加了一个this指针，这个指针
    // 就是当前生成对象的首地址。同时对普通成员变量的存取也是通过this指针

    Add(&nc, 1);     // 调用全局函数

    // 打印出类成员函数的地址
    printf("Normal Add address:%p\n", &NormalCall::Add);
}

void test_virtual_static_call()
{
    // 1.虚成员函数调用方式
    NormalCall NC;
    // 使用对象调用虚函数，就像调用普通的成员函数一样，不需要通过虚函数表
    NC.ClassVirutal();

    NormalCall *pNC = new NormalCall();
    // 通过vptr-->vftable，找到对应的虚函数地址再调用
    pNC->ClassVirutal();
    // 站在用户的角度看
    // ((*(pNC->vptr))[0])(pNC)
    // 根据vtpr，找到vftable，在根据偏移找到虚函数地址，在传递当前的对象的地址

    // 这样打印的并不是虚函数的实际地址
    printf("class virutal function address:%p\n", &NormalCall::ClassVirutal);

    printf("static function address:%p\n", &NormalCall::ClassStatic);

    NC.ClassStatic();
    pNC->ClassStatic();
    NormalCall::ClassStatic();

    // 上面三种调用static函数的生成的反汇编代码是一致的。
// 0022C7D4  call        function_semantic::NormalCall::ClassStatic (0221550h)  
// 0022C7D9  call        function_semantic::NormalCall::ClassStatic (0221550h)  
// 0022C7DE  call        function_semantic::NormalCall::ClassStatic (0221550h)  
    
    //class static function
    // 1.静态成员函数，没有this指针
    // 2.无法直接存取类中普通的非静态成员变量
    // 3.调用方式可以向类中普通的成员函数，也可以用ClassName::StaticFunction
    // 4.可以将静态的成员函数在某些环境下当做回调函数使用

    ((NormalCall *)0)->ClassStatic();
    // 这段代码在VS2013下测试没有崩溃，通过寄存器来看ecx为0，但是也没有崩溃
    ((NormalCall *)0)->Add(1);

}

class Base
{
public:
    void MemberFunction() { cout << "Base function" << endl; }
    virtual void VirtualFun(int age = 1) 
    { cout << "Base age = " << age << endl; }
	virtual ~Base() {}
};

class Child : public Base
{
public:
    void MemberFunction() { cout << "Child function" << endl; }
    virtual void VirtualFun(int age = 2) 
    { cout << "Child age = " << age << endl; }
};

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

class Child3 : public Base, public Parent
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

// 测试静态绑定和动态绑定
void test_complie_runtime_bind()
{
    // 1.静态类型和动态类型
    // 静态类型：对象定义时的类型，编译期间就确定好的
    // 动态类型：对象目前所指向的类型（运行的时候才决定的类型）
    Base base;  // base的静态类型是Base，没有动态类型，因为不是指针不是引用
    Child child;    // child的静态类型是Child，没有动态类型，因为不是指针不是引用

    // pbase的静态类型依旧就是Base*,因为没有指向对象
    Base *pbase;
    // pbase1的静态类型是Base*，但是动态类型为Child
    Base *pbase1 = new Child();
    // pbase2的静态类型是Base*，但是动态类型为Child2
    Base *pbase2 = new Child2();

    // pbase的动态类型为Child*
    pbase = pbase1;
    // pbase的动态类型为Child2*
    pbase = pbase2;

    // 2.静态绑定和动态绑定
    Child child2;
    Child *pChild = &child2;
    // Child function
    pChild->MemberFunction();

    Base *base3 = &child2;
    // Base function
    base3->MemberFunction();
    // 普通成员函数是静态绑定，所以这里调用的是父类还是子类的函数需要当前对象的静态类型
    // 所以pChild的静态类型是Child，base3的静态类型是Base
    // 所以子类必须警惕覆盖父类的同名函数

    base3->VirtualFun();
    // Child age = 1
    pChild->VirtualFun();
    // Child age = 2
    // 虚函数是动态绑定，但是函数的默认参数也同样是静态绑定，
    // base3的静态类型是Base，所以参数的默认值是1
    // pChild的静态类型是Child，所以参数的默认值是2


    // 多态的体现：
    // 1.在代码上看，如果调用一个虚函数，是通过查找虚表来找到虚函数的入口地址，就是多态
    // 2.从表现形式上看
            //a.有继承关系，存在虚函数
            //b.子类重写父类的虚函数
            //c.子类以父类的引用或者指针的形式出现

    Child child4;
    // 不是多态
    child4.VirtualFun();

    Base *base4 = &child4;
    // 多态
    base4->VirtualFun();

    Child *child5 = new Child();
    // 多态
    child5->VirtualFun();
}

// 测试多继承下含有虚函数，以及虚析构函数
void test_multi_virtual_base_dtor()
{
	Child3 *c3		= new Child3();
	Parent *pParent = c3;

	pParent->ParFun();

	c3->Child3SeflFun();

	delete pParent;

	// 多重继承下，复杂性主要体现在后面的基类上
	// 在父类中定义虚析构函数，debug模式下可以正常运行，但是切换到release模型，运行崩溃
    // delete pParent;

	// 如何成功删除用第二基类指针指向new出来的子类对象
	// Child3 --> Base --> Parent, Parent为第二基类
	// delete pParent我们实际是想做delete c3整个子类对象。
	// 1.但现在delete pParent，因为Parent中没有虚析构函数，导致系统直接删除已pParent为开头
	// 的内存，但是这个内存并不是new出来的起始内存地址，所以delete直接爆出异常
	// 2.如果pParent中含有析构函数，但不是虚函数类型。这个析构函数会被系统调用，但是delete
	// 还是pParent为开头的地址，还是会爆出异常。
	// 3.如果pParent中含有虚析构函数，那么在delete的时候就会调用~Child3-->~Parent->Base
	// 正常的释放内存
	// 4.如果存在继承的，父类一定要提供虚析构函数，以便在释放内存的时候能够正常的释放内存
}

void test_rtti()
{
    // 1.C++中的RTTI运行时类型识别，要求父类必须至少有一个虚函数，否则RTTI就不准确
    // RTTI就可以在执行难期间查询一个多态指针，或者多态引用的信息
    // RTTI能力靠typeid和dynamic_cast运算符来实现
    Base *pbase = new Child3();
    Child3 c3;
    Base &base = c3;

    cout << typeid(*pbase).name() << endl;
    cout << typeid(base).name() << endl;
    // class function_semantic::Child3
    // class function_semantic::Child3

    Child3 *pc3 = dynamic_cast<Child3 *>(pbase);
    if (nullptr != pc3) {
        pc3->Child3SeflFun();
        // child3 self fun
    }

    // 2.RTTI实现原理
    // typeid返回的是一个常量对象的引用，对象类型为type_info(class)
    const type_info &typeinfo = typeid(*pbase);
    
    Base *p1 = new Child3();
    Base *p2 = new Child3();
    const type_info &ptype1 = typeid(*p1);
    const type_info &ptype2 = typeid(*p2);
    if (ptype1 == ptype2) {
        cout << "all same" << endl;
        // all same
        // type_info每个class共享一个
    }

    // 静态类型：不属于多态类型
    cout << typeid(int).name() << endl;
	cout << typeid(Base).name() << endl;
	cout << typeid(Child3).name() << endl;
	Child3 *pa3 = new Child3();
	cout << typeid(pa3).name() << endl;
    // int
    // class function_semantic::Base
    // class function_semantic::Child3
    // class function_semantic::Child3 *

    long *vptr      = (long *)pa3;
    long *vftable   = (long *)(*vptr);
    
    long *ptypeinfo = (long *)(*(vftable-1));
    ptypeinfo += 3;
    long *ptypeinfo_address = (long *)(*ptypeinfo);
    const type_info *ptypeinfo_real_address = (type_info *)ptypeinfo_address;
    // class function_semantic::Child3
    cout << ptypeinfo_real_address->name() << endl; 

    // 3.vptr,vtbl,rtti的type_info信息，都是构造时初始化
    // rtti的信息都是编译期间就确定的，学到了可执行文件中

}

}

#endif // function_semantic_h