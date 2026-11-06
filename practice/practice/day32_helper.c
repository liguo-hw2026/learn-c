/*
 * day32_helper.c —— 第 5 周 第 5 天 多文件演示配套文件（无 main，随工程链接）
 * 提供 day32_const_static_extern.c 用 extern 引用的全局符号，演示"跨文件共享"。
 * ⚠️ 本文件由 agent 提供完整定义，不用你手敲；你只需在 day32 主文件里写 extern 声明并使用。
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 跨文件共享的全局变量（默认外部链接，别的 .c 用 extern 就能用）
int g_shared = 100;

// 跨文件共享的函数（默认外部链接）
void helper_print(void) {
    printf("[helper] g_shared = %d\n", g_shared);
}

// TODO ④ 观察（不用改）：把上面的 `int g_shared = 100;` 改成 `static int g_shared = 100;`
//   再编译 → 主文件里的 `extern int g_shared;` 会链接报错（LNK2019 找不到外部符号）。
//   原因：static 把它的链接从"外部"改成"内部"，别的翻译单元就看不见了——这就是内部链接。
