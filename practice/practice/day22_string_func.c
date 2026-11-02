/*
 * day22 字符串处理函数自己实现一遍（第 4 周 第 6 天）
 * ---------------------------------------------------------------------------
 * 资源（已 B站 API 核对真实分 P 标题，2026-11-02）：
 *   📺 V1 翁恺《C语言》BV1XZ4y1S7e1：
 *        P92 10.2.2 字符串函数strlen
 *        P93 10.2.3 字符串函数strc（strcat / strcmp 合一讲）
 *        P94 10.2.4 字符串函数strcpy
 *        P95 10.2.6 字符串搜索函数（strstr 等）
 *   📄 D2 cppreference「Strings library」<https://zh.cppreference.com/w/c/string/byte>
 *
 * TODO ↔ 分 P 对照（锚定翁恺真实分 P，不杜撰 P 号）：
 *   TODO1  my_strlen                          —— P92
 *   TODO2  my_strcat（含溢出风险）             —— P93（strc）
 *   TODO3  my_strcmp                          —— P93（strc）
 *   TODO4  my_strcpy（目标需足够大）           —— P94
 *   TODO5  my_strstr（强化 day19 失配回退 bug） —— P95（字符串搜索函数）
 *   延后/扩展项（计划列了但翁恺 P92–95 未专讲，不计入当日 TODO，留待字符串专题或自行查 cppreference）：
 *     strtok / memcpy / memset —— 其中 memcpy/memset 在嵌入式（缓冲拷贝、DMA、清零）极高频，建议后续单独补；
 *     但当日严格只覆盖 P92–95 真实讲授的 strlen/strcat/strcmp/strcpy/strstr。
 *
 * 格式约定（2026-10 定）：
 *   【任务】【预测】平铺可见、不折叠；【参考代码】用 #pragma region 折叠，置于 /* *\/ 内防误编译。
 *   本文件统一 C89 风格（for 循环外置 i），匹配 MSVC 默认模式，参考代码解注即可跑。
 *   自己敲代码跑，不要只看参考。
 */

#include <stdio.h>

