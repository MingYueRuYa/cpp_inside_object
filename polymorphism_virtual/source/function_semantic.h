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
    // ��ʵ��������ת��__ZN6NormalCall6AddEi(&nc, 1)
    // �������ڵ��������ͨ��Ա����ʱ�����ں����Ĳ�������ʽ������һ��thisָ�룬���ָ��
    // ���ǵ�ǰ���ɶ�����׵�ַ��ͬʱ����ͨ��Ա�����Ĵ�ȡҲ��ͨ��thisָ��

    Add(&nc, 1);     // ����ȫ�ֺ���

    // ��ӡ�����Ա�����ĵ�ַ
    printf("Normal Add address:%p\n", &NormalCall::Add);
}

void test_virtual_static_call()
{
    // 1.���Ա�������÷�ʽ
    NormalCall NC;
    // ʹ�ö�������麯�������������ͨ�ĳ�Ա����һ��������Ҫͨ���麯����
    NC.ClassVirutal();

    NormalCall *pNC = new NormalCall();
    // ͨ��vptr-->vftable���ҵ���Ӧ���麯����ַ�ٵ���
    pNC->ClassVirutal();
    // վ���û��ĽǶȿ�
    // ((*(pNC->vptr))[0])(pNC)
    // ����vtpr���ҵ�vftable���ڸ���ƫ���ҵ��麯����ַ���ڴ��ݵ�ǰ�Ķ���ĵ�ַ

    // ������ӡ�Ĳ������麯����ʵ�ʵ�ַ
    printf("class virutal function address:%p\n", &NormalCall::ClassVirutal);

    printf("static function address:%p\n", &NormalCall::ClassStatic);

    NC.ClassStatic();
    pNC->ClassStatic();
    NormalCall::ClassStatic();

    // �������ֵ���static���������ɵķ���������һ�µġ�
// 0022C7D4  call        function_semantic::NormalCall::ClassStatic (0221550h)  
// 0022C7D9  call        function_semantic::NormalCall::ClassStatic (0221550h)  
// 0022C7DE  call        function_semantic::NormalCall::ClassStatic (0221550h)  
    
    //class static function
    // 1.��̬��Ա������û��thisָ��
    // 2.�޷�ֱ�Ӵ�ȡ������ͨ�ķǾ�̬��Ա����
    // 3.���÷�ʽ������������ͨ�ĳ�Ա������Ҳ������ClassName::StaticFunction
    // 4.���Խ���̬�ĳ�Ա������ĳЩ�����µ����ص�����ʹ��

    ((NormalCall *)0)->ClassStatic();
    // ��δ�����VS2013�²���û�б�����ͨ���Ĵ�������ecxΪ0������Ҳû�б���
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
		// ��ӵ��ã���ͨ������������麯���ĵ�ַ
		// VirChild3(); 
		// ͨ�����ַ�ʽ��ֱ�ӵ���
		Child3::VirChild3();
        cout << "child3 self fun" << endl;
	}
    int mChild3;
};

