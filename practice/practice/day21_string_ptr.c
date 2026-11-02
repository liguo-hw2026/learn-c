/*
 * day21 字符指针与字符串处理函数（上）（第 4 周 第 5 天）
 * ---------------------------------------------------------------------------
 * 资源（已 B站 API 核对真实分 P 标题，2026-11-02）：
 *   📺 V1 翁恺《C语言》BV1XZ4y1S7e1：
 *        P87 10.1.1 字符串
 *        P88 10.1.2 字符串变量
 *        P89 10.1.3 字符串输入输出
 *        P90 10.1.4 字符串数组
 *        P91 10.2.1 单字符输入输出
 *   📄 D2 cppreference「Strings library」<https://zh.cppreference.com/w/c/string/byte>
 *
 * TODO ↔ 分 P 对照（锚定翁恺真实分 P，无翁恺 P 号的知识点不杜撰）：
 *   TODO1  字符串字面量 vs 字符数组 / char* vs char[] 能否修改 —— P87 + P88
 *   TODO2  字符串输入输出（%s / puts / scanf / fgets）          —— P89
 *   TODO3  字符串数组（char *names[]，指针数组）                —— P90
 *   TODO4  单字符输入输出（getchar / putchar，返回 int）        —— P91
 *   自测锚点：解释「char *s="abc"; s[0]='x'; 崩溃」而「char t[]="abc"; t[0]='x'; 正常」的根因。
 *
 * 格式约定（2026-10 定）：
 *   【任务】【预测】平铺可见、不折叠；【参考代码】用 #pragma region 折叠，置于 /* *\/ 内防误编译。
 *   本文件统一 C89 风格（for 循环外置 i），匹配 MSVC 默认模式，参考代码解注即可跑。
 *   自己敲代码跑，不要只看参考。
 */

#include <stdio.h>

int main(void)
{
    /* ===================== TODO1 字符串字面量 vs 字符数组（P87 + P88） ===================== */
    /* 【任务】
     * 对比两段代码，取消注释分别运行，观察哪段会崩溃：
     *   (A) char *s = "abc";  s[0] = 'x';
     *   (B) char t[] = "abc";  t[0] = 'x';
     * 思考：为什么 (A) 崩、(B) 不崩？这和 day20 讲的「数组名是地址常量」有什么关系？
     */
    /* 【预测】
     * (A) 运行时崩溃（写入访问冲突）："abc" 是字符串字面量，存放在只读段（.rdata / flash），
     *     s 只是个指针，指向那块只读内存；试图改写 = 未定义行为，现代 OS 直接拦下（硬件 fault）。
     * (B) 正常：t 是在栈上开的字符数组，初始化时把 "abc" 拷进数组；改的是栈上副本，随便改。
     * ⚠️ 根因区别：char* 指向「只读常量区」，char[] 是「可写栈缓冲」。嵌入式里后者才是你该放
     *    串口/传感器字符串的地方；前者只能读。
     */
    #pragma region TODO1 参考代码
    /*
    {
        char *s = "abc";   // s 指向只读字符串字面量
        // s[0] = 'x';     // 取消注释运行 → 崩溃（写只读段，UB）
        char t[] = "abc";  // t 是栈上数组，内容从字面量拷贝而来
        t[0] = 'x';        // 合法：改的是栈上副本，t 变成 "xbc"
        printf("t = %s\n", t);
    }
    */
    #pragma endregion

    /* ===================== TODO2 字符串输入输出（P89） ===================== */
    /* 【任务】
     * 定义一个 char buf[100]; 用 scanf("%s", buf) 读入一个单词（不含空格），
     * 分别用 puts(buf) 与 printf(">>%s<<\n", buf) 输出；
     * 再试 fgets(buf, sizeof(buf), stdin) 读一整行（含空格），对比 %s 只读到空格为止。
     */
    /* 【预测】
     * scanf("%s", buf) 读到空格/换行即停；puts 自动补换行；printf %s 不补。
     * fgets 读整行（含空格），但会把结尾 '\n' 也读进 buf —— 打印时要留意多一个换行。
     * ⚠️ MSVC 下 gets() 已被禁用（C4996），一律用 fgets 替代；scanf %s 无长度保护，buf 要开够大。
     */
    #pragma region TODO2 参考代码
    /*
    {
        char buf[100];
        printf("输入一个单词: ");
        scanf("%99s", buf);
        puts(buf);
        printf(">>%s<<\n", buf);

        printf("输入一整行: ");
        fgets(buf, sizeof(buf), stdin);   // 顺带吃掉上面 scanf 留下的 '\n'
        fgets(buf, sizeof(buf), stdin);
        printf("你输入了: %s", buf);
    }
    */
    #pragma endregion

    /* ===================== TODO3 字符串数组（P90） ===================== */
    /* 【任务】
     * 定义 char *names[] = { "Alice", "Bob", "Carol" }; 循环打印每个名字及其首字母，
     * 预测 names 的本质是什么、names[1] 指向哪里、sizeof(names) 是多少。
     */
    /* 【预测】
     * names 是「指针数组」：每个元素是一个 char*，分别指向各自的字符串字面量（只读段）。
     * names[1] 指向 "Bob" 的首字符 'B'；names[1][0] = 'B'。
     * sizeof(names) = 3 * sizeof(char*) = 24（64 位下每个指针 8 字节）—— 注意这不是字符串总长度，
     *   想求元素个数要用 sizeof(names)/sizeof(names[0]) = 3。
     */
    #pragma region TODO3 参考代码
    /*
    {
        char *names[] = { "Alice", "Bob", "Carol" };
        int n = sizeof(names) / sizeof(names[0]);
        for (int i = 0; i < n; i++)
            printf("names[%d] = %s, 首字母 = %c\n", i, names[i], names[i][0]);
        printf("sizeof(names) = %zu (字节) = %d 个指针\n", sizeof(names), n);
    }
    */
    #pragma endregion

    /* ===================== TODO4 单字符输入输出（P91） ===================== */
    /* 【任务】
     * 写一个「回显直到换行」的小循环：用 getchar() 读字符、putchar() 原样输出，
     * 遇到 '\n' 就停。思考：getchar 的返回值是 char 还是 int？为什么？
     */
    /* 【预测】
     * getchar() 返回 int（不是 char）：它要能返回 0~255 的字符，还要能返回 EOF（通常是 -1，
     *   超出 char 范围）。若用 char 接，EOF 会被截断成某个普通字符，循环 forever。
     * 正确写法：int c; while ((c = getchar()) != '\n' && c != EOF) putchar(c);
     */
    #pragma region TODO4 参考代码
    /*
    {
        int c;
        printf("输入一行，按回车结束: ");
        while ((c = getchar()) != '\n' && c != EOF)
            putchar(c);
        putchar('\n');
    }
    */
    #pragma endregion

    return 0;
}
