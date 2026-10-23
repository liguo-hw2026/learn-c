/*
 * day11_pointer2.c - 第 3 周第 2 天 · 指针（下）：声明读法 / * 双重含义 / 野指针与 NULL / 指针大小
 *                   （翁恺 V1 第 82 讲 9.1.3 指针的使用）
 *
 * 骨架格式约定（2026-10-23 起，以后所有骨架统一）：
 *   - 【任务】与【预测】为普通注释，直接平铺可见，不折叠。
 *   - 【参考代码】统一用 #pragma region … #pragma endregion 折叠存放，默认注释掉（防误编译）。
 *     需要时把对应 region 里的星斜杠块解注即可运行。
 *   - VS 折叠：Ctrl+M, Ctrl+M 折叠/展开单个；Ctrl+M, Ctrl+O 折叠全部。
 *   - 方法：先预测后验证（predict-then-verify）。
 *
 * 视频（B站分P，已用 API 核实 2026-10-23）：
 *   P82 9.1.3 指针的使用：指针有什么用呢？
 *   https://www.bilibili.com/video/BV1XZ4y1S7e1
 * 参考：菜鸟教程「C 指针」https://www.runoob.com/cprogramming/c-pointers.html
 *
 * TODO 与 分P 对照（已复核：全部落在 P82 内，不超纲）：
 *   TODO1  声明读法 + * 双重含义（int* p,q 只有 p 是指针）        → P82
 *   TODO2  野指针与 NULL（未初始化解引用会崩；NULL 初值+用前判空）→ P82
 *   TODO3  指针的大小（sizeof(int*) / sizeof(char*) / sizeof(double*) 都=8，与类型无关与平台有关）→ P82
 *   TODO4  p+1 差值 recap 自测（重跑 day10 实验，凭直觉解释；完整 p+1 规则归 P85 第3周第4天）→ P82 延伸
 *
 * 延后项（不在本日，属后续指针章）：
 *   - p+1 完整运算（p+i / p-q / 比较 / 数组名是常量指针）→ P85（第3周第4天）
 *   - 指针与数组 / sizeof 退化 → P83   - 指针与 const → P84   - 动态内存 → P86
 *   注：计划原文把"指针类型决定步长"列为首日，但严格按分P 步长属 P85；今天只 recap 直觉（差值=房间数）。
 *
 * 收工自测（能口述）：① int* p,q; 只有 p 是指针，q 是普通 int ② * 在声明时是指针标记、在表达式时是解引用
 *      ③ 野指针解引用会崩、NULL 初值能防（用前 if(p!=NULL) 判空）④ 所有指针变量大小相同、与平台有关（64位=8，32位MCU=4）
 *
 * 硬件相关性 极高：
 *   - 野指针在 MCU = 指向错误/未映射寄存器地址 → 写错硬件或触发 HardFault；读外设寄存器前必须确认地址非空且已映射。
 *   - ⚠️ 32 位 MCU（STM32 等）上 sizeof(指针) = 4，不是 8 —— “指针大小与平台有关”的落地。
 */

#include <stdio.h>

