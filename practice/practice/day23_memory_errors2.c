/*
 * day23_memory_errors2.c
 * 第 4 周 第 3 天（内存错误专题·下，原第2周·下）
 * 资源：📺 V2 小甲鱼《带你学 C 带你飞》内存相关章节 https://www.bilibili.com/video/BV17s411N78s
 *       📄 D1「C 内存管理」
 * 翁恺 P 号：无（本日无新增翁恺讲次，由 V2 小甲鱼替代；前序动态内存基础已在第 4 周 第 1 天覆盖）
 *
 * TODO ↔ 分P 对照（本日无翁恺 V1 P 号，故对照写"V2 小甲鱼 / 无 V1 P"）：
 *   TODO1 内存泄漏（malloc 不 free + 计数器自测）   → V2 小甲鱼内存章；无 V1 P
 *   TODO2 野指针（未初始化即解引用）               → V2 小甲鱼内存章；无 V1 P
 *   TODO3 悬空指针（free 后继续用）                → V2 小甲鱼内存章；无 V1 P
 *   TODO4 越界写（覆盖相邻变量）                   → V2 小甲鱼内存章；无 V1 P
 *   TODO5 函数返回堆内存的接口约定（谁申请谁释放） → V2 小甲鱼内存章；无 V1 P
 * ⚠️ 自查脚本 check_push_coverage.py 对"无 V1 P 号"的日直接放行（返回码 0），
 *    本日因此天然不重复第 3 周内容，符合 Plan A 正轨接续。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 泄漏/释放计数器：全局维护，malloc 时 +1、free 时 +1，差值即泄漏块数 */
static int g_malloc_count = 0;
static int g_free_count   = 0;

// ============ TODO1：内存泄漏（谁申请谁释放 + 计数器自测）============
// 【任务】写一个 leak_demo()，内部 malloc 一块 100 字节但不 free；
//   在 main 里调用它 3 次，最后打印 g_malloc_count 与 g_free_count，
//   观察"malloc 次数 > free 次数"即泄漏。
//   思考（硬件）：长期运行的 MCU 固件若每帧都泄漏几字节，几小时后会怎样？
// 【预测】g_malloc_count = 3、g_free_count = 0（差值 3 = 泄漏块数）；程序退出无崩溃（泄漏不立即报错）。
// 【参考代码】
#pragma region TODO1 参考代码（解注运行看现象）
/*
void leak_demo(void) {
    char* p = (char*)malloc(100);   // g_malloc_count++
    if (!p) return;
    strcpy(p, "leak");
    printf("leak_demo: %s (p=%p)\n", p, (void*)p);
    // 故意不 free(p)  → 泄漏
}
*/
#pragma endregion

// ============ TODO2：野指针（未初始化的指针就解引用）============
// 【任务】声明 int* p 但不赋值，直接 *p = 10；解注运行，观察现象
//   （多数环境段错误/崩溃，或写入随机地址——后者更危险，silent corruption）。
// 【预测】程序崩溃（访问未分配地址）；若未崩溃则写入了不可控内存（数据损坏，更隐蔽）。
// 【参考代码】
#pragma region TODO2 参考代码
/*
void wild_demo(void) {
    int* p;          // 未初始化，值是不确定的垃圾地址
    *p = 10;         // 写到随机地址 → UB（崩溃 / 数据损坏）
    printf("%d\n", *p);
}
*/
#pragma endregion

// ============ TODO3：悬空指针（free 后继续用）============
// 【任务】malloc 一块 int，赋值 42，free 掉，再解引用它（读或写）；
//   解注运行，观察现象（free 后那块内存已被回收，再访问是 UB，行为不确定）。
// 【预测】不确定：可能看似正常、可能读到垃圾、也可能崩溃；这是最隐蔽的一类。
// 【参考代码】
#pragma region TODO3 参考代码
/*
void dangling_demo(void) {
    int* p = (int*)malloc(sizeof(int));
    if (!p) return;
    *p = 42;
    printf("before free: *p = %d\n", *p);
    free(p);                 // p 现在悬空
    // *p = 100;             // 解注这一行 → 悬空访问 UB
    // printf("after free: *p = %d\n", *p);
}
*/
#pragma endregion

// ============ TODO4：越界写（覆盖相邻变量）============
// 【任务】定义相邻数组 a[4] 和变量 b=999，向 a 写入第 5、6 个元素（越界），
//   观察 b 的值是否被悄悄改掉（嵌入式里这就是"隔壁变量莫名变化"的元凶）。
// 【预测】a 越界写入会覆盖 b 的内存，打印 b 时看到非预期值（不再是 999）。
// 【参考代码】
#pragma region TODO4 参考代码
/*
void oob_demo(void) {
    int a[4] = {0, 0, 0, 0};
    int b = 999;
    a[4] = 111;      // 越界写，可能落到 b 的位置
    a[5] = 222;
    printf("b = %d (预期 999，越界后可能变了)\n", b);
}
*/
#pragma endregion

// ============ TODO5：函数返回堆内存的正确接口约定 ============
// 【任务】写 make_buffer(size_t n)，内部 malloc(n) 并返回指针；
//   在 main 里调用、使用、然后【由调用方 free】。
//   思考并口头讲清："谁申请谁释放"在跨函数时如何落实？为什么不能让被调用函数
//   既 malloc 又 free 再返回（那样返回的是悬空指针）？
// 【预测】main 中 free 后 g_malloc_count == g_free_count（无泄漏），程序干净退出。
// 【参考代码】
#pragma region TODO5 参考代码
/*
char* make_buffer(size_t n) {
    char* p = (char*)malloc(n);
    if (!p) return NULL;
    g_malloc_count++;
    return p;              // 返回堆指针，由调用方负责 free
}

// 正确的调用方用法（放在 main 里解注）：
//   char* buf = make_buffer(64);
//   if (buf) {
//       strcpy(buf, "hi");
//       printf("buf = %s\n", buf);
//       free(buf);
//       g_free_count++;
//   }
*/
#pragma endregion

int main(void) {
    // 解注上面的 TODO 逐一定位运行（一次跑一个，避免互相干扰）：
    // leak_demo();   wild_demo();   dangling_demo();   oob_demo();
    // make_buffer 的用法见 TODO5 参考代码注释，放进 main 后解注。
    return 0;
}