int main(void)
{
    /* ===================== TODO1 自己实现 strlen（P92） ===================== */
    /* 【任务】
     * 实现 size_t my_strlen(const char *s)，返回字符串长度（不含结尾 '\0'）。
     * 预测：my_strlen("hello") = 5；my_strlen("") = 0。
     * 思考：为什么参数写 const char*（只读）？返回值为什么用 size_t 而不是 int？
     */
    /* 【预测】
     * 顺着 s 走，遇到 '\0' 就停，数走了几个字符。const char* 表示"函数不修改所指内容"，是契约也是保护。
     * size_t 是无符号长度类型（能表达任意合法内存长度，不会为负）；用 int 在长字符串上可能溢出/负号歧义。
     */
    //char *s = "hello";
    //printf("len=%zu\n", my_strlen(s));   // 预测 5
    #pragma region TODO1 参考代码
    /*
    size_t my_strlen(const char *s)
    {
        size_t n = 0;
        while (s[n] != '\0') n++;
        return n;
    }
    */
    #pragma endregion

    /* ===================== TODO2 自己实现 strcat（P93·strc） ===================== */
    /* 【任务】
     * 实现 char* my_strcat(char *dest, const char *src)，把 src 拼到 dest 末尾，返回 dest。
     * 预测：dest="ab" + src="cd" → dest 变成 "abcd"。
     * 思考：dest 原本必须有足够空间容纳拼接结果，否则会发生什么？
     */
    /* 【预测】
     * 先走到 dest 的 '\0'（末尾），再从那开始逐字符拷 src（含 src 的 '\0'）。
     * ⚠️ 致命坑：dest 必须有 >= strlen(dest)+strlen(src)+1 的空间。空间不够 → 溢出改写相邻内存，
     *    MCU 上轻则数据错乱、重则跑飞/hardfault。标准 strcat 不检查长度，正是缓冲区溢出的头号来源。
     */
    //char d[20] = "ab";
    //printf("cat=%s\n", my_strcat(d, "cd"));   // 预测 abcd
    #pragma region TODO2 参考代码
    /*
    char* my_strcat(char *dest, const char *src)
    {
        int i = 0, j = 0;
        while (dest[i] != '\0') i++;        // 找到 dest 末尾
        while (src[j] != '\0') dest[i++] = src[j++];
        dest[i] = '\0';
        return dest;
    }
    */
    #pragma endregion

    /* ===================== TODO3 自己实现 strcmp（P93·strc） ===================== */
    /* 【任务】
     * 实现 int my_strcmp(const char *a, const char *b)：字典序 a<b 返回负、相等返回 0、a>b 返回正。
     * 预测：my_strcmp("abc","abd") < 0；my_strcmp("ab","ab") = 0；my_strcmp("abd","abc") > 0。
     */
    /* 【预测】
     * 逐字符比 ASCII 码，第一个不同处返回差值；两边都到 '\0' 仍相同则返回 0。
     * 注意用 unsigned char 比较（避免符号扩展导致 '\xff' 等被当成负数而排错序）。
     */
    //printf("cmp=%d\n", my_strcmp("abc","abd"));   // 预测 <0（负）
    #pragma region TODO3 参考代码
    /*
    int my_strcmp(const char *a, const char *b)
    {
        int i = 0;
        while (a[i] && b[i] && a[i] == b[i]) i++;
        return (unsigned char)a[i] - (unsigned char)b[i];
    }
    */
    #pragma endregion

    /* ===================== TODO4 自己实现 strcpy（P94） ===================== */
    /* 【任务】
     * 实现 char* my_strcpy(char *dest, const char *src)，把 src（含 '\0'）拷到 dest，返回 dest。
     * 预测：my_strcpy(d,"xyz") → d 变成 "xyz"。
     * 思考：调用前你必须保证什么？src 如果没 '\0' 结尾会怎样？
     */
    /* 【预测】
     * 逐字符拷，直到把 src 的 '\0' 也一起拷过去（用一个赋值表达式的值当循环条件）。
     * ⚠️ 两大约束：① dest 空间必须 >= strlen(src)+1；② src 必须 '\0' 结尾，否则会越界读内存。
     * 标准 strcpy 同样不检查，安全版是 strncpy（但仍需自己补 '\0'）。
     */
    //char d[20];
    //printf("cpy=%s\n", my_strcpy(d, "xyz"));   // 预测 xyz
    #pragma region TODO4 参考代码
    /*
    char* my_strcpy(char *dest, const char *src)
    {
        int i = 0;
        while ((dest[i] = src[i]) != '\0') i++;
        return dest;
    }
    */
    #pragma endregion

    /* ===================== TODO5 自己实现 strstr（P95·搜索函数，强化 day19 bug） ===================== */
    /* 【任务】
     * 实现 char* my_strstr(const char *hay, const char *needle)：在 hay 中找 needle 首次出现，
     * 返回其首地址；找不到返回 NULL。预测：my_strstr("abcde","cd") 指向 hay 里的 'c'。
     */
    /* 【预测】
     * ⚠️ 强化 day19 你写 my_strstr 时的真 bug：部分失配（如 hay="abcde" needle="cde"，
     *   比到 'e'≠'d'）绝不能 return NULL——必须从 hay 的下一字符（i+1）重新从 needle[0] 匹配（回退）。
     * 只有当 needle 完整匹配（j 走到其 '\0'）才返回。needle 为空串返回 hay 本身。
     */
    //char *r = my_strstr("abcde", "cd");
    //printf("strstr=%s\n", r ? r : "NULL");   // 预测 cde
    #pragma region TODO5 参考代码
    /*
    char* my_strstr(const char *hay, const char *needle)
    {
        if (!*needle) return (char*)hay;          // 空 needle 视为匹配开头
        int i = 0;
        for (i = 0; hay[i]; i++) {
            int j = 0;
            while (needle[j] && hay[i+j] == needle[j]) j++;
            if (!needle[j]) return (char*)&hay[i]; // 完整匹配才返回
        }
        return NULL;                              // 走完 hay 都没完整匹配
    }
    */
    #pragma endregion

    return 0;
}
