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
    ��������ѧ

    ���ж��̳еĹ�ϵ�У�ʹ���ڴ濽�����������ิ�Ƹ�����һ��Ҫע�⣬
    ��Ϊ�������ı���֮����ڴ沼�ֿ����ǲ�һ���ģ�ֱ��ʹ��memcpy�������ܿ���������������
*/
namespace data_semantics
{
	class TestDataAnalyse {

#ifdef test_class_func_parameter
		// һ�㽫�˴��Ĵ������class�Ŀ�ͷ
		typedef int mytype;
#endif

	public:
		int Fun();

		// ���ڳ�Ա�����Ľ������������ǵ�һ������������͵�mytype���͵�ʱ�򱻾�����
		// mytype��һ��������ʱ��Ϳ�����type string mytype
		void CopyValue(mytype value);

	private:
		// ���ж���һ����ȫ�ֱ�������һ�������Ͳ�һ���ı���
		// ��ʱ�����������ܹ�����ʶ��
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
		// ����û������
		// �����������Ա�ĺ������������ڿ���TestDataAnalyse�������֮��ſ�ʼ��
		// �����ڶ�tempvalue�Ľ����Ͱ󶨣���������ඨ�����֮�����ġ�
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
	// ���		   ������				   ���		   ������
	// 1c 3e 2e 00 2c 3e 2e 00 00 00 00 00 ec 43 2e 00 bc 3d 2e 00 01 00 00 00 02 00 00 00 03 00 00 00
    Child1 *c1  = new Child1(); 
	c1->b1 = 0;
	c1->b2 = 1;
	c1->c1 = 2;
	c1->BN1 = 3;

    // b2�ĵ�ַ=c1+sizeof(B1)
    Base2 *b2   = c1;

    // ����delete b2���ܻ���ɱ�������Ϊb2�ĵ�ַ������֮ǰ���׵�ַ
    delete b2;
}

class Grand
{
public:
    int G1;
    int G11;
};

class Grand2
{
public:
    int G2;
    int G22;
};

class Parent1 : virtual public Grand, virtual public Grand2
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
};

void test_virtual_base_table()
{
    Parent1 p1;
    p1.G1 = 0;
    p1.P1 = 1;

    Child3 c3;
    c3.G1 = 0;
    c3.P1 = 1;
    c3.P2 = 2;
    c3.C3 = 3;
    c3.G2 = 4;
    
    // c3 --> vbptr --> vftable
    // vftable�а������࣬0-3�ֽڱ�ʾ��ǰ����λ�þ��뵱ǰ�����׵�ַ�ľ���
    // 4-7�ֽڱ�ʾ�����м̳г�Ա������ƫ�Ƶ�ַ����̳�ʱ���������̳еĹ�����Ա����
    // ��׷��������������
    // vftable����������ݴ�С���Ǹ���үү��������ĳ�Ա���پ�����

    // ����̳������麯��ʱ�����ָ�뻹��λ���׵�ַ��ǰ4���ֽڣ������ž��������ָ��λ��
    // ��ʱ������ǰ�ĸ��ֽھͻ�Ϊ0xfffffffc(-4)�������׵�ַ��ƫ�Ƶ�ַΪ-4

}

void Func(int Child3::*mempoint, Child3 &C3)
{
    C3.*mempoint = 100; 
}

void test_member_point()
{
    int Child3::*cpoint3 = &Child3::C3;
    

    Child3 c3;
    Func(cpoint3, c3);

    int Child3::*mempoint = 0;

    mempoint = nullptr;

}

};

#endif // virtual_fun_table_h
