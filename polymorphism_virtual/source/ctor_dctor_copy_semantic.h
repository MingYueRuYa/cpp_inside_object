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

int g_number = 0;

class ObjClass
{
public:
    explicit ObjClass() : mCount(g_number++) 
    { 
        // cout << std::hex << this << endl; 
        cout << std::hex << "0x" << this << " ObjClass ctor:" << mCount << endl; 
    }

    ~ObjClass() 
    { 
        // 这里再赋值是为了在内存更明显的观察
        mCount = g_number++;
        cout << std::hex << "0x" <<  this <<" ~ObjClass ctor:" << mCount << endl; 
    }

private:
    int mCount;
};

void test_object_array_ctor_dtor()
{
    // ObjClass objarr[12];
    ObjClass *objarr = new ObjClass[12];
    // 0x001D59CC ObjClass ctor:0
    // 0x001D59D0 ObjClass ctor:1
    // 0x001D59D4 ObjClass ctor:2
    // 0x001D59D8 ObjClass ctor:3
    // 0x001D59DC ObjClass ctor:4
    // 0x001D59E0 ObjClass ctor:5
    // 0x001D59E4 ObjClass ctor:6
    // 0x001D59E8 ObjClass ctor:7
    // 0x001D59EC ObjClass ctor:8
    // 0x001D59F0 ObjClass ctor:9
    // 0x001D59F4 ObjClass ctor:a
    // 0x001D59F8 ObjClass ctor:b  


    delete[] objarr;
    // 0x001D59F8 ~ObjClass ctor:c
    // 0x001D59F4 ~ObjClass ctor:d
    // 0x001D59F0 ~ObjClass ctor:e
    // 0x001D59EC ~ObjClass ctor:f
    // 0x001D59E8 ~ObjClass ctor:10
    // 0x001D59E4 ~ObjClass ctor:11
    // 0x001D59E0 ~ObjClass ctor:12
    // 0x001D59DC ~ObjClass ctor:13
    // 0x001D59D8 ~ObjClass ctor:14
    // 0x001D59D4 ~ObjClass ctor:15
    // 0x001D59D0 ~ObjClass ctor:16
    // 0x001D59CC ~ObjClass ctor:17

    // 对象数组构造伪代码
    char *ptr = reinterpret_cast<char *>(operator new[](0x34));
    char *tempptr = ptr;
    if (tempptr) {
        *(reinterpret_cast<int *>(tempptr)) = 0x0C;
        tempptr += 4;
        for (int i = 0; i < 12; ++i) {
            (*(reinterpret_cast<ObjClass *>(tempptr))).ObjClass::ObjClass();
            tempptr += 4;
        } 
    }

    // 对象数组析构伪代码
    char *delete_ptr = reinterpret_cast<char *>(operator new[](0x34));
    if (delete_ptr) {
        char *tempptr = delete_ptr;
        // 跳过前面保存数组大小的4byte
        tempptr += 4;
        // 移动最后一个对象的位置
        tempptr += 0x30; 
        for (int i = 12; i >= 0; --i) {
            (*(reinterpret_cast<ObjClass *>(tempptr))).ObjClass::~ObjClass();
            tempptr -= 4;
        }
        
        // 注意这里是我们自己的模拟过程，直接这样调用会造成崩溃，毕竟内存模型和真正的
        // operatr new[]是不一样的
        // operator delete[](delete_ptr);
    }
}

void test_new_obj()
{
    ObjClass *obj = new ObjClass();
}

};
