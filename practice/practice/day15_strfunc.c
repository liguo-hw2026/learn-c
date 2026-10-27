/*
 * day15_strfunc.c - 第 3 周第 6 天 · 字符串·下 / 字符串函数（翁恺 V1 第 92–95 讲）
 *
 * 视频（B站分P，已用 API 核实 2026-10-27）：
 *   P92 10.2.2 字符串函数 strlen
 *   P93 10.2.3 字符串函数 strc（即 strcat）
 *   P94 10.2.4 字符串函数 strcpy
 *   P95 10.2.6 字符串搜索函数
 *   https://www.bilibili.com/video/BV1XZ4y1S7e1
 *
 * 骨架格式（用户 2026-10-26 要求，自 day14 起执行）：
 *   【任务】写完整自洽题面，用户自己敲代码，不必展开参考代码才懂题；
 *   【参考代码】折叠存放仅作兜底，不是题面本身。
 *
 * TODO ↔ 分P 对照（严格落在 P92–P95，不超纲）：
 *   TODO1 my_strlen（自己实现，不数 '\0'）              → P92
 *   TODO2 my_strcpy（+ 溢出风险）                       → P94
 *   TODO3 my_strcat（+ 溢出风险）                       → P93
 *   TODO4 my_strcmp（比较，计划 resource 行列入；P92–95 分P标题未单列，属同族延伸）
 *   TODO5 my_strstr（子串搜索，返回指针或 NULL）         → P95
 *
 * 延后项（不在 P92–P95，计划 resource 行列入但分P无对应讲次，标延后避免超纲）：
 *   strtok / memcpy / memset —— 与后续内存章（malloc/free）及通用库函数相关，
 *   留作熟练后或穿插复习，不占本日。
 *
 * 收工自测（能口述）：
 *   ① strlen 为什么不数 '\0'？它怎么知道在哪停？
 *   ② strcpy / strcat 为什么"不检查目标够不够大"是头号危险？嵌入式里用什么替代？
 *   ③ strcat 实现里为什么要先找到 dst 的 '\0' 再接？
 *   ④ strcmp 返回 <0/0/>0 分别意味着什么？为什么不能直接用 == 比字符串？
 *   ⑤ 字符串搜索（strstr）找不到时返回什么？为什么用 NULL 而不是 -1？
 *
 * 硬件相关性 🟢 极高：
 *   - 固件里所有字符串操作（拼 AT 指令、组日志、解析报文）本质都是这几个函数；
 *   - 裸 strcpy/strcat 不检查长度 = 缓冲区溢出 = 嵌入式最常见的 hard fault / 安全漏洞源头；
 *     工业界一律用 strncpy / strncat / snprintf 或自己带长度参数；
 *   - 命令解析（"AT+LED=1" 里找 "LED"）就是 strstr 的用武之地。
 */

#include <stdio.h>
#include <string.h>   /* 仅作对照：跑通自己的实现后，可与库函数结果比对 */

