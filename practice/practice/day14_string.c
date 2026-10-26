/*
 * day14_string.c - 第 3 周第 5 天 · 字符串·上（翁恺 V1 第 87–91 讲）
 *
 * 视频（B站分P，已用 API 核实 2026-10-26）：
 *   P87 10.1.1 字符串
 *   P88 10.1.2 字符串变量
 *   P89 10.1.3 字符串输入输出
 *   P90 10.1.4 字符串数组
 *   P91 10.2.1 单字符输入输出
 *   https://www.bilibili.com/video/BV1XZ4y1S7e1
 *
 * 骨架格式（用户 2026-10-26 要求，自 day14 起执行）：
 *   【任务】写完整自洽题面，用户自己敲代码，不必展开参考代码才懂题；
 *   【参考代码】折叠存放仅作兜底，不是题面本身。
 *
 * TODO ↔ 分P 对照（全部落在 P87–P91，不超纲）：
 *   TODO1 字符串本质（char 数组 + 结束符 \0）           → P87
 *   TODO2 字符串变量：数组 vs 指针指向字面量            → P88
 *   TODO3 字符串输入输出：scanf %s 与宽度保护           → P89
 *   TODO4 字符串数组（命令表 / 菜单）                  → P90
 *   TODO5 单字符输入输出 getchar/putchar（返回 int）    → P91
 *
 * 延后项（不在本日）：字符串函数 strlen/strcmp/strcpy/strcat/搜索 → P92–95（第 3 周第 6 天 · 字符串·下）
 *
 * 收工自测（能口述）：
 *   ① C 里"字符串"本质是什么？靠什么判断结束？
 *   ② `char a[]="x"` 与 `char *p="x"` 改首字符有何不同？
 *   ③ 为什么 scanf("%s") 不加宽度限制危险？
 *   ④ `char *m[]` 这种字符串数组，每个元素是什么类型？
 *   ⑤ getchar()/putchar() 为何用 int 而非 char？
 *
 * 硬件相关性 🟢 极高：
 *   - 固件里一切文本（AT 指令、日志、菜单）都是"以 \0 结尾的 char 数组"；
 *   - 串口/UART 收帧必须限长，否则一帧超长冲掉别的内存（= scanf 宽度保护的硬件版）；
 *   - 字符串数组就是命令匹配表；单字符流读写即 UART 收发模型。
 */

#include <stdio.h>

