// day03_branch.c
// 分支结构：if / else if / switch（第 1 周第 5–6 天）
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
     /*int n = 0;
    printf("Enter an integer: ");
    scanf("%d", &n);
    if (n > 0) {
        printf("positive\n");
    }
    else if (n < 0) {
        printf("negative\n");
    }
    else
        printf("zero\n");
       
    // 用 if-else if-else 输出 "positive" / "negative" / "zero"

    // ========== 第 25–26 讲：判断的条件 / 找零计算器 ==========
    // TODO 2：输入应付金额 price 和票面 bill，计算并输出找零；
    int price = 0;
    int bill = 0;
    printf("enter the price and bill:\n");
    scanf("%d %d", &price,&bill);
    if (bill >= price) {
        printf("the change is :%d", bill - price);
    }
    else
        printf("your money is not enough\n");
    //         若钱不够，输出 "Not enough money."
     
    // ========== 第 27–29 讲：else / 嵌套与级联的 if-else ==========
    // TODO 3：输入百分制成绩 score（0–100），输出等级 A/B/C/D/F
    //   A: 90–100   B: 80–89   C: 70–79   D: 60–69   F: <60
    //   非法输入输出 "Invalid score."
    int score = 0;
    printf("enter the score:\n");
    int ret=scanf("%d", &score);
    if (ret != 1) {
        printf("invalid score\n");
    }
    else if (score > 100||score<0)
 { printf("invalid score\n"); }
    else if (score >= 90) {
        printf("grade:A\n");
    }
    else if (score >= 80) {
        printf("grade:B\n");
    }
    else if (score >= 70) {
        printf("grade:C\n");
    }
    else if (score >= 60) {
        printf("grade:D\n");
    }
    else if (score < 60) {
        printf("grade:F\n");
    }
        // ========== 第 31 讲：多路分支 switch-case ==========
    // TODO 4：把 TODO 3 的成绩分级改写成 switch-case 版本。
    //   提示：score / 10 可以把 90–99 都映射到 9，80–89 映射到 8……
    //   想一想：if-else if 和 switch，哪种更适合这个场景？为什么？
    int score = 0;
    printf("enter the score:\n");
    int ret = scanf("%d", &score);
    if (ret != 1) {
        printf("invalid score\n");
    }
    else if(score > 100 || score < 0)
    {
        printf("invalid score\n");
    }
    else {
        switch (score / 10) {
        case(10):
        case(9):
            printf("grade:A\n");
            break;
        case(8):
            printf("grade:B\n");
            break;
        case(7):
            printf("grade:C\n");
            break;
        case(6):
            printf("grade:D\n");
            break;
        default:
            printf("grade:F\n");
            break;
        }
    }
    // ========== 第 64–66 讲：逻辑运算与条件运算 ==========
    // TODO 5：输入三个整数，判断它们能否构成三角形（任意两边之和大于第三边）
    //         用 &&（与）和 ||（或）写出条件
    int a = 0, b = 0, c = 0;
    printf("enter three sides:\n");
    int ret=scanf("%d %d %d", &a, &b, &c);
    if (ret != 3) {
        printf("invalid input\n");
    }
    else if (a < 0 || b < 0 || c < 0) {
        printf("invalid input\n");
    }
    else if (a + b > c && a + c > b && b + c > a) {
        printf("the three sides can make a triangle\n");
    }
    else
        printf("the three sides can not make a triangle\n");
        */
    // TODO 6：输入两个整数，用条件表达式 ?: 输出较大者
    //   例如 int a, b; int max = (a > b) ? a : b;
int a = 0,b=0;
printf("enter two number:");
scanf("%d %d", &a, &b);
int max = 0;
printf("%d", max = (a > b) ? a : b);
    return 0;
}
