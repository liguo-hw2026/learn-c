/*
 * day06_array2.c - 第 2 周第 2 天（下）· 数组运算 / 素数 / 二维数组（翁恺 V1 第 77–79 讲）
 *   （与 day05 同属「第 2 周第 2 天｜数组与字符数组·上」，拆分两份练习）
 *
 * ⚠️ 提示骨架：参考代码用 #pragma region 折叠（见各 TODO 末尾）。
 *    VS 折叠：Ctrl+M, Ctrl+M 折叠/展开单个；Ctrl+M, Ctrl+O 折叠全部。
 *
 * 方法：先预测后验证。
 *
 * 📺 视频（B站分P，已用 API 核标题）：
 *    P77  8.2.1 数组运算        https://www.bilibili.com/video/BV1XZ4y1S7e1?p=77
 *    P78  8.2.2 数组例子：素数   https://www.bilibili.com/video/BV1XZ4y1S7e1?p=78
 *    P79  8.2.3 二维数组        https://www.bilibili.com/video/BV1XZ4y1S7e1?p=79
 *
 * TODO 清单（P77–79 范围）：
 *   1  数组求最大/最小值及下标（P77 数组运算）
 *   2  数组逆序存放（P77 数组运算变体）
 *   3  用数组存素数（筛法，P78）
 *   4  二维数组按行/列求和 + 理解行优先（P79）
 *   5  冒泡排序（补充练习，自 D4 TODO13 移入）
 *
 * 自测（收工前能讲清）：二维数组在内存里是“行优先”连续存放的——
 *       说清 m[1][0] 紧跟在 m[0][2] 之后、m[2][0] 紧跟在 m[1][2] 之后。
 *
 * 🔧 硬件相关性：
 *   - 最大/最小/逆序 🟢 高相关：找峰值、去极值、翻转序列
 *   - 素数筛 🟡 通用素养：标记数组/位图思路用于状态管理，硬件日常不直接用
 *   - 二维数组 🟢 高相关：LED 点阵 / 显示屏刷新 / ADC 多通道网格
 *   - 冒泡 🟡 通用素养：了解原理即可，真实排序用标准库 qsort
 */

#include <stdio.h>

