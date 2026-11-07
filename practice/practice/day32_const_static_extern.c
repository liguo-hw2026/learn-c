/*
 * day32_const_static_extern.c —— 第 5 周 第 5 天（const/static/extern 与作用域、链接属性，3.2h）
 * 计划源知识点（outputs/李果_硬件转型48周_半量慢速计划.md 第5周第5天 line 324–328）：
 *   const 四种位置语义（const int* / int* const / const int* const）、static 修饰局部变量（延长生命周期）
 *   / 全局变量与函数（限制链接域）、作用域 / 存储期 / 链接属性
 * 资源：📺 V1 106–107 讲（全局变量 / 静态本地变量 / 返回指针的函数）<https://www.bilibili.com/video/BV1XZ4y1S7e1?p=106> ・ <https://www.bilibili.com/video/BV1XZ4y1S7e1?p=107>
 *      ｜ V1 111–112 讲（多个源代码文件 / 头文件 / 声明）<https://www.bilibili.com/video/BV1XZ4y1S7e1?p=111> ・ <https://www.bilibili.com/video/BV1XZ4y1S7e1?p=112>
 *      ｜ 📄 D2「cv 限定符」<https://en.cppreference.com/w/c/language/const>（zh 版被墙，用 en；另看 storage_duration 与 linkage 两页）
 * 硬件相关性：🟢 极高——const 表只读寄存器/查表、static 限文件内符号、extern 跨文件共享驱动接口、链接属性决定符号是否跨模块可见，全是嵌入式工程日常。
 * 衔接 day31：day31 讲"数据在内存里怎么摆"（对齐/位域）；day32 进阶"符号本身怎么放、活多久、谁能看见"——作用域/存储期/链接三件套。
 * ⚠️ 本日为翁恺 P 号日（与 day30/31 的 V2 日不同，需看翁恺正课 P106–107、P111–112）。
 *
 * ⭐ 练习日骨架约定（甘 2026-11-05 定）：实现区只放【题目 + 空壳函数】，完整参考放 #pragma region 折叠区（注释防误编译），由你手敲。
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>   // 根治中文控制台输出乱码（day23 已落地）
#endif

// ============ TODO（平铺；先预测后实现，预测写在代码行尾）============
// 【任务】
//   1) 看 V1 106–107、111–112 + 文档，吃透三件事：① const 四种位置语义 ② static 两种修饰 ③ 作用域 / 存储期 / 链接属性
//   2) const 四种位置：在 main 里写 a/b/c/p1/p2/p3（见下方空壳），分别尝试"改值 / 改指向"，预测哪些编译报错
//   3) static 局部变量：实现 counter()，内部 static int n=0; n++; main 调 3 次打印 n，预测输出 1 2 3（而非 1 1 1）
//   4) static 全局/函数：看 day32_helper.c 注释，理解"加 static 就只在本文件可见"（内部链接）
//   5) extern 多文件：day32_helper.c 已定义 int g_shared 与 helper_print()；本文件写 extern 声明并调用，预测打印出 100
//   6) 自测（口述）：volatile 的三个使用场景？（计划列了，正式内容在下一天，先想一想）
// 【预测】（实现前填，写在对应代码行尾）
//   - *p1 = 5（指向 const 的指针改值）→ 编译报错；p1 = &a（改指向）→ 允许
//   - *p2 = 5（const 指针改值）→ 允许；p2 = &c（const 指针改指向）→ 编译报错（与类型无关，是 p2 自身 const）
//   - counter 调 3 次 → 1 2 3
//   - extern 用 day32_helper 的 g_shared → 打印 100
// 【完成标准】① 能手写 const 四种声明并说清"哪个能改" ② 能用 static 局部做出跨调用计数 ③ 理解 extern 跨文件机制 ④ 自测能说出 volatile 三场景
// 【参考代码】（#pragma region 折叠 + 注释，自己写完后对照）

#pragma region day32 参考代码（自己写完后对照，勿直接解注当作业交）
/*
int counter(void) {
    static int n = 0;   // 只初始化一次，跨调用保持
    n++;
    return n;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    const int a = 10;
    int b = 20;
    int c = 30;
    const int* p1 = &b;      // 指向 const int：*p1 不可改，p1 可改
    int* const p2 = &b;      // const 指针：p2 不可改，*p2 可改
    const int* const p3 = &b;

    // *p1 = 5;   // 编译报错：向 const 写
    // p2 = &c;   // 编译报错：const 指针不能改指向
    p1 = &a;      // OK：p1 非 const 指针，且 &a 也是 const int*
    *p2 = 5;      // OK：*p2 非 const，可改 b 的值

    printf("counter: %d %d %d\n", counter(), counter(), counter()); // 1 2 3

    extern int g_shared;
    extern void helper_print(void);
    printf("g_shared=%d\n", g_shared);   // 100
    helper_print();
    return 0;
}
*/
#pragma endregion

// ============ 你的实现区（手敲；参考代码在上方折叠区）============
// TODO ②：const 四种位置声明（空壳，解注后做"改值/改指向"实验）
const int a = 10;//a的值不能改
int b = 20;
int c = 30;
 const int* p1 = &b;//*p1 也就是b不能改
 int* const p2 = &b;//p2 也就是b的地址不能改
 const int* const p3 = &b;//p3 *p3 也就是b的地址和b的值都不能改

// TODO ③：实现 counter——static 局部计数（空壳）
int counter(void) {
     static int n = 0;
     n++;
     return n;
}

// TODO ⑤：extern 声明（定义见 day32_helper.c）（空壳）
 extern int g_shared;
 extern void helper_print(void);

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // TODO ②：分别解注下面两行之一，观察谁报编译错（验证 const 位置语义）
    // *p1 = 5;//和预测一样 还没运行程序直接红线报错 必须是可修改的左值 *p1是const 不能修改
     //p2 = &c; 和预测一样 还没运行程序直接红线报错 必须是可修改的左值 p2是const 不能修改
    p1 = &a;//预测地址a和p的值是一样的
    //printf("adda=%p,addp1=%p\n", &a, p1);和预测一致
    //*p2 = 5;//预测5正常输出
    //printf("*p2=%d\n", *p2);和预测一致

    // TODO ③：调 3 次 counter，预测输出 1 2 3（验证 static 局部跨调用保持）
    // printf("counter: %d %d %d\n", counter(), counter(), counter());//预测1,2,3 这里有问题 输出是3,2,1 是不是说明函数的运行顺序在一行中是从右往左的
    //printf("g_shared=%d\n", g_shared);//helper文件中g_shared改为static静态储存变量 则只在static所在文件中生效 跨文件调用失败 报错LNK200 LNK1120
    //helper_print();
    // TODO ⑤：用 extern 符号（验证跨文件共享）
    // printf("g_shared=%d\n", g_shared);
    // helper_print();
    return 0;
}
