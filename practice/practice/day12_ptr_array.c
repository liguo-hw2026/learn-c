/*
 * day12_ptr_array.c - 第 3 周第 3 天 · 指针与数组 / 指针与 const
 *                   （翁恺 V1 第 83 讲 9.1.4 指针与数组；第 84 讲 9.1.5 指针与 const）
 *
 * 骨架格式约定（同 day11）：【任务】【预测】平铺不折叠；【参考代码】放 #pragma region
 *   折叠块内、默认包在块注释里防误编译。VS 折叠：Ctrl+M,Ctrl+M 单个、Ctrl+M,Ctrl+O 全部。
 *
 * 视频（B站分P，已用 API 核实 2026-10-23）：
 *   P83 9.1.4 指针与数组：为什么数组传进函数后的 sizeof 不对了
 *   P84 9.1.5 指针与const：指针本身和所指的变量都可能 const
 *   https://www.bilibili.com/video/BV1XZ4y1S7e1
 * 参考：菜鸟教程「C 指针」 https://www.runoob.com/cprogramming/c-pointers.html
 *       菜鸟教程「C 数组」 https://www.runoob.com/cprogramming/c-arrays.html
 *
 * ⚠️ 计划-分P 冲突修正（B站 API 实核 2026-10-23）：计划原文把「指针运算」排在第 3 周第 3 天，
 *   但真实分P：指针与数组=P83、指针与const=P84、指针运算=P85、动态内存=P86。
 *   → 今天只做 P83-84 的内容；指针运算（p+i、p-q、比较的规则化讲解）归第 3 周第 4 天（P85）。
 *
 * TODO 与 分P 对照（全部落在 P83-84，不超纲）：
 *   TODO1  数组名就是首元素地址；a[i] 与 *(a+i) 等价            → P83
 *   TODO2  数组传进函数后 sizeof 为什么「不对了」（退化成指针）   → P83（标题直接实验）
 *   TODO3  用指针遍历数组（下标法与指针法输出应一致）             → P83（应用）
 *   TODO4  指针与 const：const int* 与 int* const 谁不能改       → P84
 *
 * 延后项（不在本日）：
 *   - p+1 完整运算（p+i、p-q、比较的规则化讲解）→ P85（第 3 周第 4 天；TODO3 只凭 day10/11 直觉用）
 *   - 动态内存分配 → P86   - 字符串与指针 → 第 10 章 P87-95
 *
 * 收工自测（能口述）：
 *   ① 数组名 = 首元素地址，a[i] 就是 *(a+i)
 *   ② 数组传参传的只是首地址，函数内 sizeof 拿到的是指针大小（8），不是数组总大小（20）
 *   ③ const int* p：所指不可改、p 可换指向；int* const p：p 不可换指向、所指可改
 *
 * 硬件相关性 极高：
 *   - MCU 固件最常见坑：数组作参数传给函数后 sizeof 退化——想在函数里知道数组长度必须额外传长度参数。
 *   - const 数组（字模表、查找表）会被链接器放进 Flash，省 RAM；const 指针常用于固定的寄存器地址。
 */

#include <stdio.h>

// TODO2 配套函数（P83 标题的直接实验对象）。函数定义必须在 main 外面，这里先放好：
// 平时不调用它不产生任何输出；解注 TODO2 的 region 后它才会被调用。
void print_array_size(int a[])
{
    printf("函数内 sizeof(a)=%zu\n", sizeof(a));   // 预测：8（退化成指针），不是 20
}