int main(void)
{
    /* ===== TODO 1：数组求最大/最小值及下标（P77 数组运算） =====
     * 任务：找出数组最大值并打印其下标。
     * 提示：先令 max=a[0]、idx=0，从 i=1 起比较，更大就更新 max 和 idx。
     * 预测：{8,3,9,2,7,5} → max=9 at index 2
     
    int max[] = { 8,3,9,2,7,5,10,16,};
    int index = 0;
    int MAX = max[0];
    for (int i = 1; i < sizeof(max) / sizeof(max[0]); i++) {
        if (max[i] > MAX) {
            MAX = max[i];
            index = i;
        }
    }
    printf("the MAX is:max[%d]=%d", index,MAX);
    */
#pragma region TODO1 参考（展开看，写自己代码不需要）
    /*
    int a[6] = { 8, 3, 9, 2, 7, 5 };
    int max = a[0];
    int idx = 0;
    for (int i = 1; i < 6; i++) {
        if (a[i] > max) { max = a[i]; idx = i; }
    }
    printf("max=%d at index %d\n", max, idx);
    */
#pragma endregion

    /* ===== TODO 2：数组逆序存放（P77 数组运算变体） =====
     * 任务：把数组原地逆序（不借助第二个数组）。
     * 提示：首尾两两交换，循环到中点 i < n/2；配对下标 i 与 n-1-i。
     * 预测：{1,2,3,4,5} → 5 4 3 2 1
     
    int A[] = { 1,2,3,4,5 };
    int n = sizeof(A) / sizeof(A[0]);
    for (int i = 0,t=0; i <n/2; i++) {
        t = A[i];
        A[i] = A[n - 1 - i];
        A[n - 1 - i] = t;
    }
    printf("the new is:");
    for (int i = 0; i < n; i++) {
        printf("%d ",A[i]);
    }
    */
#pragma region TODO2 参考（展开看，写自己代码不需要）
    /*
    int a[5] = { 1, 2, 3, 4, 5 };
    int t = 0;
    for (int i = 0; i < 5 / 2; i++) {
        t = a[i]; a[i] = a[4 - i]; a[4 - i] = t;
    }
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    */
#pragma endregion

    /* ===== TODO 3：用数组存素数（筛法，P78） =====
     * 任务：用“标记数组”找出 2..30 之间所有素数并打印。
     * 提示：isPrime[i]=1 表示 i 疑似素数；从 i=2 起，把 i 的倍数全标 0。
     *       只需筛到 i*i<=N（同 D4 的 √x 优化思想）。
     * 预测：2 3 5 7 11 13 17 19 23 29
     * 关联：D4 你是“逐个试除到 √x”判单个数；今天用“数组批量标记”一次性生成素数表。
     
#define N 30 
    int isprime[N+1];
    for (int i=2; i <=N; i++) {
        isprime[i] = 1;
    }
    for (int i = 2; i*i <= N; i++){
        if (isprime[i] == 1) {
            for (int j = i * i; j <= N; j += i)
                isprime[j] = 0;
        }
        }
    printf("prime is:\n");
    for (int i = 2; i <= N; i++) {
        if (isprime[i] == 1)
            printf("%d ",i);
    }
    */
#pragma region TODO3 参考（展开看，写自己代码不需要）
    /*
    #define N 30
    int isPrime[N + 1];
    for (int i = 2; i <= N; i++) isPrime[i] = 1;
    for (int i = 2; i * i <= N; i++)
        if (isPrime[i])
            for (int j = i * i; j <= N; j += i) isPrime[j] = 0;
    for (int i = 2; i <= N; i++) if (isPrime[i]) printf("%d ", i);
    */
#pragma endregion

    /* ===== TODO 4：二维数组按行/列求和 + 行优先（P79） =====
     * 任务：3x3 矩阵，分别求每行之和、每列之和并打印。
     * 提示：int m[3][3]={{1,2,3},{4,5,6},{7,8,9}}; 外层 i 行、内层 j 列。
     *       内存中“行优先”：m[0][0],m[0][1],m[0][2],m[1][0]... 连续。
     * 预测：rsum = 6,15,24 ；csum = 12,15,18
    
    int m[3][3] = { {1,2,3 } ,{ 4, 5, 6 }, { 7, 8, 9 }
};
     int rsum = 0;
     int csum = 0;
     for (int i = 0; i < 3; i++) {
         for (int j = 0; j < 3; j++) {
             rsum += m[i][j];
         }
         printf("the rsum is:%d ", rsum);
         rsum = 0;
     }
     for (int j = 0; j < 3; j++) {
         for (int i = 0; i< 3; i++) {
             csum += m[i][j];
         }
         printf("the csum is:%d ", csum);
         csum = 0;
     }
     */
#pragma region TODO4 参考（展开看，写自己代码不需要）
    /*
    int m[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
    int rsum[3] = {0}, csum[3] = {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            rsum[i] += m[i][j];
            csum[j] += m[i][j];
        }
    for (int i = 0; i < 3; i++) printf("row%d sum=%d\n", i, rsum[i]);
    for (int j = 0; j < 3; j++) printf("col%d sum=%d\n", j, csum[j]);
    */
#pragma endregion

    /* ===== TODO 5：冒泡排序（补充，自 D4 TODO13 移入） =====
     * 任务：对 int a[]={5,2,9,1,3} 从小到大排序并打印。
     * 提示：外层轮数 n-1；内层相邻比较+交换（借 t）；swapped 标志提前退出。
     * 预测：1 2 3 5 9
     * 关联：swapped 标志套路 = D4 TODO9 嵌套循环跳出同源。

int a[] = { 5,2,9,1,3, };
int n = sizeof(a) / sizeof(a[0]);
int t = 0;
for (int i = 0; i < n-1; i++){
    for (int j = 0; j < n-1-i; j++) {
        if (a[j] > a[j + 1]) {
            t = a[j];
            a[j] = a[j+1];
            a[j+1] = t;
        }
    }
}
for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
}
*/
#pragma region TODO5 参考（展开看，写自己代码不需要）
    /*
    int a[5] = { 5, 2, 9, 1, 3 };
    int t = 0;
    for (int i = 0; i < 5 - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < 5 - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    */
#pragma endregion

    return 0;
}
