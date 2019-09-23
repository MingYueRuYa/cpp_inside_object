/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*
	测试：对象的构造、析构、拷贝语意
*/
namespace object_ctor_dtor_copy_semantic
{
// 测试全局和全局静态对象
// #define test_global_static_cotr 1

class Dog
{
public:
    Dog() : mSize(0), mAge(0) {}

    int mSize;
    int mAge;

    virtual void size() {}
};

void test_pod_type()
{
    Dog *dog = new Dog;

    Dog *dog1 = new Dog();
}

class Cat
{
public:
    explicit Cat(const string &name) : mName(name) { cout << mName << endl; }
    ~Cat() { cout << "~" << mName << endl; }

private:
    string mName;
};

#ifdef test_global_static_cotr
// 全局对象
Cat g_Cat("global cat");
// 全局静态对象
Cat g_s_Cat("global static cat");
#endif // test_global_static_cotr

void test_obj_ctor()
{
    // 局部变量
    Cat local_cat("local cat");

    // 局部静态对象
    static Cat local_s_cat("local static cat");

    // global cat
    // global static cat
    // ------------start main------------
    // local cat
    // local static cat
    // ~local cat
    // ------------end main------------
    // ~local static cat
    // ~global static cat
    // ~global cat
}

void test_local_useless(bool find)
{
    Dog dog;
    
    // 返回操作，而这里初始化的dog对象没有任何的作用，平白无故的增加dog的构造函数调用
    if (find) { return; }
	// 应该将对象的初始化延迟到真正需要的时候在初始化
    // 对dog的一系列操作
    // ...
}

class Point
{
public:
    Point() : mX(1), mY(2) { cout << "point" << endl; }
    virtual ~Point() { cout << "~point" << endl; }
protected:
    int mX;
    int mY;
};

class Point3D : public virtual Point
{
public:    
    Point3D() : mZ(3) { cout << "point3d" << endl; }
    virtual ~Point3D() { cout << "~point3d" << endl; }
	virtual void VirFun1() { cout << "~VirFun1" << endl; }
	
protected:
    int mZ;
};

class Vertex : public virtual Point
{
public:
    Vertex() : mAngle(4) { cout << "vertex" << endl; }
    virtual ~Vertex() { cout << "~vertex" << endl; }
	virtual void VirFun2() { cout << "~VirFun2" << endl; }
	
protected:
    int mAngle;

};

class Vertex3D : public Point3D, public Vertex
{
public:
    Vertex3D() { cout << "vertex3D" << endl; }
    virtual ~Vertex3D() { cout << "~vertex3D" << endl; }
	virtual void VirFun3() { cout << "~VirFun3" << endl; }
};

class PVertex : public Vertex3D
{
public:
    PVertex() : mCount(5) { cout << "PVertex3D" << endl; }
    virtual ~PVertex() { cout << "~PVertex3D" << endl; }
	virtual void VirFun4() { cout << "~VirFun4" << endl; }

    void setvalue(int value) { mY = value; }

protected:
    int mCount;
};

void test_virtual_inherit_ctor()
{
    Point point;

    PVertex pvertex;
    // pvertex.PVertex::~PVertex();
    // pvertex.setvalue(10);
    // 露出海面的表象
    // point
    // point3d
    // vertex
    // vertex3D
    // PVertex3D
    // ~PVertex3D
    // ~vertex3D
    // ~vertex
    // ~point3d
    // ~point
}

};
