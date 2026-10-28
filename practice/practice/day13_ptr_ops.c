/*
 * day13_ptr_ops.c - 第 3 周第 4 天 · 指针运算
 *                   （翁恺 V1 第 85 讲 9.2.1 指针运算）
 *
 * 骨架格式约定（同 day11/12）：【任务】【预测】平铺不折叠；【参考代码】放 #pragma region
 *   折叠块内、默认包在块注释里防误编译。VS 折叠：Ctrl+M,Ctrl+M 单个、Ctrl+M,Ctrl+O 全部。
 *
 * 视频（B站分P，已用 API 核实 2026-10-26）：
 *   P85 9.2.1 指针运算
 *   https://www.bilibili.com/video/BV1XZ4y1S7e1
 * 参考：菜鸟教程「C 指针的算术运算」
 *   https://www.runoob.com/cprogramming/c-pointer-arithmetic.html
 *
 * ⚠️ 计划-分P 对齐说明（B站 API 实核 2026-10-26）：计划原文第 4 天列的
 *   「a[i] ≡ *(a+i)」「sizeof(a) vs sizeof(p)」两项已在第 3 周第 3 天（day12, P83）做完。
 *   → 今天只做 P85 真实讲授的指针运算：p+n 的步长 / *p++ 优先级 / p-q 相减 / 数组名不可自增。
 *
 * TODO 与 分P 对照（全部落在 P85，不超纲）：
 *   TODO1  p+1 跨多少字节？步长由指针类型决定               → P85
 *   TODO2  *p++ 与 (*p)++：++ 到底作用在 p 还是 *p          → P85（经典优先级）
 *   TODO3  同类型指针相减 p-q：得到元素个数，不是字节差       → P85
 *   TODO4  数组名 vs 指针：p++ 可以，a++ 编译错             → P85（计划「能否++」）
 *
 * 延后项（不在本日）：
 *   - 动态内存分配 malloc/free → P86（计划排第 3 周第 7 天）
 *   - 字符串与指针 → 第 10 章 P87-95（第 3 周第 5-6 天）
 *
 * 收工自测（能口述）：
 *   ① p+1 加的「1」是什么单位？为什么不是 1 个字节？
 *   ② *p++ 先做哪件事、后做哪件事？++ 作用在谁身上？
 *   ③ 同类型指针 p-q 得到什么？如果想要字节差怎么办？
 *   ④ 数组名和指针变量，谁不能 ++？为什么？
 *
 * 硬件相关性 极高：
 *   - 嵌入式直接读写内存映射寄存器就是「指针 + 解引用」：
 *     #define GPIOA_ODR (*(volatile unsigned int*)0x4001080C)
 *   - 数组/缓冲区按类型步长遍历（p+1）是读 FIFO、解析数据帧的日常写法。
 */

#include <stdio.h>

int main(void)
{
    // ===== TODO1 p+1 跨多少字节？步长由类型决定（P85）=====
    // 【任务】定义 int a[3]、double d[3]、char c[3]，用 (char*) 强转测出相邻元素的字节差。
    // 【预测】int 差 4、double 差 8、char 差 1 —— p+1 加的是「1 个元素」，宽度由类型定。
    // 【参考代码】见 region（解注运行）。
   /* int a[3] = { 1,2,3 };
    double d[3] = { 1,2,3 };
    char c[3] = { 1,2,3 };
    printf("int step=%d\n", (char*)(a + 1) - (char* )(a));
    printf("double step=%d\n", (char*)(d + 1) - (char*)(d));
    printf("char step=%d\n", (a + 1) - a);*/
#pragma region TODO1 参考代码（解注运行）
    /* int a[3] = {0};
     * double d[3] = {0};
     * char c[3] = {0};
     * printf("int    step = %lld bytes\n", (long long)((char*)(a + 1) - (char*)a));
     * printf("double step = %lld bytes\n", (long long)((char*)(d + 1) - (char*)d));
     * printf("char   step = %lld bytes\n", (long long)((char*)(c + 1) - (char*)c));
     * // 结论：p+1 = 地址 + sizeof(*p)。指针类型决定「跨一步走多远」。
     */
#pragma endregion

    // ===== TODO2 *p++ 与 (*p)++：++ 作用在谁身上（P85 经典优先级）=====
    // 【任务】先 x = *p++ 打印 x、*p；再把 p 拨回 a，y = (*p)++ 打印 y、a[0]、*p。
    // 【预测】x = 10 且 p 后移到 a[1]（++ 作用在 p 上：先取 *p，p 再自增）；
    //         y = 10（旧值）且 a[0] 变 11、p 不动（++ 作用在 *p 上）。
    // 【参考代码】见 region（解注运行）。
    //int a[2] = { 10,20 };
    //int x = 0;
    //int* p = a;
    //x = *p++;
    //printf("x=%d,*p=%d\n", x, *p);
    //p--;
    //int y = (*p)++;
    //printf("y=%d,a[0]=%d,*p=%d\n", y, a[0], *p);
#pragma region TODO2 参考代码（解注运行）
    /* int a[2] = {10, 20};
     * int *p = a;
     * int x = *p++;
     * printf("x=%d  *p=%d  (p now -> a[1])\n", x, *p);
     * p = a;
     * int y = (*p)++;
     * printf("y=%d  a[0]=%d  *p=%d  (p stays)\n", y, a[0], *p);
     * // 口诀：*p++ = 先用后走；(*p)++ = 先用后加。括号改优先级。
     */
#pragma endregion

    // ===== TODO3 同类型指针相减 p-q：元素个数，不是字节（P85）=====
    // 【任务】int a[5]，p 指向 a[4]、q 指向 a[1]，打印 p-q；再用 (char*) 算字节差对比。
    // 【预测】p-q = 3（元素个数）；字节差 = 12 —— 想要字节得自己乘 sizeof(int) 或强转 char*。
    // 【参考代码】见 region（解注运行）。
   /* int a[5] = { 1,2,3,4,5 };
    int* p = &a[4];
    int* q = &a[1];
    printf("p-q steps=%td\n", p - q);
    printf("p-q=%zu\n", sizeof(int) * (p - q));*/
#pragma region TODO3 参考代码（解注运行）
    /* int a[5] = {0, 1, 2, 3, 4};
     * int *p = &a[4];
     * int *q = &a[1];
     * printf("p - q          = %d (elements)\n", (int)(p - q));
     * printf("(char*)p-(char*)q = %lld (bytes)\n", (long long)((char*)p - (char*)q));
     * // 结论：C 对「指针减指针」的约定是按元素个数算，编译器替你除了 sizeof(int)。
     */
#pragma endregion

    // ===== TODO4 数组名 vs 指针：谁能 ++（P85 / 计划「能否++」）=====
    // 【任务】p++ 先跑通打印 *p；再把标「编译错」的 a++ 解注，看报什么错，然后注释回去。
    // 【预测】p++ 没问题，*p 打 2；a++ 编译错 —— 数组名是「常量指针」，不能改指向。
    // 【参考代码】见 region（解注运行）。
    int a[2] = { 1,2 };
    int* p = a;
    p++;
    printf("*p=%d\n", *p);
 /*   a++;*/
#pragma region TODO4 参考代码（解注运行）
    /* int a[2] = {1, 2};
     * int *p = a;
     * p++;
     * printf("*p = %d\n", *p);
     * // a++;   // 编译错：表达式必须是可修改的左值（数组名不可自增）
     * // 对比 day12：数组名还能 sizeof 出整个数组大小（20），退化成指针后就只剩 8。
     */
#pragma endregion

    return 0;
}
