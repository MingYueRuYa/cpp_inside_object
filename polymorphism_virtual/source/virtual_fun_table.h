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
    ������̽��
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
    // TODO:�����λ��������ֶ���������������?
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
    
    if (p1 == p2)   { cout << "�麯����ָ��λ�ڶ����ڴ��ĩβ" << endl; }
    else            { cout << "�麯����ָ��λ�ڶ����ڴ濪ͷ" << endl; }
    // �麯����ָ��λ�ڶ����ڴ濪ͷ
}

void test_manual_call_virtual_fun()
{
    Derive derive;
    // �麯��ָ���ַ
    long *vpoint    = (long *)(&derive);
    // �麯�����ַ
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

    // ����������е�˳���ǰ���������˳�����ģ����һ�����Ϊ0��ʾ������

    //TODO �������뺯����Ҫ����
}

void test_call_virtual_fun()
{
    // 1.���õĻ��Ǹ���ĺ��������﷢���˶�����и����󣬱������Ὣ�����еĸ���
    // ���ݸ��Ƶ�base������
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
    // Derive::g()  // ��������ĺ���
    // Base::h()

    Derive *d1 = new Derive();
    Derive *d2 = new Derive();


    // 2.һ�����а����麯������ô�ͻ�����һ���麯����ͬһ���๲��һ���麯����
    // ����static��Ա����
    // (�麯����ĵ�ַ��һ���ģ������麯��ָ�벻һ��)��
    // �������Լ����麯��������Ҳ���Լ����麯�������������һ�����࣬��ô�ͻ�һ��
    // �麯�����������Ļ�����ô���п����ж���麯����
    // 3.�����������ȫû����д�����е��麯������ô������麯�����е����ݺ͸�����һ����
    // ���������ű��ֱ�洢���ڴ�Ĳ�ͬ�ط���

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

    // ��ȡ�ڶ����麯��ָ���λ�ã��ӻ�ַ��ʼ�ĵ�ַ+��һ���̳ж���Ĵ�С
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
        // ����麯����ָ��
        memset(this, 0, sizeof(MemsetObj));
        cout << "memsetobj ctor" << endl;
    }

    MemsetObj(const MemsetObj &obj)
    {
        // ����ͬ������麯����ָ��
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
    // �麯�����Ѿ�memsetΪ0�������麯�����ܵ��óɹ�
    // ���ﲢû�����ֶ�̬�����ھ�̬����:�ڱ����ʱ���ȷ�����
    obj.virtual_func();

    // �ӷ����ĽǶȿ���������ֱ�ӵ��õģ�ֻ����2�д���
// 010B9AC7  lea         ecx,[obj]  
// 010B9ACA  call        virtual_fun_table::MemsetObj::virtual_func (010B154Bh)  

    MemsetObj *pobj = new MemsetObj();
    pobj->test();
    // shutdown
    // �������ֶ�̬�����ڶ�̬����:�ڳ������е�ʱ�򣬸���ʵ�������
    // ��̬�İѵ������ͱ����ú����󶨵�һ��
    pobj->virtual_func();
    // �ӷ����ĽǶȿ������ﶯ̬�Ļ�ȡ�����ҵ����ָ�룬���ҵ�����ַ�����ҵ��麯��
    // ���Լ�ӵĿ���Ϊ��ʵ�ֶ�̬��Ч����һ���Ľ���
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