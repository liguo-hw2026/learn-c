/*
 * day18 内存错误专题：泄漏 / 野指针 / 悬空 / 越界（第 4 周 第 2 天）
 * ---------------------------------------------------------------------------
 * 资源（计划原文）：
 *   📺 V2 小甲鱼《带你学 C 带你飞》内存相关章节  https://www.bilibili.com/video/BV17s411N78s
 *   📄 D1「C 内存管理」
 * ⚠️ 计划↔视频冲突说明：本日四大内存错误 + 返回局部变量地址，翁恺 V1 无专讲，
 *   计划指定的资源是「小甲鱼 V2」而非翁恺 P，属于计划内部一致安排，无冲突。
 *   自测原定「修上一周成绩管理系统 ≥2 处隐患」，但本仓库尚未建该项目，
 *   故自测改为「附录：一段有隐患的示例代码，找出 ≥2 处并修复」（见文件尾）。
 *
 * TODO ↔ 知识点对照（均以小甲鱼 V2 内存章节为锚，无翁恺 P 号）：
 *   TODO1  内存泄漏（leak）            —— 分配后不 free，malloc 计数 > free 计数
 *   TODO2  野指针（wild/uninit）       —— 未初始化的指针直接解引用
 *   TODO3  悬空·返回局部变量地址        —— 函数 return &局部变量，调用者拿到悬空指针
 *   TODO4  悬空·free 后继续使用        —— free 后指针仍被读写
 *   TODO5  越界（out-of-bounds）       —— 写超出分配边界，踩坏相邻内存
 *   自测   找隐患并修复（附录示例）
 *
 * 格式约定（2026-10 定）：
 *   【任务】【预测】平铺可见、不折叠；【参考代码】用 #pragma region 折叠，置于 /* *\/ 内防误编译。
 * 自己敲代码跑，不要只看参考。
 */

#include <stdio.h>
#include <stdlib.h>

/* 泄漏计数器：全局，便于 TODO 内自增对比 */
static int cnt_malloc = 0;
static int cnt_free = 0;

