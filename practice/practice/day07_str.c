/*
 * day07_str.c - 第 2 周第 3 天 · 字符数组与字符串（翁恺 V1 第 87–95 讲）
 *   数组作函数参数退化自检（sizeof 退化成指针）也落在本日。
 *
 * ⚠️ 提示骨架：每题的"参考写法"用 #pragma region 折叠（见各 TODO 末尾）。
 *    VS 折叠：Ctrl+M, Ctrl+M 折叠/展开单个；Ctrl+M, Ctrl+O 折叠全部。
 * 方法：先预测后验证（predict-then-verify）。
 *
 * 📺 视频（B站分P，已用 API 核标题）：
 *    P87 字符串 / P88 字符数组 / P89 字符串变量 / P90 字符串的输入
 *    P91 字符串数组 / P92 字符串函数 / P93 字符串函数的实现 / P94 程序参数
 *    https://www.bilibili.com/video/BV1XZ4y1S7e1
 * 📄 参考：D1「C 字符串 / C 输入输出」
 *
 * TODO 清单（P87–95 范围）：
 *   1  字符数组 vs 字符串（'\0' 结尾）：观察无 '\0' 的字符数组用 %s 打印的后果
 *   2  自己实现 my_strlen（遍历到 '\0'），对比库 strlen
 *   3  数组作函数参数退化：sizeof(arr) 在函数内退化成指针大小（8字节）、丢长度（D5/D6 自检）
 *   4  安全读入：fgets 带宽度限制 vs gets（废弃）/ scanf("%s")（无宽度、遇空格停、可能溢出）
 *   5  自测：写 count_digit(const char*) 统计字符串中数字字符个数
 *
 * 收工自测（能口述）：① 为什么字符串必须以 '\0' 结尾；
 *      ② 为什么数组传参后 sizeof 得到指针大小而非数组长度；
 *      ③ 为什么 gets 危险、fgets 更安全。
 *
 * 🔧 硬件相关性：
 *   - '\0' 结尾与缓冲区边界 🟢 高相关：读串口/网络帧、定长缓冲必须边界检查，
 *     越界=缓冲区溢出=嵌入式头号安全/崩溃隐患
 *   - 字符串处理 🟡 通用素养：配置解析/日志；但 '\0' 与越界是嵌入式必踩点
 *   - 数组退化→指针传参 🟢 高相关：直接为 W3 指针日打底
 *
 * 说明：本文件顶部已提供 my_strlen / show_size / count_digit 三个工具函数
 *      （文件作用域，可直接调用）。W1-D8 你将从头自己写函数；今天先"调用 + 观察 + 预测"。
 */

#include <stdio.h>
#include <string.h>

/* ===== 本日提供的工具函数（W1-D8 你将自己从头写函数，今天先调用观察） ===== */
int my_strlen(const char *s) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}

void show_size(int arr[]) {
    /* arr 在这里已退化成指针，sizeof(arr) 得到的是指针大小，不是数组长度 */
    printf("inside  sizeof(arr) = %zu (退化成指针大小)\n", sizeof(arr));
}

int count_digit(const char *s) {
    int c = 0;
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] >= '0' && s[i] <= '9') c++;
    return c;
}

int main(void)
{
    /* ===== TODO 1：字符数组 vs 字符串（'\0' 结尾） =====
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

    /* ===== TODO 2：自己实现 my_strlen =====
     * 任务：不调库，写一个遍历到 '\0' 返回长度的函数。
     * 预测："hello" → 5；"" → 0。（本文件已提供 my_strlen，直接调用对比库 strlen）
     */
#pragma region TODO2 参考（展开看，写自己代码不需要）
    /*
    printf("my_strlen=%d  lib_strlen=%d\n", my_strlen("hello"), (int)strlen("hello"));
    */
#pragma endregion

    /* ===== TODO 3：数组作函数参数退化（sizeof 自检，自 D5/D6 移入） =====
     * 任务：主函数里对一个真实数组打印 sizeof(数组)，再调用 show_size(a) 看函数内 sizeof。
     * 预测：调用处 sizeof(a)=元素数*4（如 5*4=20）；函数内 sizeof(arr)=8（指针大小），
     *       长度信息在传参时丢失——这正是数组传参常要再传一个长度 n 的原因。
     */
#pragma region TODO3 参考（展开看，写自己代码不需要）
    /*
    int a[5] = { 1, 2, 3, 4, 5 };
    printf("outside sizeof(a) = %zu (真实数组长度)\n", sizeof(a));
    show_size(a);
    */
#pragma endregion

    /* ===== TODO 4：安全读入（fgets vs gets/scanf） =====
     * 任务：用 fgets(buf, sizeof(buf), stdin) 读一行（含空格、不会溢出）；
     *       对照说明 gets(buf) 已废弃（无长度限制，危险）、scanf("%s",buf) 遇空格即停且无宽度保护。
     * 预测：输入 "hello world" → fgets 完整读入（含换行），最多读 sizeof(buf)-1 字符，绝不越界。
     */
#pragma region TODO4 参考（展开看，写自己代码不需要）
    /*
    char buf[16];
    fgets(buf, sizeof(buf), stdin);   // 最多读 15 字符 + '\0'，安全
    printf("got: %s", buf);
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
