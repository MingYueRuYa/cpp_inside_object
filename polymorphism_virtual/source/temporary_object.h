/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef temporary_object_h
#define temporary_object_h

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

namespace temporary_object
{

class Obj
{
public:
    Obj() { cout << "Obj ctor" << endl; }
    ~Obj() { cout << "~Obj dtor" << endl; }

};

Obj test_local_temporary_object()
{
    // �ֲ�����
    Obj local_obj;  
    return local_obj;
}

class ConvertObj
{
public:
    explicit ConvertObj() { cout << "ConvertObj ctor" << endl; }
    ~ConvertObj() { cout << "mNum:"<< mNum << " ~ConvertObj dtor" << endl; }

    // explicit ConvertObj(int num) 
    ConvertObj(int num) 
    {  
        mNum = num;
        cout << "mNum:" << mNum << "ConvertObj ctor num" << endl; 
    }

    ConvertObj(const ConvertObj &rhs) 
    {   
        mNum = rhs.mNum;
        cout << "ConvertObj copy ctor" << endl; 
    }
	
    int mNum = 0;
};

void ConvertUp(ConvertObj obj)
{
    //TODO something
    // obj.mNum = 2;

}

void ConvertInt(int num)
{
}

// ��δ���������ubuntu 14.04 GCC 4.8.4 
// Ҫ����ѡ�� -fno-elide-constructors
ConvertObj test_ret_obj()
{
    ConvertObj obj;

    return obj;
	
	// ConvertObj ctor
	// ConvertObj copy ctor
	// mNum:0 ~ConvertObj dtor
	// mNum:0 ~ConvertObj dtor


    // �����Ż�ѡ��
    // ConvertObj ctor
    // mNum:0 ~ConvertObj dtor
}

void test_implicit_convert()
{
    ConvertUp(1);
	// mNum:1ConvertObj ctor num
	// mNum:1 ~ConvertObj dtor
}

void test(string str)
{
    //TODO something
}

// ���û����������test���������ڵ���test�������ݵĲ�����char *����
// ��ʱ�ͻṹ��һ����ʱ��������ͨ��string�Ĺ��캯����char *����
// ת��Ϊstring���ͣ��ٴ��ݽ�ȥ������test����֮�󣬾ͻ�ʡȥһ����ʱ����
// �Ĺ���
void test(char *str)
{
    //TODO something
}

void test_full_expression()
{
    Obj objA, objB, objC, objD;
}
};

#endif // temporary_object_h 

