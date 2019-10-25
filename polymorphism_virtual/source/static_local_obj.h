/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef static_local_obj_h 
#define static_local_obj_h

#include <Windows.h>

#include <iostream>
#include <thread>

using std::cout; 
using std::endl;
using std::thread;

namespace static_local_obj
{
class Obj
{
public:
    Obj() { ++number; }

    int number = 0;
};

void static_local_obj()
{
    static Obj obj;

    cout << obj.number << endl; 
}

void test_static_local_obj()
{
//    for (;;) {
//        Sleep(5000);
//        for (int i = 0; i < 10; ++i) {
//            thread t1(static_local_obj);
//            t1.detach();
//        }
//    }

	static_local_obj();
}

}

#endif // virtual_fun_table_h
