/*
 * day23_memory_errors2.c
 * 第 4 周 第 3 天（内存错误专题·下，原第2周·下）
 *
 * ⚠️ 重要定位（2026-11-03 修正，避免与 day18 重复）：
 *   - day18（第 4 周 第 2 天 = 内存错误专题·上）已经把四类内存错误【逐个隔离讲透】：
 *       泄漏 / 野指针 / 悬空(返回局部变量地址) / 悬空(free 后继续使用) / 越界。
 *   - 本日计划源（第 4 周 第 3 天）的知识点【只有两项新的】：
 *       ① 函数返回堆内存的接口约定（谁申请谁释放）
 *       ② 简单的泄漏自测手法（计数器：malloc 次数 == free 次数）
 *   - 因此本骨架【不再重讲】野指针 / 悬空(free后) / 越界（那些 day18 学过）；
 *     改为：落地上述两项新知识点，并把 day18 的 4 类错误放进一个真实混合 bug
 *     程序里【综合排查（查漏，不是再教一遍）】+ 用新约定重写接口 + 用计数器验证无泄漏。
 *   - 自查脚本 check_push_coverage.py 只比对翁恺 P 号，本日无 P 号 → 无法自动发现
 *     此类"同主题 V2 内容重复"。已补"同主题手动 diff"机制（见打卡防错自查机制.md）。
 *
 * 资源：📺 V2 小甲鱼《带你学 C 带你飞》内存相关章节 BV17s411N78s ｜ 📄 D1「C 内存管理」
 * 翁恺 P 号：无（V2 替代，无新增 V1 P）
 *
 * TODO ↔ 知识点对照（均为本日计划真实新内容 / 或应用 day18 已学）：
 *   TODO1  返回堆内存的接口约定（谁申请谁释放）     → 计划第4周第3天①【新·核心】
 *   TODO2  泄漏自测手法：计数器封装为可复用自检      → 计划第4周第3天②【新·方法论】
 *   TODO3  综合实战：混合 bug 程序查漏 + 用新约定重写 → 应用 day18 已学 + 上面两项新
 *
 * 硬件相关性：🟢 极高。泄漏/野指针/悬空/越界在 MCU 固件里直接 hardfault、数据静默
 *   损坏、长跑后宕机；"谁申请谁释放"是写驱动天天要守的纪律；计数器自检是定位泄漏
 *   的最轻量手法。
 *
 * 格式约定：【任务】【预测】平铺可见不折叠；【参考代码】用 #pragma region 折叠、
 *   置于 /* *\/ 内防误编译。自己敲代码跑，不要只看参考。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 泄漏/释放计数器：全局维护，malloc 时 +1、free 时 +1，差值即泄漏块数。
   day18 已用过同类计数器；本日 TODO2 把它升级为"可复用自检手法"。 */
static int g_malloc_count = 0;
static int g_free_count   = 0;

/* 泄漏自检：打印当前 malloc/free 差额；差为 0 即无泄漏（可放在任意函数退出前调用） */
static void leak_check(const char* tag) {
    int leak = g_malloc_count - g_free_count;
    printf("[泄漏自检 %s] malloc=%d free=%d 泄漏=%d %s\n",
           tag, g_malloc_count, g_free_count, leak,
           leak == 0 ? "(OK)" : "(LEAK!)");
}

// ============ TODO1（新·核心）：函数返回堆内存的接口约定（谁申请谁释放）============
// 【任务】写 make_buffer(size_t n)，内部 malloc(n) 并返回指针；在 main 里调用、使用、
//   然后【由调用方 free】。口头讲清两点：
//     a) 为什么"被调用函数既 malloc 又 free 再 return 指针"是错的？（那样返回的是悬空指针）
//     b) "谁申请谁释放"在跨函数时如何落实？若调用方忘了 free 会怎样？
// 【预测】main 中 free 后 g_malloc_count == g_free_count（无泄漏），程序干净退出。
// 【参考代码】
#pragma region TODO1 参考代码（解注运行看现象）
/*
char* make_buffer(size_t n) {
    char* p = (char*)malloc(n);
    if (!p) return NULL;
    g_malloc_count++;
    return p;                 // 返回堆指针，由【调用方】负责 free
}

// 正确使用（放进 main 解注）：
//   char* buf = make_buffer(64);
//   if (buf) {
//       strcpy(buf, "hi");
//       printf("buf = %s\n", buf);
//       free(buf);
//       g_free_count++;
//   }
//   leak_check("TODO1");      // 应输出 泄漏=0 (OK)

// 反例（体会为什么错）：下面这种"函数内 malloc 又 free 再 return"——
//   char* bad(void){ char* p=malloc(8); free(p); return p; }  // 返回悬空指针！
// 调用方拿到 p 再 free/解引用 → UB（这正是 day18 悬空专题的跨函数版）。
*/
#pragma endregion