int main(void)
{
    printf("day12 ptr_array skeleton ready; uncomment a TODO region to run\n");

    // ===== TODO1 数组名 = 首元素地址；a[i] 等价 *(a+i)（P83）=====
    // 【任务】定义 int a[5]={10,20,30,40,50}; 打印 a、&a[0]、*a，再对比 a[2] 与 *(a+2)。
    // 【预测】a 与 &a[0] 是同一个地址（数组名就是首元素地址）；*a = 10；
    //         a[2] 与 *(a+2) 都等于 30 —— a[i] 和 *(a+i) 是同一件事的两种写法。
    // 【参考代码】见 region（解注运行）。
#pragma region TODO1 参考代码（解注运行）
    /* int a[5] = {10, 20, 30, 40, 50};
     * printf("a     = %p\n", (void*)a);
     * printf("&a[0] = %p\n", (void*)&a[0]);   // 预测：与 a 完全相同
     * printf("*a    = %d\n", *a);             // 预测：10（解引用首元素）
     * printf("a[2]  = %d   *(a+2) = %d\n", a[2], *(a+2));   // 预测：都是 30
     */
#pragma endregion

    // ===== TODO2 数组传参后 sizeof「不对了」（P83 标题直接实验）=====
    // 【任务】main 里打印 sizeof(a)（整个数组的字节数），再调用 print_array_size(a) 看函数内结果。
    // 【预测】main 里 = 20（5 个 int，每个 4 字节）；函数内 = 8 —— 传进函数的其实只是指针！
    // 【参考代码】见 region（解注运行）。
#pragma region TODO2 参考代码（解注运行）
    /* int a[5] = {10, 20, 30, 40, 50};
     * printf("main 里 sizeof(a) = %zu\n", sizeof(a));   // 预测：20
     * print_array_size(a);                              // 预测：函数内打 8
     * // 结论：数组作参数传的只是首地址，函数内 sizeof 拿到的是指针大小。
     * //       所以 C 的惯例是把数组长度作为另一个参数一起传进去。
     */
#pragma endregion

    // ===== TODO3 用指针遍历数组（P83 应用）=====
    // 【任务】用「下标法」和「指针法」各遍历一遍 a，对比两行输出是否一致。
    // 【预测】两行完全一致；p 每自增一次跨一个元素（凭 day10/11 的 p+1 直觉，完整规则归 P85）。
    // 【参考代码】见 region（解注运行）。
#pragma region TODO3 参考代码（解注运行）
    /* int a[5] = {10, 20, 30, 40, 50};
     * int i;
     * int *p;
     * printf("xia biao fa: ");
     * for (i = 0; i < 5; i++) printf("%d ", a[i]);
     * printf("\nzhi zhen fa: ");
     * for (p = a; p < a + 5; p++) printf("%d ", *p);
     * printf("\n两行应完全一致 —— *(a+i) 就是下标访问的本体\n");
     */
#pragma endregion

    // ===== TODO4 指针与 const：谁能改谁不能改（P84）=====
    // 【任务】把标着「编译错」的三行逐个解注，验证 const 修饰的位置决定谁能改。
    // 【预测】const int* p1：*p1 = 99 报错（所指不可改），p1 = &j 没问题（可换指向）；
    //         int* const p2：p2 = &j 报错（p2 本身不可改），*p2 = 88 没问题（所指可改）。
    // 【参考代码】见 region（解注运行）。
#pragma region TODO4 参考代码（解注运行）
    /* int i = 10;
     * int j = 20;
     * const int *p1 = &i;      // 读法：p1 指向「const int」—— 不许通过 p1 改 i 的值
     * // *p1 = 99;            // 编译错：向只读位置赋值（所指不可改）
     * p1 = &j;                 // 没问题：p1 本身可以换指向
     * int *const p2 = &i;      // 读法：p2 是 const 指针 —— p2 本身不许改
     * *p2 = 88;                // 没问题：i 的值可以改（此后 i = 88）
     * // p2 = &j;             // 编译错：向只读变量 p2 赋值（不能换指向）
     * const int *const p3 = &i;   // 双重 const：改哪个都不行
     * // *p3 = 77;            // 编译错
     * // p3 = &j;             // 编译错
     * printf("*p1=%d  *p2=%d  i=%d\n", *p1, *p2, i);   // 预测：20 88 88
     */
#pragma endregion

    return 0;
}
