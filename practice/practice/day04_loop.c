/*
 * day04_loop.c - W1-D4 循环结构（while / do-while / for）
 * 翁恺 V1 第 32–45 讲
 *
 * 方法：先预测后验证（predict-then-verify）。每个 TODO 先在 "// 预测：" 行
 * 写下你预测的输出，再解注、用 Ctrl+F5 运行核对。
 *
 * 操作方式：一次只解注一个 TODO 块（其余保持注释），不要全部解注一起跑。
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
 *   13 冒泡排序雏形：嵌套 + 交换  [计划任务]
 *
 * 间隔复习候选（延后，不在今天做，留到 D5 热身 / W1-D7 复盘交错重做）：
 *   - 整数分解（P44）      ：#5 的变体（逐位剥离）
 *   - 前 n 项和（P43）     ：#4 的变体（累加器）
 *   - 图案打印（三角形/菱形，P41 变体）：#8 的变体（嵌套）
 *   - 回文数判定           ：#5 的变体（求逆后比较）
 */

#include <stdio.h>

int main(void)
{
    /* ===== TODO 1：while 统计位数（P33） =====
     * 预测：输入 352 -> 位数 = 3 ；输入 0 -> 位数 = 1
     * 循环外 n++; x/=10; 先数掉个位，循环再数剩下的位
     */
    // {
    //     int x, n = 0;
    //     printf("enter an integer: ");
    //     scanf("%d", &x);
    //     n++;
    //     x /= 10;
    //     while (x > 0) {
    //         n++;
    //         x /= 10;
    //     }
    //     printf("digits = %d\n", n);
    // }

    /* ===== TODO 2：用 do-while 改写 TODO 1（P34） =====
     * 预测：输出同上；do-while 循环体至少执行一次（x==0 时也成立）
     */
    // {
    //     int x, n = 0;
    //     printf("enter an integer: ");
    //     scanf("%d", &x);
    //     do {
    //         n++;
    //         x /= 10;
    //     } while (x > 0);
    //     printf("digits = %d\n", n);
    // }

    /* ===== TODO 3：猜数游戏（P35） =====
     * 预测：用户反复猜，猜中（==secret）时 break 退出
     * 先用固定答案（如 57），以后可加随机数
     */
    // {
    //     int secret = 57, guess;
    //     do {
    //         printf("guess: ");
    //         scanf("%d", &guess);
    //         if (guess == secret) { printf("hit!\n"); break; }
    //         else if (guess < secret) printf("too small\n");
    //         else printf("too big\n");
    //     } while (1);
    // }

    /* ===== TODO 4：求平均数，遇 -1 结束（P36） =====
     * 预测：输入 10 20 30 -1 -> 平均数 = 20.00
     * 累加器（sum）+ 计数器（n）；n==0 时防除以零
     */
    // {
    //     int x, n = 0;
    //     double sum = 0.0;
    //     printf("enter numbers, -1 to stop: ");
    //     scanf("%d", &x);
    //     while (x != -1) {
    //         sum += x;
    //         n++;
    //         scanf("%d", &x);
    //     }
    //     if (n > 0) printf("average = %.2f\n", sum / n);
    //     else printf("no input\n");
    // }

    /* ===== TODO 5：整数求逆（P37） =====
     * 预测：输入 12345 -> 输出 54321
     * 用 %10 取末位，rev*10+末位 拼反向，/10 去掉末位
     */
    // {
    //     int x, rev = 0;
    //     printf("enter an integer: ");
    //     scanf("%d", &x);
    //     while (x > 0) {
    //         rev = rev * 10 + x % 10;
    //         x /= 10;
    //     }
    //     printf("reversed = %d\n", rev);
    // }

    /* ===== TODO 6：用 for 改写前面的程序（P38） =====
     * 预测：与对应的 while 版本输出一致
     * 挑 TODO 4（平均数）把 while 改写成 for
     */
    // {
    //     int x, n = 0;
    //     double sum = 0.0;
    //     for (printf("enter numbers, -1 to stop: "), scanf("%d", &x);
    //          x != -1;
    //          scanf("%d", &x)) {
    //         sum += x;
    //         n++;
    //     }
    //     if (n > 0) printf("average = %.2f\n", sum / n);
    // }

    /* ===== TODO 7：break 与 continue 对比（P40） =====
     * 预测：break 在第一次命中时停掉整个循环；continue 只跳过当前这一轮
     * 写两个小程序，先预测每一行输出，再验证
     */
    // {
    //     int i;
    //     printf("-- break --\n");
    //     for (i = 1; i <= 5; i++) {
    //         if (i == 3) break;
    //         printf("%d ", i);
    //     }
    //     printf("\n-- continue --\n");
    //     for (i = 1; i <= 5; i++) {
    //         if (i == 3) continue;
    //         printf("%d ", i);
    //     }
    //     printf("\n");
    // }

    /* ===== TODO 8：九九乘法表（P41，嵌套 for） =====
     * 预测：打印 9x9 下三角表
     */
    // {
    //     int i, j;
    //     for (i = 1; i <= 9; i++) {
    //         for (j = 1; j <= i; j++) {
    //             printf("%d*%d=%d ", j, i, i * j);
    //         }
    //         printf("\n");
    //     }
    // }

    /* ===== TODO 9：用标志变量从嵌套循环跳出（P42） =====
     * 预测：在 5x5 网格里找第一对 i*j==12，打印后两层都停
     * 单用 break 只能退出内层；用 found 标志配合外层条件退出两层
     */
    // {
    //     int i, j, found = 0;
    //     for (i = 1; i <= 5 && !found; i++) {
    //         for (j = 1; j <= 5; j++) {
    //             if (i * j == 12) {
    //                 printf("first pair: %d * %d = 12\n", i, j);
    //                 found = 1;
    //                 break;
    //             }
    //         }
    //     }
    // }

    /* ===== TODO 10：最大公约数（辗转相减法，P45）[计划任务] =====
     * 预测：gcd(48, 36) -> 12
     * while (a != b) { 大的减小的 }
     */
    // {
    //     int a = 48, b = 36;
    //     while (a != b) {
    //         if (a > b) a -= b;
    //         else b -= a;
    //     }
    //     printf("gcd = %d\n", a);
    // }

    /* ===== TODO 11：素数判定（穷举）[计划任务] =====
     * 预测：17 -> 是素数 ；15 -> 不是
     * 试除 2 到 sqrt(n)，命中即 break
     */
    // {
    //     int n = 17, i, isPrime = 1;
    //     if (n < 2) isPrime = 0;
    //     for (i = 2; i * i <= n; i++) {
    //         if (n % i == 0) { isPrime = 0; break; }
    //     }
    //     printf("%d is %s\n", n, isPrime ? "prime" : "not prime");
    // }

    /* ===== TODO 12：水仙花数（穷举）[计划任务] =====
     * 预测：153 -> 是（1^3+5^3+3^3 == 153）
     * 逐位剥离、立方求和、与原数比较
     */
    // {
    //     int n, m, sum = 0, d;
    //     printf("enter a 3-digit number: ");
    //     scanf("%d", &n);
    //     m = n;
    //     while (m > 0) {
    //         d = m % 10;
    //         sum += d * d * d;
    //         m /= 10;
    //     }
    //     printf("%d is %s\n", n, (sum == n) ? "narcissistic" : "not");
    // }

    /* ===== TODO 13：冒泡排序雏形（嵌套 + 交换）[计划任务] =====
     * 预测：{5,2,9,1,3} -> {1,2,3,5,9}
     * 外层轮数，内层相邻比较并交换
     */
    // {
    //     int a[5] = {5, 2, 9, 1, 3};
    //     int i, j, t;
    //     for (i = 0; i < 5 - 1; i++) {
    //         for (j = 0; j < 5 - 1 - i; j++) {
    //             if (a[j] > a[j + 1]) {
    //                 t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
    //             }
    //         }
    //     }
    //     for (i = 0; i < 5; i++) printf("%d ", a[i]);
    //     printf("\n");
    // }

    return 0;
}
