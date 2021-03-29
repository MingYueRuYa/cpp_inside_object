/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef data_semantics_h 
#define data_semantics_h

#include <string>

using std::string;

string tempvalue;
typedef string mytype;

#define test_class_func_parameter 1

/*
    数据语义学

    再有多层继承的关系中，使用内存拷贝函数将子类复制给父类一定要注意，
    因为编译器的编译之后的内存布局可能是不一样的，直接使用memcpy函数可能拷贝的数据有问题
*/
namespace data_semantics
{
	class TestDataAnalyse {

#ifdef test_class_func_parameter
		// 一般将此处的代码放在class的开头
		typedef int mytype;
#endif

	public:
		int Fun();

		// 对于成员参数的解析，编译器是第一次遇到这个类型的mytype类型的时候被决定的
		// mytype第一次遇到的时候就看到了type string mytype
		void CopyValue(mytype value);

	private:
		// 类中定义一个和全局变量名称一样但类型不一样的变量
		// 此时编译器还是能够正常识别
		int tempvalue;

#ifndef test_class_func_parameter
		typedef int mytype;
#endif // test_class_func_parameter

	};

	int TestDataAnalyse::Fun()
	{
		return tempvalue;
	}

	void TestDataAnalyse::CopyValue(mytype value)
	{
		tempvalue = value;
	}

	void test_data_analyse()
	{
		TestDataAnalyse data;
		// 编译没有问题
		// 编译器对类成员的函数解析，是在看到TestDataAnalyse定义完毕之后才开始的
		// 所以在对tempvalue的解析和绑定，是在这个类定义完成之后发生的。
		data.Fun();
	}

	// #define test_pragma_pack

#ifdef test_pragma_pack
#pragma pack(1)
#endif // test_pragma_pack
	class ClassMemberAddress
	{
	public:
		int m_i;
		static int m_si;

		int m_j;
		static int m_sj;

		int m_k;
		static int m_sk;

		char m_c;
		int m_n;

		void PrintMemberOffset()
		{
			printf("ClassMemberAddress::m_i     = %p\n", &ClassMemberAddress::m_i);
			printf("ClassMemberAddress::m_si    = %p\n", &ClassMemberAddress::m_si);
			printf("ClassMemberAddress::m_j     = %p\n", &ClassMemberAddress::m_j);
			printf("ClassMemberAddress::m_sj    = %p\n", &ClassMemberAddress::m_sj);
			printf("ClassMemberAddress::m_k     = %p\n", &ClassMemberAddress::m_k);
			printf("ClassMemberAddress::m_sk    = %p\n", &ClassMemberAddress::m_sk);
			printf("ClassMemberAddress::m_c     = %p\n", &ClassMemberAddress::m_c);
			printf("ClassMemberAddress::m_n     = %p\n", &ClassMemberAddress::m_n);
		}

		void PrintMemberAddress()
		{
			printf("ClassMemberAddress::m_i     = %p\n", &m_i);
			printf("ClassMemberAddress::m_si    = %p\n", &m_si);
			printf("ClassMemberAddress::m_j     = %p\n", &m_j);
			printf("ClassMemberAddress::m_sj    = %p\n", &m_sj);
			printf("ClassMemberAddress::m_k     = %p\n", &m_k);
			printf("ClassMemberAddress::m_sk    = %p\n", &m_sk);
			printf("ClassMemberAddress::m_c     = %p\n", &m_c);
			printf("ClassMemberAddress::m_n     = %p\n", &m_n);
		}

	};
#pragma pack()

	int ClassMemberAddress::m_si = 0;
	int ClassMemberAddress::m_sj = 0;
	int ClassMemberAddress::m_sk = 0;

