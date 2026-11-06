/*
 * day30_align.c —— 第 5 周 第 3 天（内存对齐与 sizeof 手算，3.2h）
 * 计划源知识点（outputs/李果_硬件转型48周_半量慢速计划.md 第5周第3天 line 312–316）：
 *   对齐规则（成员自身对齐 / 整体按最大成员对齐 / #pragma pack(n) 与 __attribute__((packed))）、为什么存在对齐（CPU 访问效率）
 * 资源：📺 V2 结构体对齐相关章节（小甲鱼 BV17s411N78s）｜ 📄 D2「offsetof / alignof」https://zh.cppreference.com/w/c/types/offsetof
 * 硬件相关性：🟢 极高——MCU 上结构体布局直接影响固件内存占用与寄存器映射结构体正确性；
 *   #pragma pack 常用于匹配硬件寄存器布局（避免编译器插入 padding 打乱寄存器偏移）。
 * 衔接 day28：day28 的 Sensor（int+float+int）实测 12 字节无 padding，今天正式讲「为什么会、什么情况下会冒出 padding」。
 * ⚠️ 本日主题 = day28 埋的伏笔（成员顺序/加 char 会冒 padding），day29 是数组/嵌套，day30 才讲对齐本身。
 *
 * ⭐ 甘 2026-11-05 新约定（练习日骨架）：实现区只放【练习题题目 + 空壳函数】，
 *   完整参考代码放 #pragma region 折叠区（注释围起来防误编译），由甘本人手敲实现。
 *   本文件即按此约定：下方"你的实现区"只有 typedef/空壳 + 题目，不要直接解注折叠区当作业交。
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>   // offsetof
#ifdef _WIN32
#include <windows.h>   // 根治中文控制台输出乱码（day23 已落地）
#endif

// ============ TODO（平铺；先预测后实现，预测写在代码行尾）============
// 【任务】
//   1) 看 V2 结构体对齐章节 + D2 offsetof/alignof 文档，理解对齐三规则（成员自身对齐 / 整体按最大成员对齐 / pack 覆盖）
//   2) 定义 struct S1 { char a; int b; char c; }，用 sizeof 打印（预测 12），用 offsetof 打印 a/b/c 偏移（预测 b@4）
//   3) 定义 struct S2 { int b; char a; char c; }，用 sizeof 打印（预测 8），解释与 S1 的差值来源（谁吃掉了 padding）
//   4) 用 #pragma pack(1) 重定义 S1 为 S1p，看 sizeof 变多少（预测 6，padding 被强制抹掉）
//   5) 自测（口述）：为什么需要内存对齐？哪些架构不对齐会直接报错/崩溃（而非只是慢）？
// 【预测】（实现前填，写在对应代码行尾）
//   - S1 的 sizeof 我猜：____（12）
//   - S1 中 b 的偏移我猜：____（4）
//   - #pragma pack(1) 后 S1p 的 sizeof 我猜：____（6，=1+4+1）
// 【完成标准】① 能手算 S1/S2 sizeof 并解释 padding；② 会用 offsetof 验证与预测一致；
//   ③ 理解 pack(n) 的作用与代价；④ 自测能答出「为什么对齐 / 不对齐的风险」
// 【参考代码】（#pragma region 折叠 + 注释，自己写完后对照）

#pragma region day30 参考代码（自己写完后对照，勿直接解注当作业交）
/*
#include <stddef.h>
#pragma pack(push, 1)
typedef struct { char a; int b; char c; } S1p;
#pragma pack(pop)

typedef struct { char a; int b; char c; } S1;
typedef struct { int b; char a; char c; } S2;

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    printf("S1  sizeof=%zu  a@%zu b@%zu c@%zu\n",
           sizeof(S1), offsetof(S1,a), offsetof(S1,b), offsetof(S1,c));
    printf("S2  sizeof=%zu\n", sizeof(S2));
    printf("S1p sizeof=%zu  (pack(1) 抹掉 padding)\n", sizeof(S1p));
    return 0;
}
*/
#pragma endregion

// ============ 你的实现区（手敲；参考代码在上方折叠区）============
typedef struct { char a; int b; char c; } S1;
typedef struct { int b; char a; char c; } S2;

// TODO：实现 show_layout，打印 S1/S2 的 sizeof 与各成员 offsetof（先用上面预测值，跑完再核对）
void show_layout(void) {
    // printf("S1  sizeof=%zu  a@%zu b@%zu c@%zu\n", ...);
    // printf("S2  sizeof=%zu\n", ...);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // TODO ①：用 offsetof 打印 S1 三个成员的偏移，预测 b 在第 4 字节（前 1 字节 char + 3 字节 padding）
    // TODO ②：打印 sizeof(S1) 与 sizeof(S2)，预测 12 与 8，解释 S2 为何比 S1 省 4 字节
    // TODO ③：用 #pragma pack(push,1) ... #pragma pack(pop) 定义 S1p，打印其 sizeof（预测 6）
    show_layout();
    return 0;
}
