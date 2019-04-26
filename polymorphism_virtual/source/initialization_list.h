/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef initialization_list_h
#define initialization_list_h

#include <iostream>

using std::cout;
using std::endl;

/*
	���Գ�Ա��ʼ���б�
*/

namespace initialization_list
{
class InitialzationA
{
public:
	int m_i;
	InitialzationA(int value = 0) :m_i(value) //����ת�����캯��
	{
		cout << "InitialzationA(int)���캯��������" << endl;
	}

	InitialzationA(const InitialzationA &tmpv)
	{
		cout << "InitialzationA�������캯��������" << endl;
	}

	InitialzationA& operator=(const InitialzationA &tmp)
	{
		cout << "InitialzationA������ֵ�����������" << endl;
		return *this;
	}

	~InitialzationA()
	{
		cout << "InitialzationA��������������" << endl;
	}
};

class InitialzationB
{
public:
	// �����ķѵ���һ��InitialzationA�Ĺ��캯������
//	InitialzationB()
//	{}

	InitialzationB(int value):  m_IA(value), m_a(value), m_b(value)
		/*
			1.������ڳ�Ա�б��ʼ����վ�ڱ������ĽǶȿ�
			m_IA.InitialzationA::InitialzationA(value)
		*/
	{
		/*
			m_IA = value;
			2.������ں����ڲ���ʼ����վ�ڱ������ĽǶȿ�
			A.��������һ����ʱ����
			InitialzationA oc;
			oc.InitialzationA::InitialzationA(value);
			B.��m_IA��copy ctor
			m_IA.InitialzationA::InitialzationA(oc);	
			C.��ʱ������ȥ����
			oc.InitialzationA::~InitialzationA();
			���Գ�Ա������ʼ�������Ч�ʣ���ֻ��������ͱ������Ի���������Ӱ�졣
			�ڳ�ʼ���б��У���Ҫ�����Ա����ȥ��ʼ������һ����Ա����
		*/
	}

private:
	int m_a;
	int m_b;
	InitialzationA m_IA;
};

}

#endif // initialization_list_h