// ============ TODO2（新·方法论）：泄漏自测手法（计数器封装为可复用自检）============
// 【任务】day18 你已经用"全局 malloc/free 计数器"发现过泄漏。今天把它【方法化】：
//   上面的 leak_check(tag) 就是一个最小自检工具——任何会动态分配的函数跑完，
//   调用一次 leak_check 即可确认这段逻辑有没有泄漏。
//   思考（硬件）：长期运行的 MCU 固件，可以在"每次主循环末尾"插一句 leak_check，
//   一旦差值 >0 立刻亮灯/打日志，比上线后莫名宕机好定位得多。
// 【预测】单测一个"分配后必 free"的函数，leak_check 应永远报 (OK)；
//   若某路径漏了 free，差值会变正，立刻暴露。
// 【参考代码】
#pragma region TODO2 参考代码（解注运行看现象）
/*
void alloc_ok(void) {                 // 正确：分配即配对 free
    char* p = (char*)malloc(32);
    if (!p) return;
    g_malloc_count++;
    strcpy(p, "tmp");
    printf("alloc_ok: %s\n", p);
    free(p);
    g_free_count++;
}
void alloc_leak(void) {               // 故意漏 free → 制造一次泄漏
    char* p = (char*)malloc(32);
    if (!p) return;
    g_malloc_count++;
    strcpy(p, "leak");
    printf("alloc_leak: %s (忘记 free)\n", p);
    // 没有 free(p) → 泄漏 1 块
}
// main 里：
//   alloc_ok();    leak_check("after alloc_ok");    // OK
//   alloc_leak();  leak_check("after alloc_leak");  // LEAK! 差值=1
*/
#pragma endregion

// ============ TODO3（综合实战·查漏）：混合 bug 程序 + 用新约定重写接口 ============
// 【任务】下面 TODO3 参考代码给了一段"模拟固件"函数 process_packet()，
//   它【故意混合了 day18 学过的 4 类错误各一处】+ 一处"返回局部缓冲区"的错误接口。
//   请先把 4+1 处隐患全部圈出来、写出修复方案，再动手修；修复后用 TODO2 的
//   leak_check 验证 0 泄漏，并把"返回缓冲区"的接口改成 TODO1 的 make_buffer 约定。
//   注意：本题是【应用 day18 已学 + 落地本日两项新知识点】，不是再教你每个错误。
// 【预测】修复前程序可能崩溃/乱码/泄漏；修复后 leak_check 报 (OK)，且函数接口符合
//   "调用方负责 free" 约定。
// 【参考代码】（含 bug 版 + 修复思路注释，解注运行看现象）
#pragma region TODO3 参考代码（解注运行看现象）
/*
// —— bug 版（不要直接跑，先圈隐患）——
char* process_packet_bug(int len) {
    char local_buf[16];              // 隐患1(day18 悬空类)：返回局部数组地址
    int* p;                          // 隐患2(day18 野指针)：未初始化即解引用
    *p = len;
    char* heap = (char*)malloc(len); // 隐患3(day18 泄漏)：malloc 后没 free 就返回
    if (!heap) return NULL;
    heap[0] = 'A';
    heap[len] = 'B';                 // 隐患4(day18 越界)：下标 len 越界（应 len-1）
    strcpy(local_buf, "PKT");
    return local_buf;                // 返回悬空指针 + 漏 free(heap) → 双错
}

// —— 修复版（用本日新约定重写接口 + 消灭 4 类错误）——
char* process_packet_fix(int len) {
    if (len <= 0) return NULL;
    char* heap = make_buffer((size_t)len);   // 新约定：调用方 free
    if (!heap) return NULL;
    heap[0] = 'A';
    heap[len - 1] = 'B';             // 修越界：用 len-1
    // 野指针：所有指针使用前都先赋合法地址（p 已不需要）
    printf("process_packet_fix: heap[0]=%c heap[last]=%c\n", heap[0], heap[len-1]);
    return heap;                     // 返回堆指针，由调用方 free
}
// main 里：
//   char* pkt = process_packet_fix(8);
//   if (pkt) { printf("pkt=%s\n", pkt); free(pkt); g_free_count++; }
//   leak_check("TODO3");             // 应报 (OK)
*/
#pragma endregion

int main(void) {
    // 逐一定位运行（一次跑一个，避免互相干扰）：
    // TODO1: make_buffer 用法（见 TODO1 参考代码，放进 main 解注）
    // TODO2: alloc_ok(); alloc_leak(); 各配 leak_check
    // TODO3: process_packet_fix(8) + free + leak_check
    return 0;
}
