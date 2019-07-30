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
	virtual ~Base3() {}
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
    // c3.G2 = 4;
    
    // c3 --> vbptr --> vftable
    // vftable中包含两类，0-3字节表示当前虚表的位置距离当前对象首地址的距离
    // 4-7字节表示父类中继承成员变量的偏移地址，虚继承时父类们所继承的公共成员变量
    // 是追加在子类的最后面
    // vftable的里面的数据大小，是根据爷爷类中里面的成员多少决定的

    // 当虚继承遇到虚函数时，虚表指针还是位于首地址的前4个字节，紧接着就是虚基表指针位置
    // 此时虚基表的前四个字节就会为0xfffffffc(-4)，距离首地址的偏移地址为-4

}

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
    // 其实被编译器转成__ZN6NormalCall6AddEi(&nc, 1)
    // 编译器在调用类的普通成员函数时，会在函数的参数中隐式添加了一个this指针，这个指针
    // 就是当前生成对象的首地址。同时对普通成员变量的存取也是通过this指针

    Add(&nc, 1);     // 调用全局函数

    // 打印出类成员函数的地址
    printf("Normal Add address:%p\n", &NormalCall::Add);
}


int main()
{
	return 0;
}
