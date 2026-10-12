// day03_branch.c
// W1-D3 分支结构：if / else if / switch
// 对应翁恺 V1 第 24–31 讲（做判断 if、关系运算、找零计算器、else、嵌套/级联 if-else、switch-case）
//           + 第 64–66 讲（逻辑类型、逻辑运算、条件运算与逗号运算）
//
// 提示：Windows 控制台默认代码页 936，printf 中文可能乱码；本文件提示语用英文。
// 若坚持中文输出，先在运行窗口执行 chcp 65001。

#include <stdio.h>

int main(void)
{
    // ========== 第 24 讲：做判断 if ==========
    // TODO 1：输入一个整数，判断它是正数、负数还是零
    // int n = 0;
    // printf("Enter an integer: ");
    // scanf("%d", &n);
    // 用 if-else if-else 输出 "positive" / "negative" / "zero"

    // ========== 第 25–26 讲：判断的条件 / 找零计算器 ==========
    // TODO 2：输入应付金额 price 和票面 bill，计算并输出找零；
    //         若钱不够，输出 "Not enough money."

    // ========== 第 27–29 讲：else / 嵌套与级联的 if-else ==========
    // TODO 3：输入百分制成绩 score（0–100），输出等级 A/B/C/D/F
    //   A: 90–100   B: 80–89   C: 70–79   D: 60–69   F: <60
    //   非法输入输出 "Invalid score."

    // ========== 第 31 讲：多路分支 switch-case ==========
    // TODO 4：把 TODO 3 的成绩分级改写成 switch-case 版本。
    //   提示：score / 10 可以把 90–99 都映射到 9，80–89 映射到 8……
    //   想一想：if-else if 和 switch，哪种更适合这个场景？为什么？

    // ========== 第 64–66 讲：逻辑运算与条件运算 ==========
    // TODO 5：输入三个整数，判断它们能否构成三角形（任意两边之和大于第三边）
    //         用 &&（与）和 ||（或）写出条件

    // TODO 6：输入两个整数，用条件表达式 ?: 输出较大者
    //   例如 int a, b; int max = (a > b) ? a : b;

    return 0;
}
