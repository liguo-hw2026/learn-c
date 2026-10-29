/*
 * day17_dynamic_mem2.c - 第 4 周第 1 天 · 动态内存（下）
 *
 * 视频（计划列为资源，但⚠️ 见下方冲突说明）：
 *   翁恺 V1 第 86 讲《动态内存分配》（malloc/calloc/free 入门）
 *   https://www.bilibili.com/video/BV1XZ4y1S7e1
 *
 * 文档（本日真正主资源）：
 *   D2「动态内存管理」https://zh.cppreference.com/w/c/memory
 *
 * ⚠️ 计划↔视频冲突说明（重要，别被计划误导）：
 *   计划把 P86 列为本日资源，但 P86 实际只讲 malloc/calloc/free 基本用法，
 *   **realloc / free 后置 NULL / 双重释放 / sizeof(*p) 写法** 这四点 P86 都没逐条覆盖。
 *   它们属于「C 内存安全最佳实践」，翁恺 V1 全 129 讲未单讲。
 *   → 本日以 cppreference D2「动态内存管理」为准补实，不强行说"P86 全覆盖"。
 *
 * 骨架格式（自 day14 起执行）：
 *   【任务】写完整自洽题面，用户自己敲代码，不必展开参考代码才懂题；
 *   【预测】写明 predict-then-verify 的预测；
 *   【参考代码】折叠存放仅作兜底（解注运行），不是题面本身；Ctrl+M,Ctrl+M 展开单个。
 *
 * TODO ↔ 资源/分P 对照（本日知识点翁恺 P86 未覆盖，以 cppreference 补实）：
 *   TODO1 realloc 扩容到 2n（含观察搬移）        → cppreference「realloc」（非 P86）
 *   TODO2 free 后必须置 NULL（野指针防护）       → cppreference「free」最佳实践（非 P86）
 *   TODO3 双重释放（free 两次 = UB）             → cppreference「free」（非 P86）
 *   TODO4 sizeof(*p) vs sizeof(类型) 写法习惯    → C 通用惯例（非 P86）
 *   TODO5 综合：扩容到 2n 再释放 + 泄漏自查        → 计划自测（非 P86）
 *
 * 延后项（同知识点变体，按间隔复习原则不堆在今日，留周测/错题本）：
 *   - realloc(p, 0) 等价于 free(p)（返回 NULL 或实现相关）；
 *   - realloc(NULL, size) 等价于 malloc(size)；
 *   - 用 valgrind / ASan 等工具自动检测内存泄漏（PC 端，MCU 无）。
 *
 * 收工自测（能口述）：
 *   ① realloc 在什么情况下会"搬移"内存？为什么必须用它的返回值重新接住指针？
 *   ② free 之后为什么要立刻置 NULL？不置 NULL 的野指针再被使用会怎样？
 *   ③ 什么是"双重释放"？为什么对同一指针 free 两次是未定义行为？怎么避免？
 *   ④ sizeof(类型) 和 sizeof(*p) 哪种写法更安全？为什么？
 *   ⑤ 怎么自查一段程序有没有内存泄漏？（malloc 计数 == free 计数，差值归 0）
 *
 * 硬件相关性 🟢 高（但 MCU 实战常规避运行时 malloc/realloc）：
 *   - free 后置 NULL、避免野指针/双重释放，是固件稳定性的基本功（嵌入式无 OS 兜底，野指针直接 hard fault）；
 *   - 但 tiny MCU（几十 KB RAM）通常避免运行时 malloc/realloc（碎片化/不确定性），改静态分配或内存池；
 *   - 理解 realloc 的"可能搬移"也有助于读懂 RTOS / 第三方库中动态缓冲的实现。
 */

#include <stdio.h>
#include <stdlib.h>   /* malloc / calloc / realloc / free / NULL */

