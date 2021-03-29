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
    // 局部对象
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

// 这段代码我是在ubuntu 14.04 GCC 4.8.4 
// 要开启选项 -fno-elide-constructors
ConvertObj test_ret_obj()
{
    ConvertObj obj;

    return obj;
	
	// ConvertObj ctor
	// ConvertObj copy ctor
	// mNum:0 ~ConvertObj dtor
	// mNum:0 ~ConvertObj dtor


    // 开启优化选项
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

// 如果没有下面重载test函数，你在调用test函数传递的参数是char *参数
// 这时就会构造一个临时对象，先是通过string的构造函数将char *参数
// 转换为string类型，再传递进去。重载test函数之后，就会省去一个临时对象
// 的构造
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

