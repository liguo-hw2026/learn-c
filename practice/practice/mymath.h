// mymath.h —— 头文件（放函数声明 / 原型）
// 头文件保护（include guard）：防止同一头文件被多个 .c 重复 #include 时，
// 里面的声明被重复展开，导致"重定义"编译错误。
// 约定写法：文件名全大写、点换成下划线，作为唯一宏名。
#ifndef MYMATH_H
#define MYMATH_H

// 函数原型：只声明"长什么样"（返回类型、名字、参数类型），不写实现
int square(int x);

#endif // MYMATH_H
