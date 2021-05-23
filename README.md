<h1>对C++对象模型探究的学习代码 <h1>
polymorphism_virtual 

    build_linux 
        Makefile 
    build_vs2013 
        polymorphism_virtual.sln 
        polymorphism_virtual.vcxproj 
        polymorphism_virtual.vcxproj.filters 
    source 
        // 测试this指针调整 
        analysis_adjust_this.h 
        // 测试编译器的优化 
        compiler_optimization.h 
        // 测试编译器在什么情况下会合成默认的构造函数 
        default_constructor.cpp 
        main.cpp 
        // 在vs下使用dumpbin 查看coff文件 
        objanalyze.h 
        // 测试影响对象的大小因素 
        objsize.h
        // 使用工具分析虚函数
        analysis_virtual_by_tools.cpp
        // 数据语义
        data_semantics.h
        // 函数语义
        function_semantic.h
        // 初始化列表
        initialization_list.h
        // 数据成员布局
        member_layout.cpp
        // 虚函数探讨
        virtual_fun_table.h
    README.md
**test submodule**
**1.0 version**
