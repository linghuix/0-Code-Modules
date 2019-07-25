
## C语言组织结构

###  头文件

* 全局变量声明

    > 一般来说，不会将全局变量的定义写在头文件中，因为如果多个c源文件都添加了头文件，那很容易引起重定义的问题，这时候一般编译器都会提示。
    > 正确的作法是在c源文件中定义一个全局变量。在头文件中加入全局变量的声明。比如
    
    ```C
    //var.c 一个主要用于定义全局变量的c源文件
    int g_a;
    char g_x;
    ```
     
     ```C
    //var.h 用于声明定义的全局变量
    extern int  g_a;
    extern char g_x; 
    ```
     
    ```C
    //test.c 一个用于测试的头文件
    #include <var.h>
    void f(){
        g_a = 1;
        g_x = 'x';
    }
    ```
    
* 宏定义

    * 用于简单的函数定义
    
    * 用于选择功能

* 函数声明

