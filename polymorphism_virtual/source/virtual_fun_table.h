/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef virtual_fun_table_h
#define virtual_fun_table_h

#include <iostream>

using std::cout;
using std::endl;

/*
    对虚表的探究
*/
namespace virtual_fun_table
{

typedef void (*Fun)();

class Base 
{
public:
    int m_a = 0;
    virtual void f() { cout << "Base::f()" << endl; }
    virtual void g() { cout << "Base::g()" << endl; }
    virtual void h() { cout << "Base::h()" << endl; }
    // virtual ~Base() { cout << "~Base" << endl; }
    // TODO:在虚表位置中如何手动调用虚析构函数?
};

class BaseOne
{
public:
    int m_a = 0;
    virtual void i() { cout << "BaseOne::i()" << endl; }
    virtual void j() { cout << "BaseOne::j()" << endl; }
    virtual void k() { cout << "BaseOne::k()" << endl; }
};

class Derive : public Base
{
    virtual void g() { cout << "Derive::g()" << endl; }
};

class MultiDerive: public BaseOne, public Base
{
    virtual void h() { cout << "MultiDerive::h()" << endl; }
    virtual void k() { cout << "MultiDerive::k()" << endl; }
};

void test_virtual_fun_address()
{
    Base vfclass;
    char *p1 = reinterpret_cast<char *>(&vfclass);
    char *p2 = reinterpret_cast<char *>(&vfclass.m_a);
    
    if (p1 == p2)   { cout << "虚函数表指针位于对象内存的末尾" << endl; }
    else            { cout << "虚函数表指针位于对象内存开头" << endl; }
    // 虚函数表指针位于对象内存开头
}

void test_manual_call_virtual_fun()
{
    Derive derive;
    // 虚函数指针地址
    long *vpoint    = (long *)(&derive);
    // 虚函数表地址
    long *pvtable   = (long *)(*vpoint);

    for(int i = 0; i < 4; ++i) {
        cout << std::hex << "0x" << pvtable[i] << endl;
    }
    // 0xa2112c
    // 0xa21622
    // 0xa214dd
    // 0x0


    ((Fun)pvtable[0])();
    ((Fun)pvtable[1])();
    ((Fun)pvtable[2])();
    // Base::f()
    // Derive::g()
    // Base::h()

    Base base;
    long *basevpoint    = (long *)(&base);
    long *basepvtable   = (long *)(*basevpoint);
    for(int i = 0; i < 4; ++i) {
        cout << std::hex << "0x" << basepvtable[i] << endl;
    }
    // 0xa2112c
    // 0xa21627
    // 0xa214dd
    // 0x0

    ((Fun)basepvtable[0])();
    ((Fun)basepvtable[1])();
    ((Fun)basepvtable[2])();
    // ((Fun)basepvtable[3])();
    // Base::f()
    // Base::g()
    // Base::h()

    // 函数在虚表中的顺序是按照声明的顺序来的，最后一个虚表为0表示结束符

    //TODO 析构代码函数需要调研
}

void test_call_virtual_fun()
{
    // 1.调用的还是父类的函数，这里发生了对象的切割现象，编译器会将子类中的父类
    // 数据复制到base对象中
    Base base = Derive();
    base.f();
    base.g();
    base.h();
    // Base::f()
    // Base::g()
    // Base::h()

    Base *pbase = new Derive();
    pbase->f();
    pbase->g();
    pbase->h();
    // Base::f()
    // Derive::g()  // 调用子类的函数
    // Base::h()

    Derive *d1 = new Derive();
    Derive *d2 = new Derive();


    // 2.一个类中包括虚函数，那么就会生成一个虚函数表。同一个类共用一个虚函数表，
    // 类似static成员变量
    // (虚函数表的地址是一样的，但是虚函数指针不一样)，
    // 子类有自己的虚函数表，父类也有自己的虚函数表。如果子类有一个父类，那么就会一个
    // 虚函数表，多个父类的话，那么就有可能有多个虚函数表。
    // 3.如果子类中完全没有重写父类中的虚函数，那么子类的虚函数表中的内容和父类是一样的
    // 但还是两张表，分别存储在内存的不同地方。

}

void test_multi_inhert_virtual_fun()
{
    MultiDerive multiderive;

    long *pbase_tablepoint      = (long *)(&multiderive);
    long *base_table_address    = (long *)*(pbase_tablepoint);
    
    for(int i = 0; i < 4; ++i) {
        cout << std::hex << "0x" << base_table_address[i] << endl;
    }

    ((Fun)(base_table_address[0]))();
    ((Fun)(base_table_address[1]))();
    ((Fun)(base_table_address[2]))();

    // 获取第二个虚函数指针的位置，从基址开始的地址+第一个继承对象的大小
    long *pbaseone_tablepoint = 
        (long *)(reinterpret_cast<char *>(pbase_tablepoint)+sizeof(Base));
    long *baseone_table_address = (long *)(*pbaseone_tablepoint);
    for(int i = 0; i < 4; ++i) {
        cout << std::hex << "0x" << baseone_table_address[i] << endl;
    }

    ((Fun)(baseone_table_address[0]))();
    ((Fun)(baseone_table_address[1]))();
    ((Fun)(baseone_table_address[2]))();

}

class MemsetObj {
public:
    int x;
    int y;
    int z;
public:
    MemsetObj()
    {
        // 清空虚函数表指针
        memset(this, 0, sizeof(MemsetObj));
        cout << "memsetobj ctor" << endl;
    }

    MemsetObj(const MemsetObj &obj)
    {
        // 这里同样清空虚函数表指针
        memcpy(this, &obj, sizeof(MemsetObj));
        cout << "memsetobj copy ctor" << endl;
    }

    ~MemsetObj()
    {
        cout << "memsetobj dctor" << endl;
    }

    void test() { cout << "memset obj test" << endl; }
    virtual void virtual_func() {  cout << "virtual test" << endl; }
};

void test_memset_virtual_fun()
{
    MemsetObj obj;
    obj.test();
    // 虚函数表已经memset为0，但是虚函数还能调用成功
    // 这里并没有体现多态，属于静态联编:在编译的时候就确定语句
    obj.virtual_func();

    // 从反汇编的角度看，这里是直接调用的，只用了2行代码
// 010B9AC7  lea         ecx,[obj]  
// 010B9ACA  call        virtual_fun_table::MemsetObj::virtual_func (010B154Bh)  

    MemsetObj *pobj = new MemsetObj();
    pobj->test();
    // shutdown
    // 这里体现多态，属于动态联编:在程序运行的时候，根据实际情况，
    // 动态的把调用语句和被调用函数绑定到一起
    pobj->virtual_func();
    // 从反汇编的角度看，这里动态的获取，先找到虚表指针，再找到虚表地址，再找到虚函数
    // 可以间接的看出为了实现多态，效率有一定的降低
// 010B9B2A  mov         eax,dword ptr [pobj]  
// 010B9B2D  mov         edx,dword ptr [eax]  
// 010B9B2F  mov         esi,esp  
// 010B9B31  mov         ecx,dword ptr [pobj]  
// 010B9B34  mov         eax,dword ptr [edx]  
// 010B9B36  call        eax  
// 010B9B38  cmp         esi,esp  
// 010B9B3A  call        __RTC_CheckEsp (010B147Eh) 
    delete pobj;
}

}

#endif // virtual_fun_table_h