int main(void)
{
    // ===== TODO1 realloc 扩容到 2n（含观察搬移）=====
    // 【任务】先用 malloc 分配 n 个 int（如 4），填入 0..n-1 并打印；
    //   再用 realloc 把容量扩到 2n（如 8），填入剩余元素 n..2n-1，打印全部，确认旧数据没丢；
    //   最后 free 释放。
    //   关键①：realloc 返回值必须重新赋给指针（int* tmp = realloc(p, 2n*sizeof(int)); p = tmp;），
    //           因为 realloc 可能把数据"搬到"新地址，原来的 p 可能就此失效。
    //   关键②：realloc **失败**时返回 NULL，但**原来的 p 依然有效**（没被释放），
    //           所以失败分支要 free(p)，不能用那个 NULL 去解引用。
    //   验证：扩容后前 n 个仍是旧值、后 n 个是新值；最终能正常 free。
    // 【预测】扩容后前 4 个是 0 1 2 3、后 4 个是你填的新值；free 正常不崩。
    //   另观察：realloc 前后 p 的地址"可能变也可能不变"——多数情况会搬（地址变），少数原地扩（不变）。
    // 【参考代码】见下方 region（解注运行）。
    //int n = 4;
    //int *a= (int*)malloc(n * sizeof(int));
    //if (a == NULL)
    //    printf("malloc failed!\n");
    //else {
    //    for (int i = 0; i < n; i++)
    //        a[i] = i;
    //    for (int i = 0; i < n; i++)
    //        printf("p[%d]=%d ", i, a[i]);
    //    printf("\n");
    //}
    //int* t = (int*)realloc(a, 2 * n * sizeof(int));   // ⚠️ realloc 第二参是字节数，必须乘 sizeof(int)（或用 sizeof(*a)）
    //if (t == NULL)
    //    printf("realloc failed!\n");
    //else {
    //    a = t;
    //    for (int i = 0; i < 2*n; i++)
    //        a[i] = i;
    //    for (int i = 0; i < 2*n; i++)
    //        printf("p[%d]=%d ", i, a[i]);
    //    printf("\n");
    //}
    //free(a);
#pragma region TODO1 参考代码（解注运行）
    /* int main(void) {
     *     int n = 4;
     *     int *p = (int*)malloc(n * sizeof(int));
     *     if (p == NULL) return 1;
     *     for (int i = 0; i < n; i++) p[i] = i;
     *     printf("before: ");
     *     for (int i = 0; i < n; i++) printf("%d ", p[i]);
     *     printf("\n");
     *
     *     int *tmp = (int*)realloc(p, 2 * n * sizeof(int));
     *     if (tmp == NULL) { free(p); return 1; }   // 失败：原 p 仍有效，必须 free
     *     p = tmp;                                   // 成功：必须用返回值重新接住
     *
     *     for (int i = n; i < 2 * n; i++) p[i] = i;
     *     printf("after : ");
     *     for (int i = 0; i < 2 * n; i++) printf("%d ", p[i]);
     *     printf("\n");
     *
     *     free(p);
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO2 free 后必须置 NULL（野指针防护）=====
    // 【任务】分配一块内存、用完后 free；接着尝试"再次使用"这块内存（读或写），
    //   体会野指针的危险；正确做法是在 free 之后立刻把指针置为 NULL，
    //   这样后续若再误用可通过 if (p == NULL) 提前跳过，而不是悄悄改坏别的数据。
    //   验证：free 后不置 NULL 而继续写 → 未定义行为（可能静默破坏堆 / 崩溃）；
    //        free 后置 NULL，再用前判空就能安全跳过。
    // 【预测】free 后写 p[0]=1（不置 NULL）→ 未定义行为，可能崩，也可能看似正常但破坏了堆；
    //        free 后 p=NULL，判空分支不执行写入，程序安全。
    // 【参考代码】见下方 region（解注运行）。
   // int* a = (int*)malloc(4*sizeof(int));
   // if (a == NULL)
   //     printf("malloc failed!\n");
   // else
   //     for (int i = 0; i < 4; i++)
   //                 a[i] = i;
   //             for (int i = 0; i < 4; i++)
   //                 printf("a[%d]=%d ", i, a[i]);
   // free(a);
   // printf("\n");
   ///* for (int i = 0; i < 4; i++)
   //     a[i] = i;*///测试可以写 没崩 但可能改了堆中其他数据
   // for (int i = 0; i < 4; i++)
   //     printf("a[%d]=%d ", i, a[i]);//测试释放后直接读 是不可预知的值
#pragma region TODO2 参考代码（解注运行）
    /* int main(void) {
     *     int *p = (int*)malloc(sizeof(int));
     *     if (p == NULL) return 1;
     *     *p = 100;
     *     free(p);
     *     // p 现在指向已归还的内存（野指针）
     *     // *p = 200;   // 危险：未定义行为，可能崩或静默破坏堆
     *     p = NULL;       // 正确：立刻置 NULL
     *     if (p != NULL) *p = 200;   // 判空保护：p 为 NULL 时跳过，安全
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO3 双重释放（free 两次 = UB，用置 NULL 避免）=====
    // 【任务】对同一指针连续 free 两次（free(p); free(p);），观察会发生什么
    //   （通常是崩溃 / 堆损坏——第二次 free 把已归还的块又还一遍，分配器内部状态被破坏）。
    //   正确做法：每次 free 后立即 p = NULL；第二次 free(NULL) 是安全的
    //   （C 标准规定 free(NULL) 啥也不做，无副作用）。
    //   验证：连续 free 两次裸指针 → 程序异常；free 后都置 NULL → 第二次 free(NULL) 安全通过。
    // 【预测】连续两次 free(p) → 大概率崩溃（堆损坏）；free 后都置 NULL，第二次 free(NULL) 安全。
    // 【参考代码】见下方 region（解注运行）。
//int* a = (int*)malloc(4 * sizeof(int));
// if (a == NULL)
//     printf("malloc failed!\n");
// else
//     for (int i = 0; i < 4; i++)
//                 a[i] = i;
//             for (int i = 0; i < 4; i++)
//                 printf("a[%d]=%d ", i, a[i]);
// free(a);
// //free(a);//提示使用未初始化的内存“a”
// a = NULL;
// free(a);//a=NULL后 正常跑通

#pragma region TODO3 参考代码（解注运行）
    /* int main(void) {
     *     int *p = (int*)malloc(sizeof(int));
     *     if (p == NULL) return 1;
     *     free(p);
     *     // free(p);   // 危险：对同一指针再次 free = 双重释放，UB（崩溃/堆损坏）
     *     p = NULL;
     *     free(p);       // 安全：free(NULL) 无副作用
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO4 sizeof(*p) vs sizeof(类型) 写法习惯 =====
    // 【任务】对比动态数组分配的两种写法：
    //   (a) int* p = malloc(n * sizeof(int));     ← 类型写在 sizeof 里
    //   (b) int* p = malloc(n * sizeof(*p));       ← 写 *p，让编译器按 p 指向的类型算
    //   把 p 的类型从 int* 改成 double*，观察哪种"不用改第二处"：
    //   (b) 自动跟着变（sizeof(*p) 变成 sizeof(double)）；
    //   (a) 必须手动把 sizeof(int) 也改成 sizeof(double)，漏改就会分配错误大小。
    //   验证：只改声明类型时，(b) 编译运行都正确；(a) 若漏改 sizeof(int) 会尺寸算错。
    // 【预测】(b) sizeof(*p) 更安全：类型改一处即全局正确；(a) 易漏改导致分配尺寸错误。
    // 【参考代码】见下方 region（解注运行）。
//int n = 4;
//int* a= malloc(n * sizeof(int));
//double* b= malloc(n * sizeof(*b));
//if (a == NULL || b == NULL)
//printf("malloc failed!\n");
//else
//printf("a=%zu,b=%zu\n", sizeof(*a), sizeof(*b));
//free(a);
//free(b);
#pragma region TODO4 参考代码（解注运行）
    /* int main(void) {
     *     int n = 3;
     *     // (a) 类型写在 sizeof 里
     *     int *a = (int*)malloc(n * sizeof(int));
     *     // (b) 写 *p，让编译器按指向类型算（把 b 改成 double* 后，这里自动变 sizeof(double)）
     *     double *b = (double*)malloc(n * sizeof(*b));
     *     if (!a || !b) { free(a); free(b); return 1; }
     *     printf("a 单元=%zu 字节, b 单元=%zu 字节\n", sizeof(*a), sizeof(*b));
     *     free(a); free(b);
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO5 综合（计划自测）：扩容到 2n 再释放 + 泄漏自查 =====
    // 【任务】写一个完整小程序：malloc n 个 int 并填数 → realloc 扩到 2n 并填剩余 →
    //   打印全部 → free（且释放后置 NULL）→ 用 cnt_malloc / cnt_free 两个计数器
    //   自查"分配次数 == 释放次数（差值归 0）"，确认无泄漏。
    //   这是本日自测要求的"扩容到 2n、释放的完整代码"。
    //   提示：realloc 内部已管好旧块，你最终只需 free 最终那个指针一次；计数器只数你自己的 malloc 与最终 free。
    // 【预测】打印出 0..2n-1；cnt_malloc == cnt_free，差值为 0，无泄漏。
    // 【参考代码】见下方 region（解注运行）。
int n = 4;
int cntm = 0;
int cntf = 0;
int* a = (int*)malloc(n * sizeof(int)); cntm++;
if (a == NULL)
    printf("malloc failed!\n");
else {
    for (int i = 0; i < n; i++)
        a[i] = i;
    for (int i = 0; i < n; i++)
        printf("p[%d]=%d ", i, a[i]);
    printf("\n");
}
int* t = (int*)realloc(a, 2 * n * sizeof(int));   // ⚠️ realloc 第二参是字节数，必须乘 sizeof(int)（或用 sizeof(*a)）
if (t == NULL)
    printf("realloc failed!\n");
else {
    a = t;
    for (int i = 0; i < 2*n; i++)
        a[i] = i;
    for (int i = 0; i < 2*n; i++)
        printf("p[%d]=%d ", i, a[i]);
    printf("\n");
}
free(a); cntf++;
if (cntm == cntf)
printf("malloc and free correct!\n");
else
printf("cntm-cntf=%d\n", cntm - cntf);
#pragma region TODO5 参考代码（解注运行）
    /* int main(void) {
     *     int cnt_m = 0, cnt_f = 0;
     *     int n = 4;
     *     int *p = (int*)malloc(n * sizeof(int)); cnt_m++;
     *     if (p == NULL) return 1;
     *     for (int i = 0; i < n; i++) p[i] = i;
     *
     *     int *tmp = (int*)realloc(p, 2 * n * sizeof(int));
     *     if (tmp == NULL) { free(p); cnt_f++; return 1; }   // 失败：free 原块并计数
     *     p = tmp;                                             // 成功：realloc 内部已管好旧块
     *
     *     for (int i = n; i < 2 * n; i++) p[i] = i;
     *     printf("all: ");
     *     for (int i = 0; i < 2 * n; i++) printf("%d ", p[i]);
     *     printf("\n");
     *
     *     free(p); p = NULL; cnt_f++;   // 最终释放 + 置 NULL + 计数（realloc 旧块已由其内部释放）
     *     printf("malloc=%d free=%d 泄漏%d块\n", cnt_m, cnt_f, cnt_m - cnt_f);
     *     return 0;
     * }
     */
#pragma endregion

    return 0;
}
