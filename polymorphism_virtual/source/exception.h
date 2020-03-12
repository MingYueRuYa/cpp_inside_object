/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef exception_h
#define exception_h

#include <exception>
#include <iostream>

using std::cout;
using std::endl;

namespace _test_exception
{

void test_exception()
{
    try {
        int i = 0;
        throw std::out_of_range("out of range");
    } catch(std::exception ex) {
        cout << ex.what() << endl;
    };
}

};

#endif // exception_h