// ���Ծ�̬�󶨺Ͷ�̬��
void test_complie_runtime_bind()
{
    // 1.��̬���ͺͶ�̬����
    // ��̬���ͣ�������ʱ�����ͣ������ڼ��ȷ���õ�
    // ��̬���ͣ�����Ŀǰ��ָ������ͣ����е�ʱ��ž��������ͣ�
    Base base;  // base�ľ�̬������Base��û�ж�̬���ͣ���Ϊ����ָ�벻������
    Child child;    // child�ľ�̬������Child��û�ж�̬���ͣ���Ϊ����ָ�벻������

    // pbase�ľ�̬�������ɾ���Base*,��Ϊû��ָ�����
    Base *pbase;
    // pbase1�ľ�̬������Base*�����Ƕ�̬����ΪChild
    Base *pbase1 = new Child();
    // pbase2�ľ�̬������Base*�����Ƕ�̬����ΪChild2
    Base *pbase2 = new Child2();

    // pbase�Ķ�̬����ΪChild*
    pbase = pbase1;
    // pbase�Ķ�̬����ΪChild2*
    pbase = pbase2;

    // 2.��̬�󶨺Ͷ�̬��
    Child child2;
    Child *pChild = &child2;
    // Child function
    pChild->MemberFunction();

    Base *base3 = &child2;
    // Base function
    base3->MemberFunction();
    // ��ͨ��Ա�����Ǿ�̬�󶨣�����������õ��Ǹ��໹������ĺ�����Ҫ��ǰ����ľ�̬����
    // ����pChild�ľ�̬������Child��base3�ľ�̬������Base
    // ����������뾯�踲�Ǹ����ͬ������

    base3->VirtualFun();
    // Child age = 1
    pChild->VirtualFun();
    // Child age = 2
    // �麯���Ƕ�̬�󶨣����Ǻ�����Ĭ�ϲ���Ҳͬ���Ǿ�̬�󶨣�
    // base3�ľ�̬������Base�����Բ�����Ĭ��ֵ��1
    // pChild�ľ�̬������Child�����Բ�����Ĭ��ֵ��2


    // ��̬�����֣�
    // 1.�ڴ����Ͽ����������һ���麯������ͨ������������ҵ��麯������ڵ�ַ�����Ƕ�̬
    // 2.�ӱ�����ʽ�Ͽ�
            //a.�м̳й�ϵ�������麯��
            //b.������д������麯��
            //c.�����Ը�������û���ָ�����ʽ����

    Child child4;
    // ���Ƕ�̬
    child4.VirtualFun();

    Base *base4 = &child4;
    // ��̬
    base4->VirtualFun();

    Child *child5 = new Child();
    // ��̬
    child5->VirtualFun();
}

// ���Զ�̳��º����麯�����Լ�����������
void test_multi_virtual_base_dtor()
{
	Child3 *c3		= new Child3();
	Parent *pParent = c3;

	pParent->ParFun();

	c3->Child3SeflFun();

	delete pParent;

	// ���ؼ̳��£���������Ҫ�����ں���Ļ�����
	// �ڸ����ж���������������debugģʽ�¿����������У������л���releaseģ�ͣ����б���
    // delete pParent;

	// ��γɹ�ɾ���õڶ�����ָ��ָ��new�������������
	// Child3 --> Base --> Parent, ParentΪ�ڶ�����
	// delete pParent����ʵ��������delete c3�����������
	// 1.������delete pParent����ΪParent��û������������������ϵͳֱ��ɾ����pParentΪ��ͷ
	// ���ڴ棬��������ڴ沢����new��������ʼ�ڴ��ַ������deleteֱ�ӱ����쳣
	// 2.���pParent�к��������������������麯�����͡�������������ᱻϵͳ���ã�����delete
	// ����pParentΪ��ͷ�ĵ�ַ�����ǻᱬ���쳣��
	// 3.���pParent�к�����������������ô��delete��ʱ��ͻ����~Child3-->~Parent->Base
	// �������ͷ��ڴ�
	// 4.������ڼ̳еģ�����һ��Ҫ�ṩ�������������Ա����ͷ��ڴ��ʱ���ܹ��������ͷ��ڴ�
}

void test_rtti()
{
    // 1.C++�е�RTTI����ʱ����ʶ��Ҫ�������������һ���麯��������RTTI�Ͳ�׼ȷ
    // RTTI�Ϳ�����ִ�����ڼ��ѯһ����ָ̬�룬���߶�̬���õ���Ϣ
    // RTTI������typeid��dynamic_cast�������ʵ��
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

    // 2.RTTIʵ��ԭ��
    // typeid���ص���һ��������������ã���������Ϊtype_info(class)
    const type_info &typeinfo = typeid(*pbase);
    
    Base *p1 = new Child3();
    Base *p2 = new Child3();
    const type_info &ptype1 = typeid(*p1);
    const type_info &ptype2 = typeid(*p2);
    if (ptype1 == ptype2) {
        cout << "all same" << endl;
        // all same
        // type_infoÿ��class����һ��
    }

    // ��̬���ͣ������ڶ�̬����
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

    // 3.vptr,vtbl,rtti��type_info��Ϣ�����ǹ���ʱ��ʼ��
    // rtti����Ϣ���Ǳ����ڼ��ȷ���ģ�ѧ���˿�ִ���ļ���

}

}

#endif // function_semantic_h