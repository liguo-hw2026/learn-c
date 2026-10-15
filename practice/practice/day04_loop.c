/*
 * day04_loop.c - W1-D4 循环结构（while / do-while / for）
 * 翁恺 V1 第 32–45 讲
 *
 * ⚠️ 本文件是"提示骨架"，不是答案！每个 TODO 块里只有提示和预测栏，
 *    没有任何现成代码 —— 代码要你自己写。
 *
 * 操作方法（和 day03 一致）：
 *   做哪一道，就把那一道块首尾的注释符号删掉（解注：去掉开头"斜杠星"和结尾"星斜杠"），
 *   然后把里面的"提示/预测"行自己加 // 或直接删掉，在下面写你的代码。
 *   一次只做一道，做完再下一道，不要一次全解注。
 *
 * 方法：先预测后验证（predict-then-verify）。先在"预测："行写下你猜的输出，
 *   再写代码、Ctrl+F5 运行核对。
 *
 * TODO 清单（不同知识点 + 计划必做四任务）：
 *   1  while 统计位数（P33）
 *   2  用 do-while 改写 #1（P34）
 *   3  猜数游戏：while + break（P35）
 *   4  求平均数，遇 -1 结束：累加器（P36）
 *   5  整数求逆：逐位剥离（P37）
 *   6  用 for 改写前面的程序（P38）
 *   7  break 与 continue 对比演示（P40）
 *   8  九九乘法表：嵌套 for（P41）
 *   9  用标志变量从嵌套循环跳出（P42）
 *   10 最大公约数（辗转相减法，P45）  [计划任务]
 *   11 素数判定：穷举  [计划任务]
 *   12 水仙花数：穷举  [计划任务]
 *   13 冒泡排序 —— 已移至「数组日」(依赖数组语法 P74–79 之后做)，今天不做
 *
 * 间隔复习候选（延后，不在今天做，留到 D5 热身 / W1-D7 复盘交错重做）：
 *   - 整数分解（P44）      ：#5 的变体（逐位剥离）
 *   - 前 n 项和（P43）     ：#4 的变体（累加器）
 *   - 图案打印（三角形/菱形，P41 变体）：#8 的变体（嵌套）
 *   - 回文数判定           ：#5 的变体（求逆后比较）
 */

