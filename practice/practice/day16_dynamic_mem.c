/*
 * day16_dynamic_mem.c - 第 3 周第 7 天 · 动态内存（翁恺 V1 第 86 讲）
 *
 * 视频（B站分P，已用 API 核实 2026-10-28）：
 *   P86 9.2.2 动态内存分配
 *   https://www.bilibili.com/video/BV1XZ4y1S7e1
 *
 * 文档：
 *   D2「动态内存管理」https://zh.cppreference.com/w/c/memory
 *
 * 骨架格式（自 day14 起执行）：
 *   【任务】写完整自洽题面，用户自己敲代码，不必展开参考代码才懂题；
 *   【参考代码】折叠存放仅作兜底，不是题面本身。
 *
 * TODO ↔ 分P 对照（严格落在 P86，不超纲）：
 *   TODO1 malloc 基本用法（分配 + 使用 + free）        → P86
 *   TODO2 malloc 返回值必须判空（失败返回 NULL）        → P86
 *   TODO3 内存布局（堆 / 栈 / 全局区地址观察）           → P86（堆 vs 栈 layout）
 *   TODO4 calloc 会清零 vs malloc 不清零                → P86（calloc 属动态内存分配家族）
 *   TODO5 内存泄漏基础（malloc/free 配对；计数器自查）    → P86（free / 泄漏）
 *
 * 延后项（不在 P86，计划列为第 4 周第 1 天，标延后避免超纲）：
 *   realloc 可能搬移 / free 后必须置 NULL / 双重释放 / sizeof(类型) vs sizeof(*p) 写法
 *   —— 留作第 4 周第 1 天（动态内存·下）专门处理，不占本日。
 *   注：计划「第 7 天 自测」提到的"学生结构体数组"涉及 struct（P96+），不在 P86 范围，
 *       本日不强行上结构体，改用 int 数组 / 计数器落地同等概念。
 *
 * 收工自测（能口述）：
 *   ① 堆和栈分别存什么？malloc 出来的内存在哪、局部变量在哪？
 *   ② 为什么 malloc 返回值必须判空？不判空、分配失败时解引用会怎样？
 *   ③ calloc(n, sz) 与 malloc(n*sz) 最关键的区别是什么（清零）？
 *   ④ free 之后那块内存归谁了？为什么 free 后还指着它（野指针）危险？
 *   ⑤ 怎么判断一段程序有没有内存泄漏？（malloc 次数 == free 次数）
 *
 * 硬件相关性 🟢 极高：
 *   - MCU 堆通常极小（几十 KB 甚至无堆），malloc 失败是常态，必须判空，否则固件 hard fault；
 *   - 嵌入式常避免运行时 malloc（碎片化、不确定性），改用语静态分配或内存池；
 *   - 但"读 datasheet / RTOS 源码 / 堆布局"都建立在本日概念上；
 *   - free 后置 NULL、避免野指针，是固件稳定性的基本功。
 */

#include <stdio.h>
#include <stdlib.h>   /* malloc / calloc / free / NULL */

