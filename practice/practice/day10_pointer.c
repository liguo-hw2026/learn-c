/*
 * day10_pointer.c - 第 3 周第 1 天 · 指针（上）：取地址 & / 指针变量 / 解引用 * / 类型决定访问宽度
 *                   （翁恺 V1 第 80–81 讲）
 *
 * 骨架格式约定（2026-10-23 起，以后所有骨架统一）：
 *   - 【任务】与【预测】为普通注释，直接平铺可见，不折叠。
 *   - 【参考代码】统一用 #pragma region … #pragma endregion 折叠存放，默认注释掉（防误编译）。
 *     需要时把对应 region 里的星斜杠块解注即可运行。
 *   - VS 折叠：Ctrl+M, Ctrl+M 折叠/展开单个；Ctrl+M, Ctrl+O 折叠全部。
 *   - 方法：先预测后验证（predict-then-verify）。
 *
 * 视频（B站分P，已用 API 核实真实标题 2026-10-23）：
 *   P80 9.1.1 取地址运算：&运算符取得变量的地址
 *   P81 9.1.2 指针：指针变量就是记录地址的变量
 *   https://www.bilibili.com/video/BV1XZ4y1S7e1
 * 参考：菜鸟教程「C 指针」https://www.runoob.com/cprogramming/c-pointers.html
 *
 * TODO 与 分P 对照（已复核：全部落在 P80–81 内，不超纲）：
 *   TODO1  取地址运算 &（取得变量首字节地址）          → P80
 *   TODO2  指针变量 + 解引用 *（通过指针读/改原变量）  → P81
 *   TODO3  类型决定解引用访问宽度（sizeof(*p)）        → P81 延伸
 *
 * 延后项（标红：不在本日，属后续指针章，不要提前钻）：
 *   - p+1 的"地址步长"（= 地址 + sizeof(所指类型)）→ P85 指针运算（第 3 周后续日）
 *   - 指针与数组 / sizeof 退化                       → P83
 *   - 指针与 const                                  → P84
 *   - 动态内存分配                                  → P86
 *   注：计划原文把"指针类型决定步长"写在首日，但严格按分P，步长属 P85；
 *       本日只建立"类型决定解引用宽度"的直觉（宽度与步长同源但不同），p+1 留 P85。
 *
 * 收工自测（能口述）：① & 取得的是变量首字节地址；② 指针变量存的是地址、* 去那个地址取值；
 *      ③ 改 *p 等于改它指向的变量；④ 指针类型决定解引用时读写几个字节（int→4 / double→8 / char→1）。
 *
 * 硬件相关性 极高：
 *   - MCU 外设寄存器就是"特定地址的内存"：
 *       #define GPIOA_ODR (*(volatile uint32_t*)0x4001080C)
 *     这里的 (volatile uint32_t*) 就是"把地址当 uint32_t 指针"，* 解引用一次读/写 4 字节寄存器。
 *   - 类型决定宽度：把 uint32_t* 误当 uint8_t* 解引用会只读 1 字节，搬错寄存器值。
 *   - 调试器内存窗口看地址/字节 → 今天第一次真正派上用场。
 */

#include <stdio.h>

int main(void)
{
    // day10 pointer skeleton ready; 参考代码见各 TODO 的 #pragma region 折叠块。
    // 默认所有练习代码注释掉，main 直接 return 0（无输出属于正常）——解注某个 region 才会打印。
    printf("day10 pointer skeleton ready; uncomment a TODO region to run\n");

    // ===== TODO1 取地址运算 &（P80）=====
    // 【任务】定义 int a=10; double b=3.14; char c='X'; 分别打印 值 + 地址。
    // 【预测】&a、&b、&c 是三个不同的十六进制地址；& 取的是变量首字节地址；
    //         相邻变量地址一般也不连续（编译器按类型对齐排布，int 4 字节对齐、double 8 字节对齐）。
    /*int a = 10;
    double b = 3.14;
    char c = 'X';
    printf("ADa=%p\n", &a);
    printf("ADb=%p\n", &b);
    printf("ADc=%p\n", &c);*/
#pragma region TODO1 参考代码（解注运行）
    /* int a = 10;
     * double b = 3.14;
     * char c = 'X';
     * printf("a=%d  &a=%p\n", a, (void*)&a);
     * printf("b=%f  &b=%p\n", b, (void*)&b);
     * printf("c=%c  &c=%p\n", c, (void*)&c);
     */
#pragma endregion

    // ===== TODO2 指针变量 + 解引用 *（P81）=====
    // 【任务】int a=10; int *p=&a; 打印 p 与 &a（应相等）、*p（应=10）；再 *p=20; 打印 a（应=20）。
    // 【预测】*p 解出来就是 a 的值；改 *p 就是改 a（p 指向 a）。
    /*int a = 10;
    int* p = &a;
    printf("p=%p\n", p);
    printf("&a=%p\n", &a);
    *p = 20;
    printf("a=%d\n", a);*/
#pragma region TODO2 参考代码（解注运行）
    /* int a = 10;
     * int *p = &a;
     * printf("p=%p  &a=%p  *p=%d\n", (void*)p, (void*)&a, *p);
     * *p = 20;
     * printf("after *p=20, a=%d\n", a);   // 预测 20
     */
#pragma endregion

    // ===== TODO3 类型决定解引用访问宽度（P81 延伸）=====
    // 【任务】定义 int *pi=0; double *pd=0; char *pc=0; 打印 sizeof(*pi)、sizeof(*pd)、sizeof(*pc)。
    // 【预测】4 / 8 / 1。含义：指针声明的类型决定"解引用时读写几个字节"。
    int* pi = 0;
    double* pd = 0;
    char* pc = 0;
    printf("sizeof(pi)=%d\n", sizeof(*pi));
    printf("sizeof(pd)=%d\n", sizeof(*pd));
    printf("sizeof(pc)=%d\n", sizeof(*pc));
#pragma region TODO3 参考代码（解注运行）
    /* int *pi = 0;
     * double *pd = 0;
     * char *pc = 0;
     * printf("sizeof(*pi)=%zu  sizeof(*pd)=%zu  sizeof(*pc)=%zu\n",
     *        sizeof(*pi), sizeof(*pd), sizeof(*pc));
     */
#pragma endregion

    return 0;
}