	void test_class_member_address()
	{
		cout << sizeof(ClassMemberAddress) << endl;

		ClassMemberAddress cma;
		cma.PrintMemberAddress();
		// ClassMemberAddress::m_i     = 00AFFB54
		// ClassMemberAddress::m_si    = 00E276E8
		// ClassMemberAddress::m_j     = 00AFFB58
		// ClassMemberAddress::m_sj    = 00E276EC
		// ClassMemberAddress::m_k     = 00AFFB5C
		// ClassMemberAddress::m_sk    = 00E276F0
		// ClassMemberAddress::m_c     = 00AFFB60
		// ClassMemberAddress::m_n     = 00AFFB64
		cout << "---------------------------------" << endl;
		cma.PrintMemberOffset();
		// ClassMemberAddress::m_i     = 00000000
		// ClassMemberAddress::m_si    = 00E276E8
		// ClassMemberAddress::m_j     = 00000004
		// ClassMemberAddress::m_sj    = 00E276EC
		// ClassMemberAddress::m_k     = 00000008
		// ClassMemberAddress::m_sk    = 00E276F0
		// ClassMemberAddress::m_c     = 0000000C
		// ClassMemberAddress::m_n     = 00000010

		cout << "---------------------------------" << endl;
		ClassMemberAddress *pcma = new ClassMemberAddress();
		pcma->PrintMemberAddress();
		// ClassMemberAddress::m_i     = 010D5A20
		// ClassMemberAddress::m_si    = 012C76E8
		// ClassMemberAddress::m_j     = 010D5A24
		// ClassMemberAddress::m_sj    = 012C76EC
		// ClassMemberAddress::m_k     = 010D5A28
		// ClassMemberAddress::m_sk    = 012C76F0
		// ClassMemberAddress::m_c     = 010D5A2C
		// ClassMemberAddress::m_n     = 010D5A30
		cout << "---------------------------------" << endl;
		pcma->PrintMemberOffset();
		// ClassMemberAddress::m_i     = 00000000
		// ClassMemberAddress::m_si    = 012C76E8
		// ClassMemberAddress::m_j     = 00000004
		// ClassMemberAddress::m_sj    = 012C76EC
		// ClassMemberAddress::m_k     = 00000008
		// ClassMemberAddress::m_sk    = 012C76F0
		// ClassMemberAddress::m_c     = 0000000C
		// ClassMemberAddress::m_n     = 00000010
	}

class BaseNew
{
public:
	int BN1;
};

class Base1 : virtual public BaseNew
{
public:
    int b1;
    virtual void B1Func() { cout << "B1Func" << endl; }
};

class Base2 : virtual public BaseNew
{
public:
    int b2;
    virtual void B2Func() { cout << "B2Func" << endl; }
};

class Child1 : public Base1, public Base2
{
public:    
    int c1;
};

void test_inherit_class_member_layout()
{
	// 虚表		   虚基类表				   虚表		   虚基类表
	// 1c 3e 2e 00 2c 3e 2e 00 00 00 00 00 ec 43 2e 00 bc 3d 2e 00 01 00 00 00 02 00 00 00 03 00 00 00
    Child1 *c1  = new Child1(); 
	c1->b1 = 0;
	c1->b2 = 1;
	c1->c1 = 2;
	c1->BN1 = 3;

    // b2的地址=c1+sizeof(B1)
    Base2 *b2   = c1;

    // 这里delete b2可能会造成崩溃，因为b2的地址并不是之前的首地址
    delete b2;
}

class Grand
{
public:
    int G1;
    int G11;
    virtual ~Grand() {}
};

class Grand2
{
public:
    int G2;
    int G22;
};

class Parent1 : virtual public Grand//, virtual public Grand2
{
public:
    int P1;
};

class Parent2: virtual public Grand
{
public:
    int P2;
};

class Child3: public Parent1, public Parent2
{
public:
    int C3;
	static int s_Age;
};

int Child3::s_Age = -1;

void test_virtual_base_table()
{
//    Parent1 p1;
//    p1.G1 = 0;
//    p1.P1 = 1;
//
    Child3 c3;
    c3.G1 = 0;
    c3.G11 = 11;
    c3.P1 = 1;
    c3.P2 = 2;
    c3.C3 = 3;
    // c3.G2 = 4;
    
    // c3 --> vbptr --> vftable
    // vftable中包含两类，0-3字节表示当前虚表的位置距离当前对象首地址的距离
    // 4-7字节表示父类中继承成员变量的偏移地址，虚继承时父类们所继承的公共成员变量
    // 是追加在子类的最后面
    // vftable的里面的数据大小，是根据爷爷类中里面的成员多少决定的

    // 当虚继承遇到虚函数时，虚表指针还是位于首地址的前4个字节，紧接着就是虚基表指针位置
    // 此时虚基表的前四个字节就会为0xfffffffc(-4)，距离首地址的偏移地址为-4

}

void test_call_member()
{
	Child3::s_Age = 0;

	Child3 c3;
	c3.s_Age = 1;
	
	Child3 *pc3 = new Child3();
	pc3->s_Age = 2;
}

void Func(int Child3::*mempoint, Child3 &C3)
{
    C3.*mempoint = 100; 
}

class Class7
{
public:
    Class7() {
        m_a = 0;
        m_b = 0;
        m_c = 0;
        m_d = 0;
    }