#include <stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void)
{
   
    /* ===== TODO 1：while 统计位数（P33） =====
     * 任务：输入一个整数，输出它是几位数。
     * 提示：回想今天讨论的 P33——循环外先 n++; x/=10; 数掉并划掉个位；
     *       循环内 while(x>0) 再数剩下的位。
     * 思考：输入 0 时循环为何一次都不进，却能得到 1？这正是对 0 边界的正确处理。
     * 预测：352 -> 3 位 ；0 -> 1 位
     * （自己写代码：声明 x,n；读入；循环外数+划一位；循环内数剩下的）
     
    int n = 0;
    int x = 0;
    int ret = 0;
    printf("enter a number:\n");
    ret = scanf("%d",&x);
    if (x < 0) {
        printf("invalid number!\n");
    }
    else if (ret == 0) {
        printf("invalid number!\n");
    }
    else {
        n++;
        x /= 10;
        while (x > 0) {
        x /= 10;
        n++;
        }
        printf("digit:%d\n", n);
    }
     ===== TODO 2：用 do-while 改写 TODO 1（P34） =====
     * 任务：把 TODO 1 用 do-while 重写一遍。
     * 提示：do-while 循环体至少执行一次。想想 x==0 时它和 while 版有什么区别。
     * 预测：输出应与 TODO 1 一致。
     * （自己写代码）
     
    int n = 0;
    int x = 0;
    printf("enter a number:\n");
    scanf("%d", &x);
    do {
        n++;
        x /= 10;
    } while (x > 0);
    printf("digit:%d\n", n);
    */
    /* ===== TODO 3：猜数游戏（P35） =====
     * 任务：程序定一个秘密数（例如 57），用户反复猜；猜中用 break 退出，
     *       猜错提示"too small"或"too big"。
     * 提示：可用 do-while 或 while(1)+break 实现"猜中才停"。
     * 预测：猜中即停，打印 hit。
     * （自己写代码）
     
    srand(time(0));
    int hit = rand() % 100;
    int x = 0;
    int ret = 0;
    do {
        printf("enter a number(0-100):\n");
        ret = scanf("%d", &x);
        if (x < 0 || x>100) {
            printf("invalid number!\n");
            continue;
        }
        else if (ret == 0) {
            printf("invalid number!\n");
            scanf("%*s");
            continue;
        }
        else if (x>hit) {
            printf("too big!\n");
        }
        else if (x < hit) {
            printf("too small!\n");
        }
        else
            printf("the hit number is:%d\n", x);
    } while (x != hit);
    */
    /* ===== TODO 4：求平均数，遇 -1 结束（P36） =====
     * 任务：读入若干整数，遇 -1 停止，输出它们的平均数。
     * 提示：累加器 sum + 计数器 n；注意 n==0 时别除以零（否则运行崩溃）。
     * 预测：输入 10 20 30 -1 -> 平均数 = 20.00
     * （自己写代码）
     
        int x = 0;
        int sum = 0;
        int count = 0;
        float ave = 0.0;
        do {
            printf("enter a number:\n");
            scanf("%d",&x);
            if (x == -1) {
                break;
            }
            sum += x;
            count++;
        } while (x != -1);
        ave = 1.0 * sum / count;
        printf("the average is %f\n", ave);
        */
        /* ===== TODO 5：整数求逆（P37） =====
         * 任务：输入一个正整数，反向输出各位（12345 -> 54321）。
         * 提示：x%10 取末位；rev = rev*10 + 末位 拼接；x/=10 去掉末位。
         * 预测：12345 -> 54321
         * （自己写代码）
     
    int x=0;
    int rev=0;
    int ret = 0;
    int r = 0;
    do {
        printf("enter a number(>0):\n");
        ret=scanf("%d", &x);
        if (ret == 0 ) {
            printf("invalid number!\n");
            scanf("%*s");
            continue;
        }
        else if (x <= 0) {
            printf("invalid number!\n");
            continue;
        }
        else {
            while (x > 0) {
                rev = rev * 10 + x % 10;
                x /= 10;
            }
            printf("the rev is:%d\n", rev);
            r = 1;
        }
    }while (r!=1);
*/
    /* ===== TODO 6：用 for 改写前面的程序（P38） =====
     * 任务：挑前面某道（例如 TODO 4 平均数）把 while 改写成 for。
     * 提示：for 的三个部分分别放 初始化 / 循环条件 / 更新。
     * 预测：与对应的 while 版本输出一致。
     * （自己写代码）
    int sum = 0;
    int count = 0;
    float ave = 0.0;
    for (int x = 0; x >=0; count++)
    {
        printf("enter a number:\n");
        scanf("%d", &x);
        if (x == -1) {
            count++;
            break;
        }
        sum += x;
    } 
    ave = 1.0 * sum / count;
    printf("the average is %f\n", ave);
*/

    /* ===== TODO 7：break 与 continue 对比（P40） =====
     * 任务：写两个小程序，分别用 break 和 continue，先预测每一行输出再验证。
     * 提示：break 直接结束整个循环；continue 只跳过当前这一轮、进入下一轮。
     * 预测：for i=1..5，i==3 时——break 输出 "1 2"；continue 输出 "1 2 4 5"。
     * （自己写代码）
     
    for (int i = 1; i <= 5; i++) {
        //if (i == 3) { break; }
       if (i == 3) { continue; }
        printf("i is:%d\n", i);
}
*/
    /* ===== TODO 8：九九乘法表（P41，嵌套 for） =====
     * 任务：用嵌套 for 打印 9x9 下三角乘法表。
     * 提示：外层 i 控制行(1..9)，内层 j 从 1 到 i；每行结束 printf("\n")。
     * 预测：打印下三角（每行项数=行号）。
     * （自己写代码）
    
int p = 1;
for (int i = 1; i <= 9; i++) {
    printf("row%d:", i);
    for (int j = 1; j <= i; j++) {
        p = i * j;
        printf("%d ", p);
        if (i == j) {
            printf("\n");
        }
    }
}
 */
    /* ===== TODO 9：用标志变量从嵌套循环跳出（P42） =====
     * 任务：在 5x5 网格里找第一对 i*j==12，打印后两层循环都停。
     * 提示：单用 break 只能退出内层；用 found 标志配合外层 for 的条件退出两层。
     * 预测：找到第一对即停。
     * （自己写代码）
     
int p = 1;
int found = 0;
for (int i = 1; i <= 5&&found!=1; i++) {
    for (int j = 1; j <= 5; j++) {
        p = i * j;
        if (p == 12) {
            printf("the first 12 is on R%d C%d", i, j);
            found = 1;
            break;
        }
        }
    }
    */
    /* ===== TODO 10：最大公约数（辗转相减法，P45）[计划任务] =====
     * 任务：求 gcd(48, 36)。
     * 提示：while (a != b) { 大的减小的 }，循环结束 a 即为答案。
     * 预测：gcd(48,36) -> 12
     * （自己写代码）
     
int a = 32, b = 48;
int t = 0;
int gcd = 0;
while (a != b) {
    if (a < b) {
        t = a;
        a = b;
        b = t;
    }
    t = a - b;
    if (t == b) {
        gcd = t;
        printf("the gcd is:%d", gcd);
        break;
    }
    a = b;
    b = t;
}*/

    /* ===== TODO 11：素数判定（穷举）[计划任务] =====
     * 任务：判断一个整数 n 是否为素数。
     * 提示：n<2 不是素数；试除 2 到 sqrt(n)，能整除即不是（命中可 break）。
     * 预测：17 -> 是素数 ；15 -> 不是
     * （自己写代码）
    
int x=0;
int t = 0;
printf("enter a number:\n");
scanf("%d", &x);
for (int i=2; i < x; i++) {
    t = x % i;
    if (t == 0) {
        printf("no!\n");
        break;
    }
}
if (t != 0||x==2) printf("yes!\n");
 */
    /* ===== TODO 12：水仙花数（穷举）[计划任务] =====
     * 任务：输入一个三位数，判断它是否为水仙花数（各位立方和等于本身）。
     * 提示：逐位剥离、立方求和、与原数比较。
     * 预测：153 -> 是（1^3+5^3+3^3 == 153）
     * （自己写代码）
     */
int x=0;
int y=0;
int a = 0, b = 0, c = 0;
printf("enter a number(100-999):\n");
scanf("%d", &x);
a = x / 100;
x %= 100;
b = x / 10;
c = x % 10;
y = a * 100 + b * 10 + c;
if (y == a * a * a + b * b * b + c * c * c)
printf("yes!\n");
else
printf("no!\n");

    /* ===== TODO 13：冒泡排序 —— 已移至「数组日」，今天不做 =====
     * 原因：冒泡排序依赖数组（int a[] / a[j]），而数组排在循环之后
     *       （翁恺 P74–79，见新计划「第2周·第2天 数组与字符数组」）。
     *       为避免"没学数组就写排序"，本题已挪到数组日，届时在该日骨架补回。
     * 逻辑回顾（已讲）：外层轮数 n-1；内层相邻比较+交换（借临时变量 t）；
     *       每轮最大数沉底；可用 swapped 标志提前停（同 TODO9 标志变量套路）。
     * 预测：{5,2,9,1,3} -> {1,2,3,5,9}
     */

    return 0;
}
