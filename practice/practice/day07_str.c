/*
 * day07_str.c - 第 2 周第 3 天 · 字符数组与字符串（翁恺 V1 第 87–95 讲）
 *
 * ⚠️ 提示骨架：每题的"参考写法"用 #pragma region 折叠（见各 TODO 末尾）。
 *    VS 折叠：Ctrl+M, Ctrl+M 折叠/展开单个；Ctrl+M, Ctrl+O 折叠全部。
 * 方法：先预测后验证（predict-then-verify）。
 *
 * 📺 视频（B站分P，已用 API 核实真实标题）：
 *    P87 字符串 / P88 字符串变量 / P89 字符串输入输出 / P90 字符串数组
 *    P91 单字符输入输出 / P92 字符串函数 strlen / P93 字符串函数 strcmp
 *    P94 字符串函数 strcpy / P95 字符串搜索函数
 *    https://www.bilibili.com/video/BV1XZ4y1S7e1
 * 📄 参考：D1「C 字符串 / C 输入输出」
 *
 * ✅ TODO ↔ 分P 对照（已复核：本骨架 5 条全部落在 P87–95 内）：
 *   TODO1  字符数组 vs 字符串（'\0' 结尾）                   → P87
 *   TODO2  字符串输入输出：scanf("%s") 遇空格即停 + 宽度保护  → P89
 *   TODO3  字符串数组（char *a[] / char a[][10]）            → P90
 *   TODO4  my_strlen（遍历到 '\0'），对比库 strlen           → P92
 *   TODO5  统计字符串中数字字符个数 count_digit              → 综合（计划自测题）
 *
 * ⚠️ 延后项（不在 P87–95，今日不做）：
 *   ① 数组作函数参数的 sizeof 退化 → 属 指针章 P80–86（第 3 周）
 *   ② gets / fgets 行输入          → 属 文件 P114–116
 *   注：48 周计划把 ① 列在本日，但翁恺视频不在本日范围；
 *       按"以分P标题为准"的约定移出，避免超纲。
 *
 * 收工自测（能口述）：① 为什么字符串必须以 '\0' 结尾；
 *      ② scanf("%s") 读入字符串有什么风险、怎么用宽度保护；
 *      ③ 字符串数组 char *a[] 与二维字符数组 char a[][10] 有什么不同。
 *
 * 🔧 硬件相关性：
 *   - '\0' 结尾与缓冲区边界 🟢 高相关：读串口/网络帧、定长缓冲必须边界检查，
 *     越界 = 缓冲区溢出 = 嵌入式头号崩溃/安全隐患
 *   - 定长读入 + 宽度保护 🟢 高相关：串口命令行 / AT 指令解析必踩点
 *   - 字符串表（char *a[]）🟢 高相关：AT 指令表、菜单项、日志级别名——嵌入式常见
 *   - 字符串处理 🟡 通用素养：配置解析 / 日志
 *
 * 说明：本文件顶部已提供 my_strlen / count_digit 两个工具函数（文件作用域，可直接调用）。
 *      第 2 周第 4 天（函数·上）你将从头自己写函数；今天先"调用 + 观察 + 预测"。
 */

#include <stdio.h>
#include <string.h>

/* ===== 本日提供的工具函数（第 2 周第 4 天 你将自己从头写函数，今天先调用观察） ===== */
int my_strlen(const char *s) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}

int count_digit(const char *s) {
    int c = 0;
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] >= '0' && s[i] <= '9') c++;
    return c;
}

int main(void)
{
    /* ===== TODO 1：字符数组 vs 字符串（'\0' 结尾） → P87 =====
     * 任务：定义 s1="hello"（自带 '\0'）与 s2={'h','e','l','l','o'}（无 '\0'），
     *       分别 printf("%s\n", s1/s2)，观察 s2 为何会打印到内存里下一个 '\0' 才停。
     * 预测：s1 正常打印 hello；s2 打印 hello 后继续吐乱码直到碰巧遇到 '\0'。
     */
#pragma region TODO1 参考（展开看，写自己代码不需要）
    /*
    char s1[] = "hello";
    char s2[] = { 'h','e','l','l','o' };   // 注意：没有 '\0'
    printf("s1=%s\n", s1);
    printf("s2=%s\n", s2);
    */
#pragma endregion

    /* ===== TODO 2：字符串输入输出（P89）——scanf("%s") 的行为与宽度保护 =====
     * 任务：char buf[8];
     *       ① 先用 scanf("%7s", buf) 读入，输入 "hello world" —— 观察实际读到了什么？
     *       ② 再想：如果写成 scanf("%s", buf)，输入超过 7 个字符会发生什么？
     * 预测：%s / %7s 都"遇空格即停" —— "hello world" 只能得到 "hello"；
     *       %7s 最多读 7 字符 + '\0'，绝不越界；%s 无宽度保护，输入超长会越界写坏内存。
     * 要点：宽度应写成 sizeof(buf)-1。
     */
#pragma region TODO2 参考（展开看，写自己代码不需要）
    /*
    char buf[8];
    scanf("%7s", buf);          // 宽度 7 = sizeof(buf)-1：最多读 7 字符 + '\0'，安全
    printf("got: %s\n", buf);
    // 对照：scanf("%s", buf) 无宽度保护 + 遇空格即停，输入超长会越界（危险）
    */
#pragma endregion

    /* ===== TODO 3：字符串数组 → P90 =====
     * 任务：用两种写法存同一组字符串，遍历打印，观察写法差别：
     *       char *a[] = { "Mon", "Tue", "Wed" };      // 指针数组：每个元素是一个指针
     *       char b[][8] = { "Mon", "Tue", "Wed" };    // 二维字符数组：连续存放，每行 8 字节
     * 预测：两者打印结果一样（Mon Tue Wed），但内存布局不同：
     *       a 里每个元素是指针；b 是 3×8 的连续字节块。
     */
#pragma region TODO3 参考（展开看，写自己代码不需要）
    /*
    char *a[] = { "Mon", "Tue", "Wed" };
    char b[][8] = { "Mon", "Tue", "Wed" };
    for (int i = 0; i < 3; i++) printf("%s ", a[i]);
    printf("\n");
    for (int i = 0; i < 3; i++) printf("%s ", b[i]);
    printf("\n");
    */
#pragma endregion

    /* ===== TODO 4：自己实现 my_strlen → P92 =====
     * 任务：不调库，写一个遍历到 '\0' 返回长度的函数。
     * 预测："hello" → 5；"" → 0。（本文件已提供 my_strlen，直接调用对比库 strlen）
     */
#pragma region TODO4 参考（展开看，写自己代码不需要）
    /*
    printf("my_strlen=%d  lib_strlen=%d\n", my_strlen("hello"), (int)strlen("hello"));
    */
#pragma endregion

    /* ===== TODO 5：统计字符串中的数字字符个数（计划自测题） =====
     * 任务：调用 count_digit(s)，统计 s 中 '0'..'9' 的个数。
     * 预测："a1b22c3" → 4；"no digit" → 0。
     */
#pragma region TODO5 参考（展开看，写自己代码不需要）
    /*
    printf("digits=%d\n", count_digit("a1b22c3"));  // 4
    */
#pragma endregion

    return 0;
}