    virtual void VirFunc() {}

    int m_a;
    int m_b;
    int m_c;
    int m_d;
};

void test_member_point()
{
    printf("&Class7::m_a:%x\n", &Class7::m_a);
    printf("&Class7::m_b:%x\n", &Class7::m_b);
    printf("&Class7::m_c:%x\n", &Class7::m_c);
    printf("&Class7::m_d:%x\n", &Class7::m_d);
    // &Class7::m_a:4
    // &Class7::m_b:8
    // &Class7::m_c:c
    // &Class7::m_d:10

	// 用法
    int Class7::*cpoint = &Class7::m_a;
    Class7 c7;
    c7.*cpoint = 1; 
    // *(&c7+cpoint) = 1;


    int Child3::*cpoint3 = &Child3::C3;

    Child3 c3;
    Func(cpoint3, c3);

    int Child3::*mempoint = 0;

    // mempoint = nullptr;

    if (0 == mempoint) {
        int i = 0;
        cout << "eqaul" << endl; 
    } else {
        cout << "not eqaul" << endl; 
    }

}

extern float x;

class Point3D
{
private:
    float x, y, z;	
public:
    Point3D(float, float, float);
    
    float X() { return x; }
    void X(float new_x) { x = new_x; }
};

class Base
{
public:
    int m_base_a;
    int m_base_b;
    virtual ~Base() {}
};

class Base3
{
public:
    int m_base3_a;
    int m_base3_b;
};

class Child : public Base, public Base3
{
public:
    int m_a;
    int m_b;
    int m_c;
    int m_d;
    int m_e;
};



void test_member_layout()
{
    Child child;

    printf("vptr = 0x%p\n", (long *)&child);
    printf("m_base_a = 0x%p\n", &child.m_base_a);
    printf("m_basse_b = 0x%p\n", &child.m_base_b);
    printf("m_base3_a = 0x%p\n", &child.m_base3_a);
    printf("m_basse3_b = 0x%p\n", &child.m_base3_b);
    printf("m_a = 0x%p\n", &child.m_a);
    printf("m_b = 0x%p\n", &child.m_b);
    printf("m_c = 0x%p\n", &child.m_c);
    printf("m_d = 0x%p\n", &child.m_d);
    printf("m_e = 0x%p\n", &child.m_e);


 
}


class Child4
{
public:
    int m1;
    int m2;
    int m3;
    int m4;
};

void test_member_initialize()
{
	
    Child4 *c5 = new Child4();
    c5->m1 = 0;
    c5->m2 = 1;
    c5->m3 = 2;
    c5->m4 = 3;
	
    Child4 c4;
    c4.m1 = 0;
    c4.m2 = 1;
    c4.m3 = 2;
    c4.m4 = 3;

}

class Base6
{
public:
    int m_base6_a;
    virtual ~Base6() {}
    static int s_base6_b;
};
int Base6::s_base6_b = 0;

class Base4 : virtual public Base6
{
public:
    int m_base4_a;
    int m_base4_b;
    static int s_base4_c;
    virtual ~Base4() {}
};
int Base4::s_base4_c = 0;

class Base5 : virtual public Base6
{
public:
    int m_base5_a;
    int m_base5_b;
    static int s_base5_c;
    virtual ~Base5() {}
};
int Base5::s_base5_c = 0;

class Child5 : public Base4, public Base5
{
public:
    int m_a;
    int m_b;
    int m_c;
    int m_d;
    int m_e;
};

void test_member_effective()
{
    Child5::s_base6_b = 10;
    Child5::s_base4_c = 1;
    Child5::s_base5_c = 2;

    Child5 c5;
    c5.m_a = 3;
    c5.m_base4_a = 4;
    c5.m_base5_a = 5;
    c5.m_base6_a = 6;
}


};

#endif // virtual_fun_table_h
