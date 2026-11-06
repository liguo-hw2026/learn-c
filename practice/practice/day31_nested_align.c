/*
 * day31_nested_align.c —— 第 5 周 第 4 天（结构体嵌套对齐与位域，3.2h）
 * 计划源知识点（outputs/李果_硬件转型48周_半量慢速计划.md 第5周第4天 line 318–322）：
 *   部分架构不对齐直接报错、结构体嵌套时的对齐、位域(bit-field)
 * 资源：📺 结构体内存对齐专讲（B站「大厂笔试题精讲之结构体内存对齐」）<https://www.bilibili.com/video/BV1ay4y1t7V7>
 *      ｜ 📄 图文备份「一文轻松理解内存对齐」<https://www.bilibili.com/read/cv6036664> ・「内存对齐精讲」<https://www.bilibili.com/read/cv18382318>
 *      ｜ 📄 D2「offsetof / alignof」<https://en.cppreference.com/w/c/types/offsetof>
 * 硬件相关性：🟢 极高——位域常用于寄存器位定义；嵌套结构体对齐直接影响硬件寄存器组布局正确性。
 * 衔接 day30：day30 讲单层结构体内存对齐（成员自身对齐 / 整体按最大成员对齐 / pack），day31 进阶两件事：
 *   ① 嵌套结构体——内层结构体按其【内部最大对齐成员】对齐，不是按它的整体 sizeof；
 *   ② 位域——把多个布尔/小整数压进一个机器字，省空间（也埋下跨平台不确定性）。
 * ⚠️ 本日同为 V2 日（无翁恺 P 号）。
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
//   1) 看对齐视频（day30 同款）+ 文档，理解：嵌套结构体按其【内部最大对齐成员】对齐（非整体 sizeof）、位域语法与省空间原理
//   2) 定义 Inner { char a; int b; }（对齐4，sizeof=8），定义 Outer { char x; Inner y; char z; }，预测 Outer 布局
//   3) 用 offsetof 验证 Outer 中 y 的偏移是否 = 4（而非 8）
//   4) 定义位域 struct Flags { unsigned int ready:1; unsigned int error:1; unsigned int mode:2; }，预测 sizeof(Flags)=4
//   5) 自测（口述）：位域为什么不能对其成员取地址？跨平台（MSVC vs GCC）用位域定义寄存器有什么坑？
// 【预测】（实现前填，写在对应代码行尾）
//   - Outer 中 y 的偏移我猜：____（4，按 Inner 内部最大对齐 4，不按 sizeof 8）
//   - Outer 的 sizeof 我猜：____（16）
//   - Flags 的 sizeof 我猜：____（4，4 个 bit 挤在一个 unsigned int 里）
// 【完成标准】① 能手算嵌套结构体布局；② 会用 offsetof 验证嵌套对齐；③ 理解位域省空间机制与跨平台不确定性；④ 自测能答出位域的坑
// 【参考代码】（#pragma region 折叠 + 注释，自己写完后对照）

#pragma region day31 参考代码（自己写完后对照，勿直接解注当作业交）
/*
typedef struct { char a; int b; } Inner;            // 对齐4, sizeof=8
typedef struct { char x; Inner y; char z; } Outer;  // x@0, y@4(按Inner内部最大对齐4), z@12, 整体对齐4 → sizeof=16

struct Flags { unsigned int ready:1; unsigned int error:1; unsigned int mode:2; };

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    printf("Outer sizeof=%zu  x@%zu y@%zu z@%zu\n",
           sizeof(Outer), offsetof(Outer,x), offsetof(Outer,y), offsetof(Outer,z));
    printf("Flags sizeof=%zu\n", sizeof(struct Flags));
    return 0;
}
*/
#pragma endregion

// ============ 你的实现区（手敲；参考代码在上方折叠区）============
typedef struct { char a; int b; } Inner;
typedef struct { char x; Inner y; char z; } Outer;

struct Flags { unsigned int ready:1; unsigned int error:1; unsigned int mode:2; };

// TODO：实现 show_nested，打印 Outer 的 sizeof 与各成员 offsetof，验证 y 的偏移是否 = 4
void show_nested(void) {
    // printf("Outer sizeof=%zu  x@%zu y@%zu z@%zu\n", sizeof(Outer), offsetof(Outer,x), offsetof(Outer,y), offsetof(Outer,z));
    // printf("Flags sizeof=%zu\n", sizeof(struct Flags));
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    printf("outer.x=%zu,outer.y=%zu,outer.z=%zu\n", offsetof(Outer, x), offsetof(Outer, y), offsetof(Outer, z));//预测 x@0 y@4 z@12
    printf("sizeof(Outer)=%zu\n", sizeof(Outer));//预测4（补3）+8+4（补3）=16
    printf("sizeof(Flags)=%zu\n", sizeof(struct Flags));//预测4 sizeof由类型int大小决定
    // TODO ①：用 offsetof 打印 Outer 三个成员偏移，预测 y@4（Inner 的对齐是 4，不是其 sizeof 8）
    // TODO ②：打印 sizeof(Outer)（预测16）与 sizeof(struct Flags)（预测4）
    // TODO ③：自测口述 — 位域为何不能对其成员取地址？地址是按字节取的 位没有地址可取 
    // MSVC 与 GCC 位域打包顺序不同意味着什么？这个还没学 我的理解是 MSVC和GCC位域打包顺序不一样 跨平台后 成员位置就乱了
    //show_nested();
    return 0;
}