int main(void)
{
    /* ===================== TODO1 内存泄漏 ===================== */
    /* 【任务】
     * 写一个程序：用 malloc 分配一个含 5 个 int 的数组，但不调用 free。
     * 用上面两个计数器 cnt_malloc / cnt_free 分别记录「分配次数」和「释放次数」，
     * 打印「泄漏块数 = cnt_malloc - cnt_free」。
     * 然后写正确版：在同一个位置补上 free，再打印一次泄漏块数。
     * 预期两版输出分别显示泄漏 1 块 与 泄漏 0 块。
     */
    /* 【预测】
     * 不 free 版：cnt_malloc=1, cnt_free=0 → 泄漏 1 块；
     * 正确版：cnt_malloc=1, cnt_free=1 → 泄漏 0 块。
     * 这是你 day17 就在用的「malloc 计数 == free 计数」自查法的实战。
     */
    #pragma region TODO1 参考代码
    /*
    {
        int *a = (int*)malloc(5 * sizeof(int));
        cnt_malloc++;
        // 注意：这里故意不 free → 泄漏
        printf("[泄漏版] 分配=%d 释放=%d 泄漏=%d\n",
               cnt_malloc, cnt_free, cnt_malloc - cnt_free);

        int *b = (int*)malloc(5 * sizeof(int));
        cnt_malloc++;
        free(b);
        cnt_free++;
        printf("[修复版] 分配=%d 释放=%d 泄漏=%d\n",
               cnt_malloc, cnt_free, cnt_malloc - cnt_free);
    }
    */
    #pragma endregion

    /* ===================== TODO2 野指针（未初始化） ===================== */
    /* 【任务】
     * 声明 int *p; 但【不要】让它指向任何合法地址（不要 malloc，也不要 = &某变量），
     * 紧接着写 *p = 42; 再 printf("%d\n", *p);
     * 观察程序行为（可能崩溃，也可能打印垃圾值）。
     */
    /* 【预测】
     * p 里是随机垃圾值（一个随机地址），对它解引用 = 访问一个你无权访问的随机内存，
     * 结果不可信：多数情况直接崩溃（段错误 / 访问冲突），少数情况恰好没崩但读到乱码。
     * 这是「未定义行为」的典型——不是「有时对有时错」，是「编译器随便怎么处理都合法」。
     */
    #pragma region TODO2 参考代码
    /*
    {
        int *p;          // 未初始化，p 里是随机地址
        *p = 42;         // 危险：往随机地址写 → 很可能崩溃
        printf("%d\n", *p);
    }
    */
    #pragma endregion

    /* ===================== TODO3 悬空·返回局部变量地址 ===================== */
    /* 【任务】
     * 写函数 int* getptr(void){ int x = 10; return &x; }
     * 在 main 里 int *q = getptr(); 然后 printf("%d\n", *q);
     * 观察输出（可能是 10，也可能是乱码/崩溃）。
     * 再写正确版：改成「调用者提供地址」——main 里定义 int buf; getptr2(&buf) 把值写进 buf；
     * 或函数内 malloc 返回（记得 free）。
     */
    /* 【预测】
     * 返回 &x 后，x 所在栈帧已随函数返回被回收，q 指向的槽随时会被下一次调用覆盖，
     * 所以 *q 可能侥幸还是 10（弹栈不清零），也可能已被覆盖成乱码，甚至崩溃——
     * 这正是 day16 你搞懂的「悬空指针 / 生命周期」的活样例。
     */
    #pragma region TODO3 参考代码
    /*
    int* getptr(void) {
        int x = 10;
        return &x;       // 返回局部变量地址 → 悬空指针（危险）
    }
    void getptr_ok(int *out) {
        *out = 10;       // 调用者提供的地址，安全
    }
    // 用法：
    //   int *q = getptr(); printf("%d\n", *q);   // 危险
    //   int buf; getptr_ok(&buf); printf("%d\n", buf);  // 安全
    */
    #pragma endregion

    /* ===================== TODO4 悬空·free 后继续使用 ===================== */
    /* 【任务】
     * malloc 一个 int，赋值 7，free 它；之后还去 printf("%d\n", *p) 或 *p = 8;
     * 观察现象。对比：free 后立刻 p = NULL; 再 printf("%d\n", *p) 会发生什么。
     */
    /* 【预测】
     * free 后那块内存已归还堆管理器，p 变成悬空指针；再读写是未定义行为，
     * 可能读到旧值（看着"没错"），也可能乱码/崩溃。
     * 若 free 后 p = NULL，再解引用会立刻崩溃（比静默破坏好定位）——这也是 day17 强调「free 后置 NULL」的原因。
     */
    #pragma region TODO4 参考代码
    /*
    {
        int *p = (int*)malloc(sizeof(int));
        cnt_malloc++;
        *p = 7;
        free(p);
        cnt_free++;
        // printf("%d\n", *p);   // 悬空访问，危险
        p = NULL;
        // printf("%d\n", *p);   // free(NULL)后还解引用 → 立刻崩溃，易定位
    }
    */
    #pragma endregion

    /* ===================== TODO5 越界访问 ===================== */
    /* 【任务】
     * malloc 一块能放 4 个 int 的数组 a，写 a[0]..a[3]（合法）；
     * 然后故意写 a[4]、a[5]（越界），再 free(a)。观察程序表现。
     */
    /* 【预测】
     * 越界写踩到了这块堆内存【边界之外】的空间：
     * 要么程序退出时 CRT 报 HEAP CORRUPTION（你 day17 刚见过），
     * 要么静默改坏了相邻内存、制造难以复现的 bug。越界不会"编译报错"，是运行时炸弹。
     */
    #pragma region TODO5 参考代码
    /*
    {
        int *a = (int*)malloc(4 * sizeof(int));
        cnt_malloc++;
        for (int i = 0; i < 4; i++) a[i] = i;
        // a[4] = 99;   // 越界！踩坏相邻堆内存
        // a[5] = 100;  // 越界！同上
        free(a);
        cnt_free++;
    }
    printf("[最终] 分配=%d 释放=%d 泄漏=%d\n",
           cnt_malloc, cnt_free, cnt_malloc - cnt_free);
    */
    #pragma endregion

    return 0;
}

/*
 * ============================ 自测：找隐患并修复 ============================
 * 下面这段「简化成绩管理系统」故意埋了 ≥2 处内存隐患（泄漏 / 悬空 / 越界）。
 * 不要直接运行，先把隐患圈出来、写出修复方案；跑通后再对照。
 *
 * 隐患示例（至少 2 处，等你找全）：
 *   1. read_scores 返回局部数组 s 的地址 → 调用者拿到悬空指针（对应 TODO3）。
 *   2. main 里 p 指向已返回栈帧，随后 free(p) 对「非 malloc 来的指针」free → UB（free 只该配 malloc）。
 *   3. 若改用 malloc 实现 read_scores，却没在 main 里 free → 泄漏。
 *
 * int* read_scores(int n) {
 *     int s[100];
 *     for (int i = 0; i < n; i++) s[i] = i * 10;
 *     return s;            // ← 返回局部数组地址
 * }
 * int main(void) {
 *     int *p = read_scores(5);
 *     free(p);             // ← 对非 malloc 指针 free
 *     return 0;
 * }
 */
