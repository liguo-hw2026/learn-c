/*
 * day27_stack_heap_growth.c —— 第 4 周 第 7 天（复盘 + 手绘内存布局图 · 下，机动日 1.2h）
 * 计划源知识点：**栈的生长方向与堆的生长方向**（line 287–291）
 * 资源：📺 猫巷故事局《从零开始学电路》EP06「串联、并联到底怎么看？从等效电路到分压分流」（bvid 待补）
 *      ｜ 📺 电力熊猫WP《电路知识点精讲》2-1 电路等效的概念 / 2-2-2 电阻的串联并联 ｜ 📄 D1 复习
 * ⚠️ 本日无翁恺 P 号（机动日）；同主题手动 diff：day26 讲「各段放什么」，本日**只讲往哪长**，不重复
 * 硬件相关性：🟢 极高——MCU 里栈向下、堆向上相向生长，中间那块空隙被吃光就是栈溢出 / 堆破坏，
 *   嵌入式最经典的运行时故障之一；链接脚本里 _estack / heap 边界就是为它划的
 *
 * 📌 前置说明：`%p` 打印地址已在 day26 补给；本日**不用递归**（递归不在翁恺 V1 正式教学内），
 *   改用 f1→f2→f3 三层普通函数调用观察栈，避免引入未学概念（按步骤 3.5 前置缺口扫描）
 */

#define _CRT_SECURE_NO_WARNINGS   // 必须在 include 之前定义，才能压掉 scanf 的 C4996 弃用警告
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>   // 根治中文控制台输出乱码（day23 已落地）
#endif

// ============ TODO（平铺；先预测后运行，预测写在代码行尾）============
// 【任务】
//   1) 盲报热身（不看图、不翻笔记）：对话里给的 5 行代码，报「作用域 / 生存周期 / 存储位置」
//   2) 观察栈：f1→f2→f3 三层调用，各打印自己局部变量的地址，看地址往哪边走
//   3) 观察堆：连续 malloc 4 块，打印地址，看**整体趋势**（不要求严格递增）
//   4) 手绘：把 day26 那张图补上两个箭头（栈朝哪、堆朝哪），标出中间「未使用的空隙」
// 【预测】（跑之前填，写在下面对应代码行尾）
//   - 调用越深，局部变量地址会变大还是变小？ 我猜：____
//   - 连续 malloc，地址整体递增还是递减？     我猜：____
//   - 栈和堆是相向生长还是背向生长？         我猜：____
// 【完成标准】① 两个方向各自实测确认；② 能说清"相向生长、撞上会怎样"；③ 手绘图补完两个箭头
// 【注意】堆地址可能因堆管理器复用/合并块而局部乱序，看趋势即可；若真乱序，那本身就是发现，记下来
// 【参考代码】（#pragma region 折叠 + 注释，先自己写再对照）
#pragma region day27 参考代码（预测完再对照）
/*
void f3(void) {
    int x3 = 3;
    printf("f3  局部变量 &x3 : %p\n", (void*)&x3);
}
void f2(void) {
    int x2 = 2;
    printf("f2  局部变量 &x2 : %p\n", (void*)&x2);
    f3();
}
void f1(void) {
    int x1 = 1;
    printf("f1  局部变量 &x1 : %p\n", (void*)&x1);
    f2();
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    printf("--- 栈：调用越深，地址往哪走？ ---\n");
    f1();

    printf("--- 堆：连续 malloc，地址往哪走？ ---\n");
    int* p[4];
    for (int i = 0; i < 4; i++) {
        p[i] = (int*)malloc(sizeof(int));
        if (!p[i]) return 1;
        printf("第 %d 块 : %p\n", i + 1, (void*)p[i]);
    }
    for (int i = 0; i < 4; i++) free(p[i]);   // 配平，无泄漏
    return 0;
}
*/
#pragma endregion

// ============ 你的实现区（解注/照抄折叠区，或自己写）============
void f3(void);
void f2(void);
void f1(void);

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // TODO：先填【预测】，再补全栈/堆地址打印并运行

    return 0;
}

void f3(void) {
    // TODO
}
void f2(void) {
    // TODO
}
void f1(void) {
    // TODO
}