int main(void)
{
    // ===== TODO1 malloc 基本用法（P86）=====
    // 【任务】用 malloc 分配能装下 n 个 int 的连续内存（n 自己定，如 5），
    //   写入 0..n-1，逐个打印，确认能正常读写，最后 free 掉。
    //   提示：int *p = (int*)malloc(n * sizeof(int));  用完 free(p);
    //   验证：打印出 0 1 2 3 4；free 后这块内存归还给堆（不能再依赖其内容）。
    // 【预测】打印 0..n-1 正常；free 后若再读 p[0] 内容是未定义的（可能还是旧值，也可能变）。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO1 参考代码（解注运行）
    /* int main(void) {
     *     int n = 5;
     *     int *p = (int*)malloc(n * sizeof(int));
     *     if (p == NULL) return 1;            // 防御：分配失败直接退出
     *     for (int i = 0; i < n; i++) p[i] = i;
     *     for (int i = 0; i < n; i++) printf("%d ", p[i]);
     *     printf("\n");
     *     free(p);
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO2 malloc 返回值必须判空（P86）=====
    // 【任务】故意请求一个"几乎不可能成功"的大尺寸（如 malloc((size_t)1 << 40)，即 1TB），
    //   检查返回值是否为 NULL；再设想"如果不判空就直接用"会发生什么。
    //   验证：打印返回值是否为 NULL；写出"不判空 → 解引用 NULL → 崩溃"的结论。
    // 【预测】超大请求返回 NULL；若跳过 if(p==NULL) 直接 p[0]=1，程序崩溃（段错误 / hard fault）。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO2 参考代码（解注运行）
    /* int main(void) {
     *     void *p = malloc((size_t)1 << 40);   // 1 TB，必定失败
     *     if (p == NULL) {
     *         printf("malloc failed (NULL)\n");
     *     } else {
     *         printf("unexpected success\n");
     *         free(p);
     *     }
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO3 内存布局：堆 vs 栈 vs 全局区（P86）=====
    // 【任务】写程序分别打印：① 一个局部变量（在函数内定义）的地址；
    //   ② 一块 malloc 出来的地址；③ 一个全局/静态变量的地址。
    //   观察三者大致落在什么范围、谁高谁低（典型：栈高、堆低、全局居中）。
    //   结论：malloc 的内存在"堆"，局部变量在"栈"，二者不是一回事。
    // 【预测】三者地址各不相同；栈地址通常高于堆地址（x64 Windows/Linux 典型布局）；
    //   全局变量地址与二者都不在同一区。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO3 参考代码（解注运行）
    /* int g = 0;
     * int main(void) {
     *     int local = 0;
     *     int *heap = (int*)malloc(sizeof(int));
     *     if (heap == NULL) return 1;
     *     printf("stack  local : %p\n", (void*)&local);
     *     printf("heap   malloc: %p\n", (void*)heap);
     *     printf("global g     : %p\n", (void*)&g);
     *     free(heap);
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO4 calloc 会清零 vs malloc 不清零（P86）=====
    // 【任务】分别用 calloc 和 malloc 分配一个含 5 个 int 的数组，
    //   打印首元素（或前几个元素）的初始值，对比差异。
    //   验证：calloc 分配后元素全是 0；malloc 分配后元素是随机垃圾（未初始化）。
    // 【预测】calloc 的首元素 == 0；malloc 的首元素可能为非零（取决于堆里残留）。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO4 参考代码（解注运行）
    /* int main(void) {
     *     int *pc = (int*)calloc(5, sizeof(int));
     *     int *pm = (int*)malloc(5 * sizeof(int));
     *     if (!pc || !pm) return 1;
     *     printf("calloc[0]=%d (应 0)\n", pc[0]);
     *     printf("malloc[0]=%d (随机垃圾)\n", pm[0]);
     *     free(pc); free(pm);
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO5 内存泄漏基础：malloc/free 配对（P86）=====
    // 【任务】写一个小程序，用两个计数器 cnt_malloc / cnt_free 统计分配与释放次数；
    //   正常情况每次 malloc 都有对应 free，二者应相等。再故意"漏写一次 free"，
    //   观察计数器是否还相等，体会"泄漏 = 分配了没还"。
    //   验证：配对时 cnt_malloc == cnt_free；漏 free 时 cnt_malloc > cnt_free。
    // 【预测】正常配对计数相等；故意漏 free 则 malloc 计数比 free 多 1（即泄漏了 1 块）。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO5 参考代码（解注运行）
    /* int main(void) {
     *     int cnt_m = 0, cnt_f = 0;
     *     int *a = (int*)malloc(sizeof(int)); cnt_m++;
     *     int *b = (int*)malloc(sizeof(int)); cnt_m++;
     *     free(a); cnt_f++;
     *     // 故意漏 free(b);  ← 制造一次泄漏
     *     printf("malloc=%d free=%d 泄漏%d块\n", cnt_m, cnt_f, cnt_m - cnt_f);
     *     return 0;
     * }
     */
#pragma endregion

    return 0;
}
