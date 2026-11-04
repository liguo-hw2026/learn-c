/*
 * day26_memory_layout.c —— 第 4 周 第 6 天（复盘 + 手绘内存布局图 · 上，机动日 1.2h）
 * 计划源知识点：一张图画出【代码段 / 只读数据段 / 已初始化数据段(.data) / BSS / 堆 / 栈 / 内核区】，
 *   并标注：全局变量、static、字符串字面量、malloc、局部变量各自落在哪里
 * 资源：📺 V4 合集第 2 章（电阻串并联/等效变换，30min）https://www.bilibili.com/video/BV1Lb4y1m7vD ｜ 📄 D1 复习
 * ⚠️ 本日无翁恺 P 号（V2 盲区规则已做同主题手动 diff：手绘内存布局为首次出现，与 day23 内存错误专题无重复）
 * 硬件相关性：🟢 极高——嵌入式绕不开"这个变量落在 Flash 还是 RAM"：链接脚本、启动文件、
 *   .data/.bss 的拷贝初始化，全是这张图的工程化版本。面试也爱考。
 *
 * 📌【前置知识补给 · %p 打印地址】（新概念，最小前置）：
 *   printf("%p", (void*)&x) 打印变量 x 的地址（十六进制）。%p 是"打印指针值"的专用格式符，
 *   传参时习惯强转 (void*)——因为 %p 承诺接收 void* 类型。地址数值每次运行可能变（ASLR），
 *   你要看的不是具体数值，而是【谁和谁落在同一个区域、各区域之间的相对位置】。
 *   ⭐ 另一个要点：`char* lit = "abc";` 里 lit（指针变量本身）和它指向的内容（字面量）是两个东西、两个地址。
 */

#define _CRT_SECURE_NO_WARNINGS   // 必须在 include 之前定义，才能压掉 scanf 的 C4996 弃用警告
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>   // 根治中文控制台输出乱码（day23 已落地）
#endif

// ============ 待观察的样本变量（先写预测，再跑！）============
int g_init = 42;            // 已初始化全局变量 → 你预测落在哪个段？
int g_uninit;               // 未初始化全局变量 → 你预测落在哪个段？
static int s_g_init = 7;    // static 全局（已初始化）→ 你预测落在哪个段？
static int s_g_uninit;      // static 全局（未初始化）→ 你预测落在哪个段？

int helper(void) { return 0; }   // 函数本体 → 你预测落在哪个段？

// ============ TODO（平铺，先预测后运行看现象；参考代码在底部折叠区）============
// 【任务】
//   1) 在下方【预测】区逐行写下你预测的落点（先别跑！）
//   2) 补全 main 里的地址打印（用 %p + (void*) 强转；或参考折叠区写法）
//   3) 运行，把打印出的地址按"数值相近的归为一组"分组，每组对号入座到一个段
//   4) 对照预测：哪些猜对了？哪些意外？（重点验证三件事：
//      ① static 局部变量【不在】栈上；② 字符串字面量本体【不在】栈上；
//      ③ lit 的值 vs &lit 的地址是两个不同位置）
//   5) 在纸上手绘内存布局图（从低地址到高地址画 7 个区域，把每个样本变量填进去）
// 【预测】（跑之前逐行填！格式：样本 → 我猜在 X 段）
//   g_init →
//   g_uninit →
//   s_g_init →
//   s_g_uninit →
//   helper（函数）→
//   s_l_init（static 局部·已初始化）→
//   s_l_uninit（static 局部·未初始化）→
//   local（普通局部）→
//   lit 的值（字面量本体）→
//   &lit（指针变量本身）→
//   heap（malloc 返回）→
// 【完成标准】① 预测 vs 实测逐项对照，三个重点各验证到；② 手绘图完成（画完拍照或文字描述给我）
// 【参考代码】（#pragma region 折叠 + 注释，先自己写再对照）
#pragma region day26 参考代码（预测完再对照）
/*
int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    static int s_l_init = 99;    // static 局部（已初始化）
    static int s_l_uninit;       // static 局部（未初始化）
    int local = 5;               // 普通局部变量
    char* lit = "hello day26";   // lit 本身在栈，指向的字面量在只读数据段
    int* heap = (int*)malloc(sizeof(int));
    if (!heap) return 1;
    *heap = 123;

    printf("--- 各样本地址（只看分组，不看具体数值）---\n");
    printf("函数 helper            : %p\n", (void*)helper);
    printf("字面量本体（lit 的值） : %p\n", (void*)lit);
    printf("指针变量本身（&lit）   : %p\n", (void*)&lit);
    printf("g_init   (全局已初始化): %p\n", (void*)&g_init);
    printf("g_uninit (全局未初始化): %p\n", (void*)&g_uninit);
    printf("s_g_init (static全局i): %p\n", (void*)&s_g_init);
    printf("s_g_uninit(static全局u): %p\n", (void*)&s_g_uninit);
    printf("s_l_init (static局部i): %p\n", (void*)&s_l_init);
    printf("s_l_uninit(static局部u): %p\n", (void*)&s_l_uninit);
    printf("local    (普通局部)   : %p\n", (void*)&local);
    printf("heap     (malloc)     : %p\n", (void*)heap);

    free(heap);
    return 0;
}
*/
#pragma endregion

// ============ 你的实现区（解注/照抄折叠区，或自己写）============
int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // TODO：先填【预测】，再在这里补全地址打印并运行

    return 0;
}