int main(void)
{
    // ===== TODO1 my_strlen：自己实现，不依赖库（P92）=====
    // 【任务】写一个函数 `size_t my_strlen(const char *s)`，返回字符串长度（不含 '\0'）。
    //   提示：从 s[0] 开始数，遇到 '\0' 停止；用循环，不要调用库 strlen。
    //   验证：用 "hello"（应得 5）和 ""（空串，应得 0）各测一次，与库函数对比。
    // 【预测】my_strlen("hello") = 5；my_strlen("") = 0；与 strlen() 结果一致。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO1 参考代码（解注运行）
    /* size_t my_strlen(const char *s) {
     *     size_t n = 0;
     *     while (s[n] != '\0') n++;
     *     return n;
     * }
     * int main(void) {
     *     printf("mine=%zu lib=%zu\n", my_strlen("hello"), strlen("hello"));
     *     printf("mine=%zu lib=%zu\n", my_strlen(""), strlen(""));
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO2 my_strcpy：自己实现 + 溢出风险（P94）=====
    // 【任务】写 `char *my_strcpy(char *dst, const char *src)`，把 src（含 '\0'）整段拷到 dst，返回 dst。
    //   ① 先保证"拷对了"：dst 用足够大的数组（如 char dst[32]），src="Hello";
    //   ② 思考并写出风险：如果 dst 比 src 短会怎样？为什么标准 strcpy 不替你检查？
    //   ③ 进阶：写一版 my_strncpy(dst, src, n) 限制最多拷 n 个（嵌入式更安全，留作延伸也可）。
    // 【预测】拷完后 dst == "Hello"；若 dst 太小，多余字符会写穿 dst 旁边的内存（缓冲区溢出）。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO2 参考代码（解注运行）
    /* char *my_strcpy(char *dst, const char *src) {
     *     int i = 0;
     *     while (src[i] != '\0') { dst[i] = src[i]; i++; }
     *     dst[i] = '\0';
     *     return dst;
     * }
     * int main(void) {
     *     char dst[32];
     *     my_strcpy(dst, "Hello");
     *     printf("dst = %s\n", dst);
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO3 my_strcat：自己实现 + 溢出风险（P93）=====
    // 【任务】写 `char *my_strcat(char *dst, const char *src)`，把 src 接到 dst 末尾。
    //   步骤：先找到 dst 当前的 '\0'（从那儿开始写），再把 src 逐个拷过去并补新 '\0'。
    //   验证：dst 初值 "abc"（数组要够大，如 char dst[32]），src="def"，结果应得 "abcdef"。
    //   风险：接完后总长在不在 dst 容量内？溢出同样会写穿内存。
    // 【预测】接完 dst == "abcdef"；关键在"先定位 dst 原 '\0' 再覆盖它"，否则会丢字符或重复。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO3 参考代码（解注运行）
    /* char *my_strcat(char *dst, const char *src) {
     *     int i = 0, j = 0;
     *     while (dst[i] != '\0') i++;          // 找到 dst 末尾
     *     while (src[j] != '\0') { dst[i] = src[j]; i++; j++; }
     *     dst[i] = '\0';
     *     return dst;
     * }
     * int main(void) {
     *     char dst[32] = "abc";
     *     my_strcat(dst, "def");
     *     printf("dst = %s\n", dst);
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO4 my_strcmp：自己实现（计划 resource 列入；P92–95 分P标题未单列，同族延伸）=====
    // 【任务】写 `int my_strcmp(const char *a, const char *b)`，逐字符比较：
    //   返回 <0 表示 a 小于 b，0 表示相等，>0 表示 a 大于 b（按 ASCII 字典序）。
    //   验证："abc" vs "abd" → 负；"abc" vs "abc" → 0；"abd" vs "abc" → 正。
    //   ⚠️ 为什么字符串不能用 `a == b` 比较？== 比的是"两个指针地址"不是"内容"。
    // 【预测】my_strcmp("abc","abd") < 0；my_strcmp("abc","abc") == 0；与 strcmp() 一致。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO4 参考代码（解注运行）
    /* int my_strcmp(const char *a, const char *b) {
     *     int i = 0;
     *     while (a[i] != '\0' && a[i] == b[i]) i++;
     *     return (unsigned char)a[i] - (unsigned char)b[i];
     * }
     * int main(void) {
     *     printf("%d\n", my_strcmp("abc", "abd"));   // <0
     *     printf("%d\n", my_strcmp("abc", "abc"));   // 0
     *     printf("%d\n", my_strcmp("abd", "abc"));   // >0
     *     return 0;
     * }
     */
#pragma endregion

    // ===== TODO5 my_strstr：子串搜索（P95）=====
    // 【任务】写 `const char *my_strstr(const char *hay, const char *needle)`，
    //   在 hay 中找 needle 第一次出现的位置，返回指向该处的指针；找不到返回 NULL。
    //   验证：hay="hello world"，needle="world" → 返回指向 'w' 的指针（打印从该处到末尾应得 "world"）；
    //        needle="xyz" → 返回 NULL（打印"not found"）。
    //   提示：外层遍历 hay 每个起点，内层逐个比对 needle；needle 是空串时约定返回 hay。
    // 【预测】my_strstr("hello world","world") != NULL 且从该位置打印得 "world"；
    //        my_strstr("hello world","xyz") == NULL。
    // 【参考代码】见下方 region（解注运行）。
#pragma region TODO5 参考代码（解注运行）
    /* const char *my_strstr(const char *hay, const char *needle) {
     *     if (needle[0] == '\0') return hay;
     *     for (int i = 0; hay[i] != '\0'; i++) {
     *         int j = 0;
     *         while (needle[j] != '\0' && hay[i + j] == needle[j]) j++;
     *         if (needle[j] == '\0') return &hay[i];
     *     }
     *     return NULL;
     * }
     * int main(void) {
     *     const char *r = my_strstr("hello world", "world");
     *     if (r) printf("found: %s\n", r);
     *     else   printf("not found\n");
     *     return 0;
     * }
     */
#pragma endregion

    return 0;
}