int main(void)
{
    // day11 pointer(下) skeleton ready; 参考代码见各 TODO 的 #pragma region 折叠块。
    // 默认所有练习代码注释掉，main 直接 return 0（无输出属于正常）——解注某个 region 才会打印。
    printf("day11 pointer(下) skeleton ready; uncomment a TODO region to run\n");

    // ===== TODO1 声明读法 + * 双重含义（P82）=====
    // 【任务】写 int* p, q; 然后分别打印 (void*)&p 和 (void*)&q，预测 q 的类型。
    // 【预测】int* p, q; 中只有 p 是“指向 int 的指针”，q 是普通 int（逗号分隔的声明，* 只绑定 p）。
    //         验证：sizeof(p) 应为 8（指针），sizeof(q) 应为 4（int）。
    // 【参考代码】见 region（解注运行）。
#pragma region TODO1 参考代码（解注运行）
    /* int* p, q;
     * printf("sizeof(p)=%zu (指针)  sizeof(q)=%zu (int)\n", sizeof(p), sizeof(q));
     * // 预测：p 的大小 = 8，q 的大小 = 4 —— 证明只有 p 是指针，q 只是 int
     * int x = 7;
     * p = &x;                 // p 指向 x
     * printf("*p=%d\n", *p);  // 表达式里的 * 是“解引用”，取出 x 的值 7
     * // 声明里的 * 与 表达式里的 * 含义不同：前者标记“指针类型”，后者“按地址取值”
     */
#pragma endregion

    // ===== TODO2 野指针与 NULL（P82）=====
    // 【任务】演示未初始化指针的危害，并练习 NULL 初值 + 用前判空。
    // 【预测】int *bad; 未初始化时它等于一个随机地址；解引用 *bad 行为未定义（可能崩）。
    //         把 bad 初始化为 NULL，再用 if (bad != NULL) 保护，就安全。
#pragma region TODO2 参考代码（解注运行）
    /* int *bad;               // 未初始化 = 野指针（指向随机地址）
     * // *bad = 10;          // 危险！写到一个随机地址，可能崩或改坏别的数据——先注释别跑
     * int *safe = NULL;      // 显式置空
     * if (safe != NULL) {    // 用前判空
     *     *safe = 10;
     * } else {
     *     printf("safe 是 NULL，跳过解引用，安全\n");
     * }
     * int real = 5;
     * safe = &real;          // 真正指向一个变量后再用
     * printf("*safe=%d\n", *safe);
     */
#pragma endregion

    // ===== TODO3 指针的大小（P82）=====
    // 【任务】打印 sizeof(int*) / sizeof(char*) / sizeof(double*)，预测三者关系。
    // 【预测】三者相等，都等于 8（64 位平台）；指针大小与“指向谁”无关，只与平台地址总线宽度有关。
    //         （回忆 day10：地址纸条固定 8 字节——今天收尾它。）
#pragma region TODO3 参考代码（解注运行）
    /* printf("sizeof(int*)=%zu\n", sizeof(int*));
     * printf("sizeof(char*)=%zu\n", sizeof(char*));
     * printf("sizeof(double*)=%zu\n", sizeof(double*));
     * // 预测三者都是 8；硬件提醒：32 位 MCU 上会是 4
     */
#pragma endregion

    // ===== TODO4 p+1 差值 recap 自测（P82 延伸；完整规则归 P85）=====
    // 【任务】重跑 day10 的 int/double/char* 的 p+1 地址差值实验，凭直觉解释“为什么 int+1 跨 4、double+1 跨 8”。
    // 【预测】差值 = sizeof(所指类型)：int→4、double→8、char→1。类型的“房间数”决定了步长。
    //         注：p+1 的完整运算规则（p+i、p-q、比较、数组名是常量指针）属 P85，第 3 周第 4 天系统讲，今天只需直觉。
#pragma region TODO4 参考代码（解注运行）
    /* int i = 0; double d = 0; char c = 0;
     * int *pi = &i; double *pd = &d; char *pc = &c;
     * printf("int*    pi=%p  pi+1=%p  差=%td 字节\n", (void*)pi, (void*)(pi+1), (char*)(pi+1)-(char*)pi);
     * printf("double* pd=%p  pd+1=%p  差=%td 字节\n", (void*)pd, (void*)(pd+1), (char*)(pd+1)-(char*)pd);
     * printf("char*   pc=%p  pc+1=%p  差=%td 字节\n", (void*)pc, (void*)(pc+1), (char*)(pc+1)-(char*)pc);
     * // %td 用于打印指针差（ptrdiff_t）；差值应 = sizeof(所指类型) = 4 / 8 / 1
     */
#pragma endregion

    return 0;
}