int main(void)
{
    // ===== TODO1 字符串本质：char 数组 + 结束符 \0（P87）=====
    // 【任务】用 `char s[] = "hello";` 存一个字符串。
    //   ① 写循环逐个打印字符，直到遇到 '\0' 才停（不要用 sizeof 当长度，要靠 '\0' 判断结束）；
    //   ② 打印 sizeof(s) 和"靠 '\0' 数出的字符串长度"，说明两者差 1 的原因。
    // 【预测】sizeof(s)=6（5 个可见字符 + 1 个 '\0'）；循环只打出 h e l l o 共 5 个就停；
    //        逻辑长度=5，比 sizeof 少 1 是因为字符串多存了一个结束符。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO1 参考代码（解注运行）
    /* char s[] = "hello";
     * int len = 0;
     * while (s[len] != '\0') { putchar(s[len]); len++; }
     * printf("\nsizeof(s)=%zu, 逻辑长度=%d (比 sizeof 少 1：多存了 '\\0')\n", sizeof(s), len);
     */
#pragma endregion

    // ===== TODO2 字符串变量：数组 vs 指针指向字面量（P88）=====
    // 【任务】分别用两种写法：① `char a[] = "hello";` ② `char *p = "hello";`。
    //   各尝试把首字符改成 'H'（`a[0]='H';` / `p[0]='H';`），观察哪个能改、哪个运行会出错。
    //   想清楚原因：a 是自己的一份可写拷贝；p 指向"字符串字面量"（通常在只读段，不该写）。
    // 【预测】a[0]='H' 合法，a 变成 "Hello"；p[0]='H' 行为未定义——很多系统运行时崩溃
    //        （写入只读区），代码能编过但一运行就挂。这正是"别往常量区写"的活教材。
    // 【参考代码】见下方 region（p 那行先注释着试，避免真崩）。
#pragma region TODO2 参考代码（解注运行）
    /* char a[] = "hello";
     * a[0] = 'H';
     * printf("a = %s\n", a);          // Hello
     * char *p = "hello";
     * // p[0] = 'H';                  // 未定义行为：字面量在只读段，写入可能崩溃
     * printf("p = %s\n", p);
     */
#pragma endregion

    // ===== TODO3 字符串输入输出 + 宽度保护（P89）=====
    // 【任务】`char buf[8];`
    //   ① 用 `scanf("%s", buf)` 读一个单词并打印；
    //   ② 再用带宽度限制的 `scanf("%7s", buf)` 读，预测它最多读几个字符、为什么是 7 不是 8；
    //   ③ 故意输入超过 7 个字符，对比"有/无宽度限制"时程序会不会写穿 buf。
    // 【预测】%s 遇空格或回车停止；%7s 最多读 7 个字符再补 '\0'（恰好占满 buf[8]），绝不越界；
    //        无宽度限制的 %s 输入过长会缓冲区溢出（经典漏洞）。
    // 【参考代码】见下方 region。
#pragma region TODO3 参考代码（解注运行）
    /* char buf[8];
     * printf("enter word: ");
     * scanf("%7s", buf);              // 最多 7 字符 + '\0' = 8，恰好填满 buf
     * printf("got (width-safe): %s\n", buf);
     * // 对照：scanf("%s", buf) 输入超长会写穿 buf —— 危险，勿在日常用
     */
#pragma endregion

    // ===== TODO4 字符串数组（命令表 / 菜单）（P90）=====
    // 【任务】定义一个"字符串数组"存 12 个月英文名：
    //   `const char *months[] = {"Jan","Feb",...,"Dec"};`（或 `char months[12][10]`）。
    //   ① 打印第 5 个月；② 用循环打印全部 12 个；③ 找出并打印"最长"的那个月份名及其长度。
    // 【预测】months[4] = "May"；循环打出 12 个；最长的是 "September"（9 字符，按你实际数组定）。
    // 【参考代码】见下方 region。
#pragma region TODO4 参考代码（解注运行）
    /* const char *months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
     * printf("month[4] = %s\n", months[4]);
     * int maxlen = 0; const char *longest = months[0];
     * for (int i = 0; i < 12; i++) {
     *     int l = 0; while (months[i][l] != '\0') l++;
     *     printf("%s\n", months[i]);
     *     if (l > maxlen) { maxlen = l; longest = months[i]; }
     * }
     * printf("longest = %s (%d)\n", longest, maxlen);
     */
#pragma endregion

    // ===== TODO5 单字符输入输出：getchar/putchar（返回 int）（P91）=====
    // 【任务】用 `getchar()`/`putchar()` 逐个读字符、原样回显，直到读到回车 '\n' 或 EOF 才停；
    //   用 `int c; while ((c = getchar()) != EOF && c != '\n') putchar(c);` 统计回显了几个字符。
    // 【预测】输入 "Hi\n" 回显 H i 共 2 个后停止；getchar 返回 int 是为了能表示 EOF(-1)
    //        这种超出 char 范围的值——用 char 接会丢 EOF 判断。
    // 【参考代码】见下方 region。
    // ⚠️ 小坑：若前面用过 scanf 读字符串，输入缓冲里可能残留 '\n'，会让 getchar 一上来就吃到回车。
    //    想干净验证本 TODO，可把前面 TODO 的解注代码先注释掉，单独跑这一块。
#pragma region TODO5 参考代码（解注运行）
    /* int c; int n = 0;
     * printf("type something: ");
     * while ((c = getchar()) != EOF && c != '\n') { putchar(c); n++; }
     * printf("\nechoed %d chars\n", n);
     */
#pragma endregion

    return 0;
}
